#include <iostream>
#include <fstream>
#include "../include/Volunteer.h"


Volunteer::Volunteer(int id, const string &name)
:completedOrderId(NO_ORDER),activeOrderId(NO_ORDER),id(id),name(name){}

int Volunteer::getId() const{return id;}
const string & Volunteer::getName() const{return name;}
int Volunteer::getActiveOrderId() const{return activeOrderId;}
int Volunteer::getCompletedOrderId() const{return completedOrderId;}
bool Volunteer::isBusy() const{return activeOrderId!=NO_ORDER;}

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int coolDown):Volunteer(id,name),coolDown(coolDown),timeLeft(0){}
CollectorVolunteer* CollectorVolunteer::clone() const {return new CollectorVolunteer(*this);}
void CollectorVolunteer::step() 
{
    if(completedOrderId!=-1)
        completedOrderId=-1;
    if(isBusy()){
        if(decreaseCoolDown())
        {
            completedOrderId=activeOrderId;
            activeOrderId=NO_ORDER;
        }
    }
    
}



int CollectorVolunteer::getCoolDown() const{return coolDown;}
int CollectorVolunteer::getTimeLeft() const{return timeLeft;}
bool CollectorVolunteer::decreaseCoolDown() //Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
{
    timeLeft--;
    if (timeLeft==0)
        return true;
    else
        return false; 

}
bool CollectorVolunteer::hasOrdersLeft() const {return true;}
bool CollectorVolunteer::canTakeOrder(const Order &order) const 
{
    return activeOrderId==-1;
}
void CollectorVolunteer::acceptOrder(const Order &order) 
{
    if (canTakeOrder(order))
    {
        activeOrderId=order.getId(); 
        timeLeft=coolDown;
    }
}

string CollectorVolunteer::toString() const 
{
    string busy= isBusy() ? "True":"False";
    return "VolunteerID: " + std::to_string(getId()) + "\nIsBusy: " + busy +
    "\nOrderId: " + (activeOrderId==-1 ? "NONE":to_string(activeOrderId)) 
    +"\nTime Left: " +(timeLeft==0 ? "NONE" : std::to_string(timeLeft)) +"\nOrdersLeft: No Limit"; 
}

string CollectorVolunteer::typeOf() const{return "COLLECTOR";}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, 
int coolDown ,int maxOrders):CollectorVolunteer(id,name,coolDown),maxOrders(maxOrders),ordersLeft(maxOrders){}
        
LimitedCollectorVolunteer* LimitedCollectorVolunteer:: clone() const 
    {return new LimitedCollectorVolunteer(*this);}

bool LimitedCollectorVolunteer::hasOrdersLeft() const {return ordersLeft>0;};

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const 
    {   
        return (CollectorVolunteer::canTakeOrder(order) & hasOrdersLeft()); 
    }

void LimitedCollectorVolunteer::acceptOrder(const Order &order) 
{
    CollectorVolunteer::acceptOrder (order);
    ordersLeft--;    
}

int LimitedCollectorVolunteer::getMaxOrders() const {return maxOrders;}

int LimitedCollectorVolunteer::getNumOrdersLeft() const {return ordersLeft;}

string LimitedCollectorVolunteer::toString() const{
    string busy= isBusy() ? "True":"False";
    return "VolunteerID:" +std::to_string(getId())+ "\nIs busy:" + busy +
    "\nOrderId: " + (activeOrderId==-1 ? "NONE":to_string(activeOrderId)) 
    + "\nTime Left: " +(CollectorVolunteer::getTimeLeft()==0 ? "NONE" : std::to_string(CollectorVolunteer::getTimeLeft()))
    +"\nOrdersLeft:"+ std::to_string(ordersLeft);
} 

string LimitedCollectorVolunteer::typeOf() const{return "LIMITED_COLLECTOR";}


DriverVolunteer::DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep)
:Volunteer(id,name),maxDistance(maxDistance),distancePerStep(distancePerStep),distanceLeft(0){}
DriverVolunteer* DriverVolunteer::clone() const {return new DriverVolunteer(*this);}
int DriverVolunteer::getDistanceLeft() const{return distanceLeft;}
int DriverVolunteer::getMaxDistance() const{return maxDistance;}
int DriverVolunteer::getDistancePerStep() const{return distancePerStep;}
bool DriverVolunteer::decreaseDistanceLeft()
{
    distanceLeft=distanceLeft-distancePerStep;
    if(distanceLeft<=0){
        distanceLeft=0;
        return true;
    }
    else
        return false;
} //Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}
bool DriverVolunteer::canTakeOrder(const Order &order) const
{ 
    if(activeOrderId==-1 && order.getDistance()<=maxDistance)
        return true;
    return false;
} // Signal if the volunteer is not busy and the order is within the maxDistance
void DriverVolunteer::acceptOrder(const Order &order) 
{
    if(canTakeOrder(order))
    {
        activeOrderId=order.getId();
        distanceLeft=order.getDistance();
    }
} // Assign distanceLeft to order's distance
void DriverVolunteer::step() 
{
    if(completedOrderId!=-1)
        completedOrderId=-1;
    if(isBusy()){
        if(decreaseDistanceLeft())
        {
            completedOrderId=activeOrderId;
            activeOrderId=NO_ORDER;
            
        }
    }
} // Decrease distanceLeft by distancePerStep
string DriverVolunteer::toString() const
{
    return "VolunteerID: " + std::to_string(getId()) + "\nIsBusy: " + (isBusy() ? "True":"False") +
    "\nOrderId: " + (activeOrderId==-1 ? "NONE":to_string(activeOrderId)) + "\nDistance Left: " 
    + (distanceLeft==0 ? "NONE":to_string(distanceLeft)) +"\nOrdersLeft: No Limit"; 
}

string DriverVolunteer::typeOf() const{return "DRIVER";}


LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance,
    int distancePerStep,int maxOrders):DriverVolunteer(id,name,maxDistance,distancePerStep),
    maxOrders(maxOrders),ordersLeft(maxOrders){}

LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const 
    {return new LimitedDriverVolunteer (*this);}

int LimitedDriverVolunteer::getMaxOrders() const {return maxOrders;}
int LimitedDriverVolunteer::getNumOrdersLeft() const {return ordersLeft;}
bool LimitedDriverVolunteer::hasOrdersLeft() const {return ordersLeft>0;}
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const 
{   
    return DriverVolunteer::canTakeOrder(order) & hasOrdersLeft();
} // Signal if the volunteer is not busy, the order is within the maxDistance.

void LimitedDriverVolunteer::acceptOrder(const Order &order) {
    DriverVolunteer::acceptOrder (order);
    ordersLeft--;
} // Assign distanceLeft to order's distance and decrease ordersLeft

string LimitedDriverVolunteer::toString() const{
    string busy= isBusy() ? "True":"False";
    return "VolunteerID: " + std::to_string(getId()) + "\nIsBusy: " + busy +
    "\nOrderId: " + (activeOrderId==-1 ? "NONE":to_string(activeOrderId)) + "\nDistance Left: " + (DriverVolunteer::getDistanceLeft()==0 ? "NONE":to_string(DriverVolunteer::getDistanceLeft())) 
    +"\nOrdersLeft:"+ std::to_string(ordersLeft); 
}
string LimitedDriverVolunteer::typeOf() const{return "LIMITED_DRIVER";}
