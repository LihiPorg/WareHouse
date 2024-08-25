#pragma once

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class BaseAction;
class Action;
class Volunteer;
class Order;
class Customer;
// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse& other);
        WareHouse(WareHouse&& other);
        ~WareHouse();
        WareHouse& operator=(const WareHouse& other);
        WareHouse & operator=(WareHouse&& other);
        void start();
        void addOrder(Order* order);
        void addCustomer(Customer* customer);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        int getOrderCounter() const; 
        int getVolunteerCounter() const; 
        int getCustomerCounter() const; 
        void close();
        void open();
        void allStep();

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter; //For assigning unique Order IDs
        Volunteer* defultVolunteer;

};