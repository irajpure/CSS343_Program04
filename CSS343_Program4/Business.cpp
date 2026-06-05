#include "Business.h"
#include "Customers/CustomerAccounts.h"
#include "Customers/CustomerList.h"
#include "Storage/MovieStorage.h"

#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


int Business::processCustomerData(ifstream& file) {

    try {

        string line;
        while (getline(file, line)) {   //while there are still lines to be read...

            vector<string> tokens;      //vector for tokens. 
            istringstream iss(line);    //
            string token;               //variable in which we will extract tokens

            while (iss >> token) {
                tokens.push_back(token); //add the token to the vector
            }

            int customerID = stoi(tokens[0]);
            string firstName = tokens[1];
            string lastName = tokens[2];

            accounts.addAccount(customerID, firstName, lastName);

        }

    }

    catch (const char* msg) {
        cout << "Customer Data Population failed: " << msg << endl;
        return -1;
    }

    return 0;

}

void Business::printCustomers() {
    accounts.print();
}