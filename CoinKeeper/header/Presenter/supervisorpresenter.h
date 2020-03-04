#pragma once

#include <QObject>
#include "Presenter/presenter.h"

namespace Presenter
{
    class SupervisorPresenter : public QObject {
        Q_OBJECT

    public:
        SupervisorPresenter(QObject* parent = Q_NULLPTR);
        ~SupervisorPresenter() = default;

    public slots:
        void ChangePresenter(Presenters p, std::string const& s = "");

    private:
        std::unique_ptr<Presenter> presenter;
    };
}
