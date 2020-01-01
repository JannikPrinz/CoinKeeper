#pragma once
#ifndef PROFILECHOOSERPRESENTER_HPP
#define PROFILECHOOSERPRESENTER_HPP

#include "presenter.hpp"
#include "profilechooserview.hpp"
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
    list<string> currentProfiles;
    void CreateConnections();

};

#endif // !PROFILECHOOSERPRESENTER_HPP