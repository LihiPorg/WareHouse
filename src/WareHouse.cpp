#include "../include/WareHouse.h"



WareHouse::WareHouse(const string &configFilePath):isOpen(false), actionsLog(), 
                volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), 
                customers(), customerCounter(0), volunteerCounter(0),orderCounter(0),
                defultVolunteer(new CollectorVolunteer(-1,"defult",-1)){
                
    std::ifstream file(configFilePath);
    std::string   line;

    while(std::getline(file, line)) //run on all lines
    {
        std::stringstream   linestream(line);
        std::string         data1; // customer/volenteer
        std::string         data2; //name of customer/vullenteer
        std::string         data3;//type/role
        int                 val1;//vulonteer- cooldown/max distance costumer-distance
        int                 val2;//volunteer- distemce per step(only drivers) customers-max order
        int                 val3;//volunteer- max order (optional)

        // If you have truly tab delimited data use getline() with third parameter.
        // If your data is just white space separated data
        // then the operator >> will do (it reads a space separated word into a string).
        std::getline(linestream, data1, ' ');  // read up-to the first tab (discard tab).
        if(data1 == "customer" || data1 == "volunteer"){
            // Read the integers using the operator >>
            linestream >>data2 >> data3 >> val1 >> val2 >> val3; 
            if(data1 == "customer" && data3 == "civilian"){
                customers.push_back(new CivilianCustomer(customerCounter, data2, val1, val2));
                customerCounter++;
            }
            if(data1 == "customer" && data3 == "soldier"){
                customers.push_back(new SoldierCustomer(customerCounter, data2, val1, val2));
                customerCounter++;
            }
            if(data1 == "volunteer" && data3 == "collector"){
                volunteers.push_back(new CollectorVolunteer(volunteerCounter, data2, val1));
                volunteerCounter++;
            }
            if(data1 == "volunteer" && data3 == "driver"){
                volunteers.push_back(new DriverVolunteer(volunteerCounter, data2, val1, val2));
                volunteerCounter++;
            }
            if(data1 == "volunteer" && data3 == "limited_collector"){
                volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, data2, val1, val2));
                volunteerCounter++;
            }
            if(data1 == "volunteer" && data3 == "limited_driver"){
                volunteers.push_back(new LimitedDriverVolunteer(volunteerCounter, data2, val1, val2,val3));
                volunteerCounter++;
            }
        }
    }

}

WareHouse::WareHouse(const WareHouse& other):isOpen(other.isOpen),actionsLog(),volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), 
                customers(),customerCounter(other.customerCounter),
                volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter),defultVolunteer(other.defultVolunteer->clone())
{
    for (BaseAction* ba: other.actionsLog){
        actionsLog.push_back (ba-> clone());
    }
    for (Volunteer* v: other.volunteers){
        volunteers.push_back (v-> clone());
    }
    for (Customer* c: other.customers){
        customers.push_back (c-> clone());
    }
    for (Order* o: other.inProcessOrders){
        inProcessOrders.push_back(new Order(*o));
    }
    for (Order* o: other.pendingOrders){
        pendingOrders.push_back(new Order(*o));
    }
     for (Order* o: other.completedOrders){
        completedOrders.push_back(new Order(*o));
    }
    
}

WareHouse::WareHouse(WareHouse&& other):isOpen(other.isOpen),
    actionsLog(),volunteers(),pendingOrders(), inProcessOrders(),completedOrders(),customers()
    ,customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter)
    ,defultVolunteer(other.defultVolunteer)
{
    other.defultVolunteer=nullptr;
    for (int i=0; i <(int)other.actionsLog.size() ; i++ ){
        actionsLog.push_back(other.actionsLog.at(i));
    }
    for (int i=0; i <(int)other.actionsLog.size() ; i++ ){
        delete other.actionsLog.at(i);
        actionsLog[i]=nullptr;
    }
    other.actionsLog.clear();


    for (int i=0; i <(int)other.volunteers.size() ; i++ ){
        volunteers.push_back(other.volunteers.at(i));
    }
    for (int i=0; i <(int)other.volunteers.size() ; i++ ){
        delete other.volunteers.at(i);
        volunteers[i]=nullptr;
    }
    other.volunteers.clear();


    for (int i=0; i <(int)other.customers.size() ; i++ ){
        customers.push_back(other.customers.at(i));
    }
    for (int i=0; i <(int)other.customers.size() ; i++ ){
        delete other.customers.at(i);
        customers[i]=nullptr;
    }
    other.customers.clear();


    for (int i=0; i <(int)other.inProcessOrders.size() ; i++ ){
        inProcessOrders.push_back(other.inProcessOrders.at(i));
    }
    for (int i=0; i <(int)other.inProcessOrders.size() ; i++ ){
        delete other.inProcessOrders.at(i);
        inProcessOrders[i]=nullptr;
    }
    other.inProcessOrders.clear();


    for (int i=0; i <(int)other.pendingOrders.size() ; i++ ){
        pendingOrders.push_back(other.pendingOrders.at(i));
    }
    for (int i=0; i <(int)other.pendingOrders.size() ; i++ ){
        delete other.pendingOrders.at(i);
        pendingOrders[i]=nullptr;
    }
    other.pendingOrders.clear();


    for (int i=0; i <(int)other.completedOrders.size() ; i++ ){
        completedOrders.push_back(other.completedOrders.at(i));
    }
    for (int i=0; i <(int)other.completedOrders.size() ; i++ ){
        delete other.completedOrders.at(i);
        completedOrders[i]=nullptr;
    }
    other.completedOrders.clear();
}

WareHouse::~WareHouse(){
    delete defultVolunteer;
    defultVolunteer = nullptr;
    for (int i=0; i<(int) actionsLog.size(); i++){
        delete actionsLog[i];
        actionsLog[i] = nullptr;
    }   
    actionsLog.clear();
    for (int i=0; i<(int) volunteers.size(); i++){
        delete volunteers[i];
        volunteers[i] = nullptr;
    }
    volunteers.clear();
    for (int i=0; i<(int) customers.size(); i++){
        delete customers[i];
        customers[i] = nullptr;
    }
    customers.clear();
    for (int i=0; i<(int)pendingOrders.size(); i++){
        delete pendingOrders[i];
        pendingOrders[i] = nullptr;
    }
    pendingOrders.clear();
    for (int i=0; i<(int)inProcessOrders.size(); i++){
        delete inProcessOrders[i];
        inProcessOrders[i] = nullptr;
    }
    inProcessOrders.clear();
    for (int i=0; i<(int)completedOrders.size(); i++){
        delete completedOrders[i];
        completedOrders[i] = nullptr;
    }
    completedOrders.clear();
}




WareHouse & WareHouse::operator=(WareHouse&& other){
    if(this!=&other){
        for (int i=0; i <(int)actionsLog.size() ; i++ ){
            delete actionsLog.at(i);
            actionsLog[i]=nullptr;
        }
        actionsLog.clear();
        for (int i=0; i <(int)other.actionsLog.size() ; i++ ){
            actionsLog.push_back(other.actionsLog.at(i));
        }
        for (int i=0; i <(int)other.actionsLog.size() ; i++ ){
            delete other.actionsLog.at(i);
            actionsLog[i]=nullptr;
        }
        other.actionsLog.clear();


        for (int i=0; i <(int)volunteers.size() ; i++ ){
            delete volunteers.at(i);
            volunteers[i]=nullptr;
        }
        volunteers.clear();
        for (int i=0; i <(int)other.volunteers.size() ; i++ ){
            volunteers.push_back(other.volunteers.at(i));
        }
        for (int i=0; i <(int)other.volunteers.size() ; i++ ){
            delete other.volunteers.at(i);
            volunteers[i]=nullptr;
        }
        other.volunteers.clear();


        for (int i=0; i <(int)customers.size() ; i++ ){
            delete customers.at(i);
            customers[i]=nullptr;
        }
        customers.clear();
        for (int i=0; i <(int)other.customers.size() ; i++ ){
            customers.push_back(other.customers.at(i));
        }
        for (int i=0; i <(int)other.customers.size() ; i++ ){
            delete other.customers.at(i);
            customers[i]=nullptr;
        }
        other.customers.clear();


        for (int i=0; i <(int)inProcessOrders.size() ; i++ ){
            delete inProcessOrders.at(i);
            inProcessOrders[i]=nullptr;
        }
        inProcessOrders.clear();
        for (int i=0; i <(int)other.inProcessOrders.size() ; i++ ){
            inProcessOrders.push_back(other.inProcessOrders.at(i));
        }
        for (int i=0; i <(int)other.inProcessOrders.size() ; i++ ){
            delete other.inProcessOrders.at(i);
            inProcessOrders[i]=nullptr;
        }
        other.inProcessOrders.clear();


        for (int i=0; i <(int)pendingOrders.size() ; i++ ){
            delete pendingOrders.at(i);
            pendingOrders[i]=nullptr;
        }
        pendingOrders.clear();
        for (int i=0; i <(int)other.pendingOrders.size() ; i++ ){
            pendingOrders.push_back(other.pendingOrders.at(i));
        }
        for (int i=0; i <(int)other.pendingOrders.size() ; i++ ){
            delete other.pendingOrders.at(i);
            pendingOrders[i]=nullptr;
        }
        other.pendingOrders.clear();


        for (int i=0; i <(int)completedOrders.size() ; i++ ){
            delete completedOrders.at(i);
            completedOrders[i]=nullptr;
        }
        completedOrders.clear();
        for (int i=0; i <(int)other.completedOrders.size() ; i++ ){
            completedOrders.push_back(other.completedOrders.at(i));
        }
        for (int i=0; i <(int)other.completedOrders.size() ; i++ ){
            delete other.completedOrders.at(i);
            completedOrders[i]=nullptr;
        }
        other.completedOrders.clear();

        defultVolunteer=other.defultVolunteer;
        other.defultVolunteer=nullptr;
        customerCounter=other.customerCounter; 
        volunteerCounter=other.volunteerCounter; 
        orderCounter=other.customerCounter; 
        isOpen=other.isOpen;
    }
    return *this;
}


WareHouse& WareHouse::operator=(const WareHouse& other){
    if (&other != this) {
        isOpen=other.isOpen;
        customerCounter=other.customerCounter;
        volunteerCounter=other.volunteerCounter;
        orderCounter=other.orderCounter;
        delete (defultVolunteer);
        defultVolunteer = other.defultVolunteer->clone();
        
        for (int i=0; i <(int)actionsLog.size() ; i++ ){
            delete actionsLog.at(i);
            actionsLog.at(i) = nullptr;
        }
        actionsLog.clear();
        for (int i=0; i <(int)other.actionsLog.size() ; i++ ){
            actionsLog.push_back(other.actionsLog.at(i)->clone());
        }
        for (int i=0; i <(int)volunteers.size() ; i++ ){
            delete volunteers.at(i);
            volunteers.at(i) = nullptr;
            }
        volunteers.clear();
        for (int i=0; i <(int)other.volunteers.size() ; i++ ){
            volunteers.push_back(other.volunteers.at(i)->clone());
        }

        for (int i=0; i <(int)pendingOrders.size() ; i++ ){
            delete pendingOrders.at(i);
            pendingOrders.at(i) = nullptr;
        }
        pendingOrders.clear();
        for (int i=0; i <(int)other.pendingOrders.size() ; i++ ){
            pendingOrders.push_back(new Order(*other.pendingOrders.at(i)));
        }

        for (int i=0; i <(int)customers.size() ; i++ ){
            delete customers.at(i);
            customers.at(i) = nullptr;
        }
        customers.clear();
        for (int i=0; i <(int)other.customers.size() ; i++ ){
            customers.push_back(other.customers.at(i)->clone());
        }

        for (int i=0; i <(int)completedOrders.size() ; i++ ){
            delete completedOrders.at(i);
            completedOrders.at(i) = nullptr;
        }
        completedOrders.clear();
        for (int i=0; i <(int)other.completedOrders.size() ; i++ ){
            completedOrders.push_back(new Order(*other.completedOrders.at(i)));
        }
        
        for (int i=0; i <(int)inProcessOrders.size() ; i++ ){
            delete inProcessOrders.at(i);
            inProcessOrders.at(i) = nullptr;
        }
        inProcessOrders.clear();
        for (int i=0; i <(int)other.inProcessOrders.size() ; i++ ){
            inProcessOrders.push_back(new Order(*other.inProcessOrders.at(i)));
        }
    
    }
    return *this;
}








void WareHouse::start() 
{
    open();
    string line="";
    
    while(isOpen)
    {
        BaseAction* acts=nullptr;
        std::getline(cin,line);
        std::stringstream    linestream(line);
        std::string          data1; // action
        std::string          data2;//id/numofsteps/name
        std::string          data3;//customertype
        int                  val1;// distance
        int                  val2;// max order
        //std::getline(linestream, data1, ' ');  // read up-to the first tab (discard tab).
        linestream >>data1>>data2 >> data3 >> val1 >> val2 ; 
        if(data1=="step")
        {
            acts=new SimulateStep(stoi(data2));
        } else if(data1=="order")
        {
            acts=new AddOrder(stoi(data2));
        } else if(data1=="customer")
        {
            acts=new AddCustomer(data2,data3,val1,val2);
        } else if(data1=="volunteerStatus")
        {
            acts=new PrintVolunteerStatus(stoi(data2));
        } else if(data1=="customerStatus")
        {
            acts=new PrintCustomerStatus(stoi(data2));
        } else if(data1=="orderStatus")
        {
            acts=new PrintOrderStatus(stoi(data2));
        } else if(data1=="log")
        {
            acts=new PrintActionsLog();
        } else if(data1=="backup")
        {
            acts=new BackupWareHouse();
        } else if(data1=="restore")
        {
            acts=new RestoreWareHouse();
        } else if(data1 == "close"){
            acts=new Close();
        } else {
            cerr << "invalid command" << endl;
            continue; 
        }
        acts->act(*this);
        actionsLog.push_back(acts);
        
    }
    
}
void WareHouse::addCustomer(Customer* customer){
    customers.push_back(customer);
    customerCounter++;
}
void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
    orderCounter++;
}


void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

Customer & WareHouse::getCustomer(int customerId) const
{
    for (Customer* c:customers)
    {
        if(c->getId()==customerId)
        {
            return *c;
        }
    }
    static Customer* cus=new CivilianCustomer(-1,"defult",-1,-1);
    return *cus;
}
Volunteer & WareHouse::getVolunteer(int volunteerId) const
{
    for (Volunteer* v:volunteers)
    {
        if(v->getId()==volunteerId)
        {
            return *v;
        }
    }
    return *defultVolunteer;
}
Order& WareHouse::getOrder(int orderId) const
{
    
    for (Order* o:pendingOrders)
    {
        if(o->getId()==orderId)
        {
            return *o;
        }
    }
    for (Order* o:completedOrders)
    {
        if(o->getId()==orderId)
        {
            return *o;
        }
    }
    for (Order* o:inProcessOrders)
    {
        if(o->getId()==orderId)
        {
            return *o;
        }
    }
    static Order* ord=new Order(-1,-1,-1);
    return *ord;
}
void WareHouse::allStep()
{
    vector<Order*>::iterator it = pendingOrders.begin();
    while(it!=pendingOrders.end())
    {
        bool flag=false;
        if ((*it)->getStatus()==OrderStatus::PENDING){

            for (Volunteer* v:volunteers){
                    if((v->typeOf()=="COLLECTOR" || v->typeOf()=="LIMITED_COLLECTOR")&&v->canTakeOrder(**it))
                    {
                        v->acceptOrder(**it);
                        (**it).setStatus(OrderStatus::COLLECTING);
                        (**it).setCollectorId((*v).getId());
                        inProcessOrders.push_back(*it);
                        it=pendingOrders.erase(it);
                        flag=true;
                        break;
                    }
            }
            
            }
        else{

            if ((*it)->getStatus()==OrderStatus::COLLECTING){
                for (Volunteer* v:volunteers){
                    if((v->typeOf()=="DRIVER" || v->typeOf()=="LIMITED_DRIVER")&&v->canTakeOrder(**it))
                    { 
                        v->acceptOrder(**it);
                        (**it).setStatus(OrderStatus::DELIVERING);
                        (**it).setDriverId((*v).getId());
                        inProcessOrders.push_back(*it);
                        it=pendingOrders.erase(it);
                        flag=true;
                        break;
                    }
                }
            }
        }
        if(!flag)
            it++;

    }
    vector<Volunteer*>::iterator itv = volunteers.begin();
    while (itv!=volunteers.end())
    {
        (*itv)->step();
        int orderid = (*itv)->getCompletedOrderId();
        if(orderid !=-1) 
        {
            vector<Order*>::iterator ito = inProcessOrders.begin();
            while(ito!=inProcessOrders.end())
            {
                if((*ito)->getId()==orderid)
                {
                    if(((*itv)->typeOf()=="DRIVER" || (*itv)->typeOf()=="LIMITED_DRIVER"))
                        {
                            (*ito)->setStatus(OrderStatus::COMPLETED);
                            completedOrders.push_back(*ito);
                            ito=inProcessOrders.erase(ito);
                            
                        }   
                    if(((*itv)->typeOf()=="COLLECTOR" || (*itv)->typeOf()=="LIMITED_COLLECTOR"))
                        {
                            pendingOrders.push_back(*ito);
                            ito=inProcessOrders.erase(ito);    
                        } 
                    if(!((*itv)->hasOrdersLeft())&& !(*itv)->isBusy())
                        {
                            delete(*itv);
                            itv=volunteers.erase(itv); 
                        }
                    break;
                }
                else
                    ito++;
            }
        }
        else
            itv++;
    }
}
int WareHouse::getOrderCounter() const 
{
    return orderCounter;
}
int WareHouse::getVolunteerCounter() const 
{
    return volunteerCounter;
}
int WareHouse::getCustomerCounter() const 
{
    return customerCounter;
}
const vector<BaseAction*> & WareHouse::getActions() const{return actionsLog;}
void WareHouse::close()
{
    isOpen=false;
    for (Order* o:pendingOrders)
    {
        cout<<"OrderID: " +to_string(o->getId())+", "+"CustomerID: "+ to_string(o->getCustomerId())+", "+"OrderStatus: "+o->getStatusStr()<<endl;
    }
    for (Order* o:inProcessOrders)
    {
        cout<<"OrderID: " +to_string(o->getId())+", "+"CustomerID: "+ to_string(o->getCustomerId())+", "+"OrderStatus: "+o->getStatusStr()<<endl;
    }
    for (Order* o:completedOrders)
    { 
        cout<<"OrderID: " +to_string(o->getId())+", "+"CustomerID: "+ to_string(o->getCustomerId())+", "+"OrderStatus: "+o->getStatusStr()<<endl;
    }
    
}
void WareHouse::open()
{
    isOpen= true;
    cout<<"Warehouse is open!"<<endl;
}

