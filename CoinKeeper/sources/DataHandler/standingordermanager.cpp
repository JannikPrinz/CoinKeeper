#include "DataHandler/standingordermanager.h"

#include "qmessagebox.h"

namespace DataHandler
{
    using Value = DataClasses::Value;
    using StandingOrder = DataClasses::StandingOrder;
    using StandingOrderType = DataClasses::StandingOrder::StandingOrderType;

    StandingOrderManager::StandingOrderManager(std::shared_ptr<Database> data, AccountVector const& accounts, LabelVector const& labels) :
        database(data),
        currentAccounts(accounts),
        currentLabels(labels)
    {
    }

    void StandingOrderManager::ManageStandingOrders()
    {
        manageStandingOrdersWindow = std::make_unique<Ui::ManageStandingOrders>();
        QDialog dialog;
        manageStandingOrdersWindow->setupUi(&dialog);
        RefreshWindow();
        // connect buttons:
        connect(manageStandingOrdersWindow->buttonAddOrder, &QPushButton::clicked, this, [this] { AddStandingOrder(); });
        connect(manageStandingOrdersWindow->buttonChangeOrder, &QPushButton::clicked, this, [this] { ChangeStandingOrder(); });
        connect(manageStandingOrdersWindow->buttonDeleteOrder, &QPushButton::clicked, this, [this] { DeleteStandingOrder(); });
        dialog.exec();
    }

    void StandingOrderManager::ExecuteOrders()
    {
        QDate currentDate = QDate::currentDate();
        int date = currentDate.year() * 10000 + currentDate.month() * 100 + currentDate.day();
        StandingOrderVector executableOrders = database->GetExecutableStandingOrders(date);

        if (executableOrders.empty()) {
            return;
        }

        int addedTransactions = 0;
        size_t lastItem = executableOrders.size() - 1;

        while (executableOrders.size() != 0) {
            auto& orderDate = executableOrders[lastItem].Date;
            if (orderDate > currentDate) {
                date = orderDate.year() * 10000 + orderDate.month() * 100 + orderDate.day();
                database->UpdateStandingOrderDate(executableOrders[lastItem].StandingOrderId, date);
                executableOrders.pop_back();
                lastItem = executableOrders.size() - 1;
            }
            else {
                database->CreateNewTransaction(executableOrders[lastItem].Description, executableOrders[lastItem].AccountId, executableOrders[lastItem].StandingOrderValue,
                    orderDate, executableOrders[lastItem].LabelId, executableOrders[lastItem].ConnectedAccountId);
                ++addedTransactions;

                switch (executableOrders[lastItem].Type) {
                case StandingOrderType::EveryDay:
                    orderDate.addDays(1);
                    break;
                case StandingOrderType::EveryWeek:
                    orderDate.addDays(7);
                    break;
                case StandingOrderType::EveryMonth:
                    orderDate.addMonths(1);
                    break;
                case StandingOrderType::EveryQuarter:
                    orderDate.addMonths(3);
                    break;
                case StandingOrderType::Every4Months:
                    orderDate.addMonths(4);
                    break;
                case StandingOrderType::EveryYear:
                    orderDate.addYears(1);
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
        addStandingOrderWindow = std::make_unique<Ui::AddStandingOrderWindow>();
        QDialog dialog;
        addStandingOrderWindow->setupUi(&dialog);

        // insert values:
        for (int i = 0; i < (currentAccounts).size(); i++) {
            addStandingOrderWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>((currentAccounts)[i])));
        }

        for (int i = 0; i < (currentLabels).size(); i++) {
            addStandingOrderWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>((currentLabels)[i])));
        }

        for (int32_t i = 0; i < StandingOrder::NUMBER_OF_STANDING_ORDER_TYPES; ++i) {
            addStandingOrderWindow->comboBoxChooseType->addItem(QString::fromStdString(StandingOrder::GetStringFromStandingOrderType(static_cast<StandingOrderType>(i))));
        }

        addStandingOrderWindow->comboBoxChooseType->setCurrentIndex(static_cast<int>(StandingOrderType::EveryMonth));
        addStandingOrderWindow->dateEditNextDate->setDate(QDate::currentDate());

        connect(addStandingOrderWindow->buttonAddOrder, &QPushButton::clicked, this, [this] { CreateNewStandingOrder(); });
        connect(addStandingOrderWindow->checkBoxActivateInternalTransaction, &QCheckBox::clicked, this, [this] { UpdateEnabledElements(); });

        dialog.exec();
        ExecuteOrders();
        RefreshWindow();
    }

    void StandingOrderManager::ChangeStandingOrder()
    {
        int selectedRow = manageStandingOrdersWindow->tableStandingOrders->currentRow();
        if (selectedRow < 0) {
            return;
        }

        addStandingOrderWindow = std::make_unique<Ui::AddStandingOrderWindow>();
        QDialog dialog;
        addStandingOrderWindow->setupUi(&dialog);

        // insert values:
        addStandingOrderWindow->comboBoxChooseAccount->clear();        // remove 'choose account'

        for (int i = 0; i < (currentAccounts).size(); i++) {
            addStandingOrderWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>((currentAccounts)[i])));
            if (std::get<0>((currentAccounts)[i]) == currentOrders[selectedRow].AccountId) {
                selectedRow = i;
            }
        }
        addStandingOrderWindow->comboBoxChooseAccount->setCurrentIndex(selectedRow);

        for (int i = 0; i < (currentLabels).size(); i++) {
            addStandingOrderWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>((currentLabels)[i])));
            if (std::get<0>((currentLabels)[i]) == currentOrders[selectedRow].LabelId) {
                selectedRow = i;
            }
        }
        addStandingOrderWindow->comboBoxChooseLabel->setCurrentIndex(selectedRow);

        for (int i = 0; i < StandingOrder::NUMBER_OF_STANDING_ORDER_TYPES; i++) {
            addStandingOrderWindow->comboBoxChooseType->addItem(QString::fromStdString(StandingOrder::GetStringFromStandingOrderType(static_cast<StandingOrderType>(i))));
            if (static_cast<StandingOrderType>(i) == currentOrders[selectedRow].Type) {
                selectedRow = i;
            }
        }
        addStandingOrderWindow->comboBoxChooseType->setCurrentIndex(selectedRow);

        // insert values of the standing order, which is altered
        addStandingOrderWindow->dateEditNextDate->setDate(currentOrders[selectedRow].Date);
        addStandingOrderWindow->textEditDescription->setPlainText(QString::fromStdString(currentOrders[selectedRow].Description));
        if (currentOrders[selectedRow].StandingOrderValue < Value(0)) {
            Value v = currentOrders[selectedRow].StandingOrderValue * -1;
            addStandingOrderWindow->spinBoxVK->setValue(v.VK);
            addStandingOrderWindow->spinBoxNK->setValue(v.NK);
            addStandingOrderWindow->radioButtonNegativ->setChecked(true);
        }
        else {
            addStandingOrderWindow->spinBoxVK->setValue(currentOrders[selectedRow].StandingOrderValue.VK);
            addStandingOrderWindow->spinBoxNK->setValue(currentOrders[selectedRow].StandingOrderValue.NK);
            addStandingOrderWindow->radioButtonPositiv->setChecked(true);
        }

        addStandingOrderWindow->buttonAddOrder->setText(QString::fromStdString(TEXT_CHANGE_STANDING_ORDER));

        connect(addStandingOrderWindow->buttonAddOrder, &QPushButton::clicked, this, [this, orderID = currentOrders[selectedRow].StandingOrderId] { UpdateStandingOrder(orderID); });
        connect(addStandingOrderWindow->checkBoxActivateInternalTransaction, &QCheckBox::clicked, this, [this] { UpdateEnabledElements(); });

        dialog.exec();
        ExecuteOrders();
        RefreshWindow();
    }

    void StandingOrderManager::UpdateStandingOrder(const int& orderID)
    {
        int selectedAccount = addStandingOrderWindow->comboBoxChooseAccount->currentIndex();
        int selectedLabel = addStandingOrderWindow->comboBoxChooseLabel->currentIndex();
        Value value = Value(addStandingOrderWindow->spinBoxVK->value(), addStandingOrderWindow->spinBoxNK->value());
        if (addStandingOrderWindow->radioButtonNegativ->isChecked()) {
            value *= -1;
        }

        StandingOrder updatedOrder = StandingOrder(orderID, std::get<0>((currentAccounts)[selectedAccount]), std::get<0>((currentLabels)[selectedLabel]), value,
            addStandingOrderWindow->textEditDescription->toPlainText().toStdString(), addStandingOrderWindow->comboBoxChooseType->currentIndex(), addStandingOrderWindow->dateEditNextDate->date(), );
        database->UpdateStandingOrder(updatedOrder);
        addStandingOrderWindow->buttonCancel->click();
    }

    void StandingOrderManager::DeleteStandingOrder()
    {
        int selectedRow = manageStandingOrdersWindow->tableStandingOrders->currentRow();
        if (selectedRow >= 0) {
            QMessageBox msg;
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_STANDING_ORDER));
            switch (msg.exec()) {
            case QMessageBox::Yes:
                database->DeleteStandingOrder(currentOrders[selectedRow].StandingOrderId);
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
        auto selectedAccount = addStandingOrderWindow->comboBoxChooseAccount->currentIndex();
        if (selectedAccount == 0) {
            QMessageBox msg;
            msg.setText(QString::fromStdString(TEXT_CHOOSE_ACCOUNT_FOR_STANDING_ORDER));
            msg.exec();
            return;
        }

        auto selectedTargetAccount = addStandingOrderWindow->comboBoxChooseTargetAccount->currentIndex();
        auto isInternalTransaction = addStandingOrderWindow->checkBoxActivateInternalTransaction->checkState() == Qt::CheckState::Checked;
        if (isInternalTransaction && selectedTargetAccount == 0) {
            QMessageBox msg;
            msg.setText(QString::fromStdString(TEXT_CHOOSE_CONNECTED_ACCOUNT_FOR_INTERNAL_TRANSACTION));
            msg.exec();
            return;
        }

        auto selectedLabel = addStandingOrderWindow->comboBoxChooseLabel->currentIndex();
        Value value = Value(addStandingOrderWindow->spinBoxVK->value(), addStandingOrderWindow->spinBoxNK->value());
        if (addStandingOrderWindow->radioButtonNegativ->isChecked()) {
            value *= -1;
        }

        std::optional<int32_t> connectedTransactionAccountId = std::nullopt;
        if (isInternalTransaction) {
            connectedTransactionAccountId = std::get<0>(currentAccounts[selectedTargetAccount - 1]);
        }

        QDate date = addStandingOrderWindow->dateEditNextDate->date();
        database->CreateNewStandingOrder(addStandingOrderWindow->textEditDescription->toPlainText().toStdString(),
            std::get<0>(currentAccounts[selectedAccount - 1]), value, date, std::get<0>((currentLabels)[selectedLabel]),
            static_cast<StandingOrderType>(addStandingOrderWindow->comboBoxChooseType->currentIndex()), connectedTransactionAccountId);
        addStandingOrderWindow->buttonCancel->click();
    }

    void StandingOrderManager::RefreshWindow()
    {
        if (manageStandingOrdersWindow != nullptr) {
            currentOrders = database->GetAllStandingOrders();
            int numberOfStandingOrders = static_cast<int>(currentOrders.size());
            manageStandingOrdersWindow->tableStandingOrders->setRowCount(numberOfStandingOrders);

            // insert existing values:
            for (int i = 0; i < numberOfStandingOrders; ++i) {
                auto labelIterator = std::find_if((currentLabels).begin(), (currentLabels).end(), [labelID = currentOrders[i].LabelId](std::tuple<int, std::string, int> label) {
                    return std::get<0>(label) == labelID;
                    });
                auto accountIterator = std::find_if((currentAccounts).begin(), (currentAccounts).end(), [accountID = currentOrders[i].AccountId](std::tuple<int, std::string, Value> acc) {
                    return std::get<0>(acc) == accountID;
                    });

                if (labelIterator == (currentLabels).end() || accountIterator == (currentAccounts).end()) {
                    return;        //should not happen
                }

                QColor qColor = ConvertIntToQColor(std::get<2>(*labelIterator));
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::get<1>(*accountIterator))));
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(StandingOrder::GetStringFromStandingOrderType(currentOrders[i].Type))));
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(currentOrders[i].StandingOrderValue.ToString())));
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 3, new QTableWidgetItem(currentOrders[i].Date.toString("dd.MM.yy")));
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(std::get<1>(*labelIterator))));
                manageStandingOrdersWindow->tableStandingOrders->item(i, 4)->setBackgroundColor(qColor);
                manageStandingOrdersWindow->tableStandingOrders->item(i, 4)->setTextColor((qColor.value() + (255 - qColor.alpha()) < 128) ? Qt::white : Qt::black);
                manageStandingOrdersWindow->tableStandingOrders->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(currentOrders[i].Description)));
            }
        }
    }

    void StandingOrderManager::UpdateEnabledElements()
    {
        bool enabled = addStandingOrderWindow->checkBoxActivateInternalTransaction->checkState() == Qt::CheckState::Checked;

        addStandingOrderWindow->lblTargetAccount->setEnabled(enabled);
        addStandingOrderWindow->comboBoxChooseTargetAccount->setEnabled(enabled);
    }
}
