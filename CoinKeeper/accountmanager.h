#pragma once

#include "database.h"

class AccountManager : QObject
{
    Q_OBJECT

public:
    /*
     * Constructor of the class which manages the accounts of a profile.
     *
     * Parameters:
     * string const& profile : path of the current profile
     * Database* data        : Database-object to change the stored data of the given profile
     */
    AccountManager(string const& profile, Database* data);
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
     * string const& oldName : old name of the account
     * Value const& oldValue : old value of the account
     */
    void ChangeAccount(int accountID, string const& oldName, Value const& oldValue);

private:
    [[nodiscard]]
    bool CreateNewAccount(QString const& accountName, int vk, int nk, bool negative);
    [[nodiscard]]
    bool ChangeExistingAccount(int accountID, QString const& accountName, int vk, int nk, bool negative);

private:
    string currentProfile;
    Database* database;
};
