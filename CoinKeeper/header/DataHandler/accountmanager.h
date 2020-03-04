#pragma once

#include <qobject.h>

#include "DataHandler/database.h"

namespace DataHandler
{
    class AccountManager : QObject
    {
        Q_OBJECT

    public:
        /*
         * Constructor of the class which manages the accounts of a profile.
         *
         * Parameters:
         * std::string const& profile : path of the current profile
         * Database* data        : Database-object to change the stored data of the given profile
         */
        AccountManager(std::shared_ptr<Database> data);
        ~AccountManager() = default;
        /*
         * This method starts a new account creation.
         */
        void CreateAccount();
        /*
         * This method gives the user the ability, to change an existing account.
         *
         * Parameters:
         * int accountID  : id of the account, which will be changed
         * std::string const& oldName : old name of the account
         * Value const& oldValue : old value of the account
         */
        void ChangeAccount(int accountID, std::string const& oldName, DataClasses::Value const& oldValue);

    private:
        [[nodiscard]]
        bool CreateNewAccount(QString const& accountName, int vk, int nk, bool negative);
        [[nodiscard]]
        bool ChangeExistingAccount(int accountID, QString const& accountName, int vk, int nk, bool negative);

    private:
        std::shared_ptr<Database> database;
    };
}
