#include "coinkeeperview.h"

CoinKeeperView::CoinKeeperView(std::string const& profileName, QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString("CoinKeeper - " + profileName));

    date = QDateTime::currentDateTime();
    ui.spinBoxYear->setValue(date.toString("yyyy").toInt());
    ui.comboBoxMonth->setCurrentIndex(13 - date.date().month());
    UpdateTime();
    UpdateEnableButtonsTableMonthOverview();
    UpdateEnableButtonsTableAccounts();
    timer = std::make_unique<QTimer>(this);
    connect(timer.get(), &QTimer::timeout, this, &CoinKeeperView::UpdateTime);
    timer->start(1000);
    CreateConnections();
}

CoinKeeperView::~CoinKeeperView() {
    timer->stop();
    this->close();
}

void CoinKeeperView::FillAccountData(AccountVector const& accounts)
{
    int x = static_cast<int>(accounts.size());
    ui.tableAccounts->setRowCount(x);

    for (int i = 0; i < x; ++i) {
        int accountID;        // not used
        std::string accountName;
        Value accountValue;
        tie(accountID, accountName, accountValue) = accounts[i];
        ui.tableAccounts->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(accountName)));
        ui.tableAccounts->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(accountValue.ToString())));
    }
}

void CoinKeeperView::FillTransactionData(std::vector<std::tuple<QDate, std::string, int, std::string, Value>> const& transactions)
{
    int x = static_cast<int>(transactions.size());
    ui.tableMonthOverview->setRowCount(x);
    Value sum(0);
    for (int i = 0; i < x; ++i) {
        int color;
        std::string labelName, description;
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

int CoinKeeperView::GetSelectedMonth()
{
    int currentIndex = ui.comboBoxMonth->currentIndex();
    if (currentIndex == 0) {
        return 0;
    }
    return 13 - ui.comboBoxMonth->currentIndex();
}

int CoinKeeperView::GetSelectedYear()
{
    return ui.spinBoxYear->value();
}

int CoinKeeperView::GetSelectedAccount()
{
    return ui.comboBoxAccount->currentIndex();
}

void CoinKeeperView::setComboboxAccountValues(QStringListModel* model)
{
    ui.comboBoxAccount->setModel(model);
    if (ui.comboBoxAccount->currentIndex() < 0) {   // to make sure that 1 element is always selected
        ui.comboBoxAccount->setCurrentIndex(0);
    }
}

int CoinKeeperView::GetSelectedRowTableMonthOverview()
{
    return ui.tableMonthOverview->currentRow();
}

int CoinKeeperView::GetSelectedRowTableAccounts()
{
    return ui.tableAccounts->currentRow();
}

void CoinKeeperView::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ResizeColumns();
}

void CoinKeeperView::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    ResizeColumns();
}

void CoinKeeperView::ResizeColumns()
{
    ui.tableAccounts->setColumnWidth(0, ui.tableAccounts->width() - 200);
    ui.tableAccounts->setColumnWidth(1, 0);

    ui.tableMonthOverview->setColumnWidth(0, 100);
    ui.tableMonthOverview->setColumnWidth(1, 100);
    ui.tableMonthOverview->setColumnWidth(2, ui.tableMonthOverview->width() - 350);
    ui.tableMonthOverview->setColumnWidth(3, 0);
}

void CoinKeeperView::CreateConnections()
{
    connect(ui.buttonChangeProfile, &QPushButton::clicked, this, [this] { emit ButtonChangeProfileClicked(); });
    connect(ui.buttonModifyAccount, &QPushButton::clicked, this, [this] { emit ButtonChangeAccountClicked(); });
    connect(ui.buttonAddAccount, &QPushButton::clicked, this, [this] { emit ButtonCreateNewAccountClicked(); });
    connect(ui.buttonAddTransaction, &QPushButton::clicked, this, [this] { emit ButtonAddTransactionClicked(); });
    connect(ui.buttonDeleteTransaction, &QPushButton::clicked, this, [this] { emit ButtonDeleteTransactionClicked(); });
    connect(ui.buttonDeleteAccount, &QPushButton::clicked, this, [this] { emit ButtonDeleteAccountClicked(); });
    connect(ui.buttonManageStandingOrders, &QPushButton::clicked, this, [this] { emit ButtonManageStandingOrdersClicked(); });
    connect(ui.buttonManageLabels, &QPushButton::clicked, this, [this] { emit ButtonManageLabelsClicked(); });
    connect(ui.buttonChangeTransaction, &QPushButton::clicked, this, [this] { emit ButtonUpdateTransactionClicked(); });
    connect(ui.comboBoxAccount, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.comboBoxMonth, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.spinBoxYear, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this] { emit SelectionMonthYearAccountChanged(); });
    connect(ui.tableMonthOverview, static_cast<void(QTableWidget::*)(void)>(&QTableWidget::itemSelectionChanged), this, [this] { UpdateEnableButtonsTableMonthOverview(); });
    connect(ui.tableAccounts, static_cast<void(QTableWidget::*)(void)>(&QTableWidget::itemSelectionChanged), this, [this] { UpdateEnableButtonsTableAccounts(); });
}

void CoinKeeperView::UpdateEnableButtonsTableMonthOverview()
{
    if (ui.tableMonthOverview->currentRow() < 0) {
        ui.buttonChangeTransaction->setEnabled(false);
        ui.buttonDeleteTransaction->setEnabled(false);
    }
    else {
        ui.buttonChangeTransaction->setEnabled(true);
        ui.buttonDeleteTransaction->setEnabled(true);
    }
}

void CoinKeeperView::UpdateEnableButtonsTableAccounts()
{
    if (ui.tableAccounts->currentRow() < 0) {
        ui.buttonDeleteAccount->setEnabled(false);
        ui.buttonModifyAccount->setEnabled(false);
    }
    else {
        ui.buttonDeleteAccount->setEnabled(true);
        ui.buttonModifyAccount->setEnabled(true);
    }
}

void CoinKeeperView::UpdateTime()
{
    date = QDateTime::currentDateTime();
    ui.labelDate->setText(date.toString("dd.MM.yyyy"));
    ui.labelTime->setText(date.toString("HH:mm:ss"));
}
