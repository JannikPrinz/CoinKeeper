#pragma once

#include "ui_addtransactionwindow.h"
#include "DataHandler/database.h"

namespace DataHandler
{
    class TransactionManager : QObject
    {
        Q_OBJECT

    public:
        /*
         * Creates a new LabelManager with the given parameters.
         *
         * Parameters:
         * std::shared_ptr<Database> data : the current database
         */
        TransactionManager(std::shared_ptr<Database> data);
        ~TransactionManager() = default;
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

    private:
        void CreateTransaction();
        void UpdateTransactionInDatabase(const int& transactionID, const int& oldAccountID, const Value& oldValue);

    private:
        std::shared_ptr<Database> database;
        AccountVector currentAccounts;
        LabelVector currentLabels;
        std::unique_ptr<Ui::AddTransactionWindow> addTransactionWindow;
    };
}
