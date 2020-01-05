#include "profilechooserpresenter.h"

#include "database.h"

ProfileChooserPresenter::ProfileChooserPresenter(QObject * parent) : Presenter(parent) {
    ProfileChooserView* v = new ProfileChooserView();
    (*v).show();
    view = v;
    CreateConnections();
//    database->CreateNewProfile("CreateDBTest.ckdb");
    RefreshProfilesList();
    //database->TestForeignKeys();
}

void ProfileChooserPresenter::CreateNewProfile()
{
    bool userClickedOk;
    QString text = QInputDialog::getText(view, tr("Neues Profil erstellen"), tr("Profilname:"), QLineEdit::Normal, "", &userClickedOk);
    if (userClickedOk && !text.isEmpty())
    {
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
    connect(view, &ProfileChooserView::ButtonNewProfileClicked, this, &ProfileChooserPresenter::CreateNewProfile);
    connect(view, &ProfileChooserView::ButtonRefreshListClicked, this, &ProfileChooserPresenter::RefreshProfilesList);
    connect(view, &ProfileChooserView::ButtonOpenProfileClicked, this, &ProfileChooserPresenter::OpenProfile);
    connect(view, &ProfileChooserView::ButtonDeleteProfileClicked, this, &ProfileChooserPresenter::DeleteProfile);
}

ProfileChooserPresenter::~ProfileChooserPresenter() {
    view->~ProfileChooserView();
    //delete view;
}
