#pragma once

#include <QObject>

#include "constants.h"

class Presenter : public QObject {
    Q_OBJECT

public:
    Presenter(QObject* parent = Q_NULLPTR);
    ~Presenter();

signals:
    void ChangePresenter(Presenters p, std::string s = "");
};
