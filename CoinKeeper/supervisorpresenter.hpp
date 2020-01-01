#pragma once
#ifndef SUPERVISORPRESENTER_H
#define SUPERVISORPRESENTER_H


#include <QObject>
#include "presenter.hpp"
#include "database.h"
#include "profilechooserpresenter.hpp"
#include "coinkeeperpresenter.hpp"

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

#endif // !SUPERVISORPRESENTER_H