#include "accountmanager.hpp"

AccountManager::AccountManager(const string& profile, Database* data)
{
	currentProfile = profile;
	database = data;
}

void AccountManager::CreateAccount()
{
	addAccountWindow = new Ui::AddAccountWindow;
	QDialog dialog;
	addAccountWindow->setupUi(&dialog);
	connect(addAccountWindow->buttonOk, &QPushButton::clicked, this, [=] { CreateNewAccount(); });
	dialog.exec();
	delete addAccountWindow;
}

void AccountManager::CreateNewAccount()
{
	if (addAccountWindow->txtNameOfAccount->text() == QString(""))
	{
		QMessageBox msg;
		msg.setText(TEXT_ACCOUNT_NAME_NEEDED);
		msg.exec();
		return;
	}
	Value value = Value(addAccountWindow->spinBoxVK->value(), addAccountWindow->spinBoxNK->value());
	if (addAccountWindow->radioButtonNegativ->isChecked()) value *= -1;
	database->CreateNewAccount(currentProfile.c_str(), addAccountWindow->txtNameOfAccount->text().toStdString(), value);
	addAccountWindow->buttonCancel->click();
}

void AccountManager::ChangeAccount(const int& accountID, const string& oldName, const Value& oldValue)
{
	addAccountWindow = new Ui::AddAccountWindow;
	QDialog dialog;
	addAccountWindow->setupUi(&dialog);
	connect(addAccountWindow->buttonOk, &QPushButton::clicked, this, [=] { ChangeExistingAccount(accountID); });
	addAccountWindow->txtNameOfAccount->setText(QString::fromStdString(oldName));
	addAccountWindow->buttonOk->setText(TEXT_CHANGE_ACCOUNT);
	if (oldValue < 0)
	{
		Value v = oldValue * -1;
		addAccountWindow->spinBoxVK->setValue(v.VK);
		addAccountWindow->spinBoxNK->setValue(v.NK);
		addAccountWindow->radioButtonNegativ->setChecked(true);
	}
	else
	{
		addAccountWindow->spinBoxVK->setValue(oldValue.VK);
		addAccountWindow->spinBoxNK->setValue(oldValue.NK);
		addAccountWindow->radioButtonPositiv->setChecked(true);
	}
	dialog.exec();
	delete addAccountWindow;
}

void AccountManager::ChangeExistingAccount(const int& accountID)
{
	if (addAccountWindow->txtNameOfAccount->text() == QString(""))
	{
		QMessageBox msg;
		msg.setText(TEXT_ACCOUNT_NAME_NEEDED);
		msg.exec();
		return;
	}
	Value value = Value(addAccountWindow->spinBoxVK->value(), addAccountWindow->spinBoxNK->value());
	if (addAccountWindow->radioButtonNegativ->isChecked()) value *= -1;
	database->UpdateAccount(currentProfile.c_str(), accountID, addAccountWindow->txtNameOfAccount->text().toStdString(), value);
	addAccountWindow->buttonCancel->click();
}

AccountManager::~AccountManager()
{
}