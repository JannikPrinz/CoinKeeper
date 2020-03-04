#include "DataHandler/transactionmanager.h"

#include "qmessagebox.h"

namespace DataHandler
{
    using Value = DataClasses::Value;

    TransactionManager::TransactionManager(std::shared_ptr<Database> data) :
        database(data)
    {
    }

    void TransactionManager::CreateNewTransaction()
    {
        currentAccounts = database->GetAccounts();
        currentLabels = database->GetLabels();
        addTransactionWindow = std::make_unique<Ui::AddTransactionWindow>();
        QDialog dialog;
        addTransactionWindow->setupUi(&dialog);

        for (int i = 0; i < currentAccounts.size(); i++) {
            addTransactionWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
            addTransactionWindow->comboBoxChooseTargetAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
        }

        for (int i = 0; i < currentLabels.size(); i++) {
            addTransactionWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>(currentLabels[i])));
        }

        connect(addTransactionWindow->buttonAddTransaction, &QPushButton::clicked, this, [this] { CreateTransaction(); });
        connect(addTransactionWindow->checkBoxActivateInternalTransaction, &QCheckBox::clicked, this, [this] { UpdateEnabledElements(); });
        dialog.exec();
    }

    void TransactionManager::UpdateTransaction(DataClasses::Transaction const& transaction)
    {
        currentAccounts = database->GetAccounts();
        currentLabels = database->GetLabels();
        addTransactionWindow = std::make_unique<Ui::AddTransactionWindow>();
        QDialog dialog;
        addTransactionWindow->setupUi(&dialog);
        int preSelectRow = -1;
        int preSelectTargetAccountRow = -1;
        addTransactionWindow->comboBoxChooseAccount->clear();        // remove the "select account" value.
        addTransactionWindow->comboBoxChooseTargetAccount->clear();

        std::optional<DataClasses::Transaction> connectedTransaction = std::nullopt;
        if (transaction.ConnectedTransactionId.has_value()) {
            connectedTransaction = database->GetTransaction(transaction.ConnectedTransactionId.value());
        }

        for (int i = 0; i < currentAccounts.size(); i++) {
            addTransactionWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
            addTransactionWindow->comboBoxChooseTargetAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
            if (std::get<0>(currentAccounts[i]) == transaction.AccountId) {
                preSelectRow = i;
            }

            if (transaction.ConnectedTransactionId.has_value() && std::get<0>(currentAccounts[i]) == connectedTransaction.value().AccountId) {
                preSelectTargetAccountRow = i;
            }
        }
        addTransactionWindow->comboBoxChooseAccount->setCurrentIndex(preSelectRow);
        addTransactionWindow->comboBoxChooseTargetAccount->setCurrentIndex(preSelectTargetAccountRow);

        for (int i = 0; i < currentLabels.size(); i++) {
            addTransactionWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>(currentLabels[i])));
            if (std::get<0>(currentLabels[i]) == transaction.LabelId) {
                preSelectRow = i;
            }
        }
        addTransactionWindow->comboBoxChooseLabel->setCurrentIndex(preSelectRow);

        addTransactionWindow->calendarWidget->setSelectedDate(transaction.Date);
        addTransactionWindow->textEditDescription->setPlainText(QString::fromStdString(transaction.Description));

        // set old value in form:
        if (transaction.TransactionValue < Value(0)) {
            Value v = transaction.TransactionValue * -1;
            addTransactionWindow->spinBoxVK->setValue(v.VK);
            addTransactionWindow->spinBoxNK->setValue(v.NK);
            addTransactionWindow->radioButtonNegativ->setChecked(true);
        }
        else {
            addTransactionWindow->spinBoxVK->setValue(transaction.TransactionValue.VK);
            addTransactionWindow->spinBoxNK->setValue(transaction.TransactionValue.NK);
            addTransactionWindow->radioButtonPositiv->setChecked(true);
        }

        addTransactionWindow->checkBoxActivateInternalTransaction->setEnabled(false);
        if (transaction.ConnectedTransactionId.has_value()) {
            addTransactionWindow->checkBoxActivateInternalTransaction->setChecked(true);
        }

        addTransactionWindow->buttonAddTransaction->setText(QString::fromStdString(TEXT_CHANGE_TRANSACTION));
        dialog.setWindowTitle(QString::fromStdString(TEXT_CHANGE_TRANSACTION));
        connect(addTransactionWindow->buttonAddTransaction, &QPushButton::clicked, this, [this, transaction] {
            UpdateTransactionInDatabase(transaction);
        });
        dialog.exec();
    }

    void TransactionManager::UpdateTransactionInDatabase(DataClasses::Transaction const& oldTransaction)
    {
        int selectedAccount = addTransactionWindow->comboBoxChooseAccount->currentIndex();
        int selectedTargetAccount = addTransactionWindow->comboBoxChooseTargetAccount->currentIndex();
        int selectedLabel = addTransactionWindow->comboBoxChooseLabel->currentIndex();
        Value value = Value(addTransactionWindow->spinBoxVK->value(), addTransactionWindow->spinBoxNK->value());
        if (addTransactionWindow->radioButtonNegativ->isChecked()) {
            value *= -1;
        }

        bool accountChanged = oldTransaction.AccountId != std::get<0>(currentAccounts[selectedAccount]);
        bool valueChanged = oldTransaction.TransactionValue != value;
        bool isInternalTransaction = oldTransaction.ConnectedTransactionId.has_value();
        bool removeConnectionBetweenTransactions = false;

        if (isInternalTransaction && accountChanged) {
            QMessageBox msg;
            msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Abort);
            msg.setText(QString::fromStdString(TEXT_CONFIRMATION_REMOVE_CONNECTED_ACCOUNT_ON_ACCOUNT_CHANGE_ON_TRANSACTION_CHANGE));

            switch (msg.exec()) {
            case QMessageBox::Ok:
                removeConnectionBetweenTransactions = true;
                break;
            case QMessageBox::Abort:
            default:
                return;
            }
        }

        if (isInternalTransaction && valueChanged && !removeConnectionBetweenTransactions)
        {
            QMessageBox msg;
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
            msg.setText(QString::fromStdString(TEXT_QUESTION_MODIFY_CONNECTED_TRANSACTION));

            switch (msg.exec()) {
            case QMessageBox::Yes:
                database->UpdateAccountValue(std::get<0>(currentAccounts[selectedTargetAccount]), (value - oldTransaction.TransactionValue) * -1);
                break;
            case QMessageBox::No:
                removeConnectionBetweenTransactions = true;
                break;
            case QMessageBox::Abort:
            default:
                return;
            }
        }

        if (removeConnectionBetweenTransactions) {
            database->UpdateConnectedTransaction(oldTransaction.TransactionId, std::nullopt);
            database->UpdateConnectedTransaction(oldTransaction.ConnectedTransactionId.value(), std::nullopt);
        }

        if (accountChanged) {
            database->UpdateAccountValue(oldTransaction.AccountId, oldTransaction.TransactionValue * -1);
            database->UpdateAccountValue(std::get<0>(currentAccounts[selectedAccount]), value);
        }
        else if (valueChanged) {
            database->UpdateAccountValue(oldTransaction.AccountId, value - oldTransaction.TransactionValue);
        }

        database->UpdateTransaction(oldTransaction.TransactionId, addTransactionWindow->textEditDescription->toPlainText().toStdString(),
            std::get<0>(currentAccounts[selectedAccount]), value, addTransactionWindow->calendarWidget->selectedDate(), std::get<0>(currentLabels[selectedLabel]));

        if (isInternalTransaction && !removeConnectionBetweenTransactions) {
            database->UpdateTransaction(oldTransaction.ConnectedTransactionId.value(), addTransactionWindow->textEditDescription->toPlainText().toStdString(),
                std::get<0>(currentAccounts[selectedTargetAccount]), value * -1, addTransactionWindow->calendarWidget->selectedDate(),
                std::get<0>(currentLabels[selectedLabel]));
        }

        addTransactionWindow->buttonCancel->click();
    }

    void TransactionManager::CreateTransaction()
    {
        int32_t selectedAccountIndex = addTransactionWindow->comboBoxChooseAccount->currentIndex();
        if (selectedAccountIndex == 0) {
            QMessageBox msg;
            msg.setText(QString::fromStdString(TEXT_CHOOSE_ACCOUNT_FOR_TRANSACTION));
            msg.exec();
            return;
        }

        std::optional<int32_t> selectedTargetAccountId = std::nullopt;
        bool isInternalTransaction = addTransactionWindow->checkBoxActivateInternalTransaction->checkState() == Qt::CheckState::Checked;
        if (isInternalTransaction) {
            auto selectedTargetAccountIndex = addTransactionWindow->comboBoxChooseTargetAccount->currentIndex();

            if (selectedTargetAccountIndex == 0) {
                QMessageBox msg;
                msg.setText(QString::fromStdString(TEXT_CHOOSE_CONNECTED_ACCOUNT_FOR_TRANSACTION));
                msg.exec();
                return;
            }

            selectedTargetAccountId = std::get<0>(currentAccounts[selectedTargetAccountIndex - 1]);
        }

        int32_t selectedLabel = addTransactionWindow->comboBoxChooseLabel->currentIndex();
        Value value = Value(addTransactionWindow->spinBoxVK->value(), addTransactionWindow->spinBoxNK->value());

        if (addTransactionWindow->radioButtonNegativ->isChecked()) {
            value *= -1;
        }

        QDate date = addTransactionWindow->calendarWidget->selectedDate();

        database->CreateNewTransaction(addTransactionWindow->textEditDescription->toPlainText().toStdString(),
            std::get<0>(currentAccounts[selectedAccountIndex - 1]), value, date, std::get<0>(currentLabels[selectedLabel]), selectedTargetAccountId);
        addTransactionWindow->buttonCancel->click();
    }

    void TransactionManager::UpdateEnabledElements()
    {
        bool enabled = addTransactionWindow->checkBoxActivateInternalTransaction->checkState() == Qt::CheckState::Checked;

        addTransactionWindow->lblTargetAccount->setEnabled(enabled);
        addTransactionWindow->comboBoxChooseTargetAccount->setEnabled(enabled);
    }
}
