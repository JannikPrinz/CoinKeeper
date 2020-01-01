#pragma once
#ifndef ACCOUNTMANAGER_HPP
#define ACCOUNTMANAGER_HPP

#include "database.h"
#include "ui_addaccountwindow.h"
#include "qmessagebox.h"

class AccountManager : QObject
{
    Q_OBJECT

public:
    /*
    * This method gives the user the ability, to change an existing account.
    *
    * Parameters:
    * const string& profile    : path of the current profile
    * Database* data        : Database-object to change the stored data of the given profile
    */
    AccountManager(const string& profile, Database* data);
    ~AccountManager();
    /*
     * This method starts a new account creation.
     */
    void CreateAccount();
    /*
     * This method gives the user the ability, to change an existing account.
     *
     * Parameters:
     * const int& accountID        : id of the account, which will be changed
     * const string& oldName    : old name of the account
     * const Value& oldValue    : old value of the account
     */
    void ChangeAccount(const int& accountID, const string& oldName, const Value& oldValue);

private:
    string currentProfile;
    Database* database;
    Ui::AddAccountWindow* addAccountWindow;
    void CreateNewAccount();
    void ChangeExistingAccount(const int& accountID);
};

#endif // !ACCOUNTMANAGER_HPP
