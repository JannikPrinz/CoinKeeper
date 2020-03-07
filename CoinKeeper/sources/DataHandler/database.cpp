#include "DataHandler/database.h"

#include <filesystem>
#include <sstream>

#include <qmessagebox.h>

#include "sqlite-amalgamation-3120100/sqlite3.h"

namespace DataHandler
{
    namespace fs = std::filesystem;
    using Value = DataClasses::Value;
    using StandingOrder = DataClasses::StandingOrder;

    Database::Database(std::string const& profile) :
        openProfile(profile)
    {
        InitializeCallbackFunctions();
        UpdateDBVersion();
    }

    void Database::ChangeProfileName(std::filesystem::path const& oldPath, std::string const& newProfileName)
    {
        fs::path newPath(oldPath);
        newPath.replace_filename(newProfileName + "." + DATABASE_FILETYPE);

        if (fs::exists(newPath)) {
            return;
        }

        fs::rename(oldPath, newPath);
    }

    void Database::CreateNewAccount(std::string const& name, Value const& balance)
    {
        std::stringstream ss;
        ss << INSERT_NEW_ACCOUNT_PART_1;
        ss << name;
        ss << INSERT_NEW_ACCOUNT_PART_2;
        ss << balance.VK;
        ss << INSERT_NEW_ACCOUNT_PART_3;
        ss << balance.NK;
        ss << INSERT_NEW_ACCOUNT_PART_4;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::CreateNewLabel(std::string const& name, int const color)
    {
        std::stringstream ss;
        ss << INSERT_NEW_LABEL_PART_1;
        ss << name;
        ss << INSERT_NEW_LABEL_PART_2;
        ss << color;
        ss << INSERT_NEW_LABEL_PART_3;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::CreateNewOption(Options const& option, std::string const& optionValue)
    {
        std::stringstream ss;
        ss << INSERT_NEW_OPTION_PART_1;
        ss << static_cast<int32_t>(option);
        ss << INSERT_NEW_OPTION_PART_2;
        ss << optionValue;
        ss << INSERT_NEW_OPTION_PART_3;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::CreateNewProfile(std::string const& fileName)
    {
        auto path = fs::current_path();
        path.append(fileName + "." + DATABASE_FILETYPE);

        sqlite3* db;
        sqlite3_open(path.string().c_str(), &db);
        sqlite3_exec(db, CREATE_TABLES_OF_A_PROFILE.c_str(), nullptr, 0, 0);
        sqlite3_exec(db, INSERT_DEFAULT_VALUES.c_str(), nullptr, 0, 0);
        sqlite3_close(db);
    }

    void Database::CreateNewStandingOrder(std::string const& description, int32_t const accountID, Value const& value, QDate const& date, int32_t const labelID,
        StandingOrder::StandingOrderType const orderType, std::optional<int32_t> const& connectedAccountId)
    {
        std::stringstream ss;
        ss << INSERT_NEW_STANDING_ORDER_PART_1;
        ss << accountID;
        ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
        ss << labelID;
        ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
        ss << value.VK;
        ss << INSERT_NEW_STANDING_ORDER_PART_2_TO_4;
        ss << value.NK;
        ss << INSERT_NEW_STANDING_ORDER_PART_5;
        ss << description;
        ss << INSERT_NEW_STANDING_ORDER_PART_6;
        ss << static_cast<int32_t>(orderType);
        ss << INSERT_NEW_STANDING_ORDER_PART_7_TO_8;
        ss << (date.year() * 10000 + date.month() * 100 + date.day());
        ss << INSERT_NEW_STANDING_ORDER_PART_7_TO_8;
        ss << (connectedAccountId.has_value() ? std::to_string(connectedAccountId.value()) : "NULL");
        ss << INSERT_NEW_STANDING_ORDER_PART_9;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::CreateNewTransaction(std::string const& description, int32_t const account, Value const& value, QDate const& date, int32_t const labelID, std::optional<int32_t> targetAccount)
    {
        // insert the new transaction:
        std::stringstream ss;
        ss << INSERT_NEW_TRANSACTION_PART_1;
        ss << description;
        ss << INSERT_NEW_TRANSACTION_PART_2;
        ss << value.VK;
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << value.NK;
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << date.day();
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << date.month();
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << date.year();
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << account;
        ss << INSERT_NEW_TRANSACTION_PART_3_TO_8;
        ss << labelID;
        ss << INSERT_NEW_TRANSACTION_PART_9;

        ExecuteSQLStatementWithoutReturnValue(ss);
        UpdateAccountValue(account, value);

        if (targetAccount.has_value()) {
            int32_t firstID = GetMaxTransactionID().value();
            int32_t secondID = firstID + 1;

            CreateNewTransaction(description, targetAccount.value(), value * -1, date, labelID, std::nullopt);
            UpdateConnectedTransaction(firstID, secondID);
            UpdateConnectedTransaction(secondID, firstID);
        }
    }

    void Database::DeleteAccount(int const accountID)
    {
        std::stringstream ss;
        ss << DELETE_ACCOUNT_PART_1;
        ss << accountID;
        ss << DELETE_ACCOUNT_PART_2;
        ss << accountID;
        ss << DELETE_ACCOUNT_PART_3;
        ss << accountID;
        ss << DELETE_ACCOUNT_PART_4;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::DeleteLabel(int const labelID)
    {
        std::stringstream ss;
        ss << DELETE_LABEL_PART_1;
        ss << labelID;
        ss << DELETE_LABEL_PART_2;
        ss << labelID;
        ss << DELETE_LABEL_PART_3;
        ss << labelID;
        ss << DELETE_LABEL_PART_4;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::DeleteProfile(std::filesystem::path const& profilePath)
    {
        fs::remove(profilePath);
    }

    void Database::DeleteStandingOrder(int const orderID)
    {
        std::stringstream ss;
        ss << DELETE_STANDING_ORDER_PART_1;
        ss << orderID;
        ss << DELETE_STANDING_ORDER_PART_2;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::DeleteTransaction(int const transactionID, bool const changeAccountValue)
    {
        if (changeAccountValue) {
            auto transactionOpt = GetTransaction(transactionID);
            UpdateAccountValue(transactionOpt->AccountId, transactionOpt->TransactionValue * -1);
        }

        std::stringstream ss;
        ss << DELETE_TRANSACTION_PART_1;
        ss << transactionID;
        ss << DELETE_TRANSACTION_PART_2;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    AccountVector Database::GetAccounts()
    {
        std::stringstream ss;
        ss << GET_ALL_ACCOUNTS;

        AccountVector accounts;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetAccounts, static_cast<void*>(&accounts));

        return accounts;
    }

    Value Database::GetAccountValue(int const accountID)
    {
        std::stringstream ss;
        ss << GET_ACCOUNT_VALUE_PART_1;
        ss << accountID;
        ss << GET_ACCOUNT_VALUE_PART_2;

        Value value;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetAccountValue, static_cast<void*>(&value));

        return value;
    }

    StandingOrderVector Database::GetAllStandingOrders()
    {
        std::stringstream ss;
        ss << GET_ALL_STANDING_ORDERS;

        StandingOrderVector orders;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetStandingOrders, static_cast<void*>(&orders));

        return orders;
    }

    ProfileVector Database::GetDatabaseList()
    {
        ProfileVector profiles;
        for (auto const& directoryEntry : fs::directory_iterator(fs::current_path())) {
            if (directoryEntry.is_regular_file()) {
                std::string const& filename = directoryEntry.path().filename().string();

                bool filenameHasDBEnding = filename.length() > DATABASE_FILETYPE.length() &&
                    filename.substr(filename.length() - (DATABASE_FILETYPE.length() + 1), DATABASE_FILETYPE.length() + 1) == "." + DATABASE_FILETYPE;

                if (filenameHasDBEnding) {
                    profiles.push_back(std::make_pair(filename.substr(0, filename.length() - (DATABASE_FILETYPE.length() + 1)), directoryEntry.path()));
                }
            }
        }

        return profiles;
    }

    StandingOrderVector Database::GetExecutableStandingOrders(int const date)
    {
        std::stringstream ss;
        ss << GET_EXECUTABLE_STANDING_ORDERS_PART_1;
        ss << date;
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

    std::optional<std::string> Database::GetOption(Options option)
    {
        std::stringstream ss;
        ss << GET_OPTION_PART_1;
        ss << static_cast<int32_t>(option);
        ss << GET_OPTION_PART_2;

        std::optional<std::string> value = std::nullopt;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetOption, static_cast<void*>(&value));

        return value;
    }

    std::optional<DataClasses::Transaction> Database::GetTransaction(int32_t transactionID)
    {
        std::stringstream ss;
        ss << GET_TRANSACTION_PART_1;
        ss << transactionID;
        ss << GET_TRANSACTION_PART_2;

        std::optional<DataClasses::Transaction> transaction = std::nullopt;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetTransaction, static_cast<void*>(&transaction));

        return transaction;
    }

    TransactionVector Database::GetTransactions(int const month, int const year)
    {
        std::stringstream ss;
        if (month == 0) {       // show all transactions of the selected year
            ss << GET_TRANSACTIONS_Y_PART_1;
            ss << year;
            ss << GET_TRANSACTIONS_Y_PART_2;
        }
        else {
            ss << GET_TRANSACTIONS_M_Y_PART_1;
            ss << month;
            ss << GET_TRANSACTIONS_M_Y_PART_2;
            ss << year;
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
            ss << year;
            ss << GET_TRANSACTIONS_Y_A_PART_2;
            ss << accountID;
            ss << GET_TRANSACTIONS_Y_A_PART_3;
        }
        else {
            ss << GET_TRANSACTIONS_M_Y_A_PART_1;
            ss << month;
            ss << GET_TRANSACTIONS_M_Y_A_PART_2;
            ss << year;
            ss << GET_TRANSACTIONS_M_Y_A_PART_3;
            ss << accountID;
            ss << GET_TRANSACTIONS_M_Y_A_PART_4;
        }

        TransactionVector transactions;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetTransactions, static_cast<void*>(&transactions));

        return transactions;
    }

    void Database::UpdateAccount(int const accountID, std::string const& accountName, Value const& accountValue)
    {
        std::stringstream ss;
        ss << UPDATE_ACCOUNT_PART_1;
        ss << accountName;
        ss << UPDATE_ACCOUNT_PART_2;
        ss << accountValue.VK;
        ss << UPDATE_ACCOUNT_PART_3;
        ss << accountValue.NK;
        ss << UPDATE_ACCOUNT_PART_4;
        ss << accountID;
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
        ss << v.VK;
        ss << UPDATE_ACCOUNT_VALUE_PART_2;
        ss << v.NK;
        ss << UPDATE_ACCOUNT_VALUE_PART_3;
        ss << accountID;
        ss << UPDATE_ACCOUNT_VALUE_PART_4;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateConnectedTransaction(int32_t transactionID, std::optional<int32_t> connectedTransactionID)
    {
        std::stringstream ss;
        ss << UPDATE_CONNECTED_TRANSACTION_PART_1;
        ss << (connectedTransactionID.has_value() ? std::to_string(connectedTransactionID.value()) : "NULL");
        ss << UPDATE_CONNECTED_TRANSACTION_PART_2;
        ss << transactionID;
        ss << UPDATE_CONNECTED_TRANSACTION_PART_3;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateLabel(int const labelID, std::string const& name, int const color)
    {
        std::stringstream ss;
        ss << UPDATE_LABEL_PART_1;
        ss << name;
        ss << UPDATE_LABEL_PART_2;
        ss << color;
        ss << UPDATE_LABEL_PART_3;
        ss << labelID;
        ss << UPDATE_LABEL_PART_4;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateOption(Options const& option, std::string const& optionValue)
    {
        std::stringstream ss;
        ss << UPDATE_OPTION_PART_1;
        ss << optionValue;
        ss << UPDATE_OPTION_PART_2;
        ss << static_cast<int32_t>(option);
        ss << UPDATE_OPTION_PART_3;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateStandingOrder(StandingOrder const& standingOrder)
    {
        std::stringstream ss;
        ss << UPDATE_STANDING_ORDER_PART_1;
        ss << standingOrder.AccountId;
        ss << UPDATE_STANDING_ORDER_PART_2;
        ss << standingOrder.LabelId;
        ss << UPDATE_STANDING_ORDER_PART_3;
        ss << standingOrder.StandingOrderValue.VK;
        ss << UPDATE_STANDING_ORDER_PART_4;
        ss << standingOrder.StandingOrderValue.NK;
        ss << UPDATE_STANDING_ORDER_PART_5;
        ss << standingOrder.Description;
        ss << UPDATE_STANDING_ORDER_PART_6;
        ss << static_cast<int32_t>(standingOrder.Type);
        ss << UPDATE_STANDING_ORDER_PART_7;
        ss << (standingOrder.Date.year() * 10000 + standingOrder.Date.month() * 100 + standingOrder.Date.day());
        ss << UPDATE_STANDING_ORDER_PART_8;
        ss << (standingOrder.ConnectedAccountId.has_value() ? std::to_string(standingOrder.ConnectedAccountId.value()) : "NULL");
        ss << UPDATE_STANDING_ORDER_PART_9;
        ss << standingOrder.StandingOrderId;
        ss << UPDATE_STANDING_ORDER_PART_10;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateStandingOrderDate(int const orderID, int const date)
    {
        std::stringstream ss;
        ss << UPDATE_STANDING_ORDER_DATE_PART_1;
        ss << date;
        ss << UPDATE_STANDING_ORDER_DATE_PART_2;
        ss << orderID;
        ss << UPDATE_STANDING_ORDER_DATE_PART_3;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    void Database::UpdateTransaction(int const transactionID, std::string const& description, int const accountID, Value const& value, QDate const& date, int const labelID)
    {
        std::stringstream ss;
        ss << UPDATE_TRANSACTION_PART_1;
        ss << description;
        ss << UPDATE_TRANSACTION_PART_2;
        ss << value.VK;
        ss << UPDATE_TRANSACTION_PART_3;
        ss << value.NK;
        ss << UPDATE_TRANSACTION_PART_4;
        ss << date.day();
        ss << UPDATE_TRANSACTION_PART_5;
        ss << date.month();
        ss << UPDATE_TRANSACTION_PART_6;
        ss << date.year();
        ss << UPDATE_TRANSACTION_PART_7;
        ss << accountID;
        ss << UPDATE_TRANSACTION_PART_8;
        ss << labelID;
        ss << UPDATE_TRANSACTION_PART_9;
        ss << transactionID;
        ss << UPDATE_TRANSACTION_PART_10;

        ExecuteSQLStatementWithoutReturnValue(ss);
    }

    std::optional<int32_t> Database::GetMaxTransactionID()
    {
        std::stringstream ss;
        ss << GET_MAX_TRANSACTION_ID;

        std::optional<int32_t> transactionID = std::nullopt;
        ExecuteSQLStatementWithReturnValue(ss, CBF_GetMaxTransactionID, &transactionID);

        return transactionID;
    }

    // TODO: define callback functions statically
    void Database::InitializeCallbackFunctions()
    {
        CBF_GetAccountValue = [](void* data, int argc, char** argv, char** azColName) {
            Value* valuePtr = static_cast<Value*>(data);
            if (argc > 1 && std::string(azColName[0]) == ACCOUNTS_VK && std::string(azColName[1]) == ACCOUNTS_NK) {
                *valuePtr = Value(atoi(argv[0]), atoi(argv[1]));
            }
            return 0;
        };

        CBF_GetTransaction = [](void* data, int argc, char** argv, char** azColName) {
            std::optional<DataClasses::Transaction>* transactionPtr = static_cast<std::optional<DataClasses::Transaction>*>(data);
            if (argc == 10 && std::string(azColName[0]) == TRANSACTIONS_ID && std::string(azColName[1]) == TRANSACTIONS_DESCRIPTION &&
                std::string(azColName[2]) == TRANSACTIONS_VK && std::string(azColName[3]) == TRANSACTIONS_NK &&
                std::string(azColName[4]) == TRANSACTIONS_DAY && std::string(azColName[5]) == TRANSACTIONS_MONTH &&
                std::string(azColName[6]) == TRANSACTIONS_YEAR && std::string(azColName[7]) == ACCOUNTS_ID &&
                std::string(azColName[8]) == LABEL_ID && std::string(azColName[9]) == TRANSACTION_CONNECTED_TRANSACTION_ID)
            {
                QDate date;
                date.setDate(atoi(argv[6]), atoi(argv[5]), atoi(argv[4]));
                std::optional<int32_t> connectedTransaction = std::nullopt;
                if (argv[9] != NULL) {
                    connectedTransaction = atoi(argv[9]);
                }
                *transactionPtr = DataClasses::Transaction(atoi(argv[0]), std::string(argv[1]), Value(atoi(argv[2]),
                    atoi(argv[3])), date, atoi(argv[7]), atoi(argv[8]), connectedTransaction);
            }
            return 0;
        };

        CBF_GetTransactions = [](void* data, int argc, char** argv, char** azColName) {
            TransactionVector* transactionPtr = static_cast<TransactionVector*>(data);
            int x = 0;
            while (x + 9 < argc) {
                if (std::string(azColName[x]) == TRANSACTIONS_ID && std::string(azColName[x + 1]) == TRANSACTIONS_DESCRIPTION &&
                    std::string(azColName[x + 2]) == TRANSACTIONS_VK && std::string(azColName[x + 3]) == TRANSACTIONS_NK &&
                    std::string(azColName[x + 4]) == TRANSACTIONS_DAY && std::string(azColName[x + 5]) == TRANSACTIONS_MONTH &&
                    std::string(azColName[x + 6]) == TRANSACTIONS_YEAR && std::string(azColName[x + 7]) == ACCOUNTS_ID &&
                    std::string(azColName[x + 8]) == LABEL_ID && std::string(azColName[x + 9]) == TRANSACTION_CONNECTED_TRANSACTION_ID)
                {
                    QDate date;
                    date.setDate(atoi(argv[x + 6]), atoi(argv[x + 5]), atoi(argv[x + 4]));
                    std::optional<int32_t> connectedTransaction = std::nullopt;
                    if (argv[x + 9] != NULL) {
                        connectedTransaction = atoi(argv[x + 9]);
                    }
                    transactionPtr->push_back(DataClasses::Transaction(atoi(argv[x]), std::string(argv[x + 1]), Value(atoi(argv[x + 2]),
                        atoi(argv[x + 3])), date, atoi(argv[x + 7]), atoi(argv[x + 8]), connectedTransaction));
                }
                x += 10;
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
            while (x + 8 < argc) {
                if (std::string(azColName[x]) == STANDING_ORDER_ID && std::string(azColName[x + 1]) == ACCOUNTS_ID &&
                    std::string(azColName[x + 2]) == LABEL_ID && std::string(azColName[x + 3]) == STANDING_ORDER_VK &&
                    std::string(azColName[x + 4]) == STANDING_ORDER_NK && std::string(azColName[x + 5]) == STANDING_ORDER_DESCRIPTION &&
                    std::string(azColName[x + 6]) == STANDING_ORDER_TYPE && std::string(azColName[x + 7]) == STANDING_ORDER_DATE &&
                    std::string(azColName[x + 8]) == STANDING_ORDER_CONNECTED_ACCOUNT)
                {
                    // convert int to date. (..YYYYMMDD)
                    int date = atoi(argv[x + 7]);
                    int year = date / 10000;
                    date -= year * 10000;
                    int month = date / 100;
                    date -= month * 100;

                    std::optional<int32_t> connectedAccountId = std::nullopt;
                    if (argv[x + 8] != NULL) {
                        connectedAccountId = atoi(argv[x + 8]);
                    }

                    orderPtr->push_back(StandingOrder(atoi(argv[x]), atoi(argv[x + 1]), atoi(argv[x + 2]), Value(atoi(argv[x + 3]), atoi(argv[x + 4])),
                        std::string(argv[x + 5]), static_cast<StandingOrder::StandingOrderType>(atoi(argv[x + 6])), QDate(year, month, date), connectedAccountId));
                }
                x += 9;
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

        CBF_GetOption = [](void* data, int argc, char** argv, char** azColName) {
            std::optional<std::string>* valuePtr = static_cast<std::optional<std::string>*>(data);
            if (argc == 1 && std::string(azColName[0]) == OPTION_VALUE) {
                *valuePtr = std::string(argv[0]);
            }
            return 0;
        };

        CBF_GetMaxTransactionID = [](void* data, int argc, char** argv, char** azColName) {
            std::optional<int32_t>* valuePtr = static_cast<std::optional<int32_t>*>(data);
            if (argc == 1 && argv[0] != NULL)
            {
                *valuePtr = atoi(argv[0]);
            }
            return 0;
        };
    }

    void Database::UpdateDBVersion()
    {
        // Check if an update is needed:
        auto optDBVersionString = GetOption(Options::DB_Version);
        int32_t dbVersion;
        if (!optDBVersionString.has_value()) {
            dbVersion = 1;
        }
        else {
            dbVersion = std::stoi(optDBVersionString.value());
        }

        if (dbVersion == LATEST_DB_VERSION) {
            return;
        }

        if (dbVersion > LATEST_DB_VERSION) {
            QMessageBox msg;
            QString m = QString::fromStdString(TEXT_DB_VERSION_NOT_SUPPORTED_PART_1);
            m.append(QString::fromStdString(std::to_string(dbVersion)));
            m.append(QString::fromStdString(TEXT_DB_VERSION_NOT_SUPPORTED_PART_2));
            m.append(QString::fromStdString(std::to_string(LATEST_DB_VERSION)));
            msg.setText(m);
            msg.exec();

            exit(0);
        }

        // Update db version:
        std::stringstream ss;
        switch (dbVersion)
        {
        case 1:
            ss << ALTER_DB_FROM_VERSION_1_TO_2;
            [[fallthrough]];
        case 2:
            ss << ALTER_DB_FROM_VERSION_2_TO_3;
            [[fallthrough]];
        default:
            break;
        }
        ExecuteSQLStatementWithoutReturnValue(ss);

        if (dbVersion == 1) {
            CreateNewOption(Options::DB_Version, std::to_string(LATEST_DB_VERSION));
        }
        else {
            UpdateOption(Options::DB_Version, std::to_string(LATEST_DB_VERSION));
        }

        QMessageBox msg;
        QString m = QString::fromStdString(TEXT_DB_VERSION_UPDATED);
        m.append(QString::fromStdString(std::to_string(LATEST_DB_VERSION)));
        msg.setText(m);
        msg.exec();
    }

    void Database::ExecuteSQLStatementWithoutReturnValue(std::stringstream const& ss) const
    {
        sqlite3* db;
        sqlite3_open(openProfile.c_str(), &db);
        std::string const& tmp = ss.str();
        sqlite3_exec(db, tmp.c_str(), nullptr, 0, 0);
        sqlite3_close(db);
    }

    void Database::ExecuteSQLStatementWithReturnValue(std::stringstream const& ss, CallbackFunction callback, void* data) const
    {
        sqlite3* db;
        sqlite3_open(openProfile.c_str(), &db);
        std::string const& tmp = ss.str();
        sqlite3_exec(db, tmp.c_str(), callback, data, 0);
        sqlite3_close(db);
    }
}
