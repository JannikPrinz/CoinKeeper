#pragma once

#include <filesystem>
#include <string>
#include <QColor>
#include <qdatetime.h>
#include <tuple>
#include <vector>

#include "DataClasses/transaction.h"

enum class Options
{
    DB_Version = 1
};

static const int32_t LATEST_DB_VERSION = 2;

/*        german characters, UTF-8 octal coded:
-----------------------------------------------------------------------------
    ä : \303\244
    ö : \303\266
    ü : \303\274
    Ä : \303\204
    Ö : \303\226
    Ü : \303\234
    ß : \303\237
-----------------------------------------------------------------------------
*/

static const std::string DATABASE_FILETYPE = "ckdb";
static const std::string ALTER_DB_FROM_VERSION_1_TO_2 = "PRAGMA foreign_keys = ON; ALTER TABLE Transactions ADD COLUMN ConnectedTransactionID INTEGER REFERENCES Transactions (TransactionID);";
static const std::string CREATE_TABLES_OF_A_PROFILE = "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS Accounts (AccountID INTEGER PRIMARY KEY, Name TEXT, VK INTEGER, NK INTEGER); CREATE TABLE IF NOT EXISTS Labels (LabelID INTEGER PRIMARY KEY, Name TEXT, Color INTEGER); CREATE TABLE IF NOT EXISTS Transactions (TransactionID INTEGER PRIMARY KEY, Description TEXT, VK INTEGER, NK INTEGER, Day INTEGER, Month INTEGER, Year INTEGER, AccountID INTEGER REFERENCES Accounts (AccountID), LabelID INTEGER REFERENCES Labels (LabelID), ConnectedTransactionID INTEGER REFERENCES Transactions (TransactionID)); CREATE TABLE IF NOT EXISTS Options (OptionID INTEGER PRIMARY KEY, OptionValue TEXT); CREATE TABLE IF NOT EXISTS StandingOrders (OrderID INTEGER PRIMARY KEY, AccountID INTEGER REFERENCES Accounts (AccountID), LabelID INTEGER REFERENCES Labels (LabelID), VK INTEGER, NK INTEGER, Description TEXT, OrderType INTEGER, NextDate INTEGER);";
static const std::string INSERT_DEFAULT_VALUES = std::string("PRAGMA foreign_keys = ON; INSERT INTO Labels (LabelID, Name, Color) VALUES (1, \"Default\", -1); INSERT INTO Accounts (Name, VK, NK) VALUES (\"Bargeld\", 0, 0); INSERT INTO Options (OptionID, OptionValue) VALUES (") + std::to_string(static_cast<int32_t>(Options::DB_Version)) + ", \"" + std::to_string(LATEST_DB_VERSION) + "\");";
static const std::string INSERT_NEW_ACCOUNT_PART_1 = "PRAGMA foreign_keys = ON; INSERT INTO Accounts (Name, VK, NK) VALUES (\"";
static const std::string INSERT_NEW_ACCOUNT_PART_2 = "\", ";
static const std::string INSERT_NEW_ACCOUNT_PART_3 = ", ";
static const std::string INSERT_NEW_ACCOUNT_PART_4 = ");";
static const std::string INSERT_NEW_OPTION_PART_1 = "PRAGMA foreign_keys = ON; INSERT INTO Options (OptionID, OptionValue) VALUES (";
static const std::string INSERT_NEW_OPTION_PART_2 = ", \"";
static const std::string INSERT_NEW_OPTION_PART_3 = "\");";
static const std::string INSERT_NEW_TRANSACTION_PART_1 = "PRAGMA foreign_keys = ON; INSERT INTO Transactions (Description, VK, NK, Day, Month, Year, AccountID, LabelID) VALUES (\"";
static const std::string INSERT_NEW_TRANSACTION_PART_2 = "\", ";
static const std::string INSERT_NEW_TRANSACTION_PART_3_TO_8 = ", ";
static const std::string INSERT_NEW_TRANSACTION_PART_9 = ");";
static const std::string INSERT_NEW_STANDING_ORDER_PART_1 = "PRAGMA foreign_keys = ON; INSERT INTO StandingOrders (AccountID, LabelID, VK, NK, Description, OrderType, NextDate) VALUES (";
static const std::string INSERT_NEW_STANDING_ORDER_PART_2_TO_4 = ", ";
static const std::string INSERT_NEW_STANDING_ORDER_PART_5 = ", \"";
static const std::string INSERT_NEW_STANDING_ORDER_PART_6 = "\", ";
static const std::string INSERT_NEW_STANDING_ORDER_PART_7 = ", ";
static const std::string INSERT_NEW_STANDING_ORDER_PART_8 = ");";
static const std::string INSERT_NEW_LABEL_PART_1 = "PRAGMA foreign_keys = ON; INSERT INTO Labels (Name, Color) VALUES (\"";
static const std::string INSERT_NEW_LABEL_PART_2 = "\", ";
static const std::string INSERT_NEW_LABEL_PART_3 = ");";
static const std::string DELETE_ACCOUNT_PART_1 = "PRAGMA foreign_keys = ON; DELETE FROM Transactions WHERE AccountID IS ";
static const std::string DELETE_ACCOUNT_PART_2 = "; DELETE FROM StandingOrders WHERE AccountID IS ";
static const std::string DELETE_ACCOUNT_PART_3 = "; DELETE FROM Accounts WHERE AccountID IS ";
static const std::string DELETE_ACCOUNT_PART_4 = ";";
static const std::string DELETE_LABEL_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Transactions SET LabelID = 1 WHERE LabelID IS ";
static const std::string DELETE_LABEL_PART_2 = "; UPDATE StandingOrders SET LabelID = 1 WHERE LabelID IS ";
static const std::string DELETE_LABEL_PART_3 = "; DELETE FROM Labels WHERE LabelID IS ";
static const std::string DELETE_LABEL_PART_4 = ";";
static const std::string DELETE_STANDING_ORDER_PART_1 = "PRAGMA foreign_keys = ON; DELETE FROM StandingOrders WHERE OrderID IS ";
static const std::string DELETE_STANDING_ORDER_PART_2 = ";";
static const std::string DELETE_TRANSACTION_PART_1 = "PRAGMA foreign_keys = ON; DELETE FROM Transactions WHERE TransactionID IS ";
static const std::string DELETE_TRANSACTION_PART_2 = ";";
static const std::string GET_ALL_ACCOUNTS = "PRAGMA foreign_keys = ON; SELECT * FROM Accounts;";
static const std::string GET_ALL_LABELS = "PRAGMA foreign_keys = ON; SELECT * FROM Labels;";
static const std::string GET_ALL_STANDING_ORDERS = "PRAGMA foreign_keys = ON; SELECT * FROM StandingOrders;";
static const std::string GET_ACCOUNT_VALUE_PART_1 = "PRAGMA foreign_keys = ON; SELECT VK, NK FROM Accounts WHERE AccountID IS ";
static const std::string GET_ACCOUNT_VALUE_PART_2 = ";";
static const std::string GET_EXECUTABLE_STANDING_ORDERS_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM StandingOrders WHERE NextDate <= ";
static const std::string GET_EXECUTABLE_STANDING_ORDERS_PART_2 = ";";
static const std::string GET_MAX_TRANSACTION_ID = "PRAGMA foreign_keys = ON; SELECT MAX(TransactionID) FROM Transactions;";
static const std::string GET_OPTION_PART_1 = "PRAGMA foreign_keys = ON; SELECT OptionValue FROM Options WHERE OptionID IS ";
static const std::string GET_OPTION_PART_2 = ";";
static const std::string GET_TRANSACTION_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE TransactionID IS ";
static const std::string GET_TRANSACTION_PART_2 = ";";
static const std::string GET_TRANSACTIONS_M_Y_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Month IS ";
static const std::string GET_TRANSACTIONS_M_Y_PART_2 = " AND Year IS ";
static const std::string GET_TRANSACTIONS_M_Y_PART_3 = ";";
static const std::string GET_TRANSACTIONS_Y_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Year IS ";
static const std::string GET_TRANSACTIONS_Y_PART_2 = ";";
static const std::string GET_TRANSACTIONS_M_Y_A_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Month IS ";
static const std::string GET_TRANSACTIONS_M_Y_A_PART_2 = " AND Year IS ";
static const std::string GET_TRANSACTIONS_M_Y_A_PART_3 = " AND AccountID IS ";
static const std::string GET_TRANSACTIONS_M_Y_A_PART_4 = ";";
static const std::string GET_TRANSACTIONS_Y_A_PART_1 = "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Year IS ";
static const std::string GET_TRANSACTIONS_Y_A_PART_2 = " AND AccountID IS ";
static const std::string GET_TRANSACTIONS_Y_A_PART_3 = ";";
static const std::string UPDATE_ACCOUNT_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Accounts SET Name = \"";
static const std::string UPDATE_ACCOUNT_PART_2 = "\", VK = ";
static const std::string UPDATE_ACCOUNT_PART_3 = ", NK = ";
static const std::string UPDATE_ACCOUNT_PART_4 = " WHERE AccountID IS ";
static const std::string UPDATE_ACCOUNT_PART_5 = ";";
static const std::string UPDATE_ACCOUNT_VALUE_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Accounts SET VK = ";
static const std::string UPDATE_ACCOUNT_VALUE_PART_2 = ", NK = ";
static const std::string UPDATE_ACCOUNT_VALUE_PART_3 = " WHERE AccountID IS ";
static const std::string UPDATE_ACCOUNT_VALUE_PART_4 = ";";
static const std::string UPDATE_CONNECTED_TRANSACTION_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Transactions SET ConnectedTransactionID = ";
static const std::string UPDATE_CONNECTED_TRANSACTION_PART_2 = " WHERE TransactionID IS ";
static const std::string UPDATE_CONNECTED_TRANSACTION_PART_3 = ";";
static const std::string UPDATE_LABEL_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Labels SET Name = \"";
static const std::string UPDATE_LABEL_PART_2 = "\", Color = ";
static const std::string UPDATE_LABEL_PART_3 = " WHERE LabelID IS ";
static const std::string UPDATE_LABEL_PART_4 = ";";
static const std::string UPDATE_OPTION_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Options SET OptionValue = \"";
static const std::string UPDATE_OPTION_PART_2 = "\" WHERE OptionID IS ";
static const std::string UPDATE_OPTION_PART_3 = ";";
static const std::string UPDATE_STANDING_ORDER_PART_1 = "PRAGMA foreign_keys = ON; UPDATE StandingOrders SET AccountID = ";
static const std::string UPDATE_STANDING_ORDER_PART_2 = ", LabelID = ";
static const std::string UPDATE_STANDING_ORDER_PART_3 = ", VK = ";
static const std::string UPDATE_STANDING_ORDER_PART_4 = ", NK = ";
static const std::string UPDATE_STANDING_ORDER_PART_5 = ", Description = \"";
static const std::string UPDATE_STANDING_ORDER_PART_6 = "\", OrderType = ";
static const std::string UPDATE_STANDING_ORDER_PART_7 = ", NextDate = ";
static const std::string UPDATE_STANDING_ORDER_PART_8 = " WHERE OrderID IS ";
static const std::string UPDATE_STANDING_ORDER_PART_9 = ";";
static const std::string UPDATE_STANDING_ORDER_DATE_PART_1 = "PRAGMA foreign_keys = ON; UPDATE StandingOrders SET NextDate = ";
static const std::string UPDATE_STANDING_ORDER_DATE_PART_2 = " WHERE OrderID IS ";
static const std::string UPDATE_STANDING_ORDER_DATE_PART_3 = ";";
static const std::string UPDATE_TRANSACTION_PART_1 = "PRAGMA foreign_keys = ON; UPDATE Transactions SET Description = \"";
static const std::string UPDATE_TRANSACTION_PART_2 = "\", VK = ";
static const std::string UPDATE_TRANSACTION_PART_3 = ", NK = ";
static const std::string UPDATE_TRANSACTION_PART_4 = ", Day = ";
static const std::string UPDATE_TRANSACTION_PART_5 = ", Month = ";
static const std::string UPDATE_TRANSACTION_PART_6 = ", Year = ";
static const std::string UPDATE_TRANSACTION_PART_7 = ", AccountID = ";
static const std::string UPDATE_TRANSACTION_PART_8 = ", LabelID = ";
static const std::string UPDATE_TRANSACTION_PART_9 = " WHERE TransactionID IS ";
static const std::string UPDATE_TRANSACTION_PART_10 = ";";
static const std::string ACCOUNTS_ID = "AccountID";
static const std::string ACCOUNTS_NAME = "Name";
static const std::string ACCOUNTS_VK = "VK";
static const std::string ACCOUNTS_NK = "NK";
static const std::string TRANSACTIONS_ID = "TransactionID";
static const std::string TRANSACTIONS_DESCRIPTION = "Description";
static const std::string TRANSACTIONS_VK = "VK";
static const std::string TRANSACTIONS_NK = "NK";
static const std::string TRANSACTIONS_DAY = "Day";
static const std::string TRANSACTIONS_MONTH = "Month";
static const std::string TRANSACTIONS_YEAR = "Year";
static const std::string TRANSACTION_CONNECTED_TRANSACTION_ID = "ConnectedTransactionID";
static const std::string LABEL_ID = "LabelID";
static const std::string LABEL_NAME = "Name";
static const std::string LABEL_COLOR = "Color";
static const std::string STANDING_ORDER_ID = "OrderID";
static const std::string STANDING_ORDER_VK = "VK";
static const std::string STANDING_ORDER_NK = "NK";
static const std::string STANDING_ORDER_DESCRIPTION = "Description";
static const std::string STANDING_ORDER_TYPE = "OrderType";
static const std::string STANDING_ORDER_DATE = "NextDate";
static const std::string OPTION_VALUE = "OptionValue";
static const std::string TEXT_ACCOUNT_NAME_NEEDED = "Bitte geben Sie einen Namen f\303\274r das Konto an.";
static const std::string TEXT_ADDED_TRANSACTIONS_PART_1 = "Es wurden ";
static const std::string TEXT_ADDED_TRANSACTIONS_PART_2 = " Transaktionen durch Dauerauftr\303\244ge hinzugef\303\274gt.";
static const std::string TEXT_ALL_ACCOUNTS = "Alle Konten";
static const std::string TEXT_CHANGE_ACCOUNT = "Konto \303\244ndern";
static const std::string TEXT_CHANGE_LABEL = "Kategorie \303\244ndern";
static const std::string TEXT_CHANGE_PROFILE_NAME = "Profilnamen \303\244ndern";
static const std::string TEXT_CHANGE_STANDING_ORDER = "Dauerauftrag \303\244ndern";
static const std::string TEXT_CHANGE_TRANSACTION = "Transaktion \303\244ndern";
static const std::string TEXT_CONFIRMATION_REMOVE_CONNECTED_ACCOUNT_ON_ACCOUNT_CHANGE_ON_TRANSACTION_CHANGE = "Bei dieser Transaktion besteht eine Verbindung zu einer anderen Transaktion. Da ein anderes Konto ausgew\303\244hlt ist, wird diese Verbindung entfernt.";
static const std::string TEXT_CHOOSE_ACCOUNT_FOR_STANDING_ORDER = "Bitte w\303\244hlen Sie ein Konto aus, auf dem die Transaktionen des Dauerauftrags ausgef\303\274hrt werden soll.";
static const std::string TEXT_CHOOSE_ACCOUNT_FOR_TRANSACTION = "Bitte w\303\244hlen Sie ein Konto aus, auf dem die Transaktion ausgef\303\274hrt werden soll.";
static const std::string TEXT_CHOOSE_CONNECTED_ACCOUNT_FOR_TRANSACTION = "Bitte w\303\244hlen Sie ein verbundenes Konto aus, auf dem die entgegengesetzte Transaktion ausgef\303\274hrt werden soll.";
static const std::string TEXT_CHOOSE_COLOR = "Farbe ausw\303\244hlen";
static const std::string TEXT_CREATE_NEW_LABEL = "Neue Kategorie erstellen";
static const std::string TEXT_CREATE_NEW_PROFILE = "Neues Profil erstellen";
static const std::string TEXT_DB_VERSION_NOT_SUPPORTED_PART_1 = "Datenbankversion des Profils: ";
static const std::string TEXT_DB_VERSION_NOT_SUPPORTED_PART_2 = "\nMaximal in dieser Programmversion unterst\303\274tzte Version: ";
static const std::string TEXT_DB_VERSION_UPDATED = "Die Datenbankversion des Profils wurde geupdated zu Version ";
static const std::string TEXT_DEFAULT_LABEL_NOT_DELETABLE = "Die default-Kategorie kann nicht gel\303\266scht werden.";
static const std::string TEXT_NAME_ENTRY = "Name:";
static const std::string TEXT_PROFILE_NAME_ENTRY = "Profilname:";
static const std::string TEXT_QUESTION_MODIFY_CONNECTED_TRANSACTION = "Mit dieser Transaktion ist eine weitere Transaktion verbunden. Soll diese ebenfalls ge\303\244ndert werden?\nFalls nicht, wird diese Verbindung entfernt.";
static const std::string TEXT_QUESTION_MODIFY_ACCOUNT_ON_TRANSACTION_DELETION = "Die Transaktion wird gel\303\266scht.\nSoll die \303\204nderung des entsprechenden Kontos auch r\303\274ckg\303\244ngig gemacht werden?";
static const std::string TEXT_QUESTION_DELETE_ACCOUNT_AND_ALL_CORRESPONDING_TRANSACTIONS_AND_STANDING_ORDERS = "Wollen Sie wirklich das ausgew\303\244hlte Konto und alle damit verbundenen Transaktionen und Dauerauftr\303\244ge l\303\266schen?";
static const std::string TEXT_QUESTION_DELETE_CONNECTED_TRANSACTION = "Mit dieser Transaktion ist eine weitere Transaktion verbunden. Soll diese ebenfalls gel\303\266scht werden?";
static const std::string TEXT_QUESTION_DELETE_LABEL = "Wollen Sie die ausgew\303\244hlte Kategorie l\303\266schen? Verbundene Transaktionen und Dauerauftr\303\244ge werden auf die default-Kategorie gesetzt.";
static const std::string TEXT_QUESTION_DELETE_PROFILE = "Wollen Sie das ausgew\303\244hlte Profil l\303\266schen?";
static const std::string TEXT_QUESTION_DELETE_STANDING_ORDER = "Wollen Sie den ausgew\303\244hlten Dauerauftrag l\303\266schen? Erzeugte Transaktionen werden nicht gel\303\266scht.";
static const std::string TEXT_STANDING_ORDER_EVERY_DAY = "Jeden Tag";
static const std::string TEXT_STANDING_ORDER_EVERY_WEEK = "Jede Woche";
static const std::string TEXT_STANDING_ORDER_EVERY_MONTH = "Jeden Monat";
static const std::string TEXT_STANDING_ORDER_EVERY_QUARTER = "Jedes Quartal";
static const std::string TEXT_STANDING_ORDER_EVERY_4_MONTHS = "Alle 4 Monate";
static const std::string TEXT_STANDING_ORDER_EVERY_YEAR = "Jedes Jahr";
constexpr unsigned int RED_BIT_MASK   = 0b11111111000000000000000000000000;
constexpr unsigned int GREEN_BIT_MASK = 0b00000000111111110000000000000000;
constexpr unsigned int BLUE_BIT_MASK  = 0b00000000000000001111111100000000;
constexpr unsigned int ALPHA_BIT_MASK = 0b00000000000000000000000011111111;

enum class Presenters
{
    ProfileChooser, CoinKeeper
};

const int NUMBER_OF_STANDING_ORDER_TYPES = 6;
enum class StandingOrderType
{
    EveryDay = 0, EveryWeek = 1, EveryMonth = 2, EveryQuarter = 3, Every4Months = 4, EveryYear = 5
};

static std::string GetStringFromStandingOrderType(StandingOrderType type)
{
    switch (type)
    {
    case StandingOrderType::EveryDay:
        return TEXT_STANDING_ORDER_EVERY_DAY;
        break;
    case StandingOrderType::EveryWeek:
        return TEXT_STANDING_ORDER_EVERY_WEEK;
        break;
    case StandingOrderType::EveryMonth:
        return TEXT_STANDING_ORDER_EVERY_MONTH;
        break;
    case StandingOrderType::EveryQuarter:
        return TEXT_STANDING_ORDER_EVERY_QUARTER;
        break;
    case StandingOrderType::Every4Months:
        return TEXT_STANDING_ORDER_EVERY_4_MONTHS;
        break;
    case StandingOrderType::EveryYear:
        return TEXT_STANDING_ORDER_EVERY_YEAR;
        break;
    default:
        return "";
        break;
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Color-functions:

/*
 * This function converts 4 integer containing values in the range [0..255] representing a RGBA-color into one integer.
 *
 * Parameters:
 * const int& red : integer representing red value of the color
 * const int& green : integer representing blue value of the color
 * const int& blue : integer representing blue value of the color
 * const int& alpha : integer representing alpha value of the color
 *
 * Returns:
 * One integer, holding all 4 input-values.
 */
static int ConvertRGBAToInt(const int& red, const int& green, const int& blue, const int& alpha)
{
    return alpha | (blue << 8) | (green << 16) | (red << 24);
}

/*
 * This function converts one integer, holding RGBA-Values, into a tuple of 4 integer,
 * where each integer represents either the red-, green-, blue- or alpha-value.
 *
 * Parameters:
 * const int& color : integer, containing all 4 RGBA-Values using 8 bit for each
 *
 * Returns:
 * A tuple of 4 integers holding the red-, green-, blue- and alpha-value
 */
static std::tuple<int, int, int, int> ConvertIntToRGBA(const int& color)
{
    unsigned int uColor = color;
    int r, g, b, a;
    r = (uColor & RED_BIT_MASK) >> 24;
    g = (uColor & GREEN_BIT_MASK) >> 16;
    b = (uColor & BLUE_BIT_MASK) >> 8;
    a = uColor & ALPHA_BIT_MASK;
    return std::make_tuple(r, g, b, a);
}

/*
 * This function converts one integer, holding RGBA-Values, into a QColor object.
 *
 * Parameters:
 * const int& color : integer, containing all 4 RGBA-Values using 8 bit for each
 *
 * Returns:
 * A QColor object, representing the input color.
 */
static QColor ConvertIntToQColor(const int& color)
{
    int r, g, b, a;
    std::tie(r, g, b, a) = ConvertIntToRGBA(color);
    return QColor(r, g, b, a);
}

// vector of tuples with the id of the transaction, string with the description, Value, date, id of the account, id of the label
using TransactionVector = std::vector<DataClasses::Transaction>;
// TODO: Add data classes for Account, Label, StandingOrder
using AccountVector = std::vector<std::tuple<int, std::string, DataClasses::Value>>;
using LabelVector = std::vector<std::tuple<int, std::string, int>>;
using StandingOrderVector = std::vector<std::tuple<int, int, int, DataClasses::Value, std::string, StandingOrderType, QDate>>;
using ProfileVector = std::vector<std::pair<std::string, std::filesystem::path>>;
