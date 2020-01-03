#pragma once

#include "presenter.h"
#include "profilechooserview.h"
#include "qinputdialog.h"

class ProfileChooserPresenter : public Presenter {
    Q_OBJECT

public:
    ProfileChooserPresenter(Database*, QObject * parent = Q_NULLPTR);
    ~ProfileChooserPresenter();

public slots:
    void CreateNewProfile();
    void RefreshProfilesList();
    void OpenProfile();
    void DeleteProfile();

private:
    ProfileChooserView* view;
    std::list<std::string> currentProfiles;
    void CreateConnections();

};
