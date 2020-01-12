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
     * std::shared_ptr<Database> data : adress of a database object
     * AccountVector const& accounts    : all accounts of the open profile
     * LabelVector const& labels        : all labels of the open profile
     */
    StandingOrderManager(std::shared_ptr<Database> data, AccountVector const& accounts, LabelVector const& labels);
    ~StandingOrderManager() = default;
    /*
     * Opens a new window, where the user can add, change and delete standing orders.
     */
    void ManageStandingOrders();
    /*
     * Executes all standing orders, which have set the date of the next execution less then or equal the current date.
     */
    void ExecuteOrders();

private:
    void AddStandingOrder();
    void CreateNewStandingOrder();
    void ChangeStandingOrder();
    void UpdateStandingOrder(const int& orderID);
    void DeleteStandingOrder();
    void RefreshWindow();

private:
    std::shared_ptr<Database> database;
    AccountVector const& currentAccounts;
    LabelVector const& currentLabels;
    StandingOrderVector currentOrders;
    std::unique_ptr<Ui::ManageStandingOrders> manageStandingOrders;
    std::unique_ptr<Ui::AddStandingOrderWindow> addStandingOrderWindow;
};
