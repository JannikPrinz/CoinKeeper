#pragma once

#include "ui_managestandingorders.h"
#include "ui_addstandingorder.h"
#include "database.h"
#include "qmessagebox.h"

class StandingOrderManager : QObject
{
    Q_OBJECT

public:
    /*
     * Creates a new StandingOrderManager with the given parameters.
     *
     * Parameters:
     * const string& profile : path of the profile
     * Database* data : adress of a database object
     */
    StandingOrderManager(const string& profile, Database* data);
    /*
     * Opens a new window, where the user can add, change and delete standing orders.
     *
     * Parameters:
     * vector<tuple<int, string, Value>>* accounts    : all accounts of the open profile
     * vector<tuple<int, string, int>>* labels        : all labels of the open profile
     */
    void ManageStandingOrders(std::vector<std::tuple<int, string, Value>>* accounts, std::vector<std::tuple<int, string, int>>* labels);
    /*
     * Executes all standing orders, which have set the date of the next execution less then or equal the current date.
     */
    void ExecuteOrders();
    ~StandingOrderManager();

private:
    string currentProfile;
    Database* database;
    std::vector<std::tuple<int, string, Value>>* currentAccounts;
    std::vector<std::tuple<int, string, int>>* currentLabels;
    std::vector<std::tuple<int, int, int, Value, string, StandingOrderType, QDate>> currentOrders;
    Ui::ManageStandingOrders* manageStandingOrders = nullptr;
    Ui::AddStandingOrderWindow* addStandingOrderWindow;
    void AddStandingOrder();
    void CreateNewStandingOrder();
    void ChangeStandingOrder();
    void UpdateStandingOrder(const int& orderID);
    void DeleteStandingOrder();
    void RefreshWindow();

};
