#include "coinkeeperpresenter.h"

CoinKeeperPresenter::CoinKeeperPresenter(Database* base, string profilePath, QObject * parent) : Presenter(base, parent) {
    currentProfile = profilePath;
    //qDebug("Übergebener string: %s", profilePath.c_str());
    view = new CoinKeeperView();
    view->show();
    CreateConnections();
    // check for executable standing orders:
    StandingOrderManager standingOrderManager(currentProfile.c_str(), database);
    standingOrderManager.ExecuteOrders();
    RefreshWindow();
}

void CoinKeeperPresenter::CreateConnections()
{
    connect(view, &CoinKeeperView::ButtonChangeProfileClicked, this, [=] { ChangeProfile(); });
    connect(view, &CoinKeeperView::ButtonCreateNewAccountClicked, this, [=] { CreateNewAccount(); });
    connect(view, &CoinKeeperView::ButtonChangeAccountClicked, this, [=] { ChangeAccount(); });
    connect(view, &CoinKeeperView::ButtonAddTransactionClicked, this, [=] { CreateNewTransaction(); });
    connect(view, &CoinKeeperView::ButtonDeleteTransactionClicked, this, [=] { DeleteTransaction(); });
    connect(view, &CoinKeeperView::ButtonDeleteAccountClicked, this, [=] { DeleteAccount(); });
    connect(view, &CoinKeeperView::ButtonManageStandingOrdersClicked, this, [=] { ManageStandingOrders(); });
    connect(view, &CoinKeeperView::ButtonManageLabelsClicked, this, [=] { ManageLabels(); });
    connect(view, &CoinKeeperView::ButtonUpdateTransactionClicked, this, [=] { UpdateTransaction(); });
    connect(view, &CoinKeeperView::SelectionMonthYearAccountChanged, this, [=] { RefreshWindow(); });
}

void CoinKeeperPresenter::CreateNewAccount()
{
    AccountManager accountManager(currentProfile, database);
    accountManager.CreateAccount();
    RefreshWindow();
}

void CoinKeeperPresenter::ChangeAccount()
{
    int row = view->GetSelectedRowTableAccounts();
    if (row >= 0)
    {
        int accountID;
        string accountName;
        Value accountValue;
        tie(accountID, accountName, accountValue) = currentAccounts[row];
        AccountManager accountManager(currentProfile, database);
        accountManager.ChangeAccount(accountID, accountName, accountValue);
        RefreshWindow();
    }
}

void CoinKeeperPresenter::CreateNewTransaction()
{
    TransactionManager transactionCreator(currentProfile, database);
    transactionCreator.CreateNewTransaction();
    RefreshWindow();
}

void CoinKeeperPresenter::DeleteTransaction()
{
    int row = view->GetSelectedRowTableMonthOverview();
    if (row >= 0)
    {
        std::tuple<int, std::string, Value, QDate, int, int> transaction = currentTransactions[row];
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
        msg.setText(TEXT_QUESTION_MODIFY_ACCOUNT_AT_TRANSACTION_DELETION);
        switch (msg.exec())
        {
        case QMessageBox::Yes:
            database->DeleteTransaction(currentProfile.c_str(), std::get<0>(transaction), true, std::get<4>(transaction), std::get<2>(transaction) * -1);
            break;
        case QMessageBox::No:
            database->DeleteTransaction(currentProfile.c_str(), std::get<0>(transaction), false);
            break;
        case QMessageBox::Abort:
            break;
        default:
            break;
        }
        RefreshWindow();
    }
}

void CoinKeeperPresenter::DeleteAccount()
{
    int row = view->GetSelectedRowTableAccounts();
    if (row >= 0)
    {
        std::tuple<int, std::string, Value> account = currentAccounts[row];
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
        msg.setText(TEXT_QUESTION_DELETE_ACCOUNT_AND_ALL_CORRESPONDING_TRANSACTIONS_AND_STANDING_ORDERS);
        switch (msg.exec())
        {
        case QMessageBox::Yes:
            database->DeleteAccount(currentProfile.c_str(), std::get<0>(account));
            break;
        case QMessageBox::No:
            break;
        case QMessageBox::Abort:
            break;
        default:
            break;
        }
        RefreshWindow();
    }
}

void CoinKeeperPresenter::ManageStandingOrders()
{
    StandingOrderManager standingOrderManager(currentProfile, database);
    standingOrderManager.ManageStandingOrders(&currentAccounts, &currentLabels);
    RefreshWindow();
}

void CoinKeeperPresenter::ManageLabels()
{
    LabelManager labelManager(currentProfile, database);
    labelManager.ManageLabels();
    RefreshWindow();
}

void CoinKeeperPresenter::UpdateTransaction()
{
    int row = view->GetSelectedRowTableMonthOverview();
    if (row >= 0)
    {
        int transactionID, accountID, labelID;
        QDate date;
        string description;
        Value value;
        tie(transactionID, description, value, date, accountID, labelID) = currentTransactions[row];
        TransactionManager transactionCreator(currentProfile, database);
        transactionCreator.UpdateTransaction(transactionID, description, accountID, value, date, labelID);
        RefreshWindow();
    }
}

void CoinKeeperPresenter::RefreshWindow()
{
    // get all accounts:
    currentAccounts = database->GetAccounts(currentProfile.c_str());
    // update list of accounts in the combobox if needed:
    if (numberOfAccounts != currentAccounts.size())
    {
        QStringList items;
        items.insert(0, QString(TEXT_ALL_ACCOUNTS));
        //acc.setRowCount(currentAccounts.size() + 1);
        //acc.setItem(0, &QStandardItem(TEXT_ALL_ACCOUNTS));
        for (int i = 1; i <= currentAccounts.size(); i++)
        {
            items.insert(i, QString::fromStdString(std::get<1>(currentAccounts[i - 1])));
        }
        accountList.setStringList(items);
        numberOfAccounts = static_cast<int32_t>(currentAccounts.size());
        view->setComboboxAccountValues(&accountList);
    }
    // read current selected values:
    tuple<int, int, int> ind = view->GetComboboxContent();
    int month, year, account;
    tie(month, year, account) = ind;
    // get and set all wanted transactions:
    if (account == 0)        // all accounts
    {
        currentTransactions = database->GetTransactions(currentProfile.c_str(), month, year);
    }
    else
    {
        currentTransactions = database->GetTransactions(currentProfile.c_str(), month, year, std::get<0>(currentAccounts[account - 1]));
    }
    // combine transaction and label information for 'nice' representation:
    currentLabels = database->GetLabels(currentProfile.c_str());
    vector<tuple<QDate, string, int, string, Value>> transactions;    // date, name of label, color of label, description of transaction, value of transaction
    int transactionID, accountID, labelID;
    string description;
    Value value;
    QDate date;
    for (int i = 0; i < currentTransactions.size(); i++)
    {
        tie(transactionID, description, value, date, accountID, labelID) = currentTransactions[i];
        std::vector<tuple<int, string, int>>::iterator it = find_if(currentLabels.begin(), currentLabels.end(), [labelID](tuple<int, string, int> label) { return get<0>(label) == labelID; });
        if (it == currentLabels.end())    // labelID not found. Should not happen. Use default-label.
        {
            tuple<int, string, int> defaultLabel = currentLabels[0];
            transactions.push_back(make_tuple(date, get<1>(defaultLabel), get<2>(defaultLabel), description, value));
        }
        else
        {
            transactions.push_back(make_tuple(date, get<1>(*it), get<2>(*it), description, value));
            //qDebug("Transaction %d: labelID: %d, labelName: %s, color: %d\n", i, get<0>(*it), get<1>(*it), get<2>(*it));
        }
    }
    view->FillAccountData(currentAccounts);
    view->FillTransactionData(transactions);
}

void CoinKeeperPresenter::ChangeProfile()
{
    emit ChangePresenter(Presenters::ProfileChooser);
}

CoinKeeperPresenter::~CoinKeeperPresenter() {
    view->~CoinKeeperView();
}
