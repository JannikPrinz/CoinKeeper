#include "supervisorpresenter.h"

SupervisorPresenter::SupervisorPresenter(QObject * parent) : QObject(parent)
{
    presenter = std::make_unique<ProfileChooserPresenter>(this);
    connect(presenter.get(), &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
}

void SupervisorPresenter::ChangePresenter(Presenters NewPresenter, std::string const& s)
{
    switch (NewPresenter)
    {
    case ProfileChooser:
        presenter = std::make_unique<ProfileChooserPresenter>(this);
        connect(presenter.get(), &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
        break;
    case CoinKeeper:
        if (s == "") break;
        presenter = std::make_unique<CoinKeeperPresenter>(s, this);
        connect(presenter.get(), &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
        break;
    default:
        break;
    }
}

SupervisorPresenter::~SupervisorPresenter() {
}
