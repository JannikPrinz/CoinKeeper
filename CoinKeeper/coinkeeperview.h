#pragma once
#include <QTimer>
#include <qdatetime.h>
#include <qstringlistmodel.h>

#include "constants.h"
#include "ui_coinkeeper.h"

class CoinKeeperView : public QMainWindow {
    Q_OBJECT

public:
    CoinKeeperView(QWidget* parent = Q_NULLPTR);
    ~CoinKeeperView();
    /*
     * Fills the table which represents the existing accounts with the given accounts
     *
     * Parameters:
     * vector<tuple<int, string, Value>> accounts : vector of accounts, which are represented as tuples with the AccountID, AccountName, AccountValue
     */
    void FillAccountData(AccountVector const& accounts);
    /* 
     * Fills the table which represents transactions with the given transactions. Also this method calculates the sum 
     * of the values of the given transactions and displays the result.
     * 
     * Parameters:
     * const vector<tuple<int, string, Value, QDate, int, int>>& transactions : vector of transactions, which are represented as tuples with the date,
     * name of the label, color of the label, TransactionDescription, value of the transaction
     */
    void FillTransactionData(std::vector<std::tuple<QDate, std::string, int, std::string, Value>> const& transactions);
    /*
     * This method returns the index of the combobox of the selected month
     *
     * Returns: the index of the combobox of the selected month
     */
    [[nodiscard]]
    int GetSelectedMonth();
    /*
     * This method returns the selected year in the spinBox
     *
     * Returns: the selected year in the spinBox
     */
    [[nodiscard]]
    int GetSelectedYear();
    /*
     * This method returns the index of the combobox of the selected account
     *
     * Returns: the index of the combobox of the selected account
     */
    [[nodiscard]]
    int GetSelectedAccount();
    /*
     * Fills the combobox, which lists all accounts, with the given content
     *
     * Parameters:
     * QStringListModel* model : contains the items, which are set to the combobox
     */
    void setComboboxAccountValues(QStringListModel* model);
    /*
     * Returns: The selected row of the table, which shows transactions
     */
    [[nodiscard]]
    int GetSelectedRowTableMonthOverview();
    /*
     * Returns: The selected row of the table, which shows accounts
     */
    [[nodiscard]]
    int GetSelectedRowTableAccounts();

private:
    void CreateConnections();
    void UpdateEnableButtonsTableMonthOverview();
    void UpdateEnableButtonsTableAccounts();

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
    std::unique_ptr<QTimer> timer;
    QDateTime date;
};
