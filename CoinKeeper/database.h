#pragma once

#include "constants.h"
#include "qdatetime.h"

using CallbackFunction = int(*)(void*, int, char**, char**);

class Database
{
public:
    Database(std::string const& profile);
    ~Database() = default;
    static void ChangeProfileName(std::filesystem::path const& oldPath, std::string const& newProfileName);
    /*
     * This method creates a new account with the given name and balance.
     *
     * Parameters:
     * std::string const& name : name of the new account
     * Value const& balance    : start-balance of the new account
     */
    void CreateNewAccount(std::string const& name, Value const& balance);
    /*
     * This method creates a new label in the given profile with the given name and color.
     *
     * Parameters:
     * std::string const& name : name of the new label
     * int color               : color of the new label
     */
    void CreateNewLabel(std::string const& name, int color);
    /*
     * This method creates a new database for the new profile.
     *
     * Parameters:
     * std::string const& fileName : the filename of the new db (exlusive .ckdb)
     */
    static void CreateNewProfile(std::string const& fileName);
    /*
     * This method creates a new standing order at the given profile with the given parameters.
     *
     * Parameters:
     * std::string& description : description of the transactions
     * int accountID            : ID of the account
     * Value const& value       : value of the inserted transactions
     * QDate const& date        : date of the next execution of the order
     * int labelID              : id of the label, which all inserted transactions will get
     * int orderType            : indentifier of the type of the standing order
     */
    void CreateNewStandingOrder(std::string const& description, int accountID, Value const& value, QDate const& date, int labelID, int orderType);
    /*
     * This method creates a new transaction at the given profile / account with the given description, value, labelID and date of the transaction.
     * Also the value of the account gets updated.
     *
     * Parameters:
     * std::string const& description : description of the transaction
     * int account                    : ID of the account
     * Value const& value             : value of the transaction
     * QDate const& date              : date of the transaction
     * int labelID                    : id of the label
     */
    void CreateNewTransaction(std::string const& description, int account, Value const& value, QDate const& date, int labelID);
    /*
     * This method deletes the given account and all corresponding transactions.
     *
     * Parameters:
     * int accountID : id of the account, which gets deleted
     */
    void DeleteAccount(int accountID);
    /*
     * This method deletes the specified label. All references to this label are changed to the standard label (labelID = 1).
     *
     * Parameters:
     * std::string const& profile : path of the profile
     * int labelID                : id of the label, which gets deleted
     */
    void DeleteLabel(int labelID);
    static void DeleteProfile(std::filesystem::path const& profilePath);
    /*
     * This method deletes the specified standing order.
     *
     * Parameters:
     * int orderID : id of the standing order, which gets deleted
     */
    void DeleteStandingOrder(int orderID);
    /*
     * This method deletes the given transaction. The value of the account gets changed if wanted.
     *
     * Parameters:
     * int transactionID       : id of the transaction, which gets deleted
     * bool changeAccountValue : if true, the value of the given account gets changed by the given value
     * int accountID           : id of the account, where the given value gets added if wanted (default = 0)
     * Value const& value      : value which gets added to the given account if wanted (default = 0)
     */
    void DeleteTransaction(int transactionID, bool changeAccountValue, int accountID = 0, Value const& value = Value(0));
    /*
     * This method returns all accounts of the given profile
     *
     * Returns: vector of tuples with an integer of the unique identifier of the account and the name and value of the account
     */
    [[nodiscard]]
    AccountVector GetAccounts();
    /*
     * This method returns the value of an given account.
     *
     * Parameters:
     * int accountID : id of an account
     *
     * Returns: the value of the given account
     */
    [[nodiscard]]
    Value GetAccountValue(int accountID);
    /*
     * This method returns all standing orders, which are saved in the given profile.
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all standing orders.
     */
    [[nodiscard]]
    StandingOrderVector GetAllStandingOrders();
    /*
     * This method searches for database-files (profiles) in the current working directory.
     *
     * Returns: vector of profiles (filenames without '.ckdb' together with the whole path in a pair)
     */
    [[nodiscard]]
    static ProfileVector GetDatabaseList();
    /*
     * This method returns all standing orders, which are saved in the given profile and are ready for execution.
     * An standing order is ready for execution, if set date of the next execution is less then or equal the given date.
     *
     * Parameters:
     * int date : maximum date, which is set as next execution date of the standing order
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all matching standing orders.
     */
    [[nodiscard]]
    StandingOrderVector GetExecutableStandingOrders(int date);
    /*
     * This method returns all labels, which are saved in the given profile.
     */
    [[nodiscard]]
    LabelVector GetLabels();
    /*
     * This method returns transactions of the given profile with the given restrictions, but with no account-restriction.
     *
     * Parameters:
     * int month : month of the wanted transactions
     * int year  : year of the wanted transactions
     *
     * Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
     */
    [[nodiscard]]
    TransactionVector GetTransactions(int month, int year);
    /*
     * This method returns transactions of the given profile with the given restrictions.
     *
     * Parameters:
     * int month     : month of the wanted transactions
     * int year      : year of the wanted transactions
     * int accountID : id of an account. Only transactions of that account will be returned
     *
     * Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
     */
    [[nodiscard]]
    TransactionVector GetTransactions(int month, int year, int accountID);
    /*
     * This method changes the specified account with the given parameters.
     *
     * Parameters:
     * int accountID                  : id of the account, which will be changed
     * std::string const& accountName : new name of the account
     * Value const& value             : new value of the account
     */
    void UpdateAccount(int accountID, std::string const& accountName, Value const& value);
    /*
     * This method adds the given value to the given account.
     *
     * Parameters:
     * int accountID      : id of the account on which the value-change is applied
     * Value const& value : value, which gets added to the current value of the selected account
     */
    void UpdateAccountValue(int accountID, Value const& value);
    /*
     * This method changes the name and the color of the specified label with given parameters
     *
     * Parameters:
     * int labelID             : id of the label, which gets changed
     * std::string const& name : new name of the label
     * int color               : new color of the label
     */
    void UpdateLabel(int labelID, std::string const& name, int color);
    /*
     * This method updates an existing standing order at the given profile with the given parameters.
     *
     * Parameters:
     * int orderID                    : id of the standing order
     * std::string const& description : description of the transactions of the standing order
     * int accountID                  : ID of the account
     * Value const& value             : value of the transactions
     * QDate const& nextDate          : date of the next inserted transaction
     * int labelID                    : id of the label
     * int orderType                  : type of the standing order
     */
    void UpdateStandingOrder(int orderID, std::string const& description, int accountID, Value const& value, QDate const& nextDate, int labelID, int orderType);
    /*
     * This method sets the next execution date of the specified standing order to the given date.
     *
     * Parameters:
     * int orderID : id of the standing order, which next date will be changed
     * int date    : date, which will be the new 'next date' of the standing order
     */
    void UpdateStandingOrderDate(int orderID, int date);
    /*
     * This method updates an existing transaction at the given profile with the given parameters.
     * Tthe value of the account will not be changed within this method!
     *
     * Parameters:
     * int transactionID              : id of the transaction
     * std::string const& description : description of the transaction
     * int accountID                  : ID of the account
     * Value const& value             : value of the transaction
     * QDate const& date              : date of the transaction
     * int const& labelID             : id of the label
     */
    void UpdateTransaction(int transactionID, std::string const& description, int accountID, Value const& value, QDate const& date, int labelID);

private:
    void InitializeCallbackFunctions();
    void ExecuteSQLStatementWithoutReturnValue(std::stringstream const& ss) const;
    void ExecuteSQLStatementWithReturnValue(std::stringstream const& ss, CallbackFunction callback, void* data) const;

private:
    std::string openProfile;
    CallbackFunction CBF_GetAccountValue;
    CallbackFunction CBF_GetTransactions;
    CallbackFunction CBF_GetAccounts;
    CallbackFunction CBF_GetStandingOrders;
    CallbackFunction CBF_GetLabels;
};
