#include "Customers/CustomerList.h"
#include "Customers/CustomerAccounts.h"
#include "Business.h"
#include <iostream>

#include <iostream>
#include <fstream>
using namespace std;

int main() {

    cout<<"\n----------- Online Movie Rental Store -----------"<<endl;
	ifstream infile("Data/data4customers.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes

    Business MovieRentalStore;

    if (MovieRentalStore.processCustomerData(infile) <0) {
        return 1;
    };
    cout << "Customers:" << endl;
    MovieRentalStore.printCustomers();


    return 0;
}