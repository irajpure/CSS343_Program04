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
        int processCustomerData(ifstream& file);
        void displayCustomers();

        int processMoviesData(ifstream& file);
        void displayAllMovies();

        int processTransactionData(ifstream& file);


    private:
        MovieStorage moviesCollection;
        CustomerAccounts accounts;

};

#endif