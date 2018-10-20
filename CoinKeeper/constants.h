#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <qcolor.h>
#include <tuple>

/*		german characters, UTF-8 octal coded:
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

#define DATABASE_FILETYPE "ckdb"
#define CREATE_TABLES_OF_A_PROFILE {"PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS Accounts (AccountID INTEGER PRIMARY KEY, Name TEXT, VK INTEGER, NK INTEGER); CREATE TABLE IF NOT EXISTS Labels (LabelID INTEGER PRIMARY KEY, Name TEXT, Color INTEGER); CREATE TABLE IF NOT EXISTS Transactions (TransactionID INTEGER PRIMARY KEY, Description TEXT, VK INTEGER, NK INTEGER, Day INTEGER, Month INTEGER, Year INTEGER, AccountID INTEGER REFERENCES Accounts (AccountID), LabelID INTEGER REFERENCES Labels (LabelID)); CREATE TABLE IF NOT EXISTS Options (OptionID INTEGER PRIMARY KEY, OptionValue TEXT); CREATE TABLE IF NOT EXISTS StandingOrders (OrderID INTEGER PRIMARY KEY, AccountID INTEGER REFERENCES Accounts (AccountID), LabelID INTEGER REFERENCES Labels (LabelID), VK INTEGER, NK INTEGER, Description TEXT, OrderType INTEGER, NextDate INTEGER);"}
#define INSERT_DEFAULT_VALUES "PRAGMA foreign_keys = ON; INSERT INTO Labels (LabelID, Name, Color) VALUES (1, \"Default\", -1); INSERT INTO Accounts (Name, VK, NK) VALUES (\"Bargeld\", 0, 0);"
#define INSERT_NEW_ACCOUNT_PART_1 "PRAGMA foreign_keys = ON; INSERT INTO Accounts (Name, VK, NK) VALUES (\""
#define INSERT_NEW_ACCOUNT_PART_2 "\", "
#define INSERT_NEW_ACCOUNT_PART_3 ", "
#define INSERT_NEW_ACCOUNT_PART_4 ");"
#define INSERT_NEW_TRANSACTION_PART_1 "PRAGMA foreign_keys = ON; INSERT INTO Transactions (Description, VK, NK, Day, Month, Year, AccountID, LabelID) VALUES (\""
#define INSERT_NEW_TRANSACTION_PART_2 "\", "
#define INSERT_NEW_TRANSACTION_PART_3_TO_8 ", "
#define INSERT_NEW_TRANSACTION_PART_9 ");"
#define INSERT_NEW_STANDING_ORDER_PART_1 "PRAGMA foreign_keys = ON; INSERT INTO StandingOrders (AccountID, LabelID, VK, NK, Description, OrderType, NextDate) VALUES ("
#define INSERT_NEW_STANDING_ORDER_PART_2_TO_4 ", "
#define INSERT_NEW_STANDING_ORDER_PART_5 ", \""
#define INSERT_NEW_STANDING_ORDER_PART_6 "\", "
#define INSERT_NEW_STANDING_ORDER_PART_7 ", "
#define INSERT_NEW_STANDING_ORDER_PART_8 ");"
#define INSERT_NEW_LABEL_PART_1 "PRAGMA foreign_keys = ON; INSERT INTO Labels (Name, Color) VALUES (\""
#define INSERT_NEW_LABEL_PART_2 "\", "
#define INSERT_NEW_LABEL_PART_3 ");"
#define DELETE_ACCOUNT_PART_1 "PRAGMA foreign_keys = ON; DELETE FROM Transactions WHERE AccountID IS "
#define DELETE_ACCOUNT_PART_2 "; DELETE FROM StandingOrders WHERE AccountID IS "
#define DELETE_ACCOUNT_PART_3 "; DELETE FROM Accounts WHERE AccountID IS "
#define DELETE_ACCOUNT_PART_4 ";"
#define DELETE_LABEL_PART_1 "PRAGMA foreign_keys = ON; UPDATE Transactions SET LabelID = 1 WHERE LabelID IS "
#define DELETE_LABEL_PART_2 "; UPDATE StandingOrders SET LabelID = 1 WHERE LabelID IS "
#define DELETE_LABEL_PART_3 "; DELETE FROM Labels WHERE LabelID IS "
#define DELETE_LABEL_PART_4 ";"
#define DELETE_STANDING_ORDER_PART_1 "PRAGMA foreign_keys = ON; DELETE FROM StandingOrders WHERE OrderID IS "
#define DELETE_STANDING_ORDER_PART_2 ";"
#define DELETE_TRANSACTION_PART_1 "PRAGMA foreign_keys = ON; DELETE FROM Transactions WHERE TransactionID IS "
#define DELETE_TRANSACTION_PART_2 ";"
#define GET_ALL_ACCOUNTS "PRAGMA foreign_keys = ON; SELECT * FROM Accounts;"
#define GET_ALL_LABELS "PRAGMA foreign_keys = ON; SELECT * FROM Labels;"
#define GET_ALL_STANDING_ORDERS "PRAGMA foreign_keys = ON; SELECT * FROM StandingOrders;"
#define GET_ACCOUNT_VALUE_PART_1 "PRAGMA foreign_keys = ON; SELECT VK, NK FROM Accounts WHERE AccountID IS "
#define GET_ACCOUNT_VALUE_PART_2 ";"
#define GET_EXECUTABLE_STANDING_ORDERS_PART_1 "PRAGMA foreign_keys = ON; SELECT * FROM StandingOrders WHERE NextDate <= "
#define GET_EXECUTABLE_STANDING_ORDERS_PART_2 ";"
#define GET_TRANSACTIONS_M_Y_PART_1 "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Month IS "
#define GET_TRANSACTIONS_M_Y_PART_2 " AND Year IS "
#define GET_TRANSACTIONS_M_Y_PART_3 ";"
#define GET_TRANSACTIONS_Y_PART_1 "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Year IS "
#define GET_TRANSACTIONS_Y_PART_2 ";"
#define GET_TRANSACTIONS_M_Y_A_PART_1 "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Month IS "
#define GET_TRANSACTIONS_M_Y_A_PART_2 " AND Year IS "
#define GET_TRANSACTIONS_M_Y_A_PART_3 " AND AccountID IS "
#define GET_TRANSACTIONS_M_Y_A_PART_4 ";"
#define GET_TRANSACTIONS_Y_A_PART_1 "PRAGMA foreign_keys = ON; SELECT * FROM Transactions WHERE Year IS "
#define GET_TRANSACTIONS_Y_A_PART_2 " AND AccountID IS "
#define GET_TRANSACTIONS_Y_A_PART_3 ";"
#define UPDATE_ACCOUNT_PART_1 "PRAGMA foreign_keys = ON; UPDATE Accounts SET Name = \""
#define UPDATE_ACCOUNT_PART_2 "\", VK = "
#define UPDATE_ACCOUNT_PART_3 ", NK = "
#define UPDATE_ACCOUNT_PART_4 " WHERE AccountID IS "
#define UPDATE_ACCOUNT_PART_5 ";"
#define UPDATE_ACCOUNT_VALUE_PART_1 "PRAGMA foreign_keys = ON; UPDATE Accounts SET VK = "
#define UPDATE_ACCOUNT_VALUE_PART_2 ", NK = "
#define UPDATE_ACCOUNT_VALUE_PART_3 " WHERE AccountID IS "
#define UPDATE_ACCOUNT_VALUE_PART_4 ";"
#define UPDATE_LABEL_PART_1 "PRAGMA foreign_keys = ON; UPDATE Labels SET Name = \""
#define UPDATE_LABEL_PART_2 "\", Color = "
#define UPDATE_LABEL_PART_3 " WHERE LabelID IS "
#define UPDATE_LABEL_PART_4 ";"
#define UPDATE_STANDING_ORDER_PART_1 "PRAGMA foreign_keys = ON; UPDATE StandingOrders SET AccountID = "
#define UPDATE_STANDING_ORDER_PART_2 ", LabelID = "
#define UPDATE_STANDING_ORDER_PART_3 ", VK = "
#define UPDATE_STANDING_ORDER_PART_4 ", NK = "
#define UPDATE_STANDING_ORDER_PART_5 ", Description = \""
#define UPDATE_STANDING_ORDER_PART_6 "\", OrderType = "
#define UPDATE_STANDING_ORDER_PART_7 ", NextDate = "
#define UPDATE_STANDING_ORDER_PART_8 " WHERE OrderID IS "
#define UPDATE_STANDING_ORDER_PART_9 ";"
#define UPDATE_STANDING_ORDER_DATE_PART_1 "PRAGMA foreign_keys = ON; UPDATE StandingOrders SET NextDate = "
#define UPDATE_STANDING_ORDER_DATE_PART_2 " WHERE OrderID IS "
#define UPDATE_STANDING_ORDER_DATE_PART_3 ";"
#define UPDATE_TRANSACTION_PART_1 "PRAGMA foreign_keys = ON; UPDATE Transactions SET Description = \""
#define UPDATE_TRANSACTION_PART_2 "\", VK = "
#define UPDATE_TRANSACTION_PART_3 ", NK = "
#define UPDATE_TRANSACTION_PART_4 ", Day = "
#define UPDATE_TRANSACTION_PART_5 ", Month = "
#define UPDATE_TRANSACTION_PART_6 ", Year = "
#define UPDATE_TRANSACTION_PART_7 ", AccountID = "
#define UPDATE_TRANSACTION_PART_8 ", LabelID = "
#define UPDATE_TRANSACTION_PART_9 " WHERE TransactionID IS "
#define UPDATE_TRANSACTION_PART_10 ";"
#define ACCOUNTS_ID "AccountID"
#define ACCOUNTS_NAME "Name"
#define ACCOUNTS_VK "VK"
#define ACCOUNTS_NK "NK"
#define TRANSACTIONS_ID "TransactionID"
#define TRANSACTIONS_DESCRIPTION "Description"
#define TRANSACTIONS_VK "VK"
#define TRANSACTIONS_NK "NK"
#define TRANSACTIONS_DAY "Day"
#define TRANSACTIONS_MONTH "Month"
#define TRANSACTIONS_YEAR "Year"
#define LABEL_ID "LabelID"
#define LABEL_NAME "Name"
#define LABEL_COLOR "Color"
#define STANDING_ORDER_ID "OrderID"
#define STANDING_ORDER_VK "VK"
#define STANDING_ORDER_NK "NK"
#define STANDING_ORDER_DESCRIPTION "Description"
#define STANDING_ORDER_TYPE "OrderType"
#define STANDING_ORDER_DATE "NextDate"
#define TEXT_ACCOUNT_NAME_NEEDED "Bitte geben Sie einen Namen f\303\274r das neue Konto an."
#define TEXT_ADDED_TRANSACTIONS_PART_1 "Es wurden "
#define TEXT_ADDED_TRANSACTIONS_PART_2 " Transaktionen durch Dauerauftr\303\244ge hinzugef\303\274gt."
#define TEXT_ALL_ACCOUNTS "Alle Konten"
#define TEXT_CHANGE_ACCOUNT "Konto \303\244ndern"
#define TEXT_CHANGE_LABEL "Kategorie \303\244ndern"
#define TEXT_CHANGE_STANDING_ORDER "Dauerauftrag \303\244ndern"
#define TEXT_CHANGE_TRANSACTION "Transaktion \303\244ndern"
#define TEXT_CHOOSE_ACCOUNT_FOR_STANDING_ORDER "Bitte w\303\244hlen Sie ein Konto aus, auf dem die Transaktionen des Dauerauftrags ausgef\303\274hrt werden soll."
#define TEXT_CHOOSE_ACCOUNT_FOR_TRANSACTION "Bitte w\303\244hlen Sie ein Konto aus, auf dem die Transaktion ausgef\303\274hrt werden soll."
#define TEXT_CHOOSE_COLOR "Farbe ausw\303\244hlen"
#define TEXT_CREATE_NEW_LABEL "Neue Kategorie erstellen"
#define TEXT_DEFAULT_LABEL_NOT_DELETABLE "Die default-Kategorie kann nicht gel\303\266scht werden."
#define TEXT_NAME_COLON "Name:"
#define TEXT_QUESTION_MODIFY_ACCOUNT_AT_TRANSACTION_DELETION "Soll die \303\204nderung des entsprechenden Kontos auch r\303\274ckg\303\244ngig gemacht werden?"
#define TEXT_QUESTION_DELETE_ACCOUNT_AND_ALL_CORRESPONDING_TRANSACTIONS_AND_STANDING_ORDERS "Wollen Sie wirklich das ausgew\303\244hlte Konto und alle damit verbundenen Transaktionen und Dauerauftr\303\244ge l\303\266schen?"
#define TEXT_QUESTION_DELETE_LABEL "Wollen Sie die ausgew\303\244hlte Kategorie l\303\266schen? Verbundene Transaktionen und Dauerauftr\303\244ge werden auf die default-Kategorie gesetzt."
#define TEXT_QUESTION_DELETE_STANDING_ORDER "Wollen Sie den ausgew\303\244hlten Dauerauftrag l\303\266schen? Erzeugte Transaktionen werden nicht gel\303\266scht."
#define TEXT_STANDING_ORDER_EVERY_DAY "Jeden Tag"
#define TEXT_STANDING_ORDER_EVERY_WEEK "Jede Woche"
#define TEXT_STANDING_ORDER_EVERY_MONTH "Jeden Monat"
#define TEXT_STANDING_ORDER_EVERY_QUARTER "Jedes Quartal"
#define TEXT_STANDING_ORDER_EVERY_4_MONTHS "Alle 4 Monate"
#define TEXT_STANDING_ORDER_EVERY_YEAR "Jedes Jahr"
#define RED_BIT_MASK	0b11111111000000000000000000000000
#define GREEN_BIT_MASK	0b00000000111111110000000000000000
#define BLUE_BIT_MASK	0b00000000000000001111111100000000
#define ALPHA_BIT_MASK	0b00000000000000000000000011111111

enum Presenters
{
	ProfileChooser, CoinKeeper
};

const int NUMBER_OF_STANDING_ORDER_TYPES = 6;
enum StandingOrderType
{
	EveryDay = 0, EveryWeek = 1, EveryMonth = 2, EveryQuarter = 3, Every4Months = 4, EveryYear = 5
};

static std::string GetStringFromStandingOrderType(StandingOrderType type)
{
	switch (type)
	{
	case EveryDay:
		return TEXT_STANDING_ORDER_EVERY_DAY;
		break;
	case EveryWeek:
		return TEXT_STANDING_ORDER_EVERY_WEEK;
		break;
	case EveryMonth:
		return TEXT_STANDING_ORDER_EVERY_MONTH;
		break;
	case EveryQuarter:
		return TEXT_STANDING_ORDER_EVERY_QUARTER;
		break;
	case Every4Months:
		return TEXT_STANDING_ORDER_EVERY_4_MONTHS;
		break;
	case EveryYear:
		return TEXT_STANDING_ORDER_EVERY_YEAR;
		break;
	default:
		return "";
		break;
	}
}

struct Value
{
	int VK;
	int NK;

	/*
		Creates a new instance with the given parameters.
		int vk0 : value before the comma (default = 0)
		int nk0 : value after the comma. Should be >= 0 and < 100 (default = 0)
	*/
	Value(int vk0 = 0, int nk0 = 0) : VK(vk0), NK(nk0) {}

	std::string ToString()
	{
		std::string s = "";
		if (VK < 0 || (VK == 0 && NK < 0)) s.append("-");
		int v = (VK < 0) ? -VK : VK;
		std::string d = "";
		d = std::to_string(v % 10).append(d);
		v /= 10;
		int x = 0;
		while (v > 0)
		{
			if (x == 2) d = std::string(".").append(d);
			d = std::to_string(v % 10).append(d);
			v /= 10;
			x++;
			x %= 3;
		}
		s.append(d);
		s.append(",");
		if (NK < 0)
		{
			if (NK > -10) s.append("0");
			s.append(std::to_string(-NK));
		}
		else
		{
			if (NK < 10) s.append("0");
			s.append(std::to_string(NK));
		}
		return s;
	}

	Value operator +(const Value& a) const
	{
		int v1 = VK;
		int v2 = a.VK;
		int n1 = (VK < 0) ? -NK : NK;
		int n2 = (a.VK < 0) ? -a.NK : a.NK;
		int v = v1 + v2;
		int n = n1 + n2;
		if (n >= 100)
		{
			n -= 100;
			v += 1;
		}
		if (n <= -100)
		{
			n += 100;
			v -= 1;
		}
		if (v >= 0 && n >= 0) return Value(v, n);
		if (v < 0 && n <= 0) return Value(v, -n);
		if (v == 0 && n < 0) return Value(v, n);
		if (v > 0 && n < 0) return Value(v - 1, n + 100);
		if (v < 0 && n > 0)
		{
			v += 1;
			n = 100 - n;
			if (v == 0) n *= -1;
			return Value(v, n);
		}
	}

	//Value operator +(const Value& a) const
	//{
	//	int v1 = VK;
	//	int v2 = a.VK;
	//	int n1 = (VK < 0) ? -NK : NK;
	//	int n2 = (a.VK < 0) ? -a.NK : a.NK;
	//	int v = v1 + v2;
	//	int n = n1 + n2;
	//	if (v == 0)
	//	{
	//		if (n <= -100) return Value(-1, -(n + 100));
	//		if (n >= 100) return Value(1, n - 100);
	//		return Value(0, n);
	//	}
	//	else
	//	{
	//		if (n < 0)
	//		{
	//			if (n <= -100)
	//			{
	//				if (v == 1) return Value(0, n + 100);
	//				if (v < 0) return Value(v - 1, -(n + 100));
	//				return Value(v - 2, 200 + n);
	//			}
	//			else
	//			{
	//				if (v < 0) return Value(v, -n);
	//				return Value(v - 1, 100 + n);
	//			}
	//		}
	//		else
	//		{
	//			if (n >= 100)
	//			{
	//				if (v == -2) return Value(0, n - 200);
	//				if (v < -2) return Value(v + 1, 200 - n);
	//				return Value(v + 1, n - 100);
	//			}
	//			else
	//			{
	//				if (v == -1) return Value(0, n - 100);
	//				if (v < -1) return Value(v + 1, 100 - n);
	//				return Value(v, n);
	//			}
	//		}
	//	}
	//}

	Value operator *(const int& x) const
	{
		if (x >= 0)
		{
			int y = NK * x;
			return Value(VK * x + (y / 100), y % 100);
		}
		else
		{
			int y = (VK != 0) ? NK * x * (-1) : NK * x;
			return Value(-(VK * (-x) + (y / 100)), y % 100);
		}
	}

	Value operator *=(const int& x)
	{
		*this = *this * x;
		return *this;
	}

	Value operator +=(const Value& x)
	{
		*this = *this + x;
		return *this;
	}

	Value operator -(const Value& a) const
	{
		return *this + (a * (-1));
	}

	bool operator ==(const Value& a) const
	{
		return VK == a.VK && NK == a.NK;
	}

	bool operator !=(const Value& a) const
	{
		return !(*this == a);
	}

	bool operator <(const Value& a) const
	{
		if (VK < a.VK) return true;
		if (VK == a.VK && NK < a.NK) return true;
		return false;
	}

	bool operator <=(const Value& a) const
	{
		return (*this < a) || (*this == a);
	}

	bool operator >(const Value& a) const
	{
		return !(*this <= a);
	}

	bool operator >=(const Value& a) const
	{
		return !(*this < a);
	}
};

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

#endif // !CONSTANTS_H