#include "supervisorpresenter.h"

SupervisorPresenter::SupervisorPresenter(QObject * parent) : QObject(parent) {
    database = new Database;
//    ProfileChooserPresenter p(database, this);
    presenter = new ProfileChooserPresenter(database, this);
    connect(presenter, &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
}

void SupervisorPresenter::ChangePresenter(Presenters NewPresenter, string s)
{
    switch (NewPresenter)
    {
    case ProfileChooser:
        presenter->~Presenter();
        presenter = new ProfileChooserPresenter(database, this);
        connect(presenter, &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
        break;
    case CoinKeeper:
        if (s == "") break;
        presenter->~Presenter();
        presenter = new CoinKeeperPresenter(database, s, this);
        connect(presenter, &Presenter::ChangePresenter, this, &SupervisorPresenter::ChangePresenter);
        break;
    default:
        break;
    }
}

SupervisorPresenter::~SupervisorPresenter() {
    delete database;
}
