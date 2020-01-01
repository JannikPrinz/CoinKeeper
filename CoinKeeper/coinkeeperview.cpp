#include "coinkeeperview.hpp"

CoinKeeperView::CoinKeeperView(QWidget * parent) : QMainWindow(parent) {
    ui.setupUi(this);
    ui.tableMonthOverview->setColumnWidth(2, 400);
    date = QDateTime::currentDateTime();
    ui.spinBoxYear->setValue(date.toString("yyyy").toInt());
    ui.comboBoxMonth->setCurrentIndex(date.date().month());
    UpdateTime();
    UpdateEnableButtonsTableMonthOverview();
    UpdateEnableButtonsTableAccounts();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CoinKeeperView::UpdateTime);
    timer->start(1000);
    connect(ui.buttonChangeProfile, &QPushButton::clicked, this, [=] { emit ButtonChangeProfileClicked(); });
    connect(ui.buttonModifyAccount, &QPushButton::clicked, this, [=] { emit ButtonChangeAccountClicked(); });
    connect(ui.buttonAddAccount, &QPushButton::clicked, this, [=] { emit ButtonCreateNewAccountClicked(); });
    connect(ui.buttonAddTransaction, &QPushButton::clicked, this, [=] { emit ButtonAddTransactionClicked(); });
    connect(ui.buttonDeleteTransaction, &QPushButton::clicked, this, [=] { emit ButtonDeleteTransactionClicked(); });
    connect(ui.buttonDeleteAccount, &QPushButton::clicked, this, [=] { emit ButtonDeleteAccountClicked(); });
    connect(ui.buttonManageStandingOrders, &QPushButton::clicked, this, [=] { emit ButtonManageStandingOrdersClicked(); });
    connect(ui.buttonManageLabels, &QPushButton::clicked, this, [=] { emit ButtonManageLabelsClicked(); });
    connect(ui.buttonChangeTransaction, &QPushButton::clicked, this, [=] { emit ButtonUpdateTransactionClicked(); });
    connect(ui.comboBoxAccount, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.comboBoxMonth, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.spinBoxYear, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.tableMonthOverview, static_cast<void(QTableWidget::*)(void)>(&QTableWidget::itemSelectionChanged), this, [=] { UpdateEnableButtonsTableMonthOverview(); });
    connect(ui.tableAccounts, static_cast<void(QTableWidget::*)(void)>(&QTableWidget::itemSelectionChanged), this, [=] { UpdateEnableButtonsTableAccounts(); });
}

tuple<int, int, int> CoinKeeperView::GetComboboxContent()
{
    return make_tuple(ui.comboBoxMonth->currentIndex(), ui.spinBoxYear->value(), ui.comboBoxAccount->currentIndex());
}

int CoinKeeperView::GetSelectedRowTableMonthOverview()
{
    return ui.tableMonthOverview->currentRow();
}

int CoinKeeperView::GetSelectedRowTableAccounts()
{
    return ui.tableAccounts->currentRow();
}

void CoinKeeperView::setComboboxAccountValues(QStringListModel* model)
{
    ui.comboBoxAccount->setModel(model);
    if (ui.comboBoxAccount->currentIndex() < 0) ui.comboBoxAccount->setCurrentIndex(0);        // to make sure that 1 element is always selected
}

void CoinKeeperView::FillAccountData(vector<tuple<int, string, Value>> accounts)
{
    int x = accounts.size();
    ui.tableAccounts->setRowCount(x);
    for (int i = 0; i < x; i++)
    {
        int accountID;        // not used
        string accountName;
        Value accountValue;
        tie(accountID, accountName, accountValue) = accounts[i];
        ui.tableAccounts->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(accountName)));
        ui.tableAccounts->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(accountValue.ToString())));
    }
}

void CoinKeeperView::FillTransactionData(const vector<tuple<QDate, string, int, string, Value>>& transactions)
{
    int x = transactions.size();
    ui.tableMonthOverview->setRowCount(x);
    Value sum(0);
    for (int i = 0; i < x; i++)
    {
        int color;
        string labelName, description;
        Value value;
        QDate date;
        tie(date, labelName, color, description, value) = transactions[i];
        QColor qColor = ConvertIntToQColor(color);
        ui.tableMonthOverview->setItem(i, 0, new QTableWidgetItem(date.toString("dd.MM.yy")));
        ui.tableMonthOverview->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(labelName)));
        ui.tableMonthOverview->item(i, 1)->setBackgroundColor(qColor);
        ui.tableMonthOverview->item(i, 1)->setTextColor((qColor.value() + (255 - qColor.alpha()) < 128) ? Qt::white : Qt::black);
        ui.tableMonthOverview->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(description)));
        ui.tableMonthOverview->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(value.ToString())));
        sum += value;
    }
    ui.txtBalance->setText(QString::fromStdString(sum.ToString()));
    ui.tableMonthOverview->resizeRowsToContents();
}

void CoinKeeperView::UpdateTime()
{
    date = QDateTime::currentDateTime();
    ui.labelDate->setText(date.toString("dd.MM.yyyy"));
    ui.labelTime->setText(date.toString("HH:mm:ss"));
}

void CoinKeeperView::UpdateEnableButtonsTableMonthOverview()
{
    if (ui.tableMonthOverview->currentRow() < 0)
    {
        ui.buttonChangeTransaction->setEnabled(false);
        ui.buttonDeleteTransaction->setEnabled(false);
    }
    else
    {
        ui.buttonChangeTransaction->setEnabled(true);
        ui.buttonDeleteTransaction->setEnabled(true);
    }
}

void CoinKeeperView::UpdateEnableButtonsTableAccounts()
{
    if (ui.tableAccounts->currentRow() < 0)
    {
        ui.buttonDeleteAccount->setEnabled(false);
        ui.buttonModifyAccount->setEnabled(false);
    }
    else
    {
        ui.buttonDeleteAccount->setEnabled(true);
        ui.buttonModifyAccount->setEnabled(true);
    }
}

CoinKeeperView::~CoinKeeperView() {
    timer->stop();
    timer->~QTimer();
    this->close();
}
