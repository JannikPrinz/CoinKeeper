#pragma once

#include <QObject>
#include "presenter.h"
#include "database.h"
#include "profilechooserpresenter.h"
#include "coinkeeperpresenter.h"

class SupervisorPresenter : public QObject {
    Q_OBJECT

public:
    SupervisorPresenter(QObject * parent = Q_NULLPTR);
    ~SupervisorPresenter();

public slots:
    void ChangePresenter(Presenters p, string s = "");

private:
    Presenter* presenter;
    Database* database;
};
