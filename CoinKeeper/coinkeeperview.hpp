#pragma once
#ifndef COINKEEPERVIEW_HPP
#define COINKEEPERVIEW_HPP

#include <QWidget>
#include "ui_coinkeeper.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "constants.h"
#include <qstringlistmodel.h>

using namespace std;

class CoinKeeperView : public QMainWindow {
	Q_OBJECT

public:
	CoinKeeperView(QWidget * parent = Q_NULLPTR);
	/*
		Fills the table which represents the existing accounts with the given accounts
		vector<tuple<int, string, Value>> accounts : vector of accounts, which are represented as tuples with the AccountID, AccountName, AccountValue
	*/
	void FillAccountData(vector<tuple<int, string, Value>> accounts);
	/* 
	 * Fills the table which represents transactions with the given transactions. Also this method calculates the sum 
	 * of the values of the given transactions and displays the result.
	 * 
	 * Parameters:
	 * const vector<tuple<int, string, Value, QDate, int, int>>& transactions : vector of transactions, which are represented as tuples with the date,
	 * name of the label, color of the label, TransactionDescription, value of the transaction
	 */
	void FillTransactionData(const vector<tuple<QDate, string, int, string, Value>>& transactions);
	/*
		This method returns the indices of the comboboxes and the value of the spinBox (year), which set the content, which is displayed in the transaction table
		Returns: tuple of indices of the comboboxes (month, year, account)
	*/
	tuple<int, int, int> GetComboboxContent();
	/*
		Fills the combobox, which lists all accounts, with the given content
		QStringListModel* model : contains the items, which are set to the combobox
	*/
	void setComboboxAccountValues(QStringListModel* model);
	/*
		Returns: The selected row of the table, which shows transactions
	*/
	int GetSelectedRowTableMonthOverview();
	/*
		Returns: The selected row of the table, which shows accounts
	*/
	int GetSelectedRowTableAccounts();
	~CoinKeeperView();

signals:
	void ButtonChangeProfileClicked();
	void ButtonChangeAccountClicked();
	void ButtonCreateNewAccountClicked();
	void ButtonAddTransactionClicked();
	void ButtonDeleteTransactionClicked();
	void ButtonDeleteAccountClicked();
	void ButtonManageLabelsClicked();
	void ButtonManageStandingOrdersClicked();
	void ButtonUpdateTransactionClicked();
	void SelectionMonthYearAccountChanged();

public slots:
	void UpdateTime();

private:
	Ui::CoinKeeperClass ui;
	QTimer* timer;
	QDateTime date;
	void UpdateEnableButtonsTableMonthOverview();
	void UpdateEnableButtonsTableAccounts();
};

#endif // !COINKEEPERVIEW_HPP