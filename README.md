# Purchase and Customer Management System

## Overview
This project is a simple Purchase and Customer Management System implemented in C++. It allows users to manage customers and their purchases, providing functionalities to add, update, delete, and display customer and purchase information. The system also allows saving and loading data from files.

## Features
- Add, update, and delete customer information
- Add and display purchase information
- Display total spend for a customer
- Save and load customer and purchase data from files
- Print all customers and purchases
- Sort customers by account number

## Dependencies
The project uses the following standard C++ libraries:
- `<iostream>` for input/output operations
- `<string>` for string manipulations
- `<vector>` for dynamic array handling
- `<fstream>` for file input/output operations
- `<algorithm>` for sorting and other algorithm operations
- `<sstream>` for string stream manipulations
- `<iomanip>` for input/output formatting
- `<limits>` for handling input limits

## Classes
### Purchase
Represents a single purchase with the following attributes:
- `accountNumber`: An integer representing the account number
- `item`: A string representing the item name
- `date`: A string representing the purchase date
- `amount`: A double representing the purchase amount

### AllPurchases
Manages a collection of `Purchase` objects and provides functionalities to:
- Load purchases from a file
- Print all purchases
- Print purchases by account number
- Print total spend for a customer
- Add new purchases
- Save purchases to a file

### Customer
Represents a customer with the following attributes:
- `firstName`: A string representing the first name
- `lastName`: A string representing the last name
- `accountNumber`: An integer representing the account number
- `streetAddress`: A string representing the street address
- `city`: A string representing the city
- `state`: A string representing the state
- `zipCode`: A string representing the ZIP code
- `phoneNumber`: A string representing the phone number

### AllCustomers
Manages a collection of `Customer` objects and provides functionalities to:
- Load customers from a file
- Print all customers
- Print sorted customers
- Print customer account information
- Print total spend for a customer
- Add new customers
- Update and delete customer information
- Save customers to a file

## Usage
1. **Compile the code** using a C++ compiler:
   ```sh
   g++ -o customer_management main.cpp
