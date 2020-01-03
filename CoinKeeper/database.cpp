#include "database.h"

#include <sstream>

#include "sqlite-amalgamation-3120100\sqlite3.h"

/*
    Start delete from here:
    ----------------------------------
*/
static char* errmsg;
#define ERRORMESSAGE &errmsg

static void printErrMsg()
{
    if (errmsg != nullptr)
    {
        qDebug(errmsg);
    }
}

/*
    ----------------------------------
    Until here!
*/

Database::Database()
{
    //qDebug(CREATE_TABLES_OF_A_PROFILE);
}

void Database::CreateNewProfile(std::string const& fileName)
{
    sqlite3* db;
    std::string exPath = LPWSTRToString(ExePath());
    exPath.pop_back();
    exPath.append(fileName);
    exPath.append(".");
    exPath.append(DATABASE_FILETYPE);
    sqlite3_open(exPath.c_str(), &db);
    sqlite3_exec(db, CREATE_TABLES_OF_A_PROFILE.c_str(), callback, 0, 0);
    sqlite3_exec(db, INSERT_DEFAULT_VALUES.c_str(), callback, 0, 0);
    //if (rc != SQLITE_OK)
    //{
    //    qDebug("Fehler beim erstellen der Datanbank!");
    //}
    //else
    //{
    //    qDebug("Erstellen der Datenbank erfolgreich!");
    //}
    // Tests:
    //char* msg;
    //rc = sqlite3_exec(db, "INSERT INTO Accounts (Name, Balance) VALUES (\"Bargeld\", 100);", callback, 0, &msg);
    //rc = sqlite3_exec(db, "INSERT INTO Transactions (Description, Value, AccountID, LabelID) VALUES (\"Erste Einzahlung\", 100, 1, 1);", callback, 0, &msg);
    //rc = sqlite3_exec(db, "SELECT * FROM Transactions;", callback, 0, &msg);
    //if (rc != SQLITE_OK)
    //{
    //    qDebug("Fehler beim ausführen der SQL_Befehle! Fehlermeldung:");
    //    qDebug(msg);
    //}
    //else
    //{
    //    qDebug("Befehlsdurchführung erfolgreich!");
    //}
    sqlite3_close(db);
}

//
//void Database::TestForeignKeys()
//{
//    sqlite3* db;
//    std::string exPath = LPWSTRToString(ExePath());
//    exPath.pop_back();
//    exPath.append(std::string("Test.ckdb"));
//    sqlite3_open(exPath.c_str(), &db);
//    char* zerrormsg = 0;
//    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", callback, 0, &zerrormsg);
//    sqlite3_close(db);
//}

std::list<std::string> Database::GetDatabaseList()
{
    WIN32_FIND_DATA winFD;
    HANDLE hFind;
    std::list<std::string> names;
    LPWSTR executionPath = ExePath();

    hFind = FindFirstFile(executionPath, &winFD);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        names.push_back(LPWSTRToString(winFD.cFileName));

        while (FindNextFile(hFind, &winFD) != 0)
        {
            names.push_back(LPWSTRToString(winFD.cFileName));
        }
    }
    FindClose(hFind);

    std::string path = LPWSTRToString(executionPath);
    path.pop_back();
    return GetFilenames(names, path);
}

void Database::CreateNewAccount(std::string const& profile, std::string const& name, Value const& balance)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = INSERT_NEW_ACCOUNT_PART_1;
    ex.append(name);
    ex.append(INSERT_NEW_ACCOUNT_PART_2);
    ex.append(std::to_string(balance.VK));
    ex.append(INSERT_NEW_ACCOUNT_PART_3);
    ex.append(std::to_string(balance.NK));
    ex.append(INSERT_NEW_ACCOUNT_PART_4);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::CreateNewTransaction(std::string const& profile, std::string const& description, int const account, Value const& value, QDate const& date, int const labelID)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);

    // insert the new transaction:
    std::stringstream ss;
    ss << INSERT_NEW_TRANSACTION_PART_1;
    ss << description;
    ss << INSERT_NEW_TRANSACTION_PART_2;
    ss << std::to_string(value.VK);
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(value.NK);
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(date.day());
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(date.month());
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(date.year());
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(account);
    ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
    ss << std::to_string(labelID);
    ss << INSERT_NEW_TRANSACTION_PART_9;

    sqlite3_exec(db, ss.str().c_str(), callback, 0, 0);
    sqlite3_close(db);
    UpdateAccountValue(profile, account, value);
}

void Database::CreateNewLabel(std::string const& profile, std::string const& name, int const color)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = INSERT_NEW_LABEL_PART_1;
    ex.append(name);
    ex.append(INSERT_NEW_LABEL_PART_2);
    ex.append(std::to_string(color));
    ex.append(INSERT_NEW_LABEL_PART_3);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::CreateNewStandingOrder(std::string const& profile, std::string const& description, int const accountID, Value const& value, QDate const& date, int const labelID, int const orderType)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = INSERT_NEW_STANDING_ORDER_PART_1;
    ex.append(std::to_string(accountID));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
    ex.append(std::to_string(labelID));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
    ex.append(std::to_string(value.VK));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
    ex.append(std::to_string(value.NK));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_5);
    ex.append(description);
    ex.append(INSERT_NEW_STANDING_ORDER_PART_6);
    ex.append(std::to_string(orderType));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_7);
    ex.append(std::to_string(date.year() * 10000 + date.month() * 100 + date.day()));
    ex.append(INSERT_NEW_STANDING_ORDER_PART_8);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateLabel(std::string const& profile, int const labelID, std::string const& name, int const color)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = UPDATE_LABEL_PART_1;
    ex.append(name);
    ex.append(UPDATE_LABEL_PART_2);
    ex.append(std::to_string(color));
    ex.append(UPDATE_LABEL_PART_3);
    ex.append(std::to_string(labelID));
    ex.append(UPDATE_LABEL_PART_4);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateAccount(std::string const& profile, int const accountID, std::string const& accountName, Value const& accountValue)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = UPDATE_ACCOUNT_PART_1;
    ex.append(accountName);
    ex.append(UPDATE_ACCOUNT_PART_2);
    ex.append(std::to_string(accountValue.VK));
    ex.append(UPDATE_ACCOUNT_PART_3);
    ex.append(std::to_string(accountValue.NK));
    ex.append(UPDATE_ACCOUNT_PART_4);
    ex.append(std::to_string(accountID));
    ex.append(UPDATE_ACCOUNT_PART_5);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateAccountValue(std::string const& profilePath, int const accountID, Value const& value)
{
    sqlite3* db;
    sqlite3_open(profilePath.c_str(), &db);
    // get value of account:
    std::string ex = GET_ACCOUNT_VALUE_PART_1;
    ex.append(std::to_string(accountID));
    ex.append(GET_ACCOUNT_VALUE_PART_2);
    Value v;
    tempAccountValue = v;
    sqlite3_exec(db, ex.c_str(), ProcessAccountValue, 0, 0);
    // update value of account:
    v = tempAccountValue + value;
    ex = UPDATE_ACCOUNT_VALUE_PART_1;
    ex.append(std::to_string(v.VK));
    ex.append(UPDATE_ACCOUNT_VALUE_PART_2);
    ex.append(std::to_string(v.NK));
    ex.append(UPDATE_ACCOUNT_VALUE_PART_3);
    ex.append(std::to_string(accountID));
    ex.append(UPDATE_ACCOUNT_VALUE_PART_4);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateStandingOrderDate(std::string const& profile, int const orderID, int const date)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = UPDATE_STANDING_ORDER_DATE_PART_1;
    ex.append(std::to_string(date));
    ex.append(UPDATE_STANDING_ORDER_DATE_PART_2);
    ex.append(std::to_string(orderID));
    ex.append(UPDATE_STANDING_ORDER_DATE_PART_3);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateStandingOrder(std::string const& profile, int const orderID, std::string const& description, int const accountID,
    Value const& value, QDate const& nextDate, int const labelID, int const orderType)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = UPDATE_STANDING_ORDER_PART_1;
    ex.append(std::to_string(accountID));
    ex.append(UPDATE_STANDING_ORDER_PART_2);
    ex.append(std::to_string(labelID));
    ex.append(UPDATE_STANDING_ORDER_PART_3);
    ex.append(std::to_string(value.VK));
    ex.append(UPDATE_STANDING_ORDER_PART_4);
    ex.append(std::to_string(value.NK));
    ex.append(UPDATE_STANDING_ORDER_PART_5);
    ex.append(description);
    ex.append(UPDATE_STANDING_ORDER_PART_6);
    ex.append(std::to_string(orderType));
    ex.append(UPDATE_STANDING_ORDER_PART_7);
    ex.append(std::to_string(nextDate.year() * 10000 + nextDate.month() * 100 + nextDate.day()));
    ex.append(UPDATE_STANDING_ORDER_PART_8);
    ex.append(std::to_string(orderID));
    ex.append(UPDATE_STANDING_ORDER_PART_9);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::UpdateTransaction(std::string const& profile, int const transactionID, std::string const& description, int const accountID, Value const& value, QDate const& date, int const labelID)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = UPDATE_TRANSACTION_PART_1;
    ex.append(description);
    ex.append(UPDATE_TRANSACTION_PART_2);
    ex.append(std::to_string(value.VK));
    ex.append(UPDATE_TRANSACTION_PART_3);
    ex.append(std::to_string(value.NK));
    ex.append(UPDATE_TRANSACTION_PART_4);
    ex.append(std::to_string(date.day()));
    ex.append(UPDATE_TRANSACTION_PART_5);
    ex.append(std::to_string(date.month()));
    ex.append(UPDATE_TRANSACTION_PART_6);
    ex.append(std::to_string(date.year()));
    ex.append(UPDATE_TRANSACTION_PART_7);
    ex.append(std::to_string(accountID));
    ex.append(UPDATE_TRANSACTION_PART_8);
    ex.append(std::to_string(labelID));
    ex.append(UPDATE_TRANSACTION_PART_9);
    ex.append(std::to_string(transactionID));
    ex.append(UPDATE_TRANSACTION_PART_10);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::DeleteTransaction(std::string const& profile, int const transactionID, bool const changeAccountValue, int const accountID, Value const& value)
{
    if (changeAccountValue)    UpdateAccountValue(profile, accountID, value);
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = DELETE_TRANSACTION_PART_1;
    ex.append(std::to_string(transactionID));
    ex.append(DELETE_TRANSACTION_PART_2);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::DeleteStandingOrder(std::string const& profile, int const orderID)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = DELETE_STANDING_ORDER_PART_1;
    ex.append(std::to_string(orderID));
    ex.append(DELETE_STANDING_ORDER_PART_2);
    sqlite3_exec(db, ex.c_str(), callback, 0, 0);
    sqlite3_close(db);
}

void Database::DeleteAccount(std::string const& profile, int const accountID)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = DELETE_ACCOUNT_PART_1;
    ex.append(std::to_string(accountID));
    ex.append(DELETE_ACCOUNT_PART_2);
    ex.append(std::to_string(accountID));
    ex.append(DELETE_ACCOUNT_PART_3);
    ex.append(std::to_string(accountID));
    ex.append(DELETE_ACCOUNT_PART_4);
    sqlite3_exec(db, ex.c_str(), callback, 0, ERRORMESSAGE);
    sqlite3_close(db);
    printErrMsg();
}

void Database::DeleteLabel(std::string const& profile, int const labelID)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::string ex = DELETE_LABEL_PART_1;
    ex.append(std::to_string(labelID));
    ex.append(DELETE_LABEL_PART_2);
    ex.append(std::to_string(labelID));
    ex.append(DELETE_LABEL_PART_3);
    ex.append(std::to_string(labelID));
    ex.append(DELETE_LABEL_PART_4);
    sqlite3_exec(db, ex.c_str(), callback, 0, ERRORMESSAGE);
    sqlite3_close(db);
    printErrMsg();
}

std::vector<std::tuple<int, std::string, Value, QDate, int, int>> Database::GetTransactions(std::string const& profilePath, int const month, int const year)
{
    sqlite3* db;
    sqlite3_open(profilePath.c_str(), &db);
    std::vector<std::tuple<int, std::string, Value, QDate, int, int>> trans;
    tempTransactions = trans;
    std::string ex;
    if (month == 0)        // show all transactions of the selected year
    {
        ex = GET_TRANSACTIONS_Y_PART_1;
        ex.append(std::to_string(year));
        ex.append(GET_TRANSACTIONS_Y_PART_2);
    }
    else
    {
        ex = GET_TRANSACTIONS_M_Y_PART_1;
        ex.append(std::to_string(month));
        ex.append(GET_TRANSACTIONS_M_Y_PART_2);
        ex.append(std::to_string(year));
        ex.append(GET_TRANSACTIONS_M_Y_PART_3);
    }
    sqlite3_exec(db, ex.c_str(), ProcessTransactionsInformation, 0, 0);
    sqlite3_close(db);
    return tempTransactions;
}

std::vector<std::tuple<int, std::string, Value, QDate, int, int>> Database::GetTransactions(std::string const& profilePath, int const month, int const year, int const accountID)
{
    sqlite3* db;
    sqlite3_open(profilePath.c_str(), &db);
    std::vector<std::tuple<int, std::string, Value, QDate, int, int>> trans;
    tempTransactions = trans;
    std::string ex;
    if (month == 0)        // show all transactions of the selected year
    {
        ex = GET_TRANSACTIONS_Y_A_PART_1;
        ex.append(std::to_string(year));
        ex.append(GET_TRANSACTIONS_Y_A_PART_2);
        ex.append(std::to_string(accountID));
        ex.append(GET_TRANSACTIONS_Y_A_PART_3);
    }
    else
    {
        ex = GET_TRANSACTIONS_M_Y_A_PART_1;
        ex.append(std::to_string(month));
        ex.append(GET_TRANSACTIONS_M_Y_A_PART_2);
        ex.append(std::to_string(year));
        ex.append(GET_TRANSACTIONS_M_Y_A_PART_3);
        ex.append(std::to_string(accountID));
        ex.append(GET_TRANSACTIONS_M_Y_A_PART_4);
    }
    sqlite3_exec(db, ex.c_str(), ProcessTransactionsInformation, 0, 0);
    sqlite3_close(db);
    return tempTransactions;
}

std::vector<std::tuple<int, std::string, Value>> Database::GetAccounts(std::string const& profilePath)
{
    sqlite3* db;
    sqlite3_open(profilePath.c_str(), &db);
    std::vector<std::tuple<int, std::string, Value>> acc;
    tempAccounts = acc;
    sqlite3_exec(db, GET_ALL_ACCOUNTS.c_str(), ProcessAccountInformation, 0, 0);
    sqlite3_close(db);
    return tempAccounts;
}

std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> Database::GetAllStandingOrders(std::string const& profile)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> orders;
    tempOrders = orders;
    sqlite3_exec(db, GET_ALL_STANDING_ORDERS.c_str(), ProcessOrderInformation, 0, 0);
    sqlite3_close(db);
    return tempOrders;
}

std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> Database::GetExecutableStandingOrders(std::string const& profile, int const date)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::vector<std::tuple<int, int, int, Value, std::string, StandingOrderType, QDate>> orders;
    tempOrders = orders;
    std::string ex = GET_EXECUTABLE_STANDING_ORDERS_PART_1;
    ex.append(std::to_string(date));
    ex.append(GET_EXECUTABLE_STANDING_ORDERS_PART_2);
    sqlite3_exec(db, ex.c_str(), ProcessOrderInformation, 0, 0);
    sqlite3_close(db);
    return tempOrders;
}

std::vector<std::tuple<int, std::string, int>> Database::GetLabels(std::string const& profile)
{
    sqlite3* db;
    sqlite3_open(profile.c_str(), &db);
    std::vector<std::tuple<int, std::string, int>> labels;
    tempLabels = labels;
    sqlite3_exec(db, GET_ALL_LABELS.c_str(), ProcessLabels, 0, 0);
    sqlite3_close(db);
    return tempLabels;
}

//static int GetIntFromChars(char* arg)
//{
//    int x = 0;
//    int result = 0;
//    while (arg[x] != '\0')
//    {
//        switch (arg[x])
//        {
//        case '0':
//            result *= 10;
//            result += 0;
//            break;
//        case '1':
//            result *= 10;
//            result += 1;
//            break;
//        case '2':
//            result *= 10;
//            result += 2;
//            break;
//        case '3':
//            result *= 10;
//            result += 3;
//            break;
//        case '4':
//            result *= 10;
//            result += 4;
//            break;
//        case '5':
//            result *= 10;
//            result += 5;
//            break;
//        case '6':
//            result *= 10;
//            result += 6;
//            break;
//        case '7':
//            result *= 10;
//            result += 7;
//            break;
//        case '8':
//            result *= 10;
//            result += 8;
//            break;
//        case '9':
//            result *= 10;
//            result += 9;
//            break;
//        default:
//            break;
//        }
//        x++;
//    }
//    return result;
//}

LPWSTR Database::ExePath()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string s = LPWSTRToString(buffer);
    std::string::size_type pos = s.find_last_of("\\/");
    s = s.substr(0, pos + 1);
    s = s.append("*");
    return StringToLPWSTR(s);
}

LPWSTR Database::StringToLPWSTR(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    LPWSTR buf = new WCHAR[len];
//    LPWSTR buff[260];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    return buf;
}

std::string Database::LPWSTRToString(LPWSTR lString)
{
    char ch[MAX_PATH];
    char DefChar = ' ';
    WideCharToMultiByte(CP_ACP, 0, lString, -1, ch, MAX_PATH, &DefChar, NULL);
    return std::string(ch);
}

std::list<std::string> Database::GetFilenames(std::list<std::string> const& rawList, std::string const& path, std::string const& type)
{
    std::list<std::string> returnList;
    std::string typeW = std::string(".").append(type);
    for each (std::string s in rawList)
    {
        size_t pos = s.find(typeW);
        if (pos != std::string::npos)
        {
            returnList.push_back(s.substr(0, pos));
            std::string ss = path;
            ss.append(s);
            returnList.push_back(ss);
        }
    }
    return returnList;
}

Database::~Database()
{
}
