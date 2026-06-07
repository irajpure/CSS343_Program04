#ifndef BUSINESS_H
#define BUSINESS_H

#include "Storage/MovieStorage.h"
#include "Customers/CustomerAccounts.h"
#include "Customers/CustomerList.h"


#include <iostream>
#include <fstream>
using namespace std;

class Business {

    public:
        int processCustomerData(ifstream& file);    //process the customer txt file
        void displayCustomers();                    //display only customers list
        void displayCustomerTable();                //display hash table

        int processMoviesData(ifstream& file);      //process the movies txt file
        void displayAllMovies();

        int processTransactionData(ifstream& file); //process the transaction txt file


    private:
        MovieStorage moviesCollection;              //movies inventory all stored here
        CustomerAccounts accounts;                  //customer accounts hash table 

};

#endif