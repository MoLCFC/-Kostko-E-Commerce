#include <iostream>     // Import the input/output library
#include <string>       // Import the string library
#include <vector>       // Import the vector library
#include <fstream>      // Import the file input/output library
#include <algorithm>    // Import the algorithm library
#include <sstream>      // Import the string stream library
#include <iomanip>      // Import the input/output manipulator library
#include <limits>       // Import the limits library


// Created by Mahmood Gheith

using namespace std;

class Purchase {// Define a class called "Purchase"
public:
    Purchase(int accountNumber, const string& item, const string& date, double amount)    // Define a constructor that takes four parameters
        : accountNumber(accountNumber), item(item), date(date), amount(amount) {          // Initialize the class variables with the values passed in the constructor
    }

    int getAccountNumber() const { return accountNumber; }  // Define a function that returns the account number
    string getItem() const { return item; }                  // Define a function that returns the item name
    string getDate() const { return date; }                  // Define a function that returns the purchase date
    double getAmount() const { return amount; }              // Define a function that returns the purchase amount

private:
    int accountNumber;      // Define a private integer variable called "accountNumber"
    string item;            // Define a private string variable called "item"
    string date;            // Define a private string variable called "date"
    double amount;          // Define a private double variable called "amount"
};

class AllPurchases {    // Define a class called "AllPurchases"
public:
    void loadPurchasesFromFile(const string& filename);    // Define a function to load purchases from a file
    void printAllPurchases() const;                        // Define a function to print all purchases
    void printPurchasesByAccountNumber(int accountNumber) const;   // Define a function to print purchases by account number
    void printTotalSpendForCustomer(int accountNumber) const;      // Define a function to print total spend for a customer
    void addNewPurchase(const Purchase& purchase);          // Define a function to add a new purchase
    void addMultiplePurchasesRecursive(int accountNumber, int count);   // Define a function to add multiple purchases recursively
    void savePurchasesToFile(const string& filename) const; // Define a function to save purchases to a file

private:
    vector<Purchase> purchases;     // Define a private vector of Purchase objects called "purchases"
};

class Customer {    // Define a class called "Customer"
public:
    Customer() = default;   // Define a default constructor

    Customer(const string& firstName, const string& lastName, int accountNumber, const string& streetAddress, const string& city, const string& state, const string& zipCode, const string& phoneNumber)
        : firstName(firstName), lastName(lastName), accountNumber(accountNumber), streetAddress(streetAddress), city(city), state(state), zipCode(zipCode), phoneNumber(phoneNumber) {
    }   // Define a constructor that takes eight parameters and initializes the class variables with the values passed in the constructor

    string getFirstName() const { return firstName; }     // Define a function that returns the first name
    string getLastName() const { return lastName; }       // Define a function that returns the last name
    int getAccountNumber() const { return accountNumber; } // Define a function that returns the account number
    string getStreetAddress() const { return streetAddress; }    // Define a function that returns the street address
    string getCity() const { return city; }                      // Define a function that returns the city
    string getState() const { return state; }                    // Define a function that returns the state
    string getZIPCode() const { return zipCode; }                // Define a function that returns the ZIP code
    string getPhoneNumber() const { return phoneNumber; }        // Define a function that returns the phone number

    void setFirstName(const string& firstName) { this->firstName = firstName; }      // Define a function that sets the first name
    void setLastName(const string& lastName) { this->lastName = lastName; }         // Define a function that sets the last name
    void setStreetAddress(const string& streetAddress) { this->streetAddress = streetAddress; }    // Define a function that sets the street address
    void setCity(const string& city) { this->city = city; }                            // Define a function that sets the city
    void setState(const string& state) { this->state = state; }                        // Define a function that sets the state
    void setZIPCode(const string& zipCode) { this->zipCode = zipCode; }                // Define a function that sets the ZIP code
    void setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }    // Define a function that sets the phone number

private:
    string firstName;       // Define a private string variable called "firstName"
    string lastName;        // Define a private string variable called "lastName"
    int accountNumber;      // Define a private integer variable called "accountNumber"
    string streetAddress;   // Define a private string variable called "streetAddress"
    string city;            // Define a private string variable called "city"
    string state;           // Define a private string variable called "state"
    string zipCode;         // Define a private string variable called "zipCode"
    string phoneNumber;     // Define a private string variable called "phoneNumber"

};

// Define a class called "AllCustomers"
class AllCustomers {
public:
    void loadCustomersFromFile(const string& filename); // Define a function to load customers from a file
    void printCustomers() const; // Define a function to print all customers
    void printSortedCustomers(bool ascending) const; // Define a function to print sorted customers
    void printCustomerAccountInfo(const AllPurchases& allPurchases, int accountNumber) const; // Define a function to print customer account info
    void printTotalSpendForCustomer(int accountNumber) const; // Define a function to print total spend for a customer
    void addCustomer(const Customer& customer); // Define a function to add a new customer
    void addMultipleCustomersRecursive(int count); // Define a function to add multiple customers recursively
    Customer* findCustomer(int accountNumber) { // Define a function to find a customer by account number and return a pointer to that customer
        for (auto& customer : customers) {
            if (customer.getAccountNumber() == accountNumber) {
                return &customer;
            }
        }
        return nullptr; // No customer with the given account number found
    }

    const Customer* findCustomer(int accountNumber) const {   // Define a const function to find a customer by account number and return a pointer to that customer
        for (const auto& customer : customers) {
            if (customer.getAccountNumber() == accountNumber) {
                return &customer;
            }
        }
        return nullptr;  // No customer with the given account number found
    }
    bool updateCustomer(int accountNumber, const Customer& updatedCustomer);   // Define a function to update a customer
    bool deleteCustomer(int accountNumber);                 // Define a function to delete a customer
    void saveCustomersToFile(const string& filename) const; // Define a function to save customers to a file
    const vector<Customer>& getCustomers() const;           // Add a getter for customers



private:
    vector<Customer> customers; // Define a private vector of Customer objects called "customers"
    vector<Purchase> purchases; // Define a private vector of Purchase objects called "purchases"
};

void AllPurchases::loadPurchasesFromFile(const string& filename) {
    ifstream file(filename); // Open the file for reading
    if (!file) { // Check if the file was opened successfully
        cerr << "Unable to open file :" << filename << endl; // Print an error message if the file could not be opened
        return;
    }

    int accountNumber;  // Declare a variable to store account number
    string item, date;  // Declare variables to store item and date
    double amount;      // Declare a variable to store amount

    while (file >> accountNumber >> item >> date >> amount) {   // Read the data from the file and create a new Purchase object
        addNewPurchase(Purchase(accountNumber, item, date, amount));   // Add the new Purchase object to the purchases vector
    }

    file.close();   // Close the file
}

// Print all purchases
void AllPurchases::printAllPurchases() const {
    // Check if the purchases vector is empty
    if (purchases.empty()) {
        cout << "No purchases found." << endl;
        return;
    }

    // Print the header
    cout << "All Purchases:" << endl;
    cout << "-------------------------" << endl;

    // Loop through each purchase and print its data
    for (const auto& purchase : purchases) {
        cout << "Account number: " << purchase.getAccountNumber() << endl;
        cout << "Item: " << purchase.getItem() << endl;
        cout << "Date: " << purchase.getDate() << endl;
        cout << "Amount: $" << fixed << setprecision(2) << purchase.getAmount() << endl;
        cout << "-------------------------" << endl;
    }
}

// Print purchases by account number
void AllPurchases::printPurchasesByAccountNumber(int accountNumber) const {
    // Loop through each purchase and print the data of purchases with the given account number
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            cout << "Item: " << purchase.getItem() << ", "
                << "Date: " << purchase.getDate() << ", "
                << "Amount: " << purchase.getAmount() << endl;
        }
    }
}

// Print the total amount spent by a customer
void AllPurchases::printTotalSpendForCustomer(int accountNumber) const {
    // Declare a variable to store the total amount spent
    double total = 0;
    // Loop through each purchase and add the amount spent to the total if the purchase has the given account number
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            total += purchase.getAmount();
        }
    }
    // Print the total amount spent
    cout << "Total spent by customer with account number " << accountNumber << ": " << total << endl;
}
// Adds a new purchase to the list of all purchases
void AllPurchases::addNewPurchase(const Purchase& purchase) {
    purchases.push_back(purchase);
}

// Adds multiple purchases to the list recursively
void AllPurchases::addMultiplePurchasesRecursive(int accountNumber, int count) {
    // Base case: stop recursion when count reaches 0 or less
    if (count <= 0) {
        return;
    }

    // Get input for new purchase
    string item, date;
    double amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter item: ";
    getline(cin, item);

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter amount: ";
    cin >> amount;
    cin.ignore();

    // Add the new purchase to the list
    addNewPurchase(Purchase(accountNumber, item, date, amount));

    cout << "Purchase added successfully." << endl;

    // Recursive call with count decremented by 1
    addMultiplePurchasesRecursive(accountNumber, count - 1);
}

// Saves all purchases to a file
void AllPurchases::savePurchasesToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (const auto& purchase : purchases) {
        file << purchase.getAccountNumber() << " " << purchase.getItem() << " "
            << purchase.getDate() << " " << purchase.getAmount() << endl;
    }

    if (file.bad()) {
        cerr << "Error writing to file: " << filename << endl;
    }

    file.close();
}

// Loads all customers from a file
void AllCustomers::loadCustomersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    // Loop through each line in the file and parse the customer data
    string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
    int accountNumber;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> firstName >> lastName >> accountNumber >> streetAddress >> city >> state >> zipCode >> phoneNumber;

        // Add the new customer to the list
        addCustomer(Customer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber));
    }

    file.close();
}

void AllCustomers::printCustomers() const {
    // loop through all customers in the list and print their information
    for (const auto& customer : customers) {
        cout << "Account number: " << customer.getAccountNumber() << endl;
        cout << "First name: " << customer.getFirstName() << endl;
        cout << "Last name: " << customer.getLastName() << endl;
        cout << "Street address: " << customer.getStreetAddress() << endl;
        cout << "City: " << customer.getCity() << endl;
        cout << "State: " << customer.getState() << endl;
        cout << "ZIP Code: " << customer.getZIPCode() << endl;
        cout << "Phone number: " << customer.getPhoneNumber() << endl;
        cout << "-------------------------" << endl;
    }
}

void AllCustomers::printSortedCustomers(bool ascending) const {
    // check if the customer list is empty
    if (customers.empty()) {
        cout << "No customers found." << endl;
        return;
    }

    // create a copy of the customer list and sort it based on account number
    vector<Customer> sortedCustomers = customers;
    if (ascending) {
        sort(sortedCustomers.begin(), sortedCustomers.end(), [](const Customer& a, const Customer& b) {
            return a.getAccountNumber() < b.getAccountNumber();
        });
    }
    else {
        sort(sortedCustomers.begin(), sortedCustomers.end(), [](const Customer& a, const Customer& b) {
            return a.getAccountNumber() > b.getAccountNumber();
        });
    }

    // loop through the sorted customer list and print their information
    cout << "Sorted Customers:" << endl;
    cout << "-------------------------" << endl;
    for (const auto& customer : sortedCustomers) {
        cout << "Account number: " << customer.getAccountNumber() << endl;
        cout << "First name: " << customer.getFirstName() << endl;
        cout << "Last name: " << customer.getLastName() << endl;
        cout << "Street address: " << customer.getStreetAddress() << endl;
        cout << "City: " << customer.getCity() << endl;
        cout << "State: " << customer.getState() << endl;
        cout << "ZIP Code: " << customer.getZIPCode() << endl;
        cout << "Phone number: " << customer.getPhoneNumber() << endl;
        cout << "-------------------------" << endl;
    }
}


void AllCustomers::printCustomerAccountInfo(const AllPurchases& allPurchases, int accountNumber) const {
    const Customer* customer = findCustomer(accountNumber); // Find the customer using their account number
    if (customer != nullptr) {
        // Print out the customer information
        cout << "Account number: " << customer->getAccountNumber() << endl;
        cout << "First name: " << customer->getFirstName() << endl;
        cout << "Last name: " << customer->getLastName() << endl;
        cout << "Street address: " << customer->getStreetAddress() << endl;
        cout << "City: " << customer->getCity() << endl;
        cout << "State: " << customer->getState() << endl;
        cout << "ZIP Code: " << customer->getZIPCode() << endl;
        cout << "Phone number: " << customer->getPhoneNumber() << endl;

        // Print out the purchases for the customer
        cout << "Purchases for customer with account number " << accountNumber << ":" << endl;
        allPurchases.printPurchasesByAccountNumber(accountNumber);
    }
    else {
        cout << "No customer with account number " << accountNumber << " found." << endl;
    }
}

void AllCustomers::printTotalSpendForCustomer(int accountNumber) const {
    double total = 0;
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            total += purchase.getAmount();
        }
    }
    cout << "Total spent by customer with account number " << accountNumber << ": " << total << endl;
}

void AllCustomers::addCustomer(const Customer& customer) {
    customers.push_back(customer); // Add a new customer to the list of customers
}

void AllCustomers::addMultipleCustomersRecursive(int count) {
    if (count <= 0) {
        return; // Base case to end the recursion
    }
    string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
    int accountNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get the customer information from the user
    cout << "Enter first name: ";
    getline(cin, firstName);

    cout << "Enter last name: ";
    getline(cin, lastName);

    cout << "Enter account number: ";
    cin >> accountNumber;
    cin.ignore();

    cout << "Enter street address: ";
    getline(cin, streetAddress);

    cout << "Enter city: ";
    getline(cin, city);

    cout << "Enter state: ";
    getline(cin, state);

    cout << "Enter ZIP code: ";
    getline(cin, zipCode);

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    // Add the new customer to the list of customers
    addCustomer(Customer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber));

    cout << "Customer added successfully." << endl;

    // Call the function recursively to add more customers
    addMultipleCustomersRecursive(count - 1);
}


bool AllCustomers::updateCustomer(int accountNumber, const Customer& updatedCustomer) {
    // Iterate through each customer in the vector
    for (auto& customer : customers) {
        // Check if the account number matches
        if (customer.getAccountNumber() == accountNumber) {
            // Update the customer with the new information
            customer = updatedCustomer;
            return true; // Update successful
        }
    }
    return false; // No customer with the given account number found
}

bool AllCustomers::deleteCustomer(int accountNumber) {
    // Use the remove_if algorithm to remove the customer with the given account number
    auto it = remove_if(customers.begin(), customers.end(), [accountNumber](const Customer& customer) {
        return customer.getAccountNumber() == accountNumber;
    });
    if (it != customers.end()) {
        // Erase the removed customer from the vector
        customers.erase(it, customers.end());
        return true;  // Delete successful
    }
    return false;  // No customer with the given account number found
}

void AllCustomers::saveCustomersToFile(const string& filename) const {
    // Open a file for writing
    ofstream file(filename);
    // Check if the file was opened successfully
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    // Iterate through each customer and write their information to the file
    for (const auto& customer : customers) {
        file << customer.getFirstName() << " " << customer.getLastName() << " "
            << customer.getAccountNumber() << " " << customer.getStreetAddress() << " "
            << customer.getCity() << " " << customer.getState() << " "
            << customer.getZIPCode() << " " << customer.getPhoneNumber() << endl;
    }

    // Check if there was an error writing to the file
    if (file.bad()) {
        cerr << "Error writing to file: " << filename << endl;
    }

    // Close the file
    file.close();
}

const vector<Customer>& AllCustomers::getCustomers() const {
    // Return a const reference to the customers vector
    return customers;
}

void saveAllData(const AllCustomers& allCustomers, const AllPurchases& allPurchases) {
    int choice;
    // Prompt the user to choose how to save the data
    cout << "Choose an option: " << endl;
    cout << "1. Save over the existing import files" << endl;
    cout << "2. Copy to new files" << endl;
    cin >> choice;
    if (choice == 1) {
        // Save the customers and purchases data to the existing files
        allCustomers.saveCustomersToFile("customers.txt");
        allPurchases.savePurchasesToFile("purchases.txt");
        cout << "Data saved to existing import files." << endl;
    }
    else if (choice == 2) {
        string newCustomersFile, newPurchasesFile;
        // Prompt the user to enter new filenames for the customers and purchases data
        cout << "Enter a new filename for customers: ";
        cin >> newCustomersFile;
        cout << "Enter a new filename for purchases: ";
        cin >> newPurchasesFile;

        // Save the customers and purchases data to the new files
        allCustomers.saveCustomersToFile(newCustomersFile);
        allPurchases.savePurchasesToFile(newPurchasesFile);
        cout << "Data saved to new files: " << newCustomersFile << " and " << newPurchasesFile << endl;
    }
    else {
        // Invalid choice
        cout << "Invalid choice. Data not saved." << endl;
    }
}

int main() {
    AllCustomers allCustomers;
    AllPurchases allPurchases;
    allCustomers.loadCustomersFromFile("customers.txt");
    allPurchases.loadPurchasesFromFile("purchases.txt");

  

   

    int option;
    do {
        cout << "\033[34m";
        cout << " Welcome to Kostko!" << endl;
        cout << "\033[31m";
        cout << "-----------MENU-----------" << endl;
        cout << "1. Add a new customer" << endl;
        cout << "2. Add multiple customers" << endl;
        cout << "3. Print all customers" << endl;
        cout << "4. Print sorted customers" << endl;
        cout << "5. Update customer information" << endl;
        cout << "6. Delete a customer" << endl;
        cout << "7. Add a new purchase" << endl;
        cout << "8. Add multiple purchases" << endl;
        cout << "9. Print all purchases" << endl;
        cout << "10. Print purchases for a customer" << endl;
        cout << "11. Print total spend for a customer" << endl;
        cout << "12. Save all data" << endl;
        cout << "\033[32m";
        cout << "0. Exit (or input a letter)" << endl;
        cout << "\033[31m";
        cout << "-------------------------" << endl;
        cout << " \033[34m";
        cout << "Enter your choice: ";
        cout << " \033[34m";
        cin >> option;

        cout << "\033[31m";

         switch (option) {
        case 1: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string accountNumberStr, zipCodeStr;
            string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
            int accountNumber;

            cout << "Enter first name: ";
            getline(cin, firstName);

            cout << "Enter last name: ";
            getline(cin, lastName);

            cout << "Enter account number: ";
            getline(cin, accountNumberStr);

            // Check if input contains non-numeric characters
            while (accountNumberStr.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid input. Please enter a valid account number: ";
                getline(cin, accountNumberStr);
            }

            accountNumber = stoi(accountNumberStr);


            cout << "Enter street address: ";
            getline(cin, streetAddress);

            cout << "Enter city: ";
            getline(cin, city);

            cout << "Enter state: ";
           getline(cin, state);

            cout << "Enter ZIP code: ";
            getline(cin, zipCode);

             //Check if input contains non-numeric characters
            while (zipCode.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid input. Please enter a valid zip code: ";
                getline(cin, zipCode);
            }

           

            cout << "Enter phone number: ";
            getline(cin,phoneNumber);
            //Check if input contains non-numeric characters
            while (phoneNumber.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid input. Please enter a valid phone number: ";
                getline(cin, phoneNumber);
            }

            allCustomers.addCustomer(Customer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber));

            cout << "Customer added successfully." << endl;
            break;
        }

        case 2: {
            int count;
            cout << "Enter the number of customers to add: ";
            cin >> count;

            while (cin.fail() || count < 1) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a valid number of customers: ";
                cin >> count;
            }

            allCustomers.addMultipleCustomersRecursive(count);
            break;
        }

        case 3:
            allCustomers.printCustomers();
            break;
        case 4: {
            bool validInput = false;
            int sortOrder = 0;

            while (!validInput) {
                cout << "Enter sort order (0 for descending, 1 for ascending): ";
                if (!(cin >> sortOrder)) {
                    cout << "Invalid input. Please try again." << endl;
                    cin.clear(); // Clear error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
                }
                else {
                    if (sortOrder == 0 || sortOrder == 1) {
                        validInput = true;
                    }
                    else {
                        cout << "Invalid input. Please try again." << endl;
                    }
                }
            }

            bool ascending = (sortOrder == 1);

            allCustomers.printSortedCustomers(ascending);
            break;
        }


        case 5: {
            int accountNumber;
            cout << "Enter the account number of the customer to update: ";
            cin >> accountNumber;

            while (cin.fail() || accountNumber < 1) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a valid account number: ";
                cin >> accountNumber;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;

            cout << "Enter new first name: ";
            getline(cin, firstName);

            cout << "Enter new last name: ";
            getline(cin, lastName);

            cout << "Enter new street address: ";
            getline(cin, streetAddress);

            cout << "Enter new city: ";
            getline(cin, city);

            cout << "Enter new state: ";
            getline(cin, state);

            cout << "Enter new ZIP code: ";
            getline(cin, zipCode);

            cout << "Enter new phone number: ";
            getline(cin, phoneNumber);

            // Validate user input for each field
            while (firstName.empty()) {
                cout << "Invalid input. Please enter a non-empty first name: ";
                getline(cin, firstName);
            }

            while (lastName.empty()) {
                cout << "Invalid input. Please enter a non-empty last name: ";
                getline(cin, lastName);
            }

            while (streetAddress.empty()) {
                cout << "Invalid input. Please enter a non-empty street address: ";
                getline(cin, streetAddress);
            }

            while (city.empty()) {
                cout << "Invalid input. Please enter a non-empty city: ";
                getline(cin, city);
            }

            while (state.empty() || state.length() != 2) {
                cout << "Invalid input. Please enter a valid two-letter state code: ";
                getline(cin, state);
            }

            while (zipCode.empty() || zipCode.length() != 5) {
                cout << "Invalid input. Please enter a valid five-digit ZIP code: ";
                getline(cin, zipCode);
            }

            while (phoneNumber.empty() || phoneNumber.length() != 10) {
                cout << "Invalid input. Please enter a valid ten-digit phone number: ";
                getline(cin, phoneNumber);
            }

            Customer updatedCustomer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);

            if (allCustomers.updateCustomer(accountNumber, updatedCustomer)) {
                cout << "Customer information updated successfully." << endl;
            }
            else {
                cout << "No customer with the given account number found." << endl;
            }

            break;
        }

        case 6: {
            int accountNumber;
            cout << "Enter the account number of the customer to delete: ";

            // Loop until valid input is received
            while (!(cin >> accountNumber)) {
                cout << "Invalid input. Please enter an integer value: ";
                cin.clear(); // Clear the failbit flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input
            }

            if (allCustomers.deleteCustomer(accountNumber)) {
                cout << "Customer deleted successfully." << endl;
            }
            else {
                cout << "No customer with the given account number found." << endl;
            }

            break;
        }

        case 7: {
            int accountNumber;

            // Loop until valid input is received
            while (true) {
                cout << "Enter account number: ";

                if (cin >> accountNumber) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else {
                    cout << "Invalid input. Please enter an integer value." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            string item, date;
            double amount;

            cout << "Enter item: ";
            getline(cin, item);

            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);

            // Loop until valid input is received
            while (true) {
                cout << "Enter amount: ";

                if (cin >> amount) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else {
                    cout << "Invalid input. Please enter a numeric value." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            allPurchases.addNewPurchase(Purchase(accountNumber, item, date, amount));

            cout << "Purchase added successfully." << endl;

            break;
        }

        case 8: {
            int accountNumber, count;
            cout << "Enter account number: ";
            while (!(cin >> accountNumber)) {
                cout << "Invalid input. Please enter a valid account number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter the number of purchases to add: ";
            while (!(cin >> count)) {
                cout << "Invalid input. Please enter a valid number of purchases: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            allPurchases.addMultiplePurchasesRecursive(accountNumber, count);

            break;
        }

        case 9:
            allPurchases.printAllPurchases();
            break;
        case 10: {
            int accountNumber;
            cout << "Enter the account number of the customer: ";
            while (!(cin >> accountNumber)) {
                cout << "Invalid input. Please enter a valid account number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            allPurchases.printPurchasesByAccountNumber(accountNumber);
            break;
        }
        case 11: {
            int accountNumber;
            cout << "Enter the account number of the customer: ";
            cin >> accountNumber;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid account number." << endl;
                break;
            }

            allCustomers.printTotalSpendForCustomer(accountNumber);
            break;
        }

        case 12:
            saveAllData(allCustomers, allPurchases);
            break;
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << endl;
    } while (option != 0);

    return 0;
}



