#include "profilechooserview.h"

ProfileChooserView::ProfileChooserView(QWidget * parent) : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.buttonRefreshList, &QPushButton::clicked, this, [this] { emit ButtonRefreshListClicked(); });
    connect(ui.buttonChangeProfileName, &QPushButton::clicked, this, [this] { emit ButtonChangeProfileNameClicked(); });
    connect(ui.buttonDeleteProfile, &QPushButton::clicked, this, [this] { emit ButtonDeleteProfileClicked(); });
    connect(ui.buttonNewProfile, &QPushButton::clicked, this, [this] { emit ButtonNewProfileClicked(); });
    connect(ui.buttonOpenProfile, &QPushButton::clicked, this, [this] { emit ButtonOpenProfileClicked(); });
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
