#pragma once

#include "ui_addtransactionwindow.h"
#include "database.h"
#include "qmessagebox.h"

class TransactionManager : QObject
{
    Q_OBJECT

public:
    /*
     * Creates a new LabelManager with the given parameters.
     *
     * Parameters:
     * std::string profile : path of the profile
     * Database* data : adress of a database object
     */
    TransactionManager(std::shared_ptr<Database> data);
    /*
     * Starts a new transaction-creation-process. If the user inputs valid data, a new transaction
     * will be inserted into the current profile.
     */
    void CreateNewTransaction();
    /*
     * Opens a window, where the user can change values of an existing transaction.
     *
     * Parameters:
     * const int& transactionID : id of the transaction, which will be changed
     * const std::string& description : old description of transaction
     * const int& accountID : old id of the corresponding account of the transaction
     * const Value& value : old value of the transaction
     * const QDate& date : old date of the transaction
     * const int& labelID : old id of the corresponding label of the transaction
     */
    void UpdateTransaction(const int& transactionID, const std::string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID);
    ~TransactionManager();

private:
    std::shared_ptr<Database> database;
    std::vector<std::tuple<int, std::string, Value>> currentAccounts;
    std::vector<std::tuple<int, std::string, int>> currentLabels;
    Ui::AddTransactionWindow* addTransactionWindow;
    void CreateTransaction();
    void UpdateTransactionInDatabase(const int& transactionID, const int& oldAccountID, const Value& oldValue);

};
