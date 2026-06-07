#include "Customers/CustomerList.h"
#include "Customers/CustomerAccounts.h"
#include "Business.h"
#include <iostream>

#include <iostream>
#include <fstream>
using namespace std;

int main() {

    cout<<"\n----------- Online Movie Rental Store -----------"<<endl;
	ifstream customerFile("Data/data4customers.txt");
	if (!customerFile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes

    Business MovieRentalStore;

    if (MovieRentalStore.processCustomerData(customerFile) <0) {
        return 1;
    };
    cout << "Customers:" << endl;
    MovieRentalStore.displayCustomers();
    MovieRentalStore.displayCustomerTable();

    cout << endl;

    ifstream moviesFile("Data/data4movies.txt");
	if (!moviesFile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

    
    if (MovieRentalStore.processMoviesData(moviesFile) <0) {
        return 1;
    };
    MovieRentalStore.displayAllMovies();

    cout << endl;

    ifstream transactionFile("Data/simple_commands.txt");
	if (!transactionFile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

    /*
    if (MovieRentalStore.processTransactionData(transactionFile) <0) {
        return 1;
    };
    */
    

    return 0;
}