#include "DataHandler/accountmanager.h"

#include "ui_addaccountwindow.h"
#include "qmessagebox.h"

namespace DataHandler
{
    AccountManager::AccountManager(std::shared_ptr<Database> data) :
        database(data)
    {
    }

    void AccountManager::CreateAccount()
    {
        auto addAccountWindow = std::make_unique<Ui::AddAccountWindow>();
        QDialog dialog;
        addAccountWindow->setupUi(&dialog);
        connect(addAccountWindow->buttonOk, &QPushButton::clicked, this, [this, &addAccountWindow] {
            auto accountCreationWasSuccessful = CreateNewAccount(
                addAccountWindow->txtNameOfAccount->text(),
                addAccountWindow->spinBoxVK->value(),
                addAccountWindow->spinBoxNK->value(),
                addAccountWindow->radioButtonNegativ->isChecked()
            );

            if (accountCreationWasSuccessful) {
                addAccountWindow->buttonCancel->click();
            }
            });
        dialog.exec();
    }

    void AccountManager::ChangeAccount(int const accountID, std::string const& oldName, Value const& oldValue)
    {
        auto addAccountWindow = std::make_unique<Ui::AddAccountWindow>();
        QDialog dialog;
        addAccountWindow->setupUi(&dialog);
        connect(addAccountWindow->buttonOk, &QPushButton::clicked, this, [this, accountID, &addAccountWindow] {
            auto changeWasSuccessful = ChangeExistingAccount(
                accountID,
                addAccountWindow->txtNameOfAccount->text(),
                addAccountWindow->spinBoxVK->value(),
                addAccountWindow->spinBoxNK->value(),
                addAccountWindow->radioButtonNegativ->isChecked()
            );

            if (changeWasSuccessful) {
                addAccountWindow->buttonCancel->click();
            }
            });

        addAccountWindow->txtNameOfAccount->setText(QString::fromStdString(oldName));
        addAccountWindow->buttonOk->setText(QString::fromStdString(TEXT_CHANGE_ACCOUNT));
        if (oldValue < 0) {
            Value v = oldValue * -1;
            addAccountWindow->spinBoxVK->setValue(v.VK);
            addAccountWindow->spinBoxNK->setValue(v.NK);
            addAccountWindow->radioButtonNegativ->setChecked(true);
        }
        else {
            addAccountWindow->spinBoxVK->setValue(oldValue.VK);
            addAccountWindow->spinBoxNK->setValue(oldValue.NK);
            addAccountWindow->radioButtonPositiv->setChecked(true);
        }
        dialog.exec();
    }

    bool AccountManager::CreateNewAccount(QString const& accountName, int const vk, int const nk, bool const negative)
    {
        if (accountName == QString("")) {
            QMessageBox msg;
            msg.setText(QString::fromStdString(TEXT_ACCOUNT_NAME_NEEDED));
            msg.exec();
            return false;
        }
        Value value = Value(vk, nk);
        if (negative) {
            value *= -1;
        }
        database->CreateNewAccount(accountName.toStdString(), value);

        return true;
    }

    bool AccountManager::ChangeExistingAccount(int const accountID, QString const& accountName, int const vk, int const nk, bool const negative)
    {
        if (accountName == QString("")) {
            QMessageBox msg;
            msg.setText(QString::fromStdString(TEXT_ACCOUNT_NAME_NEEDED));
            msg.exec();
            return false;
        }
        Value value = Value(vk, nk);
        if (negative) {
            value *= -1;
        }
        database->UpdateAccount(accountID, accountName.toStdString(), value);

        return true;
    }
}
