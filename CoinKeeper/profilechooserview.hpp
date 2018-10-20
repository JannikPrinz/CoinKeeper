#pragma once
#ifndef PROFILECHOOSERVIEW_HPP
#define PROFILECHOOSERVIEW_HPP

#include <QWidget>
#include "ui_profilechooser.h"

class ProfileChooserView : public QMainWindow {
	Q_OBJECT

public:
	ProfileChooserView(QWidget * parent = Q_NULLPTR);
	~ProfileChooserView();
	// Adds an entry into the list of profiles
	void AddProfile(QString s);
	// Removes all entrys of the list of profiles
	void ClearList();
	// Returns the current selected row of the list of profiles
	int GetSelectedRow();
	// Sets the given row as selected in the list
	void SetRowAsSelected(int row);

signals:
	void ButtonNewProfileClicked();
	void ButtonDeleteProfileClicked();
	void ButtonAddFolderClicked();
	void ButtonRefreshListClicked();
	void ButtonOpenProfileClicked();

private:
	Ui_MainWindow ui;
};

#endif // !PROFILECHOOSERVIEW_HPP