#pragma once

#include "ui_managelabels.h"
#include "database.h"
#include "qinputdialog.h"
#include "qcolordialog.h"
#include "qmessagebox.h"

class LabelManager : QObject
{
    Q_OBJECT

public:
    /*
     * Creates a new LabelManager with the given parameters.
     *
     * Parameters:
     * string profilePath : path of the profile
     * Database* data : adress of a database object
     */
    LabelManager(std::shared_ptr<Database> data);
    // Opens a new Dialog-Window to manage the labels. After execution is the window closed.
    void ManageLabels();
    ~LabelManager();

private:
    Ui::ManageLabelsWindow* manageLabelsWindow = nullptr;
    std::shared_ptr<Database> database;
    // all labels, which are display in the manage labels window (if open)
    std::vector<std::tuple<int, std::string, int>> currentLabels;
    // Creates a new label using inputs of the user.
    void CreateNewLabel();
    /*
     * Changes the name of a labal using inputs of the user.
     */
    void ChangeLabelName();
    // Changes the color of a label using inputs of the user.
    void ChangeLabelColor();
    /*
     * Deletes the label, if it is not the default label (= label with the smallest id).
     */
    void DeleteLabel();
    // Refreshs the window, which shows all labels.
    void RefreshWindow();
};
