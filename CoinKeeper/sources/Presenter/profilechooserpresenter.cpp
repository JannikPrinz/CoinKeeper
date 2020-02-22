#include "Presenter/profilechooserpresenter.h"

#include "DataHandler/database.h"

#include "qinputdialog.h"
#include "qmessagebox.h"

namespace Presenter
{
    using ProfileChooserView = Views::ProfileChooserView;

    ProfileChooserPresenter::ProfileChooserPresenter(QObject* parent) : Presenter(parent) {
        view = std::make_unique<ProfileChooserView>();

        CreateConnections();
        RefreshProfilesList();
        view->show();
    }

    void ProfileChooserPresenter::CreateNewProfile()
    {
        auto textInput = QInputDialog();
        textInput.setInputMode(QInputDialog::TextInput);
        textInput.setLabelText(QString::fromStdString(TEXT_PROFILE_NAME_ENTRY));
        textInput.setWindowTitle(QString::fromStdString(TEXT_CREATE_NEW_PROFILE));
        textInput.setTextValue(QString());
        textInput.resize(300, 100);

        bool userClickedOk = textInput.exec() == QInputDialog::Accepted;
        QString newProfileName = textInput.textValue();

        if (userClickedOk && !newProfileName.isEmpty()) {
            DataHandler::Database::CreateNewProfile(newProfileName.toStdString());
            RefreshProfilesList();
        }
    }

    void ProfileChooserPresenter::RefreshProfilesList()
    {
        view->ClearList();
        currentProfiles = DataHandler::Database::GetDatabaseList();

        for (auto const& [profileName, path] : currentProfiles) {
            view->AddProfile(QString::fromStdString(profileName));
        }

        view->SetRowAsSelected(currentProfiles.empty() ? -1 : 0);
    }

    void ProfileChooserPresenter::OpenProfile()
    {
        if (currentProfiles.empty()) {
            return;
        }

        emit ChangePresenter(Presenters::CoinKeeper, currentProfiles[view->GetSelectedRow()].second.string());
    }

    void ProfileChooserPresenter::DeleteProfile()
    {
        if (currentProfiles.empty()) {
            return;
        }

        QMessageBox msg;
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setText(QString::fromStdString(TEXT_QUESTION_DELETE_PROFILE));
        switch (msg.exec()) {
        case QMessageBox::Yes:
            DataHandler::Database::DeleteProfile(currentProfiles[view->GetSelectedRow()].second);
            RefreshProfilesList();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }

    void ProfileChooserPresenter::ChangeProfileName()
    {
        if (currentProfiles.empty()) {
            return;
        }

        auto textInput = QInputDialog();
        textInput.setInputMode(QInputDialog::TextInput);
        textInput.setLabelText(QString::fromStdString(TEXT_PROFILE_NAME_ENTRY));
        textInput.setWindowTitle(QString::fromStdString(TEXT_CHANGE_PROFILE_NAME));
        textInput.setTextValue(QString::fromStdString(currentProfiles[view->GetSelectedRow()].first));
        textInput.resize(300, 100);

        bool userClickedOk = textInput.exec() == QInputDialog::Accepted;
        QString newProfileName = textInput.textValue();

        if (userClickedOk && !newProfileName.isEmpty()) {
            DataHandler::Database::ChangeProfileName(currentProfiles[view->GetSelectedRow()].second, newProfileName.toStdString());
            RefreshProfilesList();
        }
    }

    void ProfileChooserPresenter::CreateConnections()
    {
        connect(view.get(), &ProfileChooserView::ButtonNewProfileClicked, this, &ProfileChooserPresenter::CreateNewProfile);
        connect(view.get(), &ProfileChooserView::ButtonRefreshListClicked, this, &ProfileChooserPresenter::RefreshProfilesList);
        connect(view.get(), &ProfileChooserView::ButtonOpenProfileClicked, this, &ProfileChooserPresenter::OpenProfile);
        connect(view.get(), &ProfileChooserView::ButtonDeleteProfileClicked, this, &ProfileChooserPresenter::DeleteProfile);
        connect(view.get(), &ProfileChooserView::ButtonChangeProfileNameClicked, this, &ProfileChooserPresenter::ChangeProfileName);
    }
}
