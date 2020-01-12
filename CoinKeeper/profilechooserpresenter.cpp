#include "profilechooserpresenter.h"

#include "database.h"
#include "qinputdialog.h"

ProfileChooserPresenter::ProfileChooserPresenter(QObject * parent) : Presenter(parent) {
    view = std::make_unique<ProfileChooserView>();

    CreateConnections();
    RefreshProfilesList();
    view->show();
}

void ProfileChooserPresenter::CreateNewProfile()
{
    bool userClickedOk;
    QString text = QInputDialog::getText(view.get(), tr("Neues Profil erstellen"), tr("Profilname:"), QLineEdit::Normal, "", &userClickedOk);

    if (userClickedOk && !text.isEmpty()) {
        Database::CreateNewProfile(text.toStdString());
        RefreshProfilesList();
    }
}

void ProfileChooserPresenter::RefreshProfilesList()
{
    view->ClearList();
    currentProfiles = Database::GetDatabaseList();

    for (auto const& [profileName, path] : currentProfiles) {
        view->AddProfile(QString::fromStdString(profileName));
    }

    view->SetRowAsSelected(currentProfiles.empty() ? -1 : 0);
}

void ProfileChooserPresenter::DeleteProfile()
{
    // ToDo: implement this method
}

void ProfileChooserPresenter::OpenProfile()
{
    if (currentProfiles.empty()) return;

    emit ChangePresenter(Presenters::CoinKeeper, currentProfiles[view->GetSelectedRow()].second.string());
}

void ProfileChooserPresenter::CreateConnections()
{
    connect(view.get(), &ProfileChooserView::ButtonNewProfileClicked, this, &ProfileChooserPresenter::CreateNewProfile);
    connect(view.get(), &ProfileChooserView::ButtonRefreshListClicked, this, &ProfileChooserPresenter::RefreshProfilesList);
    connect(view.get(), &ProfileChooserView::ButtonOpenProfileClicked, this, &ProfileChooserPresenter::OpenProfile);
    connect(view.get(), &ProfileChooserView::ButtonDeleteProfileClicked, this, &ProfileChooserPresenter::DeleteProfile);
}
