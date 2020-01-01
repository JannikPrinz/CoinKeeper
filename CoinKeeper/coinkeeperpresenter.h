#pragma once

#include "presenter.h"
#include "coinkeeperview.h"
#include "labelmanager.h"
#include "transactionmanager.h"
#include "accountmanager.h"
#include "standingordermanager.h"
#include <qstringlistmodel.h>
#include "qdebug.h"

class CoinKeeperPresenter : public Presenter {
    Q_OBJECT

public:
    CoinKeeperPresenter(Database* base, string profilePath, QObject * parent = Q_NULLPTR);
    ~CoinKeeperPresenter();

private:
    CoinKeeperView* view;
    string currentProfile;
    // all accounts of the open profile
    vector<tuple<int, string, Value>> currentAccounts;
    // transactions of the accounts of the open profile, which comply with the selection of the comboboxes represented as a
    // vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
    vector<tuple<int, string, Value, QDate, int, int>> currentTransactions;
    // all labels of the current profile.
    vector<tuple<int, string, int>> currentLabels;
    // number of accounts
    int numberOfAccounts = -1;
    // this item represents the content of the combobox, where the user can choose a account (to display the transactions)
    QStringListModel accountList;
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
};
