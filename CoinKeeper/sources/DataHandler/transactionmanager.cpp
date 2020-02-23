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
        int preSelectRow = 0;
        addTransactionWindow->comboBoxChooseAccount->clear();        // remove the "select account" value.

        for (int i = 0; i < currentAccounts.size(); i++) {
            addTransactionWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
            if (std::get<0>(currentAccounts[i]) == transaction.AccountId) {
                preSelectRow = i;
            }
        }

        addTransactionWindow->comboBoxChooseAccount->setCurrentIndex(preSelectRow);
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

        addTransactionWindow->buttonAddTransaction->setText(QString::fromStdString(TEXT_CHANGE_TRANSACTION));
        connect(addTransactionWindow->buttonAddTransaction, &QPushButton::clicked, this, [this, transaction] {
            UpdateTransactionInDatabase(transaction.TransactionId, transaction.AccountId, transaction.TransactionValue);
        });
        dialog.exec();
    }

    void TransactionManager::UpdateTransactionInDatabase(const int& transactionID, const int& oldAccountID, const Value& oldValue)
    {
        int selectedAccount = addTransactionWindow->comboBoxChooseAccount->currentIndex();
        int selectedLabel = addTransactionWindow->comboBoxChooseLabel->currentIndex();
        Value value = Value(addTransactionWindow->spinBoxVK->value(), addTransactionWindow->spinBoxNK->value());
        if (addTransactionWindow->radioButtonNegativ->isChecked()) {
            value *= -1;
        }

        // check if the selected account changed:
        if (oldAccountID != std::get<0>(currentAccounts[selectedAccount])) {
            database->UpdateAccountValue(oldAccountID, oldValue * -1);
            database->UpdateAccountValue(std::get<0>(currentAccounts[selectedAccount]), value);
        }
        else if (oldValue != value) {
            database->UpdateAccountValue(oldAccountID, value - oldValue);
        }

        database->UpdateTransaction(transactionID, addTransactionWindow->textEditDescription->toPlainText().toStdString(),
            std::get<0>(currentAccounts[selectedAccount]), value, addTransactionWindow->calendarWidget->selectedDate(), std::get<0>(currentLabels[selectedLabel]));
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
                msg.setText(QString::fromStdString(TEXT_CHOOSE_TARGET_ACCOUNT_FOR_TRANSACTION));
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
