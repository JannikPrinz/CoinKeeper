#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite-amalgamation-3120100\sqlite3.h"
#include <Windows.h>
#include "constants.h"
#include "qdebug.h"
#include "qdatetime.h"
using namespace std;

// ToDo: Delete this:
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++) {
        qDebug("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

class Database
{
public:
    Database();
    /*
        This method creates a new database for the new profile.
        char* fileName : the filename of the new db (exlusive .ckdb)
    */
    void CreateNewProfile(const char* fileName);
    // This method searches for database-files (profiles) in the given folders.
    // Returns: list of profiles (filenames without '.ckdb' alternating with whole path)
    list<string> GetDatabaseList();
    // This method returns all accounts of the given profile
    // const char* profile : path of the profile
    // Returns: vector of tuples with an integer of the unique identifier of the account and the name and value of the account
    vector<tuple<int, string, Value>> GetAccounts(const char* profile);
    // This method returns transactions of the given profile with the given restrictions, but with no account-restriction.
    // const char* profile : path of the profile
    // int month : month of the wanted transactions
    // int year : year of the wanted transactions
    // Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
    vector<tuple<int, string, Value, QDate, int, int>> GetTransactions(const char* profile, int month, int year);
    // This method returns transactions of the given profile with the given restrictions.
    // const char* profile : path of the profile
    // int month : month of the wanted transactions
    // int year : year of the wanted transactions
    // int accountID : id of an account. Only transactions of that account will be returned
    // Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
    vector<tuple<int, string, Value, QDate, int, int>> GetTransactions(const char* profile, int month, int year, int accountID);
    /*
     * This method returns all standing orders, which are saved in the given profile.
     *
     * Parameters:
     * const char* profile : path of the profile
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all standing orders.
     */
    vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> GetAllStandingOrders(const char* profile);
    /*
     * This method returns all standing orders, which are saved in the given profile and are ready for execution.
     * An standing order is ready for execution, if set date of the next execution is less then or equal the given date.
     *
     * Parameters:
     * const char* profile    : path of the profile
     * const int& date        : maximum date, which is set as next execution date of the standing order
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all matching standing orders.
     */
    vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> GetExecutableStandingOrders(const char* profile, const int& date);
    /*
     * This method returns all labels, which are saved in the given profile.
     *
     * Parameters:
     * const char* profile : path of the profile
     */
    vector<tuple<int, string, int>> GetLabels(const char* profile);
    // This method creates a new account at the given profile with the given name and balance.
    // const char* profile : path of the profile
    // string name : name of the new account
    // double balance : start-balance of the new account
    void CreateNewAccount(const char* profile, string name, Value balance);
    /*
     * This method creates a new transaction at the given profile / account with the given description, value, labelID and date of the transaction.
     * Also the value of the account gets updated.
     *
     * Parameters:
     * const char* profile            : path of the profile
     * const string& description    : description of the transaction
     * const int& account            : ID of the account
     * const Value& value            : value of the transaction
     * const QDate& date            : date of the transaction
     * const int& labelID            : id of the label
     */
    void CreateNewTransaction(const char* profile, const string& description, const int& account, const Value& value, const QDate& date, const int& labelID);
    /*
     * This method creates a new standing order at the given profile with the given parameters.
     *
     * Parameters:
     * const char* profile            : path of the profile
     * const string& description        : description of the transactions
     * const int& accountID            : ID of the account
     * const Value& value            : value of the inserted transactions
     * const QDate& date                : date of the next execution of the order
     * const int& labelID            : id of the label, which all inserted transactions will get
     * const int& orderType            : indentifier of the type of the standing order
     */
    void CreateNewStandingOrder(const char* profile, const string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID, const int& orderType);
    /*
     * This method creates a new label in the given profile with the given name and color.
     *
     * Parameters:
     * const char* profile    : path of the profile
     * string name            : name of the new label
     * int color            : color of the new label
     */
    void CreateNewLabel(const char* profile, string name, int color);
    /*
     * This method changes the name and the color of the specified label with given parameters
     *
     * Parameters:
     * const char* profile    : path of the profile
     * int labelID            : id of the label, which gets changed
     * string name            : new name of the label
     * int color            : new color of the label
     */
    void UpdateLabel(const char* profile, int labelID, string name, int color);
    /*
     * This method changes the specified account with the given parameters.
     *
     * Parameters:
     * const char* profile : path of the profile
     * const int& accountID : id of the account, which will be changed
     * const string& accountName : new name of the account
     * const Value value& : new value of the account
     */
    void UpdateAccount(const char* profile, const int& accountID, const string& accountName, const Value& value);
    /*
     * This method adds the given value to the given account.
     *
     * Parameters:
     * const char* profile : path of the profile
     * const int& accountID : id of the account on which the value-change is applied
     * const Value& value : value, which gets added to the current value of the selected account
     */
    void UpdateAccountValue(const char* profile, const int& accountID, const Value& value);
    /*
     * This method sets the next execution date of the specified standing order to the given date.
     *
     * Parameters:
     * const char* profile    : path of the profile
     * const int& orderID    : id of the standing order, which next date will be changed
     * const int& date        : date, which will be the new 'next date' of the standing order
     */
    void UpdateStandingOrderDate(const char* profile, const int& orderID, const int& date);
    /*
     * This method updates an existing standing order at the given profile with the given parameters.
     *
     * Parameters:
     * const char* profile            : path of the profile
     * const int& orderID            : id of the standing order
     * const string& description    : description of the transactions of the standing order
     * const int& accountID            : ID of the account
     * const Value& value            : value of the transactions
     * const QDate& nextDate        : date of the next inserted transaction
     * const int& labelID            : id of the label
     * const int& orderType            : type of the standing order
     */
    void UpdateStandingOrder(const char* profile, const int& orderID, const string& description, const int& accountID, const Value& value, const QDate& nextDate, const int& labelID, const int& orderType);
    /*
     * This method updates an existing transaction at the given profile with the given parameters.
     * Tthe value of the account will not be changed within this method!
     *
     * Parameters:
     * const char* profile            : path of the profile
     * const int& transactionID        : id of the transaction
     * const string& description        : description of the transaction
     * const int& accountID            : ID of the account
     * const Value& value            : value of the transaction
     * const QDate& date                : date of the transaction
     * const int& labelID            : id of the label
     */
    void UpdateTransaction(const char* profile, const int& transactionID, const string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID);
    /*
     * This method deletes the given transaction. The value of the account gets changed if wanted.
     *
     * Parameters:
     * const char* profile                : path of the profile
     * const int& transactionID            : id of the transaction, which gets deleted
     * const bool& changeAccountValue    : if true, the value of the given account gets changed by the given value
     * const int& accountID                : id of the account, where the given value gets added if wanted (default = 0)
     * const Value& value                : value which gets added to the given account if wanted (default = 0)
     */
    void DeleteTransaction(const char* profile, const int& transactionID, const bool& changeAccountValue, const int& accountID = 0, const Value& value = Value(0));
    /*
     * This method deletes the specified standing order.
     *
     * Parameters:
     * const char* profile    : path of the profile
     * const int& orderID    : id of the standing order, which gets deleted
     */
    void DeleteStandingOrder(const char* profile, const int& orderID);
    /*
     * This method deletes the specified label. All references to this label are changed to the standard label (labelID = 1).
     *
     * Parameters:
     * const char* profile    : path of the profile
     * const int& labelID    : id of the label, which gets deleted
     */
    void DeleteLabel(const char* profile, const int& labelID);
    /*
     * This method deletes the given account and all corresponding transactions.
     *
     * Parameters:
     * const char* profile : path of the profile
     * int accountID : id of the account, which gets deleted
     */
    void DeleteAccount(const char* profile, const int& accountID);
    ~Database();

private:
    // Return the path of the executable with '\*' at the end
    LPWSTR ExePath();
    // Converts a string to a LPWSTR
    LPWSTR StringToLPWSTR(const std::string& s);
    // Converts a LPWSTR to a string
    string LPWSTRToString(LPWSTR l);
    // extracts filenames of the files from a given list and a given file-type. This strings and original strings (incl. path)
    // get returned. Example: <abc, ..\abc.ckdb, xyz, ..\xyz.ckdb>
    // list<string> rawList : list of strings
    // path : path of the files
    // string type : type of files, which filenames get returned. Default: "ckdb" (DATABASE_FILETYPE)
    list<string> GetFilenames(list<string> rawList, string path, string type = DATABASE_FILETYPE);
};

static vector<tuple<int, string, Value>> tempAccounts;
static int ProcessAccountInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 3 < argc)
    {
        if (string(azColName[x]) == ACCOUNTS_ID && string(azColName[x + 1]) == ACCOUNTS_NAME && string(azColName[x + 2]) == ACCOUNTS_VK && string(azColName[x + 3]) == ACCOUNTS_NK)
        {
            tempAccounts.push_back(make_tuple(atoi(argv[x]), string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3]))));
        }
        x += 4;
    }
    return 0;
}

static vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> tempOrders;
static int ProcessOrderInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 7 < argc)
    {
        if (string(azColName[x]) == STANDING_ORDER_ID && string(azColName[x + 1]) == ACCOUNTS_ID && string(azColName[x + 2]) == LABEL_ID && string(azColName[x + 3]) == STANDING_ORDER_VK && string(azColName[x + 4]) == STANDING_ORDER_NK && string(azColName[x + 5]) == STANDING_ORDER_DESCRIPTION && string(azColName[x + 6]) == STANDING_ORDER_TYPE && string(azColName[x + 7]) == STANDING_ORDER_DATE)
        {
            // convert int to date. (..YYYYMMDD)
            int date = atoi(argv[x + 7]);
            int year = date / 10000;
            date -= year * 10000;
            int month = date / 100;
            date -= month * 100;
            tempOrders.push_back(make_tuple(atoi(argv[x]), atoi(argv[x + 1]), atoi(argv[x + 2]), Value(atoi(argv[x + 3]), atoi(argv[x + 4])), string(argv[x + 5]), static_cast<StandingOrderType>(atoi(argv[x + 6])), QDate(year, month, date)));
        }
        x += 8;
    }
    return 0;
}

static vector<tuple<int, string, Value, QDate, int, int>> tempTransactions;
static int ProcessTransactionsInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 8 < argc)
    {
        if (string(azColName[x]) == TRANSACTIONS_ID && string(azColName[x + 1]) == TRANSACTIONS_DESCRIPTION && string(azColName[x + 2]) == TRANSACTIONS_VK && string(azColName[x + 3]) == TRANSACTIONS_NK && string(azColName[x + 4]) == TRANSACTIONS_DAY && string(azColName[x + 5]) == TRANSACTIONS_MONTH && string(azColName[x + 6]) == TRANSACTIONS_YEAR && string(azColName[x + 7]) == ACCOUNTS_ID && string(azColName[x + 8]) == LABEL_ID)
        {
            QDate date;
            date.setDate(atoi(argv[x + 6]), atoi(argv[x + 5]), atoi(argv[x + 4]));
            tempTransactions.push_back(make_tuple(atoi(argv[x]), string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3])), date, atoi(argv[x + 7]), atoi(argv[x + 8])));
        }
        x += 9;
    }
    return 0;
}

static vector<tuple<int, string, int>> tempLabels;
static int ProcessLabels(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 2 < argc)
    {
        if (string(azColName[x]) == LABEL_ID && string(azColName[x + 1]) == LABEL_NAME && string(azColName[x + 2]) == LABEL_COLOR)
        {
            tempLabels.push_back(make_tuple(atoi(argv[x]), string(argv[x + 1]), atoi(argv[x + 2])));
        }
        x += 3;
    }
    return 0;
}

static Value tempAccountValue;
static int ProcessAccountValue(void *NotUsed, int argc, char **argv, char **azColName)
{
    if (argc > 1)
    {
        if (string(azColName[0]) == ACCOUNTS_VK && string(azColName[1]) == ACCOUNTS_NK)
        {
            Value v = Value(atoi(argv[0]), atoi(argv[1]));
            tempAccountValue = v;
        }
    }
    return 0;
}

#endif // DATABASE_H