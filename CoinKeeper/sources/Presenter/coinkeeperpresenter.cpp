#include "Presenter/coinkeeperpresenter.h"

#include <filesystem>

#include "DataHandler/accountmanager.h"
#include "DataHandler/labelmanager.h"
#include "DataHandler/standingordermanager.h"
#include "DataHandler/transactionmanager.h"

#include "qmessagebox.h"

namespace Presenter
{
    using CoinKeeperView = Views::CoinKeeperView;
    using Value = DataClasses::Value;

    CoinKeeperPresenter::CoinKeeperPresenter(std::string const& profilePath, QObject* parent) : Presenter(parent) {
        database = std::make_shared<DataHandler::Database>(profilePath);

        std::string profileName = std::filesystem::path(profilePath).filename().string();
        profileName = profileName.substr(0, profileName.length() - (DATABASE_FILETYPE.length() + 1));
        view = std::make_unique<CoinKeeperView>(profileName);
        view->show();
        CreateConnections();

        // check for executable standing orders:
        DataHandler::StandingOrderManager standingOrderManager(database, currentAccounts, currentLabels);
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
        DataHandler::AccountManager accountManager(database);
        accountManager.CreateAccount();
        RefreshWindow();
    }

    void CoinKeeperPresenter::ChangeAccount()
    {
        int row = view->GetSelectedRowTableAccounts();
        if (row >= 0) {
            int accountID;
            std::string accountName;
            Value accountValue;
            tie(accountID, accountName, accountValue) = currentAccounts[row];
            DataHandler::AccountManager accountManager(database);
            accountManager.ChangeAccount(accountID, accountName, accountValue);
            numberOfAccounts = -1;                                              // force refresh of account combobox
            RefreshWindow();
        }
    }

    void CoinKeeperPresenter::CreateNewTransaction()
    {
        DataHandler::TransactionManager transactionCreator(database);
        transactionCreator.CreateNewTransaction();
        RefreshWindow();
    }

    void CoinKeeperPresenter::DeleteTransaction()
    {
        int row = view->GetSelectedRowTableMonthOverview();
        if (row < 0) {
            return;
        }

        auto const& transaction = currentTransactions[row];
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);

        bool deleteConnectedTransaction = false;
        if (transaction.ConnectedTransactionId.has_value()) {
            msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_CONNECTED_TRANSACTION));

            switch (msg.exec()) {
            case QMessageBox::Yes:
                deleteConnectedTransaction = true;
                break;
            case QMessageBox::No:
                deleteConnectedTransaction = false;
                break;
            case QMessageBox::Abort:
            default:
                return;
            }
        }

        bool undoAccountValueChange = false;
        msg.setText(QString::fromStdString(TEXT_QUESTION_MODIFY_ACCOUNT_ON_TRANSACTION_DELETION));

        switch (msg.exec()) {
        case QMessageBox::Yes:
            undoAccountValueChange = true;
            break;
        case QMessageBox::No:
            undoAccountValueChange = false;
            break;
        case QMessageBox::Abort:
        default:
            return;
        }

        if (transaction.ConnectedTransactionId.has_value()) {
            database->UpdateConnectedTransaction(transaction.TransactionId, std::nullopt);
            database->UpdateConnectedTransaction(transaction.ConnectedTransactionId.value(), std::nullopt);
        }

        database->DeleteTransaction(transaction.TransactionId, undoAccountValueChange);

        if (deleteConnectedTransaction) {
            database->DeleteTransaction(transaction.ConnectedTransactionId.value(), undoAccountValueChange);
        }

        RefreshWindow();
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
                database->DeleteAccount(std::get<0>(account));
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
        DataHandler::StandingOrderManager standingOrderManager(database, currentAccounts, currentLabels);
        standingOrderManager.ManageStandingOrders();
        RefreshWindow();
    }

    void CoinKeeperPresenter::ManageLabels()
    {
        DataHandler::LabelManager labelManager(database);
        labelManager.ManageLabels();
        RefreshWindow();
    }

    void CoinKeeperPresenter::UpdateTransaction()
    {
        int row = view->GetSelectedRowTableMonthOverview();
        if (row >= 0) {
            DataHandler::TransactionManager transactionCreator(database);
            transactionCreator.UpdateTransaction(currentTransactions[row]);
            RefreshWindow();
        }
    }

    void CoinKeeperPresenter::RefreshWindow()
    {
        // get all accounts:
        currentAccounts = database->GetAccounts();

        // update list of accounts in the combobox if needed:
        if (numberOfAccounts != static_cast<int32_t>(currentAccounts.size())) {
            QStringList items;
            items.insert(0, QString::fromStdString(TEXT_ALL_ACCOUNTS));

            for (size_t i = 1; i <= currentAccounts.size(); ++i) {
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
            currentTransactions = database->GetTransactions(month, year);
        }
        else {
            currentTransactions = database->GetTransactions(month, year, std::get<0>(currentAccounts[account - 1]));
        }

        // sort transactions:
        std::sort(currentTransactions.begin(), currentTransactions.end(), [](auto const& el1, auto const& el2) {
            return el1.Date.toJulianDay() < el2.Date.toJulianDay();
        });

        // combine transaction and label information for 'nice' representation:
        currentLabels = database->GetLabels();
        std::vector<std::tuple<QDate, std::string, int, std::string, Value>> transactions;    // date, name of label, color of label, description of transaction, value of transaction

        for (size_t i = 0; i < currentTransactions.size(); i++) {
            auto const& transaction = currentTransactions[i];
            auto it = find_if(currentLabels.begin(), currentLabels.end(), [labelID = transaction.LabelId](std::tuple<int, std::string, int> label) {
                return std::get<0>(label) == labelID;
            });

            if (it == currentLabels.end()) {    // labelID not found. Should not happen. Use default-label.
                std::tuple<int, std::string, int> defaultLabel = currentLabels[0];
                transactions.push_back(make_tuple(transaction.Date, std::get<1>(defaultLabel), std::get<2>(defaultLabel), transaction.Description, transaction.TransactionValue));
            }
            else {
                transactions.push_back(make_tuple(transaction.Date, std::get<1>(*it), std::get<2>(*it), transaction.Description, transaction.TransactionValue));
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
}
