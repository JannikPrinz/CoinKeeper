#include "standingordermanager.h"

StandingOrderManager::StandingOrderManager(const string& profile, Database* data)
{
    currentProfile = profile;
    database = data;
}

void StandingOrderManager::ManageStandingOrders(std::vector<std::tuple<int, string, Value>>* accounts, std::vector<std::tuple<int, string, int>>* labels)
{
    currentAccounts = accounts;
    currentLabels = labels;
    manageStandingOrders = new Ui::ManageStandingOrders;
    QDialog dialog;
    manageStandingOrders->setupUi(&dialog);
    RefreshWindow();
    // connect buttons:
    connect(manageStandingOrders->buttonAddOrder, &QPushButton::clicked, this, [=] { AddStandingOrder(); });
    connect(manageStandingOrders->buttonChangeOrder, &QPushButton::clicked, this, [=] { ChangeStandingOrder(); });
    connect(manageStandingOrders->buttonDeleteOrder, &QPushButton::clicked, this, [=] { DeleteStandingOrder(); });
    dialog.exec();
    delete manageStandingOrders;
    manageStandingOrders = nullptr;
}

void StandingOrderManager::ExecuteOrders()
{
    QDate currentDate = QDate::currentDate();
    int date = currentDate.year() * 10000 + currentDate.month() * 100 + currentDate.day();
    std::vector<std::tuple<int, int, int, Value, string, StandingOrderType, QDate>> executableOrders = database->GetExecutableStandingOrders(currentProfile.c_str(), date);
    if (executableOrders.empty())
    {
        return;
    }

    int addedTransactions = 0;
    size_t lastItem = executableOrders.size() - 1;
    int orderID;
    int accountID;
    int labelID;
    Value value;
    string description;
    StandingOrderType orderType;
    QDate nextDate;
    while (executableOrders.size() != 0)
    {
        if (std::get<6>(executableOrders[lastItem]) > currentDate)
        {
            date = std::get<6>(executableOrders[lastItem]).year() * 10000 + std::get<6>(executableOrders[lastItem]).month() * 100 + std::get<6>(executableOrders[lastItem]).day();
            database->UpdateStandingOrderDate(currentProfile.c_str(), std::get<0>(executableOrders[lastItem]), date);
            executableOrders.pop_back();
            lastItem = executableOrders.size() - 1;
        } else
        {
            tie(orderID, accountID, labelID, value, description, orderType, nextDate) = executableOrders[lastItem];
            database->CreateNewTransaction(currentProfile.c_str(), description, accountID, value, nextDate, labelID);
            addedTransactions++;
            switch (orderType)
            {
            case EveryDay:
                std::get<6>(executableOrders[lastItem]) = nextDate.addDays(1);
                break;
            case EveryWeek:
                std::get<6>(executableOrders[lastItem]) = nextDate.addDays(7);
                break;
            case EveryMonth:
                std::get<6>(executableOrders[lastItem]) = nextDate.addMonths(1);
                break;
            case EveryQuarter:
                std::get<6>(executableOrders[lastItem]) = nextDate.addMonths(3);
                break;
            case Every4Months:
                std::get<6>(executableOrders[lastItem]) = nextDate.addMonths(4);
                break;
            case EveryYear:
                std::get<6>(executableOrders[lastItem]) = nextDate.addYears(1);
                break;
            default:
                return;
            }
        }
    }
    QMessageBox msg;
    QString m = QString::fromStdString(TEXT_ADDED_TRANSACTIONS_PART_1);
    m.append(QString::number(addedTransactions));
    m.append(QString::fromStdString(TEXT_ADDED_TRANSACTIONS_PART_2));
    msg.setText(m);
    msg.exec();
}

void StandingOrderManager::AddStandingOrder()
{
    addStandingOrderWindow = new Ui::AddStandingOrderWindow;
    QDialog dialog;
    addStandingOrderWindow->setupUi(&dialog);
    // insert values:
    for (int i = 0; i < (*currentAccounts).size(); i++)
    {
        addStandingOrderWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>((*currentAccounts)[i])));
    }
    for (int i = 0; i < (*currentLabels).size(); i++)
    {
        addStandingOrderWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>((*currentLabels)[i])));
    }
    for (int i = 0; i < NUMBER_OF_STANDING_ORDER_TYPES; i++)
    {
        addStandingOrderWindow->comboBoxChooseType->addItem(QString::fromStdString(GetStringFromStandingOrderType(static_cast<StandingOrderType>(i))));
    }
    addStandingOrderWindow->comboBoxChooseType->setCurrentIndex(static_cast<int>(StandingOrderType::EveryMonth));
    addStandingOrderWindow->dateEditNextDate->setDate(QDate::currentDate());
    connect(addStandingOrderWindow->buttonAddOrder, &QPushButton::clicked, this, [=] { CreateNewStandingOrder(); });
    dialog.exec();
    delete addStandingOrderWindow;
    ExecuteOrders();
    RefreshWindow();
}

void StandingOrderManager::ChangeStandingOrder()
{
    int selectedRow = manageStandingOrders->tableStandingOrders->currentRow();
    if (selectedRow < 0) return;
    int orderID, accountID, labelID;
    Value value;
    string description;
    StandingOrderType orderType;
    QDate nextDate;
    tie(orderID, accountID, labelID, value, description, orderType, nextDate) = currentOrders[selectedRow];
    addStandingOrderWindow = new Ui::AddStandingOrderWindow;
    QDialog dialog;
    addStandingOrderWindow->setupUi(&dialog);
    // insert values:
    addStandingOrderWindow->comboBoxChooseAccount->clear();        // remove 'choose account'
    for (int i = 0; i < (*currentAccounts).size(); i++)
    {
        addStandingOrderWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>((*currentAccounts)[i])));
        if (std::get<0>((*currentAccounts)[i]) == accountID) selectedRow = i;
    }
    addStandingOrderWindow->comboBoxChooseAccount->setCurrentIndex(selectedRow);
    for (int i = 0; i < (*currentLabels).size(); i++)
    {
        addStandingOrderWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>((*currentLabels)[i])));
        if (std::get<0>((*currentLabels)[i]) == labelID) selectedRow = i;
    }
    addStandingOrderWindow->comboBoxChooseLabel->setCurrentIndex(selectedRow);
    for (int i = 0; i < NUMBER_OF_STANDING_ORDER_TYPES; i++)
    {
        addStandingOrderWindow->comboBoxChooseType->addItem(QString::fromStdString(GetStringFromStandingOrderType(static_cast<StandingOrderType>(i))));
        if (static_cast<StandingOrderType>(i) == orderType) selectedRow = i;
    }
    addStandingOrderWindow->comboBoxChooseType->setCurrentIndex(selectedRow);
    // insert values of the standing order, which is altered
    addStandingOrderWindow->dateEditNextDate->setDate(nextDate);
    addStandingOrderWindow->textEditDescription->setPlainText(QString::fromStdString(description));
    if (value < Value(0))
    {
        Value v = value * -1;
        addStandingOrderWindow->spinBoxVK->setValue(v.VK);
        addStandingOrderWindow->spinBoxNK->setValue(v.NK);
        addStandingOrderWindow->radioButtonNegativ->setChecked(true);
    }
    else
    {
        addStandingOrderWindow->spinBoxVK->setValue(value.VK);
        addStandingOrderWindow->spinBoxNK->setValue(value.NK);
        addStandingOrderWindow->radioButtonPositiv->setChecked(true);
    }
    addStandingOrderWindow->buttonAddOrder->setText(QString::fromStdString(TEXT_CHANGE_STANDING_ORDER));
    connect(addStandingOrderWindow->buttonAddOrder, &QPushButton::clicked, this, [=] { UpdateStandingOrder(orderID); });
    dialog.exec();
    delete addStandingOrderWindow;
    ExecuteOrders();
    RefreshWindow();
}

void StandingOrderManager::UpdateStandingOrder(const int& orderID)
{
    int selectedAccount = addStandingOrderWindow->comboBoxChooseAccount->currentIndex();
    int selectedLabel = addStandingOrderWindow->comboBoxChooseLabel->currentIndex();
    Value value = Value(addStandingOrderWindow->spinBoxVK->value(), addStandingOrderWindow->spinBoxNK->value());
    if (addStandingOrderWindow->radioButtonNegativ->isChecked()) value *= -1;
    database->UpdateStandingOrder(currentProfile.c_str(), orderID, addStandingOrderWindow->textEditDescription->toPlainText().toStdString(), std::get<0>((*currentAccounts)[selectedAccount]),
        value, addStandingOrderWindow->dateEditNextDate->date(), std::get<0>((*currentLabels)[selectedLabel]), addStandingOrderWindow->comboBoxChooseType->currentIndex());
    addStandingOrderWindow->buttonCancel->click();
}

void StandingOrderManager::DeleteStandingOrder()
{
    int selectedRow = manageStandingOrders->tableStandingOrders->currentRow();
    if (selectedRow >= 0)
    {
        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_STANDING_ORDER));
        switch (msg.exec())
        {
        case QMessageBox::Yes:
            database->DeleteStandingOrder(currentProfile.c_str(), std::get<0>(currentOrders[selectedRow]));
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
        RefreshWindow();
    }
}

void StandingOrderManager::CreateNewStandingOrder()
{
    int selectedAccount = addStandingOrderWindow->comboBoxChooseAccount->currentIndex();
    if (selectedAccount == 0)
    {
        QMessageBox msg;
        msg.setText(QString::fromStdString(TEXT_CHOOSE_ACCOUNT_FOR_STANDING_ORDER));
        msg.exec();
        return;
    }
    int selectedLabel = addStandingOrderWindow->comboBoxChooseLabel->currentIndex();
    Value value = Value(addStandingOrderWindow->spinBoxVK->value(), addStandingOrderWindow->spinBoxNK->value());
    if (addStandingOrderWindow->radioButtonNegativ->isChecked()) value *= -1;
    QDate date = addStandingOrderWindow->dateEditNextDate->date();
    database->CreateNewStandingOrder(currentProfile.c_str(), addStandingOrderWindow->textEditDescription->toPlainText().toStdString(),
        std::get<0>((*currentAccounts)[selectedAccount - 1]), value, date, std::get<0>((*currentLabels)[selectedLabel]), addStandingOrderWindow->comboBoxChooseType->currentIndex());
    addStandingOrderWindow->buttonCancel->click();
}

void StandingOrderManager::RefreshWindow()
{
    if (manageStandingOrders != nullptr)
    {
        currentOrders = database->GetAllStandingOrders(currentProfile.c_str());
        int x = static_cast<int>(currentOrders.size());
        manageStandingOrders->tableStandingOrders->setRowCount(x);
        // insert existing values:
        for (int i = 0; i < x; ++i)
        {
            int orderID, accountID, labelID;
            StandingOrderType type;
            string description;
            Value value;
            QDate date;
            tie(orderID, accountID, labelID, value, description, type, date) = currentOrders[i];
            std::vector<std::tuple<int, string, int>>::iterator labelIterator = std::find_if((*currentLabels).begin(), (*currentLabels).end(), [labelID](std::tuple<int, string, int> label) { return std::get<0>(label) == labelID; });
            std::vector<std::tuple<int, string, Value>>::iterator accountIterator = std::find_if((*currentAccounts).begin(), (*currentAccounts).end(), [accountID](std::tuple<int, string, Value> acc) { return std::get<0>(acc) == accountID; });
            if (labelIterator == (*currentLabels).end() || accountIterator == (*currentAccounts).end()) return;        //should not happen
            QColor qColor = ConvertIntToQColor(std::get<2>(*labelIterator));
            manageStandingOrders->tableStandingOrders->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::get<1>(*accountIterator))));
            manageStandingOrders->tableStandingOrders->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(GetStringFromStandingOrderType(type))));
            manageStandingOrders->tableStandingOrders->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(value.ToString())));
            manageStandingOrders->tableStandingOrders->setItem(i, 3, new QTableWidgetItem(date.toString("dd.MM.yy")));
            manageStandingOrders->tableStandingOrders->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(std::get<1>(*labelIterator))));
            manageStandingOrders->tableStandingOrders->item(i, 4)->setBackgroundColor(qColor);
            manageStandingOrders->tableStandingOrders->item(i, 4)->setTextColor((qColor.value() + (255 - qColor.alpha()) < 128) ? Qt::white : Qt::black);
            manageStandingOrders->tableStandingOrders->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(description)));
        }
    }
}

StandingOrderManager::~StandingOrderManager()
{
}
