﻿#pragma once

#include "Presenter/presenter.h"
#include "Views/profilechooserview.h"

namespace Presenter
{
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
        std::unique_ptr<Views::ProfileChooserView> view;
        ProfileVector currentProfiles;
        void CreateConnections();
    };
}
