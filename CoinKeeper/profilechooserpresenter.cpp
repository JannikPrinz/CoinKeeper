#include "profilechooserpresenter.h"

ProfileChooserPresenter::ProfileChooserPresenter(Database* base, QObject * parent) : Presenter(base, parent) {
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
        database->CreateNewProfile(text.toStdString());
        RefreshProfilesList();
    }
}

void ProfileChooserPresenter::RefreshProfilesList()
{
    view->ClearList();
    currentProfiles = database->GetDatabaseList();
    bool mod2 = true;
    for each (std::string s in currentProfiles)
    {
        if (mod2) view->AddProfile(QString::fromStdString(s));
        mod2 = !mod2;
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
    const char* s = (*next(currentProfiles.begin(), view->GetSelectedRow() * 2 + 1)).c_str();
    //qDebug("Selected row: %d. Selected profile: %s", view->GetSelectedRow(), s);
    emit ChangePresenter(Presenters::CoinKeeper, s);
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
