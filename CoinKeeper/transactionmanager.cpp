#include "transactionmanager.h"

TransactionManager::TransactionManager(std::string profile, Database* data)
{
    currentProfile = profile;
    database = data;
}

void TransactionManager::CreateNewTransaction()
{
    currentAccounts = database->GetAccounts(currentProfile);
    currentLabels = database->GetLabels(currentProfile);
    addTransactionWindow = new Ui::AddTransactionWindow;
    QDialog dialog;
    addTransactionWindow->setupUi(&dialog);
    for (int i = 0; i < currentAccounts.size(); i++)
    {
        addTransactionWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
    }
    for (int i = 0; i < currentLabels.size(); i++)
    {
        addTransactionWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>(currentLabels[i])));
    }
    connect(addTransactionWindow->buttonAddTransaction, &QPushButton::clicked, this, [=] { CreateTransaction(); });
    dialog.exec();
    delete addTransactionWindow;
}

void TransactionManager::UpdateTransaction(const int& transactionID, const std::string& description, const int& accountID, const Value& value, const QDate& date, const int& labelID)
{
    currentAccounts = database->GetAccounts(currentProfile);
    currentLabels = database->GetLabels(currentProfile);
    addTransactionWindow = new Ui::AddTransactionWindow;
    QDialog dialog;
    addTransactionWindow->setupUi(&dialog);
    int preSelectRow = 0;
    addTransactionWindow->comboBoxChooseAccount->clear();        // remove the "select account" value.
    for (int i = 0; i < currentAccounts.size(); i++)
    {
        addTransactionWindow->comboBoxChooseAccount->addItem(QString::fromStdString(std::get<1>(currentAccounts[i])));
        if (std::get<0>(currentAccounts[i]) == accountID) preSelectRow = i;
    }
    addTransactionWindow->comboBoxChooseAccount->setCurrentIndex(preSelectRow);
    for (int i = 0; i < currentLabels.size(); i++)
    {
        addTransactionWindow->comboBoxChooseLabel->addItem(QString::fromStdString(std::get<1>(currentLabels[i])));
        if (std::get<0>(currentLabels[i]) == labelID) preSelectRow = i;
    }
    addTransactionWindow->comboBoxChooseLabel->setCurrentIndex(preSelectRow);
    addTransactionWindow->calendarWidget->setSelectedDate(date);
    addTransactionWindow->textEditDescription->setPlainText(QString::fromStdString(description));
    // set old value in form:
    if (value < Value(0))
    {
        Value v = value * -1;
        addTransactionWindow->spinBoxVK->setValue(v.VK);
        addTransactionWindow->spinBoxNK->setValue(v.NK);
        addTransactionWindow->radioButtonNegativ->setChecked(true);
    }
    else
    {
        addTransactionWindow->spinBoxVK->setValue(value.VK);
        addTransactionWindow->spinBoxNK->setValue(value.NK);
        addTransactionWindow->radioButtonPositiv->setChecked(true);
    }
    addTransactionWindow->buttonAddTransaction->setText(QString::fromStdString(TEXT_CHANGE_TRANSACTION));
    connect(addTransactionWindow->buttonAddTransaction, &QPushButton::clicked, this, [=] { UpdateTransactionInDatabase(transactionID, accountID, value); });
    dialog.exec();
    delete addTransactionWindow;
}

void TransactionManager::UpdateTransactionInDatabase(const int& transactionID, const int& oldAccountID, const Value& oldValue)
{
    int selectedAccount = addTransactionWindow->comboBoxChooseAccount->currentIndex();
    int selectedLabel = addTransactionWindow->comboBoxChooseLabel->currentIndex();
    Value value = Value(addTransactionWindow->spinBoxVK->value(), addTransactionWindow->spinBoxNK->value());
    if (addTransactionWindow->radioButtonNegativ->isChecked()) value *= -1;
    // check if the selected account changed:
    if (oldAccountID != std::get<0>(currentAccounts[selectedAccount]))
    {
        database->UpdateAccountValue(currentProfile, oldAccountID, oldValue * -1);
        database->UpdateAccountValue(currentProfile, std::get<0>(currentAccounts[selectedAccount]), value);
    }
    else if (oldValue != value)
    {
        database->UpdateAccountValue(currentProfile, oldAccountID, value - oldValue);
    }
    database->UpdateTransaction(currentProfile, transactionID, addTransactionWindow->textEditDescription->toPlainText().toStdString(),
        std::get<0>(currentAccounts[selectedAccount]), value, addTransactionWindow->calendarWidget->selectedDate(), std::get<0>(currentLabels[selectedLabel]));
    addTransactionWindow->buttonCancel->click();
}

void TransactionManager::CreateTransaction()
{
    int selectedAccount = addTransactionWindow->comboBoxChooseAccount->currentIndex();
    if (selectedAccount == 0)
    {
        QMessageBox msg;
        msg.setText(QString::fromStdString(TEXT_CHOOSE_ACCOUNT_FOR_TRANSACTION));
        msg.exec();
        return;
    }
    int selectedLabel = addTransactionWindow->comboBoxChooseLabel->currentIndex();
    Value value = Value(addTransactionWindow->spinBoxVK->value(), addTransactionWindow->spinBoxNK->value());
    if (addTransactionWindow->radioButtonNegativ->isChecked()) value *= -1;
    QDate date = addTransactionWindow->calendarWidget->selectedDate();
    database->CreateNewTransaction(currentProfile, addTransactionWindow->textEditDescription->toPlainText().toStdString(),
        std::get<0>(currentAccounts[selectedAccount - 1]), value, date, std::get<0>(currentLabels[selectedLabel]));
    addTransactionWindow->buttonCancel->click();
}

TransactionManager::~TransactionManager()
{
}
