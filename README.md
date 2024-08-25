# WareHouse
Warehouse Management System
This project is a C++ implementation of a Warehouse Management System, designed to simulate the operations of a warehouse. The system operates through a command-line interface and is built using object-oriented programming principles, including the "Rule of Five" in C++.

Features
Warehouse Operations: Simulates handling orders, assigning volunteers, processing orders, and managing customer interactions.
Customer and Volunteer Management: Supports different types of customers (Soldier, Civilian) and volunteers (Collector, Limited Collector, Driver, Limited Driver).
Interactive Commands: Provides actions for placing orders, creating new customers, checking order status, performing simulation steps, and more.
Getting Started
Prerequisites
Ensure that you have a C++ compiler installed on your system.

Installation
Clone the Repository:

bash
Copy code
git clone https://github.com/your-username/warehouse-management-system.git
Navigate to the Project Directory:

bash
Copy code
cd warehouse-management-system
Compile the Source Files:

Use the provided makefile to compile the project:

bash
Copy code
make
Run the Program:

Execute the compiled binary with a path to a configuration file as the first command-line argument:

bash
Copy code
./bin/warehouse <path_to_configuration_file>
Replace <path_to_configuration_file> with the actual path to your configuration file.

Configuration File Format
The configuration file should define the initial state of the warehouse, including customers and volunteers. Each line in the file represents either a customer or a volunteer. Below is an example:

text
Copy code
customer Maya soldier 4 2
customer David civilian 3 1
volunteer Noya collector 2
volunteer Ibrahim limited_collector 3 2
volunteer Din limited_driver 13 4 2
volunteer Limor driver 8 3
Configuration File Guidelines
Customers:
customer <Name> <Type> <OrdersPlaced> <OrdersCompleted>
Volunteers:
volunteer <Name> <Role> <Attribute1> <Attribute2> ...
Ensure that the configuration file adheres to this format for proper initialization.

Usage
After running the program, the warehouse will initialize based on the provided configuration file. The program will then enter a simulation mode where you can input commands to manage the warehouse. The available commands and their usage will be prompted within the command-line interface.

License
This project is licensed under the MIT License.

