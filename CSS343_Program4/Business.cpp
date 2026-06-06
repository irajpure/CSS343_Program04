#include "Business.h"
#include "Customers/CustomerAccounts.h"
#include "Customers/CustomerList.h"
#include "Storage/MovieStorage.h"
#include "Movies/MovieFac.h"

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

int Business::processMoviesData(ifstream& file) {
    
    try {

        MovieFac factory;
        
        //use "line" to extract entire lines of the file
        string line;
        while (getline(file, line)) {           //while there are still lines to be extracted

            char genre = line[0];               //extract 1st character

            vector<string> tokens;
            istringstream iss(line.substr(2));  //iss (new line) contains everything after the genre

            string token;

            while (getline(iss, token, ',')) {  //turn new line into a string vector, with commas as delimiter

                if (!token.empty() && token[0] == ' ') {    //removing white space in front of the variable
                    token.erase(0, 1);
                }

                tokens.push_back(token);                    //then adding token to vector
            }

            Movie* m = factory.createMovie(genre, tokens);
            if (m != nullptr) {
                moviesCollection.insertMovie(genre, m);
            }

        }

    }

    catch (const char* msg) {
        cout << "Customer Data Population failed: " << msg << endl;
        return -1;
    }

    return 0;
}



void Business::displayCustomers() {
    accounts.print();
}

void Business::displayAllMovies() {
    moviesCollection.displayAll();
}