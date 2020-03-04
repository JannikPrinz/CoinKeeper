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
         * DataClasses::Transaction const& oldTransaction : the old transaction, which will be changed
         */
        void UpdateTransaction(DataClasses::Transaction const& oldTransaction);

    private:
        void CreateTransaction();
        void UpdateTransactionInDatabase(DataClasses::Transaction const& oldTransaction);
        void UpdateEnabledElements();

    private:
        std::shared_ptr<Database> database;
        AccountVector currentAccounts;
        LabelVector currentLabels;
        std::unique_ptr<Ui::AddTransactionWindow> addTransactionWindow;
    };
}
