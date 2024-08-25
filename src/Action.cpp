#include "../include/Action.h"
extern WareHouse* backup;


BaseAction::BaseAction():errorMsg(""),status(ActionStatus::COMPLETED){}
ActionStatus BaseAction::getStatus() const{return status;}
void BaseAction::complete(){
    status=ActionStatus::COMPLETED; 
}
void BaseAction::error(string errorMsg)
{
    status=ActionStatus::ERROR;
    this->errorMsg=errorMsg;
}
string BaseAction::getErrorMsg() const{return "Error: "+errorMsg;}
string BaseAction::getStatusStr() const
{
    switch (getStatus())
    {
        case ActionStatus::COMPLETED:   return "COMPLETED";
        case ActionStatus::ERROR:   return "ERROR: "+errorMsg;
    
    }
    return "";
}


SimulateStep::SimulateStep(int numOfSteps):numOfSteps(numOfSteps){}
void SimulateStep::act(WareHouse &wareHouse)
{
    for (int i=1; i<=numOfSteps ; i++){
        wareHouse.allStep();
    }
    complete();
}
std::string SimulateStep::toString() const{
    return "simulateStep "+to_string(numOfSteps)+" "+getStatusStr();
}

SimulateStep* SimulateStep::clone() const{return new SimulateStep(*this);};




AddOrder::AddOrder(int id):customerId(id){}
    
void AddOrder::act(WareHouse &wareHouse) 
{
    Customer& c=wareHouse.getCustomer(customerId);
    if (c.getId()==-1||!c.canMakeOrder())
    {
       error("Cannot place this order");
       cout<< getErrorMsg()<<endl;
    }
    else 
    {
       Order* o=new Order(wareHouse.getOrderCounter(),customerId,c.getCustomerDistance());
       wareHouse.addOrder(o);
       c.addOrder(o->getId());
       complete();
    }
}

string AddOrder::toString() const {return "Order "+to_string(customerId)+" "+getStatusStr();}

AddOrder * AddOrder::clone() const {return new AddOrder (*this);}



AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders)
:customerName(customerName),customerType((customerType=="soldier")?CustomerType::Soldier:CustomerType::Civilian),distance(distance),maxOrders(maxOrders){}
void AddCustomer::act(WareHouse &wareHouse) 
{
    if(customerType==CustomerType::Soldier)
    {
        SoldierCustomer* c=new SoldierCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
        wareHouse.addCustomer(c);
    }
    if(customerType==CustomerType::Civilian)
    {
        CivilianCustomer* c=new CivilianCustomer(wareHouse.getCustomerCounter(),customerName,distance,maxOrders);
        wareHouse.addCustomer(c);
    }
    complete();
}
AddCustomer* AddCustomer::clone() const {return new AddCustomer(*this);}
string AddCustomer::toString() const 
{
    string type="";
    switch (customerType)
    {
        case CustomerType::Soldier:   type= "soldier";
        case CustomerType::Civilian:   type= "civilian";
    }
    return "Customer "+customerName+" "+type+" "+to_string(distance)+" "+to_string(maxOrders)+" "+getStatusStr();
}
PrintOrderStatus::PrintOrderStatus(int id):orderId(id){}
void PrintOrderStatus::act(WareHouse &wareHouse) {
    if (orderId>= wareHouse.getOrderCounter()){
        error("Order doesn't exist");
        cout <<  getErrorMsg()<<endl;
    }
    else{
        Order& o = wareHouse.getOrder(orderId);
        cout << o.toString()<<endl;
        complete();
    }

}
PrintOrderStatus * PrintOrderStatus::clone() const {return new PrintOrderStatus(*this);}

string PrintOrderStatus::toString() const {
    return "orderStatus "+ to_string(orderId)+" "+ getStatusStr(); 
}



PrintCustomerStatus::PrintCustomerStatus(int customerId):customerId(customerId){}
void PrintCustomerStatus::act(WareHouse &wareHouse) 
{
    if(wareHouse.getCustomerCounter()<=customerId)
    {
        error("Customer doesn't exist");
        cout << getErrorMsg()<<endl;
    }
    else
    {
        cout<<"customerID: " +to_string(customerId)<<endl;
        Customer& c= wareHouse.getCustomer(customerId);
        vector<int> ordersId = c.getOrdersIds();
        for (int i: ordersId){
            cout<< "orderId: " + to_string(i)<<endl;
            cout<<"order status: " + wareHouse.getOrder(i).getStatusStr()<<endl;
        }
        cout<<"Num orders left: " +to_string(c.getNumordersleft())<<endl;
        complete();
    }
}
PrintCustomerStatus * PrintCustomerStatus::clone() const {return new PrintCustomerStatus(*this);}
string PrintCustomerStatus::toString() const 
{
    return "customerStatus "+to_string(customerId)+" "+getStatusStr();
}


PrintVolunteerStatus::PrintVolunteerStatus(int id):volunteerId(id){}
void PrintVolunteerStatus::act(WareHouse &wareHouse) {
    Volunteer& v=wareHouse.getVolunteer(volunteerId);
    if(v.getId()==-1)
    {
      error("Volunteer doesn't exist");
      cout << getErrorMsg()<<endl;
    }
    else
    {
      cout << v.toString()<<endl;
      complete();
    }
}
PrintVolunteerStatus * PrintVolunteerStatus::clone() const{return new PrintVolunteerStatus(*this);}
string PrintVolunteerStatus::toString() const 
{
    return "volunteerStatus "+to_string(volunteerId)+" "+getStatusStr();
}


PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(WareHouse &wareHouse) 
{
    const vector<BaseAction*> & actions=wareHouse.getActions();
    for(BaseAction* ba:actions)
    {
        cout<<ba->toString()<<endl;
    }
    complete();
}
PrintActionsLog * PrintActionsLog::clone() const {return new PrintActionsLog(*this);}
string PrintActionsLog::toString() const {return "log "+getStatusStr();}


Close::Close(){}
void Close::act(WareHouse &wareHouse) 
{
    complete();
    wareHouse.close();
}
Close * Close::clone() const {return new Close(*this);}
string Close::toString() const {return "close "+getStatusStr(); }

BackupWareHouse::BackupWareHouse(){}
void BackupWareHouse::act(WareHouse &wareHouse) {
    if(backup!=nullptr)
    {
       delete backup;  
       backup = nullptr;
    }
    backup =new WareHouse(wareHouse);
    complete();
}
BackupWareHouse * BackupWareHouse::clone() const{return new BackupWareHouse (*this);}
string BackupWareHouse::toString() const {
    return "backup "+getStatusStr();
}

RestoreWareHouse::RestoreWareHouse(){}
void RestoreWareHouse::act(WareHouse &wareHouse) {
    if (backup==nullptr){
        error("No backup available");
        cout<< getErrorMsg()<<endl;
    }
    else 
    {
        wareHouse=*backup;
        complete();
    }
}
RestoreWareHouse * RestoreWareHouse::clone() const {return new RestoreWareHouse (*this); }
string RestoreWareHouse::toString() const {return "restore "+getStatusStr();}






















