#include "database.h"

#include <sstream>

#include "sqlite-amalgamation-3120100\sqlite3.h"

Database::Database(std::string const& profile) :
    openProfile(profile.c_str())
{
    InitializeCallbackFunctions();
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
    sqlite3_exec(db, CREATE_TABLES_OF_A_PROFILE.c_str(), nullptr, 0, 0);
    sqlite3_exec(db, INSERT_DEFAULT_VALUES.c_str(), nullptr, 0, 0);
    sqlite3_close(db);
}

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

void Database::CreateNewAccount(std::string const& name, Value const& balance)
{
    std::stringstream ss;
    ss << INSERT_NEW_ACCOUNT_PART_1;
    ss << name;
    ss << INSERT_NEW_ACCOUNT_PART_2;
    ss << balance.VK;                   // TODO: test if this works and apply to other methods if yes
    ss << INSERT_NEW_ACCOUNT_PART_3;
    ss << balance.NK;
    ss << INSERT_NEW_ACCOUNT_PART_4;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::CreateNewTransaction(std::string const& description, int const account, Value const& value, QDate const& date, int const labelID)
{
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

    ExecuteSQLStatementWithoutReturnValue(ss);
    UpdateAccountValue(account, value);
}

void Database::CreateNewLabel(std::string const& name, int const color)
{
    std::stringstream ss;
    ss << INSERT_NEW_LABEL_PART_1;
    ss << name;
    ss << INSERT_NEW_LABEL_PART_2;
    ss << std::to_string(color);
    ss << INSERT_NEW_LABEL_PART_3;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::CreateNewStandingOrder(std::string const& description, int const accountID, Value const& value, QDate const& date, int const labelID, int const orderType)
{
    std::stringstream ss;
    ss << INSERT_NEW_STANDING_ORDER_PART_1;
    ss << std::to_string(accountID);
    ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
    ss << std::to_string(labelID);
    ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
    ss << std::to_string(value.VK);
    ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
    ss << std::to_string(value.NK);
    ss << INSERT_NEW_STANDING_ORDER_PART_5;
    ss << description;
    ss << INSERT_NEW_STANDING_ORDER_PART_6;
    ss << std::to_string(orderType);
    ss << INSERT_NEW_STANDING_ORDER_PART_7;
    ss << std::to_string(date.year() * 10000 + date.month() * 100 + date.day());
    ss << INSERT_NEW_STANDING_ORDER_PART_8;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateLabel(int const labelID, std::string const& name, int const color)
{
    std::stringstream ss;
    ss << UPDATE_LABEL_PART_1;
    ss << name;
    ss << UPDATE_LABEL_PART_2;
    ss << std::to_string(color);
    ss << UPDATE_LABEL_PART_3;
    ss << std::to_string(labelID);
    ss << UPDATE_LABEL_PART_4;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateAccount(int const accountID, std::string const& accountName, Value const& accountValue)
{
    std::stringstream ss;
    ss << UPDATE_ACCOUNT_PART_1;
    ss << accountName;
    ss << UPDATE_ACCOUNT_PART_2;
    ss << std::to_string(accountValue.VK);
    ss << UPDATE_ACCOUNT_PART_3;
    ss << std::to_string(accountValue.NK);
    ss << UPDATE_ACCOUNT_PART_4;
    ss << std::to_string(accountID);
    ss << UPDATE_ACCOUNT_PART_5;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateAccountValue(int const accountID, Value const& value)
{
    // get current value of the account:
    Value v = GetAccountValue(accountID);

    // update the value of the account:
    v += value;
    std::stringstream ss;
    ss << UPDATE_ACCOUNT_VALUE_PART_1;
    ss << std::to_string(v.VK);
    ss << UPDATE_ACCOUNT_VALUE_PART_2;
    ss << std::to_string(v.NK);
    ss << UPDATE_ACCOUNT_VALUE_PART_3;
    ss << std::to_string(accountID);
    ss << UPDATE_ACCOUNT_VALUE_PART_4;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateStandingOrderDate(int const orderID, int const date)
{
    std::stringstream ss;
    ss << UPDATE_STANDING_ORDER_DATE_PART_1;
    ss << std::to_string(date);
    ss << UPDATE_STANDING_ORDER_DATE_PART_2;
    ss << std::to_string(orderID);
    ss << UPDATE_STANDING_ORDER_DATE_PART_3;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateStandingOrder(int const orderID, std::string const& description, int const accountID,
    Value const& value, QDate const& nextDate, int const labelID, int const orderType)
{
    std::stringstream ss;
    ss << UPDATE_STANDING_ORDER_PART_1;
    ss << std::to_string(accountID);
    ss << UPDATE_STANDING_ORDER_PART_2;
    ss << std::to_string(labelID);
    ss << UPDATE_STANDING_ORDER_PART_3;
    ss << std::to_string(value.VK);
    ss << UPDATE_STANDING_ORDER_PART_4;
    ss << std::to_string(value.NK);
    ss << UPDATE_STANDING_ORDER_PART_5;
    ss << description;
    ss << UPDATE_STANDING_ORDER_PART_6;
    ss << std::to_string(orderType);
    ss << UPDATE_STANDING_ORDER_PART_7;
    ss << std::to_string(nextDate.year() * 10000 + nextDate.month() * 100 + nextDate.day());
    ss << UPDATE_STANDING_ORDER_PART_8;
    ss << std::to_string(orderID);
    ss << UPDATE_STANDING_ORDER_PART_9;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::UpdateTransaction(int const transactionID, std::string const& description, int const accountID, Value const& value, QDate const& date, int const labelID)
{
    std::stringstream ss;
    ss << UPDATE_TRANSACTION_PART_1;
    ss << description;
    ss << UPDATE_TRANSACTION_PART_2;
    ss << std::to_string(value.VK);
    ss << UPDATE_TRANSACTION_PART_3;
    ss << std::to_string(value.NK);
    ss << UPDATE_TRANSACTION_PART_4;
    ss << std::to_string(date.day());
    ss << UPDATE_TRANSACTION_PART_5;
    ss << std::to_string(date.month());
    ss << UPDATE_TRANSACTION_PART_6;
    ss << std::to_string(date.year());
    ss << UPDATE_TRANSACTION_PART_7;
    ss << std::to_string(accountID);
    ss << UPDATE_TRANSACTION_PART_8;
    ss << std::to_string(labelID);
    ss << UPDATE_TRANSACTION_PART_9;
    ss << std::to_string(transactionID);
    ss << UPDATE_TRANSACTION_PART_10;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::DeleteTransaction(int const transactionID, bool const changeAccountValue, int const accountID, Value const& value)
{
    if (changeAccountValue) {
        UpdateAccountValue(accountID, value);
    }

    std::stringstream ss;
    ss << DELETE_TRANSACTION_PART_1;
    ss << std::to_string(transactionID);
    ss << DELETE_TRANSACTION_PART_2;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::DeleteStandingOrder(int const orderID)
{
    std::stringstream ss;
    ss << DELETE_STANDING_ORDER_PART_1;
    ss << std::to_string(orderID);
    ss << DELETE_STANDING_ORDER_PART_2;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::DeleteAccount(int const accountID)
{
    std::stringstream ss;
    ss << DELETE_ACCOUNT_PART_1;
    ss << std::to_string(accountID);
    ss << DELETE_ACCOUNT_PART_2;
    ss << std::to_string(accountID);
    ss << DELETE_ACCOUNT_PART_3;
    ss << std::to_string(accountID);
    ss << DELETE_ACCOUNT_PART_4;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

void Database::DeleteLabel(int const labelID)
{
    std::stringstream ss;
    ss << DELETE_LABEL_PART_1;
    ss << std::to_string(labelID);
    ss << DELETE_LABEL_PART_2;
    ss << std::to_string(labelID);
    ss << DELETE_LABEL_PART_3;
    ss << std::to_string(labelID);
    ss << DELETE_LABEL_PART_4;

    ExecuteSQLStatementWithoutReturnValue(ss);
}

Value Database::GetAccountValue(int const accountID)
{
    std::stringstream ss;
    ss << GET_ACCOUNT_VALUE_PART_1;
    ss << std::to_string(accountID);
    ss << GET_ACCOUNT_VALUE_PART_2;

    Value value;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetAccountValue, static_cast<void*>(&value));

    return value;
}

TransactionVector Database::GetTransactions(int const month, int const year)
{
    std::stringstream ss;
    if (month == 0) {       // show all transactions of the selected year
        ss << GET_TRANSACTIONS_Y_PART_1;
        ss << std::to_string(year);
        ss << GET_TRANSACTIONS_Y_PART_2;
    } else {
        ss << GET_TRANSACTIONS_M_Y_PART_1;
        ss << std::to_string(month);
        ss << GET_TRANSACTIONS_M_Y_PART_2;
        ss << std::to_string(year);
        ss << GET_TRANSACTIONS_M_Y_PART_3;
    }

    TransactionVector transactions;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetTransactions, static_cast<void*>(&transactions));

    return transactions;
}

TransactionVector Database::GetTransactions(int const month, int const year, int const accountID)
{
    std::stringstream ss;
    if (month == 0) {       // show all transactions of the selected year
        ss << GET_TRANSACTIONS_Y_A_PART_1;
        ss << std::to_string(year);
        ss << GET_TRANSACTIONS_Y_A_PART_2;
        ss << std::to_string(accountID);
        ss << GET_TRANSACTIONS_Y_A_PART_3;
    } else {
        ss << GET_TRANSACTIONS_M_Y_A_PART_1;
        ss << std::to_string(month);
        ss << GET_TRANSACTIONS_M_Y_A_PART_2;
        ss << std::to_string(year);
        ss << GET_TRANSACTIONS_M_Y_A_PART_3;
        ss << std::to_string(accountID);
        ss << GET_TRANSACTIONS_M_Y_A_PART_4;
    }

    TransactionVector transactions;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetTransactions, static_cast<void*>(&transactions));

    return transactions;
}

AccountVector Database::GetAccounts()
{
    std::stringstream ss;
    ss << GET_ALL_ACCOUNTS;

    AccountVector accounts;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetAccounts, static_cast<void*>(&accounts));

    return accounts;
}

StandingOrderVector Database::GetAllStandingOrders()
{
    std::stringstream ss;
    ss << GET_ALL_STANDING_ORDERS;

    StandingOrderVector orders;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetStandingOrders, static_cast<void*>(&orders));

    return orders;
}

StandingOrderVector Database::GetExecutableStandingOrders(int const date)
{
    std::stringstream ss;
    ss << GET_EXECUTABLE_STANDING_ORDERS_PART_1;
    ss << std::to_string(date);
    ss << GET_EXECUTABLE_STANDING_ORDERS_PART_2;

    StandingOrderVector orders;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetStandingOrders, static_cast<void*>(&orders));

    return orders;
}

LabelVector Database::GetLabels()
{
    std::stringstream ss;
    ss << GET_ALL_LABELS;

    LabelVector labels;
    ExecuteSQLStatementWithReturnValue(ss, CBF_GetLabels, static_cast<void*>(&labels));

    return labels;
}

void Database::InitializeCallbackFunctions()
{
    CBF_GetAccountValue = [](void* data, int argc, char** argv, char** azColName) {
        Value* valuePtr = static_cast<Value*>(data);
        if (argc > 1 && std::string(azColName[0]) == ACCOUNTS_VK && std::string(azColName[1]) == ACCOUNTS_NK) {
            *valuePtr = Value(atoi(argv[0]), atoi(argv[1]));
        }
        return 0;
    };

    CBF_GetTransactions = [](void* data, int argc, char** argv, char** azColName) {
        TransactionVector* transactionPtr = static_cast<TransactionVector*>(data);
        int x = 0;
        while (x + 8 < argc) {
            if (std::string(azColName[x]) == TRANSACTIONS_ID && std::string(azColName[x + 1]) == TRANSACTIONS_DESCRIPTION &&
                std::string(azColName[x + 2]) == TRANSACTIONS_VK && std::string(azColName[x + 3]) == TRANSACTIONS_NK &&
                std::string(azColName[x + 4]) == TRANSACTIONS_DAY && std::string(azColName[x + 5]) == TRANSACTIONS_MONTH &&
                std::string(azColName[x + 6]) == TRANSACTIONS_YEAR && std::string(azColName[x + 7]) == ACCOUNTS_ID && std::string(azColName[x + 8]) == LABEL_ID)
            {
                QDate date;
                date.setDate(atoi(argv[x + 6]), atoi(argv[x + 5]), atoi(argv[x + 4]));
                transactionPtr->push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3])), date, atoi(argv[x + 7]), atoi(argv[x + 8])));
            }
            x += 9;
        }
        return 0;
    };

    CBF_GetAccounts = [](void* data, int argc, char** argv, char** azColName) {
        AccountVector* accountPtr = static_cast<AccountVector*>(data);
        int x = 0;
        while (x + 3 < argc) {
            if (std::string(azColName[x]) == ACCOUNTS_ID && std::string(azColName[x + 1]) == ACCOUNTS_NAME &&
                std::string(azColName[x + 2]) == ACCOUNTS_VK && std::string(azColName[x + 3]) == ACCOUNTS_NK)
            {
                accountPtr->push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), Value(atoi(argv[x + 2]), atoi(argv[x + 3]))));
            }
            x += 4;
        }
        return 0;
    };

    CBF_GetStandingOrders = [](void* data, int argc, char** argv, char** azColName) {
        StandingOrderVector* orderPtr = static_cast<StandingOrderVector*>(data);
        int x = 0;
        while (x + 7 < argc) {
            if (std::string(azColName[x]) == STANDING_ORDER_ID && std::string(azColName[x + 1]) == ACCOUNTS_ID &&
                std::string(azColName[x + 2]) == LABEL_ID && std::string(azColName[x + 3]) == STANDING_ORDER_VK &&
                std::string(azColName[x + 4]) == STANDING_ORDER_NK && std::string(azColName[x + 5]) == STANDING_ORDER_DESCRIPTION &&
                std::string(azColName[x + 6]) == STANDING_ORDER_TYPE && std::string(azColName[x + 7]) == STANDING_ORDER_DATE)
            {
                // convert int to date. (..YYYYMMDD)
                int date = atoi(argv[x + 7]);
                int year = date / 10000;
                date -= year * 10000;
                int month = date / 100;
                date -= month * 100;
                orderPtr->push_back(make_tuple(atoi(argv[x]), atoi(argv[x + 1]), atoi(argv[x + 2]), Value(atoi(argv[x + 3]),
                    atoi(argv[x + 4])), std::string(argv[x + 5]), static_cast<StandingOrderType>(atoi(argv[x + 6])), QDate(year, month, date)));
            }
            x += 8;
        }
        return 0;
    };

    CBF_GetLabels = [](void* data, int argc, char** argv, char** azColName) {
        LabelVector* labelPtr = static_cast<LabelVector*>(data);
        int x = 0;
        while (x + 2 < argc) {
            if (std::string(azColName[x]) == LABEL_ID && std::string(azColName[x + 1]) == LABEL_NAME && std::string(azColName[x + 2]) == LABEL_COLOR) {
                labelPtr->push_back(make_tuple(atoi(argv[x]), std::string(argv[x + 1]), atoi(argv[x + 2])));
            }
            x += 3;
        }
        return 0;
    };
}

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

void Database::ExecuteSQLStatementWithoutReturnValue(std::stringstream const& ss) const
{
    sqlite3* db;
    sqlite3_open(openProfile, &db);
    std::string const& tmp = ss.str();
    sqlite3_exec(db, tmp.c_str(), nullptr, 0, 0);
    sqlite3_close(db);
}

void Database::ExecuteSQLStatementWithReturnValue(std::stringstream const& ss, CallbackFunction callback, void* data) const
{
    sqlite3* db;
    sqlite3_open(openProfile, &db);
    std::string const& tmp = ss.str();
    sqlite3_exec(db, tmp.c_str(), callback, data, 0);
    sqlite3_close(db);
}
