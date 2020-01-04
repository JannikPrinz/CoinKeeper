#include "coinkeeperpresenter.h"

#include "accountmanager.h"
#include "labelmanager.h"
#include "standingordermanager.h"
#include "transactionmanager.h"

CoinKeeperPresenter::CoinKeeperPresenter(string const& profilePath, QObject * parent) : Presenter(parent) {
    currentProfile = profilePath;
    database = std::make_shared<Database>(currentProfile);
    //qDebug("Übergebener string: %s", profilePath.c_str());
    view = std::make_unique<CoinKeeperView>();
    view->show();
    CreateConnections();

    // check for executable standing orders:
    StandingOrderManager standingOrderManager(database);
    standingOrderManager.ExecuteOrders();
    RefreshWindow();
}

void CoinKeeperPresenter::CreateConnections()
{
    connect(view.get(), &CoinKeeperView::ButtonChangeProfileClicked, this, [this] { ChangeProfile(); });
    connect(view.get(), &CoinKeeperView::ButtonCreateNewAccountClicked, this, [this] { CreateNewAccount(); });
    connect(view.get(), &CoinKeeperView::ButtonChangeAccountClicked, this, [this] { ChangeAccount(); });
    connect(view.get(), &CoinKeeperView::ButtonAddTransactionClicked, this, [this] { CreateNewTransaction(); });
    connect(view.get(), &CoinKeeperView::ButtonDeleteTransactionClicked, this, [this] { DeleteTransaction(); });
    connect(view.get(), &CoinKeeperView::ButtonDeleteAccountClicked, this, [this] { DeleteAccount(); });
    connect(view.get(), &CoinKeeperView::ButtonManageStandingOrdersClicked, this, [this] { ManageStandingOrders(); });
    connect(view.get(), &CoinKeeperView::ButtonManageLabelsClicked, this, [this] { ManageLabels(); });
    connect(view.get(), &CoinKeeperView::ButtonUpdateTransactionClicked, this, [this] { UpdateTransaction(); });
    connect(view.get(), &CoinKeeperView::SelectionMonthYearAccountChanged, this, [this] { RefreshWindow(); });
}

void CoinKeeperPresenter::CreateNewAccount()
{
    AccountManager accountManager(database);
    accountManager.CreateAccount();
    RefreshWindow();
}

void CoinKeeperPresenter::ChangeAccount()
{
    int row = view->GetSelectedRowTableAccounts();
    if (row >= 0) {
        int accountID;
        string accountName;
        Value accountValue;
        tie(accountID, accountName, accountValue) = currentAccounts[row];
        AccountManager accountManager(database);
        accountManager.ChangeAccount(accountID, accountName, accountValue);
        RefreshWindow();
    }
}

void CoinKeeperPresenter::CreateNewTransaction()
{
    TransactionManager transactionCreator(database);
    transactionCreator.CreateNewTransaction();
    RefreshWindow();
}

void CoinKeeperPresenter::DeleteTransaction()
{
    int row = view->GetSelectedRowTableMonthOverview();
    if (row >= 0) {
        std::tuple<int, std::string, Value, QDate, int, int> transaction = currentTransactions[row];
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
        msg.setText(QString::fromStdString(TEXT_QUESTION_MODIFY_ACCOUNT_AT_TRANSACTION_DELETION));
        switch (msg.exec()) {
        case QMessageBox::Yes:
            database->DeleteTransaction(currentProfile, std::get<0>(transaction), true, std::get<4>(transaction), std::get<2>(transaction) * -1);
            break;
        case QMessageBox::No:
            database->DeleteTransaction(currentProfile, std::get<0>(transaction), false);
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
    if (row >= 0) {
        std::tuple<int, std::string, Value> account = currentAccounts[row];
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
        msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_ACCOUNT_AND_ALL_CORRESPONDING_TRANSACTIONS_AND_STANDING_ORDERS));
        switch (msg.exec()) {
        case QMessageBox::Yes:
            database->DeleteAccount(currentProfile, std::get<0>(account));
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
    StandingOrderManager standingOrderManager(database);
    standingOrderManager.ManageStandingOrders(&currentAccounts, &currentLabels);
    RefreshWindow();
}

void CoinKeeperPresenter::ManageLabels()
{
    LabelManager labelManager(database);
    labelManager.ManageLabels();
    RefreshWindow();
}

void CoinKeeperPresenter::UpdateTransaction()
{
    int row = view->GetSelectedRowTableMonthOverview();
    if (row >= 0) {
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
    currentAccounts = database->GetAccounts(currentProfile);

    // update list of accounts in the combobox if needed:
    if (numberOfAccounts != static_cast<int32_t>(currentAccounts.size())) {
        QStringList items;
        items.insert(0, QString::fromStdString(TEXT_ALL_ACCOUNTS));
        //acc.setRowCount(currentAccounts.size() + 1);
        //acc.setItem(0, &QStandardItem(TEXT_ALL_ACCOUNTS));
        for (size_t i = 1; i <= currentAccounts.size(); i++)
        {
            items.insert(static_cast<int>(i), QString::fromStdString(std::get<1>(currentAccounts[i - 1])));
        }
        accountList.setStringList(items);
        numberOfAccounts = static_cast<int32_t>(currentAccounts.size());
        view->setComboboxAccountValues(&accountList);
    }

    // read current selected values:
    int month = view->GetSelectedMonth();
    int year = view->GetSelectedYear();
    int account = view->GetSelectedAccount();

    // get and set all wanted transactions:
    if (account == 0) {       // all accounts
        currentTransactions = database->GetTransactions(currentProfile, month, year);
    } else {
        currentTransactions = database->GetTransactions(currentProfile, month, year, std::get<0>(currentAccounts[account - 1]));
    }

    // combine transaction and label information for 'nice' representation:
    currentLabels = database->GetLabels(currentProfile);
    vector<tuple<QDate, string, int, string, Value>> transactions;    // date, name of label, color of label, description of transaction, value of transaction
    int transactionID, accountID, labelID;
    string description;
    Value value;
    QDate date;
    for (size_t i = 0; i < currentTransactions.size(); i++) {
        tie(transactionID, description, value, date, accountID, labelID) = currentTransactions[i];
        std::vector<tuple<int, string, int>>::iterator it = find_if(currentLabels.begin(), currentLabels.end(), [labelID](tuple<int, string, int> label) { return get<0>(label) == labelID; });
        if (it == currentLabels.end()) {    // labelID not found. Should not happen. Use default-label.
            tuple<int, string, int> defaultLabel = currentLabels[0];
            transactions.push_back(make_tuple(date, get<1>(defaultLabel), get<2>(defaultLabel), description, value));
        } else {
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
