# WareHouse
This project is a C++ implementation of a Warehouse Management System, designed to simulate the operations of a warehouse. 
The system operates through a command-line interface and is built using object-oriented programming principles, including the "Rule of Five" in C++.

Features
Warehouse Operations: Simulates handling orders, assigning volunteers, processing orders, and managing customer interactions.
Customer and Volunteer Management: Supports different types of customers (Soldier, Civilian) and volunteers (Collector, Limited Collector, Driver, Limited Driver).
Interactive Commands: Provides actions for placing orders, creating new customers, checking order status, performing simulation steps, and more.

Getting Started
Prerequisites
Make sure you have a C++ compiler installed on your system.

Installation
*Clone the Repository
*Navigate to the Project Directory
*Compile the source files using the provided makefile: "make"

Execute the compiled binary with a path to a configuration file as the first command-line argument:
./bin/warehouse <path_to_configuration_file>
Replace <path_to_configuration_file> with the actual path to your configuration file.

Configuration File Format
The configuration file should define the initial state of the warehouse, including customers and volunteers. 
Each line in the file represents either a customer or a volunteer. Below is an example:

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
Ensure that the configuration file adheres to the format for proper initialization.

Usage
After running the program, the warehouse will initialize based on the provided configuration file. 
The program will then enter a simulation mode where you can input commands to manage the warehouse.
The available commands and their usage will be prompted within the command-line interface.

License
This project is licensed under the MIT License.

