#pragma once
#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <QObject>
#include "database.h"


class Presenter : public QObject {
	Q_OBJECT

public:
	Presenter(Database*, QObject * parent = Q_NULLPTR);
	~Presenter();

signals:
	void ChangePresenter(Presenters p, string s = "");

protected:
	Database* database;
};

#endif // !PRESENTER_HPP