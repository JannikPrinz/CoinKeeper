#pragma once

#include <Windows.h>

#include "constants.h"
#include "qdebug.h"
#include "qdatetime.h"

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
     * This method creates a new database for the new profile.
     *
     * Parameters:
     * std::string const& fileName : the filename of the new db (exlusive .ckdb)
     */
    void CreateNewProfile(std::string const& fileName);
    // This method searches for database-files (profiles) in the given folders.
    // Returns: list of profiles (filenames without '.ckdb' alternating with whole path)
    [[nodiscard]]
    std::list<std::string> GetDatabaseList();
    // This method returns all accounts of the given profile
    // std::string const& profile : path of the profile
    // Returns: vector of tuples with an integer of the unique identifier of the account and the name and value of the account
    [[nodiscard]]
    std::vector<std::tuple<int, std::string, Value>> GetAccounts(std::string const& profile);
    // This method returns transactions of the given profile with the given restrictions, but with no account-restriction.
    // std::string const& profile : path of the profile
    // int month : month of the wanted transactions
    // int year : year of the wanted transactions
    // Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
    [[nodiscard]]
    std::vector<std::tuple<int, std::string, Value, QDate, int, int>> GetTransactions(std::string const& profile, int month, int year);
    // This method returns transactions of the given profile with the given restrictions.
    // std::string const& profile : path of the profile
    // int month : month of the wanted transactions
    // int year : year of the wanted transactions
    // int accountID : id of an account. Only transactions of that account will be returned
    // Returns: vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
    [[nodiscard]]
    std::vector<std::tuple<int, std::string, Value, QDate, int, int>> GetTransactions(std::string const& profile, int month, int year, int accountID);
    /*
     * This method returns all standing orders, which are saved in the given profile.
     *
     * Parameters:
     * std::string const& profile : path of the profile
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all standing orders.
     */
    [[nodiscard]]
    std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> GetAllStandingOrders(std::string const& profile);
    /*
     * This method returns all standing orders, which are saved in the given profile and are ready for execution.
     * An standing order is ready for execution, if set date of the next execution is less then or equal the given date.
     *
     * Parameters:
     * std::string const& profile    : path of the profile
     * int date        : maximum date, which is set as next execution date of the standing order
     *
     * Returns:
     * Tuple with OrderID, AccountID, LabelID, Value, Description, OrderType and NextDate of all matching standing orders.
     */
    [[nodiscard]]
    std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> GetExecutableStandingOrders(std::string const& profile, int date);
    /*
     * This method returns all labels, which are saved in the given profile.
     *
     * Parameters:
     * std::string const& profile : path of the profile
     */
    [[nodiscard]]
    std::vector<std::tuple<int, std::string, int>> GetLabels(std::string const& profile);
    // This method creates a new account at the given profile with the given name and balance.
    // std::string const& profile : path of the profile
    // std::string const& name : name of the new account
    // Value const& balance : start-balance of the new account
    void CreateNewAccount(std::string const& profile, std::string const& name, Value const& balance);
    /*
     * This method creates a new transaction at the given profile / account with the given description, value, labelID and date of the transaction.
     * Also the value of the account gets updated.
     *
     * Parameters:
     * std::string const& profile            : path of the profile
     * std::string const& description    : description of the transaction
     * int account            : ID of the account
     * Value const& value            : value of the transaction
     * QDate const& date            : date of the transaction
     * int labelID            : id of the label
     */
    void CreateNewTransaction(std::string const& profile, std::string const& description, int account, Value const& value, QDate const& date, int labelID);
    /*
     * This method creates a new standing order at the given profile with the given parameters.
     *
     * Parameters:
     * std::string const& profile            : path of the profile
     * std::string& description        : description of the transactions
     * int accountID            : ID of the account
     * Value const& value            : value of the inserted transactions
     * QDate const& date                : date of the next execution of the order
     * int labelID            : id of the label, which all inserted transactions will get
     * int orderType            : indentifier of the type of the standing order
     */
    void CreateNewStandingOrder(std::string const& profile, std::string const& description, int accountID, Value const& value, QDate const& date, int labelID, int orderType);
    /*
     * This method creates a new label in the given profile with the given name and color.
     *
     * Parameters:
     * std::string const& profile    : path of the profile
     * std::string const& name            : name of the new label
     * int color            : color of the new label
     */
    void CreateNewLabel(std::string const& profile, std::string const& name, int color);
    /*
     * This method changes the name and the color of the specified label with given parameters
     *
     * Parameters:
     * std::string const& profile    : path of the profile
     * int labelID            : id of the label, which gets changed
     * std::string const& name            : new name of the label
     * int color            : new color of the label
     */
    void UpdateLabel(std::string const& profile, int labelID, std::string const& name, int color);
    /*
     * This method changes the specified account with the given parameters.
     *
     * Parameters:
     * std::string const& profile : path of the profile
     * int accountID : id of the account, which will be changed
     * std::string const& accountName : new name of the account
     * Value const& value : new value of the account
     */
    void UpdateAccount(std::string const& profile, int accountID, std::string const& accountName, Value const& value);
    /*
     * This method adds the given value to the given account.
     *
     * Parameters:
     * std::string const& profile : path of the profile
     * int accountID : id of the account on which the value-change is applied
     * Value const& value : value, which gets added to the current value of the selected account
     */
    void UpdateAccountValue(std::string const& profile, int accountID, Value const& value);
    /*
     * This method sets the next execution date of the specified standing order to the given date.
     *
     * Parameters:
     * std::string const&  profile    : path of the profile
     * int orderID    : id of the standing order, which next date will be changed
     * int date        : date, which will be the new 'next date' of the standing order
     */
    void UpdateStandingOrderDate(std::string const& profile, int orderID, int date);
    /*
     * This method updates an existing standing order at the given profile with the given parameters.
     *
     * Parameters:
     * std::string const& profile            : path of the profile
     * int orderID            : id of the standing order
     * std::string const& description    : description of the transactions of the standing order
     * int accountID            : ID of the account
     * Value const& value            : value of the transactions
     * QDate const& nextDate        : date of the next inserted transaction
     * int labelID            : id of the label
     * int orderType            : type of the standing order
     */
    void UpdateStandingOrder(std::string const& profile, int orderID, std::string const& description, int accountID, Value const& value, QDate const& nextDate, int labelID, int orderType);
    /*
     * This method updates an existing transaction at the given profile with the given parameters.
     * Tthe value of the account will not be changed within this method!
     *
     * Parameters:
     * std::string const& profile            : path of the profile
     * int transactionID        : id of the transaction
     * std::string const& description        : description of the transaction
     * int accountID            : ID of the account
     * Value const& value            : value of the transaction
     * QDate const& date                : date of the transaction
     * int const& labelID            : id of the label
     */
    void UpdateTransaction(std::string const& profile, int transactionID, std::string const& description, int accountID, Value const& value, QDate const& date, int labelID);
    /*
     * This method deletes the given transaction. The value of the account gets changed if wanted.
     *
     * Parameters:
     * std::string const& profile                : path of the profile
     * int transactionID            : id of the transaction, which gets deleted
     * bool changeAccountValue    : if true, the value of the given account gets changed by the given value
     * int accountID                : id of the account, where the given value gets added if wanted (default = 0)
     * Value const& value                : value which gets added to the given account if wanted (default = 0)
     */
    void DeleteTransaction(std::string const& profile, int transactionID, bool changeAccountValue, int accountID = 0, Value const& value = Value(0));
    /*
     * This method deletes the specified standing order.
     *
     * Parameters:
     * std::string const& profile    : path of the profile
     * int orderID    : id of the standing order, which gets deleted
     */
    void DeleteStandingOrder(std::string const& profile, int orderID);
    /*
     * This method deletes the specified label. All references to this label are changed to the standard label (labelID = 1).
     *
     * Parameters:
     * std::string const& profile    : path of the profile
     * int labelID    : id of the label, which gets deleted
     */
    void DeleteLabel(std::string const& profile, int labelID);
    /*
     * This method deletes the given account and all corresponding transactions.
     *
     * Parameters:
     * std::string const& profile : path of the profile
     * int accountID : id of the account, which gets deleted
     */
    void DeleteAccount(std::string const& profile, int accountID);
    ~Database();

private:
    // Return the path of the executable with '\*' at the end
    [[nodiscard]]
    LPWSTR ExePath();
    // Converts a string to a LPWSTR
    [[nodiscard]]
    LPWSTR StringToLPWSTR(std::string const& s);
    // Converts a LPWSTR to a string
    [[nodiscard]]
    std::string LPWSTRToString(LPWSTR l);
    // extracts filenames of the files from a given list and a given file-type. This strings and original strings (incl. path)
    // get returned. Example: <abc, ..\abc.ckdb, xyz, ..\xyz.ckdb>
    // list<std::string> rawList : list of strings
    // path : path of the files
    // std::string type : type of files, which filenames get returned. Default: "ckdb" (DATABASE_FILETYPE)
    [[nodiscard]]
    std::list<std::string> GetFilenames(std::list<std::string> const& rawList, std::string const& path, std::string const& type = DATABASE_FILETYPE);
};

static std::vector<std::tuple<int, std::string, Value>> tempAccounts;
static int ProcessAccountInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 3 < argc)
    {
        if (std::string(azColName[x]) == ACCOUNTS_ID && std::string(azColName[x + 1]) == ACCOUNTS_NAME && std::string(azColName[x + 2]) == ACCOUNTS_VK && std::string(azColName[x + 3]) == ACCOUNTS_NK)
        {
            tempAccounts.push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3]))));
        }
        x += 4;
    }
    return 0;
}

static std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> tempOrders;
static int ProcessOrderInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 7 < argc)
    {
        if (std::string(azColName[x]) == STANDING_ORDER_ID && std::string(azColName[x + 1]) == ACCOUNTS_ID && std::string(azColName[x + 2]) == LABEL_ID && std::string(azColName[x + 3]) == STANDING_ORDER_VK && std::string(azColName[x + 4]) == STANDING_ORDER_NK && std::string(azColName[x + 5]) == STANDING_ORDER_DESCRIPTION && std::string(azColName[x + 6]) == STANDING_ORDER_TYPE && std::string(azColName[x + 7]) == STANDING_ORDER_DATE)
        {
            // convert int to date. (..YYYYMMDD)
            int date = atoi(argv[x + 7]);
            int year = date / 10000;
            date -= year * 10000;
            int month = date / 100;
            date -= month * 100;
            tempOrders.push_back(make_tuple(atoi(argv[x]), atoi(argv[x + 1]), atoi(argv[x + 2]), Value(atoi(argv[x + 3]), atoi(argv[x + 4])), std::string(argv[x + 5]), static_cast<StandingOrderType>(atoi(argv[x + 6])), QDate(year, month, date)));
        }
        x += 8;
    }
    return 0;
}

static std::vector<std::tuple<int, std::string, Value, QDate, int, int>> tempTransactions;
static int ProcessTransactionsInformation(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 8 < argc)
    {
        if (std::string(azColName[x]) == TRANSACTIONS_ID && std::string(azColName[x + 1]) == TRANSACTIONS_DESCRIPTION && std::string(azColName[x + 2]) == TRANSACTIONS_VK && std::string(azColName[x + 3]) == TRANSACTIONS_NK && std::string(azColName[x + 4]) == TRANSACTIONS_DAY && std::string(azColName[x + 5]) == TRANSACTIONS_MONTH && std::string(azColName[x + 6]) == TRANSACTIONS_YEAR && std::string(azColName[x + 7]) == ACCOUNTS_ID && std::string(azColName[x + 8]) == LABEL_ID)
        {
            QDate date;
            date.setDate(atoi(argv[x + 6]), atoi(argv[x + 5]), atoi(argv[x + 4]));
            tempTransactions.push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3])), date, atoi(argv[x + 7]), atoi(argv[x + 8])));
        }
        x += 9;
    }
    return 0;
}

static std::vector<std::tuple<int, std::string, int>> tempLabels;
static int ProcessLabels(void *NotUsed, int argc, char **argv, char **azColName)
{
    int x = 0;
    while (x + 2 < argc)
    {
        if (std::string(azColName[x]) == LABEL_ID && std::string(azColName[x + 1]) == LABEL_NAME && std::string(azColName[x + 2]) == LABEL_COLOR)
        {
            tempLabels.push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), atoi(argv[x + 2])));
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
        if (std::string(azColName[0]) == ACCOUNTS_VK && std::string(azColName[1]) == ACCOUNTS_NK)
        {
            Value v = Value(atoi(argv[0]), atoi(argv[1]));
            tempAccountValue = v;
        }
    }
    return 0;
}
