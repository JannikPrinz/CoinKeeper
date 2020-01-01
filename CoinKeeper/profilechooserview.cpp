#include "profilechooserview.hpp"

ProfileChooserView::ProfileChooserView(QWidget * parent) : QMainWindow(parent) {
    ui.setupUi(this);
//    connect(ui.buttonRefreshList, SIGNAL(clicked()), this, SLOT(Test()));
    connect(ui.buttonRefreshList, &QPushButton::clicked, this, [=] {emit ButtonRefreshListClicked();});
    connect(ui.buttonAddFolder, &QPushButton::clicked, this, [=] {emit ButtonAddFolderClicked();});
    connect(ui.buttonDeleteProfile, &QPushButton::clicked, this, [=] {emit ButtonDeleteProfileClicked();});
    connect(ui.buttonNewProfile, &QPushButton::clicked, this, [=] {emit ButtonNewProfileClicked();});
    connect(ui.buttonOpenProfile, &QPushButton::clicked, this, [=] {emit ButtonOpenProfileClicked();});
//    connect(this, &ProfileChooserView::NewProfileClicked, this, &ProfileChooserView::Test);
//    connect(ui.buttonAddFolder, SIGNAL(clicked()), ui.listProfiles, SLOT(clear()));
}

void ProfileChooserView::AddProfile(QString profile)
{
    ui.listProfiles->addItem(profile);
}

void ProfileChooserView::SetRowAsSelected(int row)
{
    ui.listProfiles->setCurrentRow(row);
}

int ProfileChooserView::GetSelectedRow()
{
    return ui.listProfiles->currentRow();
}

void ProfileChooserView::ClearList()
{
    ui.listProfiles->clear();
}

ProfileChooserView::~ProfileChooserView() {
    this->close();
}
