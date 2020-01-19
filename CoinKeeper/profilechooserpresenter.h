#pragma once

#include "presenter.h"
#include "profilechooserview.h"

class ProfileChooserPresenter : public Presenter {
    Q_OBJECT

public:
    ProfileChooserPresenter(QObject* parent = Q_NULLPTR);
    ~ProfileChooserPresenter() = default;

public slots:
    void CreateNewProfile();
    void RefreshProfilesList();
    void OpenProfile();
    void DeleteProfile();
    void ChangeProfileName();

private:
    std::unique_ptr<ProfileChooserView> view;
    ProfileVector currentProfiles;
    void CreateConnections();
};
