#include "database.h"

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

void Database::CreateNewProfile(const char* fileName)
{
	sqlite3* db;
	string exPath = LPWSTRToString(ExePath());
	exPath.pop_back();
	exPath.append(string(fileName));
	exPath.append(".");
	exPath.append(DATABASE_FILETYPE);
	sqlite3_open(exPath.c_str(), &db);
	sqlite3_exec(db, CREATE_TABLES_OF_A_PROFILE, callback, 0, 0);
	sqlite3_exec(db, INSERT_DEFAULT_VALUES, callback, 0, 0);
	//if (rc != SQLITE_OK)
	//{
	//	qDebug("Fehler beim erstellen der Datanbank!");
	//}
	//else
	//{
	//	qDebug("Erstellen der Datenbank erfolgreich!");
	//}
	// Tests:
	//char* msg;
	//rc = sqlite3_exec(db, "INSERT INTO Accounts (Name, Balance) VALUES (\"Bargeld\", 100);", callback, 0, &msg);
	//rc = sqlite3_exec(db, "INSERT INTO Transactions (Description, Value, AccountID, LabelID) VALUES (\"Erste Einzahlung\", 100, 1, 1);", callback, 0, &msg);
	//rc = sqlite3_exec(db, "SELECT * FROM Transactions;", callback, 0, &msg);
	//if (rc != SQLITE_OK)
	//{
	//	qDebug("Fehler beim ausf�hren der SQL_Befehle! Fehlermeldung:");
	//	qDebug(msg);
	//}
	//else
	//{
	//	qDebug("Befehlsdurchf�hrung erfolgreich!");
	//}
	sqlite3_close(db);
}

//
//void Database::TestForeignKeys()
//{
//	sqlite3* db;
//	string exPath = LPWSTRToString(ExePath());
//	exPath.pop_back();
//	exPath.append(string("Test.ckdb"));
//	sqlite3_open(exPath.c_str(), &db);
//	char* zerrormsg = 0;
//	sqlite3_exec(db, "PRAGMA foreign_keys = ON;", callback, 0, &zerrormsg);
//	sqlite3_close(db);
//}

list<string> Database::GetDatabaseList()
{
	WIN32_FIND_DATA winFD;
	HANDLE hFind;
	list<string> names;
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

	string path = LPWSTRToString(executionPath);
	path.pop_back();
	return GetFilenames(names, path);
}

void Database::CreateNewAccount(const char* profile, string name, Value balance)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = INSERT_NEW_ACCOUNT_PART_1;
	ex.append(name);
	ex.append(INSERT_NEW_ACCOUNT_PART_2);
	ex.append(to_string(balance.VK));
	ex.append(INSERT_NEW_ACCOUNT_PART_3);
	ex.append(to_string(balance.NK));
	ex.append(INSERT_NEW_ACCOUNT_PART_4);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::CreateNewTransaction(const char* profile, const string& description, const int& account, const Value& value, const QDate& date, const int& labelID)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	// insert the new transaction:
	string ex = INSERT_NEW_TRANSACTION_PART_1;
	ex.append(description);
	ex.append(INSERT_NEW_TRANSACTION_PART_2);
	ex.append(to_string(value.VK));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(value.NK));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(date.day()));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(date.month()));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(date.year()));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(account));
	ex.append(INSERT_NEW_TRANSACTION_PART_3_TO_8);
	ex.append(to_string(labelID));
	ex.append(INSERT_NEW_TRANSACTION_PART_9);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
	UpdateAccountValue(profile, account, value);
}

void Database::CreateNewLabel(const char* profile, string name, int color)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = INSERT_NEW_LABEL_PART_1;
	ex.append(name);
	ex.append(INSERT_NEW_LABEL_PART_2);
	ex.append(to_string(color));
	ex.append(INSERT_NEW_LABEL_PART_3);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::CreateNewStandingOrder(const char* profile, const string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID, const int& orderType)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = INSERT_NEW_STANDING_ORDER_PART_1;
	ex.append(to_string(accountID));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
	ex.append(to_string(labelID));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
	ex.append(to_string(value.VK));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_2_TO_4);
	ex.append(to_string(value.NK));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_5);
	ex.append(description);
	ex.append(INSERT_NEW_STANDING_ORDER_PART_6);
	ex.append(to_string(orderType));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_7);
	ex.append(to_string(date.year() * 10000 + date.month() * 100 + date.day()));
	ex.append(INSERT_NEW_STANDING_ORDER_PART_8);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateLabel(const char* profile, int labelID, string name, int color)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = UPDATE_LABEL_PART_1;
	ex.append(name);
	ex.append(UPDATE_LABEL_PART_2);
	ex.append(to_string(color));
	ex.append(UPDATE_LABEL_PART_3);
	ex.append(to_string(labelID));
	ex.append(UPDATE_LABEL_PART_4);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateAccount(const char* profile, const int& accountID, const string& accountName, const Value& accountValue)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = UPDATE_ACCOUNT_PART_1;
	ex.append(accountName);
	ex.append(UPDATE_ACCOUNT_PART_2);
	ex.append(to_string(accountValue.VK));
	ex.append(UPDATE_ACCOUNT_PART_3);
	ex.append(to_string(accountValue.NK));
	ex.append(UPDATE_ACCOUNT_PART_4);
	ex.append(to_string(accountID));
	ex.append(UPDATE_ACCOUNT_PART_5);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateAccountValue(const char* profilePath, const int& accountID, const Value& value)
{
	sqlite3* db;
	sqlite3_open(profilePath, &db);
	// get value of account:
	string ex = GET_ACCOUNT_VALUE_PART_1;
	ex.append(to_string(accountID));
	ex.append(GET_ACCOUNT_VALUE_PART_2);
	Value v;
	tempAccountValue = v;
	sqlite3_exec(db, ex.c_str(), ProcessAccountValue, 0, 0);
	// update value of account:
	v = tempAccountValue + value;
	ex = UPDATE_ACCOUNT_VALUE_PART_1;
	ex.append(to_string(v.VK));
	ex.append(UPDATE_ACCOUNT_VALUE_PART_2);
	ex.append(to_string(v.NK));
	ex.append(UPDATE_ACCOUNT_VALUE_PART_3);
	ex.append(to_string(accountID));
	ex.append(UPDATE_ACCOUNT_VALUE_PART_4);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateStandingOrderDate(const char* profile, const int& orderID, const int& date)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = UPDATE_STANDING_ORDER_DATE_PART_1;
	ex.append(to_string(date));
	ex.append(UPDATE_STANDING_ORDER_DATE_PART_2);
	ex.append(to_string(orderID));
	ex.append(UPDATE_STANDING_ORDER_DATE_PART_3);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateStandingOrder(const char* profile, const int& orderID, const string& description, const int& accountID, const Value& value, const QDate& nextDate, const int& labelID, const int& orderType)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = UPDATE_STANDING_ORDER_PART_1;
	ex.append(to_string(accountID));
	ex.append(UPDATE_STANDING_ORDER_PART_2);
	ex.append(to_string(labelID));
	ex.append(UPDATE_STANDING_ORDER_PART_3);
	ex.append(to_string(value.VK));
	ex.append(UPDATE_STANDING_ORDER_PART_4);
	ex.append(to_string(value.NK));
	ex.append(UPDATE_STANDING_ORDER_PART_5);
	ex.append(description);
	ex.append(UPDATE_STANDING_ORDER_PART_6);
	ex.append(to_string(orderType));
	ex.append(UPDATE_STANDING_ORDER_PART_7);
	ex.append(to_string(nextDate.year() * 10000 + nextDate.month() * 100 + nextDate.day()));
	ex.append(UPDATE_STANDING_ORDER_PART_8);
	ex.append(to_string(orderID));
	ex.append(UPDATE_STANDING_ORDER_PART_9);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::UpdateTransaction(const char* profile, const int& transactionID, const string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = UPDATE_TRANSACTION_PART_1;
	ex.append(description);
	ex.append(UPDATE_TRANSACTION_PART_2);
	ex.append(to_string(value.VK));
	ex.append(UPDATE_TRANSACTION_PART_3);
	ex.append(to_string(value.NK));
	ex.append(UPDATE_TRANSACTION_PART_4);
	ex.append(to_string(date.day()));
	ex.append(UPDATE_TRANSACTION_PART_5);
	ex.append(to_string(date.month()));
	ex.append(UPDATE_TRANSACTION_PART_6);
	ex.append(to_string(date.year()));
	ex.append(UPDATE_TRANSACTION_PART_7);
	ex.append(to_string(accountID));
	ex.append(UPDATE_TRANSACTION_PART_8);
	ex.append(to_string(labelID));
	ex.append(UPDATE_TRANSACTION_PART_9);
	ex.append(to_string(transactionID));
	ex.append(UPDATE_TRANSACTION_PART_10);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::DeleteTransaction(const char* profile, const int& transactionID, const bool& changeAccountValue, const int& accountID, const Value& value)
{
	if (changeAccountValue)	UpdateAccountValue(profile, accountID, value);
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = DELETE_TRANSACTION_PART_1;
	ex.append(to_string(transactionID));
	ex.append(DELETE_TRANSACTION_PART_2);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::DeleteStandingOrder(const char* profile, const int& orderID)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = DELETE_STANDING_ORDER_PART_1;
	ex.append(to_string(orderID));
	ex.append(DELETE_STANDING_ORDER_PART_2);
	sqlite3_exec(db, ex.c_str(), callback, 0, 0);
	sqlite3_close(db);
}

void Database::DeleteAccount(const char* profile, const int& accountID)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = DELETE_ACCOUNT_PART_1;
	ex.append(to_string(accountID));
	ex.append(DELETE_ACCOUNT_PART_2);
	ex.append(to_string(accountID));
	ex.append(DELETE_ACCOUNT_PART_3);
	ex.append(to_string(accountID));
	ex.append(DELETE_ACCOUNT_PART_4);
	sqlite3_exec(db, ex.c_str(), callback, 0, ERRORMESSAGE);
	sqlite3_close(db);
	printErrMsg();
}

void Database::DeleteLabel(const char* profile, const int& labelID)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	string ex = DELETE_LABEL_PART_1;
	ex.append(to_string(labelID));
	ex.append(DELETE_LABEL_PART_2);
	ex.append(to_string(labelID));
	ex.append(DELETE_LABEL_PART_3);
	ex.append(to_string(labelID));
	ex.append(DELETE_LABEL_PART_4);
	sqlite3_exec(db, ex.c_str(), callback, 0, ERRORMESSAGE);
	sqlite3_close(db);
	printErrMsg();
}

vector<tuple<int, string, Value, QDate, int, int>> Database::GetTransactions(const char* profilePath, int month, int year)
{
	sqlite3* db;
	sqlite3_open(profilePath, &db);
	vector<tuple<int, string, Value, QDate, int, int>> trans;
	tempTransactions = trans;
	string ex;
	if (month == 0)		// show all transactions of the selected year
	{
		ex = GET_TRANSACTIONS_Y_PART_1;
		ex.append(to_string(year));
		ex.append(GET_TRANSACTIONS_Y_PART_2);
	}
	else
	{
		ex = GET_TRANSACTIONS_M_Y_PART_1;
		ex.append(to_string(month));
		ex.append(GET_TRANSACTIONS_M_Y_PART_2);
		ex.append(to_string(year));
		ex.append(GET_TRANSACTIONS_M_Y_PART_3);
	}
	sqlite3_exec(db, ex.c_str(), ProcessTransactionsInformation, 0, 0);
	sqlite3_close(db);
	return tempTransactions;
}

vector<tuple<int, string, Value, QDate, int, int>> Database::GetTransactions(const char* profilePath, int month, int year, int accountID)
{
	sqlite3* db;
	sqlite3_open(profilePath, &db);
	vector<tuple<int, string, Value, QDate, int, int>> trans;
	tempTransactions = trans;
	string ex;
	if (month == 0)		// show all transactions of the selected year
	{
		ex = GET_TRANSACTIONS_Y_A_PART_1;
		ex.append(to_string(year));
		ex.append(GET_TRANSACTIONS_Y_A_PART_2);
		ex.append(to_string(accountID));
		ex.append(GET_TRANSACTIONS_Y_A_PART_3);
	}
	else
	{
		ex = GET_TRANSACTIONS_M_Y_A_PART_1;
		ex.append(to_string(month));
		ex.append(GET_TRANSACTIONS_M_Y_A_PART_2);
		ex.append(to_string(year));
		ex.append(GET_TRANSACTIONS_M_Y_A_PART_3);
		ex.append(to_string(accountID));
		ex.append(GET_TRANSACTIONS_M_Y_A_PART_4);
	}
	sqlite3_exec(db, ex.c_str(), ProcessTransactionsInformation, 0, 0);
	sqlite3_close(db);
	return tempTransactions;
}

vector<tuple<int, string, Value>> Database::GetAccounts(const char* profilePath)
{
	sqlite3* db;
	sqlite3_open(profilePath, &db);
	vector<tuple<int, string, Value>> acc;
	tempAccounts = acc;
	sqlite3_exec(db, GET_ALL_ACCOUNTS, ProcessAccountInformation, 0, 0);
	sqlite3_close(db);
	return tempAccounts;
}

vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> Database::GetAllStandingOrders(const char* profile)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> orders;
	tempOrders = orders;
	sqlite3_exec(db, GET_ALL_STANDING_ORDERS, ProcessOrderInformation, 0, 0);
	sqlite3_close(db);
	return tempOrders;
}

vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> Database::GetExecutableStandingOrders(const char* profile, const int& date)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	vector<tuple<int, int, int, Value, string, StandingOrderType, QDate>> orders;
	tempOrders = orders;
	string ex = GET_EXECUTABLE_STANDING_ORDERS_PART_1;
	ex.append(to_string(date));
	ex.append(GET_EXECUTABLE_STANDING_ORDERS_PART_2);
	sqlite3_exec(db, ex.c_str(), ProcessOrderInformation, 0, 0);
	sqlite3_close(db);
	return tempOrders;
}

vector<tuple<int, string, int>> Database::GetLabels(const char* profile)
{
	sqlite3* db;
	sqlite3_open(profile, &db);
	vector<tuple<int, string, int>> labels;
	tempLabels = labels;
	sqlite3_exec(db, GET_ALL_LABELS, ProcessLabels, 0, 0);
	sqlite3_close(db);
	return tempLabels;
}

//static int GetIntFromChars(char* arg)
//{
//	int x = 0;
//	int result = 0;
//	while (arg[x] != '\0')
//	{
//		switch (arg[x])
//		{
//		case '0':
//			result *= 10;
//			result += 0;
//			break;
//		case '1':
//			result *= 10;
//			result += 1;
//			break;
//		case '2':
//			result *= 10;
//			result += 2;
//			break;
//		case '3':
//			result *= 10;
//			result += 3;
//			break;
//		case '4':
//			result *= 10;
//			result += 4;
//			break;
//		case '5':
//			result *= 10;
//			result += 5;
//			break;
//		case '6':
//			result *= 10;
//			result += 6;
//			break;
//		case '7':
//			result *= 10;
//			result += 7;
//			break;
//		case '8':
//			result *= 10;
//			result += 8;
//			break;
//		case '9':
//			result *= 10;
//			result += 9;
//			break;
//		default:
//			break;
//		}
//		x++;
//	}
//	return result;
//}

LPWSTR Database::ExePath()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string s = LPWSTRToString(buffer);
	string::size_type pos = s.find_last_of("\\/");
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
//	LPWSTR buff[260];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	return buf;
}

string Database::LPWSTRToString(LPWSTR lString)
{
	char ch[MAX_PATH];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, lString, -1, ch, MAX_PATH, &DefChar, NULL);
	return string(ch);
}

list<string> Database::GetFilenames(list<string> rawList, string path, string type)
{
	list<string> returnList;
	string typeW = string(".").append(type);
	for each (string s in rawList)
	{
		size_t pos = s.find(typeW);
		if (pos != string::npos)
		{
			returnList.push_back(s.substr(0, pos));
			string ss = path;
			ss.append(s);
			returnList.push_back(ss);
		}
	}
	return returnList;
}

Database::~Database()
{
}