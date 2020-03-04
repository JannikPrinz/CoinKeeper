#pragma once
#include <qstringlistmodel.h>

#include "Views/coinkeeperview.h"
#include "DataHandler/database.h"
#include "Presenter/presenter.h"

namespace Presenter
{
    class CoinKeeperPresenter : public Presenter {
        Q_OBJECT

    public:
        CoinKeeperPresenter(std::string const& profilePath, QObject* parent = Q_NULLPTR);
        ~CoinKeeperPresenter() = default;

    private:
        void CreateConnections();
        void RefreshWindow();
        // Switch to first window, to choose a profile.
        void ChangeProfile();
        // Creates a new account
        void CreateNewAccount();
        // Changes the attribute of an existing account.
        void ChangeAccount();
        // Creates a new transaction
        void CreateNewTransaction();
        // Delete the selected transaction
        void DeleteTransaction();
        // Delete the selected account
        void DeleteAccount();
        // Opens a new Dialog-Window to manage the standing orders
        void ManageStandingOrders();
        // Opens a new Dialog-Window to manage the labels
        void ManageLabels();
        // Opens a window, where the user can change a selected transaction.
        void UpdateTransaction();

    private:
        std::shared_ptr<DataHandler::Database> database;
        std::unique_ptr<Views::CoinKeeperView> view;
        // all accounts of the open profile
        AccountVector currentAccounts;
        // transactions of the accounts of the open profile, which comply with the selection of the comboboxes represented as a
        // vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
        TransactionVector currentTransactions;
        // all labels of the current profile.
        LabelVector currentLabels;
        // number of accounts
        int32_t numberOfAccounts = -1;
        // this item represents the content of the combobox, where the user can choose a account (to display the transactions)
        QStringListModel accountList;
    };
}
