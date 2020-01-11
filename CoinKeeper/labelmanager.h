#pragma once

#include "database.h"
#include "ui_managelabels.h"

class LabelManager : QObject
{
    Q_OBJECT

public:
    /*
     * Creates a new LabelManager with the given parameters.
     *
     * Parameters:
     * std::shared_ptr<Database> data : the active database
     */
    LabelManager(std::shared_ptr<Database> data);
    ~LabelManager() = default;
    /*
     * Opens a new Dialog-Window to manage the labels. This window is closed, before this method returns.
     */
    void ManageLabels();

private:
    /*
     * Creates a new label using inputs of the user.
     */
    void CreateNewLabel();
    /*
     * Changes the name of a labal using inputs of the user.
     */
    void ChangeLabelName(int selectedRow);
    /*
     * Changes the color of a label using inputs of the user.
     */
    void ChangeLabelColor(int selectedRow);
    /*
     * Deletes the label, if it is not the default label (= label with the smallest id).
     */
    void DeleteLabel(int selectedRow);
    /*
     * Refreshs the window, which shows all labels.
     */
    void RefreshWindow(std::unique_ptr<Ui::ManageLabelsWindow>& window);

private:
    std::shared_ptr<Database> database;
    // all labels, which are display in the manage labels window (if open)
    std::vector<std::tuple<int, std::string, int>> currentLabels;
};
