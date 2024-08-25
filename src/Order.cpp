#include "../include/Order.h"


Order::Order(int id, int customerId, int distance):
id(id),customerId(customerId),distance(distance),
status(OrderStatus::PENDING),collectorId(NO_VOLUNTEER),driverId(NO_VOLUNTEER)
{}

int Order::getId() const {return id;}

string Order::getStatusStr() const
{
    string statusstr="";
    switch (status) {
      case OrderStatus::PENDING:
        statusstr="PENDING";
        break;
      case OrderStatus::COLLECTING:
        statusstr="COLLECTING";
        break;
      case OrderStatus::DELIVERING:
        statusstr="DELIVERING";
        break;
      case OrderStatus::COMPLETED:
        statusstr="COMPLETED";
        break;
    }
    return statusstr;
}

int Order::getCustomerId() const {return customerId;}

int Order::getCollectorId() const {return collectorId;}

int Order::getDriverId() const {return driverId;}

int Order::getDistance() const{return distance;}

void Order::setStatus(OrderStatus status)
{this->status = status;}

void Order::setCollectorId(int collectorId){this->collectorId = collectorId;}

void Order::setDriverId(int driverId){this->driverId = driverId;}

OrderStatus Order::getStatus() const{return status;};
const string Order::toString() const{
    string collectorStr=std::to_string(collectorId);
    string driverStr=std::to_string(driverId);
    if(collectorId==NO_VOLUNTEER)
        collectorStr="NONE";
    if(driverId==NO_VOLUNTEER)
        driverStr="NONE";
    return "OrderId: " + std::to_string(id) + "\nOrderStatus: " + getStatusStr() +
    "\nCustomerID: " + std::to_string(customerId) + "\nCollector: " + collectorStr +"\nDriver: " + driverStr; 
    
}
   

    
