// --------------------------------- CustomerAccounts.cpp -----------------------------------
// Isha Rajpure CSS343
// Creation Date: May 30, 2026
// Date of Last Modification: June 2, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Customer Accounts class - hash table that stores customer 
// information and transaction history.  implements addition, deletion, and search of accounts,
// as well as addition and search of customer transactions.
// -------------------------------------------------------------------------------
// Notes:
// 
// - Difference between "addAccount" and "insert":
//
//      "addAccount" is the full method for adding a customer to the hash table given the
// their details. it double checks the load factor (and decides if the hash table needs to be
// resized or no space available), and then inserts the customer.
//
//      "insert" is the helper method that takes a customer's details, creates the customer object
// (called CustomerList), and then inserts it into the table. also checks whether ID is already
// linked with an account in the table.
//
// - If the max number of accounts that can fit in the hashtable are created, then no new accounts
// can be inserted (wil throw error).
//
// -------------------------------------------------------------------------------

#include "CustomerAccounts.h"
#include "CustomerList.h"

// ----------------------------- CustomerAccounts() ------------------------------
// Description: Default constructor. Initializes all data members to defaults.
// Preconditions: None.
// Postconditions: arraySize = possibleArraySizes[0], arraySizeIndex = 0, hashTable = new CustomerList[arraySize],
// customerCount = 0.
// -------------------------------------------------------------------------------
CustomerAccounts::CustomerAccounts() {
    arraySize = possibleArraySizes[0];
    arraySizeIndex = 0;
    hashTable = new CustomerList[arraySize];
    customerCount = 0;
}

// ----------------------------- ~CustomerAccounts() -----------------------------
// Description: Destructor. Array is deleted. Destructor for objects inside will be implicitly called
// Preconditions: None.
// Postconditions: CustomerAccounts (hashtable) object destroyed.
// -------------------------------------------------------------------------------
CustomerAccounts::~CustomerAccounts() {
    delete[] hashTable;
}

// ----------------------------- addAccount() ---------------------------------
// Description: Adds customer account to hash table, if valid entry.
// Preconditions: customerID, first name, last name.
// Postconditions: customer is added to hash table and appropriate variables are
//                 updated.
// ----------------------------------------------------------------------------
int CustomerAccounts::addAccount(int customerID, string firstName, string lastName) {
    
    try {

        //if not enough space, resize hashtable
        double newLoadFactor = static_cast<double>(customerCount + 1) / arraySize;     //calculate load factor if new item were added
        if (newLoadFactor >= 0.5) {     //if we have reached 50% capacity, increase array size
            growArray();
        }
        if (newLoadFactor >= 1) {
            throw "not enough space in array to insert.";
        }

        //add the customer to hash table
        insert(customerID, firstName, lastName);

        return 0;

    }

    catch (const char* msg) {
        cout << "Error with adding account: " << msg << endl;
        return -1;
    }
}

// ----------------------------- growArray() ---------------------------------
// Description: Increases hash table size and rehashes values.
// Preconditions: none.
// Postconditions: chooses next possible array size (from list of possible array
//                 sizes), creates new array, and uses insert method to insert customers.
// ---------------------------------------------------------------------------
int CustomerAccounts::growArray() {


    //if already at max size possible (last element in possible array sizes), return error code.
    if (arraySizeIndex == sizeof(possibleArraySizes)/sizeof(possibleArraySizes[0])-1) {
        cout << "table is almost full." << endl;
    }

    //change array size and create a new array with new size and save old size
    int oldArraySize = arraySize;                       //save old size of the array in variable
    arraySizeIndex++;                                   //increase counter for index of array size
    arraySize = possibleArraySizes[arraySizeIndex];     //change the array size (to next size in the possible sizes)
    CustomerList* oldTable = hashTable;                 //save the original hash table in a variable
    hashTable = new CustomerList[arraySize];            //create a new hashtable with the new size and save in hashTable var
    customerCount = 0;                                  //reset customer count for now. it will go back up during insertion.

    //insert all slots that are occupied into new hashtable.
    for (int i = 0; i < oldArraySize; i++) {
        if (oldTable[i].getState() == State::OCCUPIED) {
            insert(oldTable[i].getCustomerID(), oldTable[i].getFirstName(), oldTable[i].getLastName());
        }
    }

    //delete the old table
    delete[] oldTable;
    return 0;

}

// ----------------------------- insert() ------------------------------------
// Description: creates a customer account (customer list) and inserts in hash table
// Preconditions: customer ID, first name, last name.
// Postconditions: state of the used slot is now occupied.
// ---------------------------------------------------------------------------
int CustomerAccounts::insert(int customerID, string firstName, string lastName) {

    
    bool inserted = false;              //bool variable to check whether the element has been inserted or not
    int collisions = 0;                 //keep track of how many collisions are happening


    //while the element has not been inserted... (will not be infinity loop because size of array is always prime)
    while (inserted == false) {
        
        int hashKey = findInsertionPoint(customerID, collisions);       //find hash key depending on number of collisions


        //if occupied spot and customerID already exists in table, throw error for repeated use of ID
        if (hashTable[hashKey].getState() == State::OCCUPIED) {
            if (customerID == hashTable[hashKey].getCustomerID()) {     
                throw "account creation error - repeated customer ID is being used.";
            }
        }

        //if spot is empty, then insert new customer account there
        if (hashTable[hashKey].getState() == State::EMPTY || hashTable[hashKey].getState() == State::DELETED) {
            hashTable[hashKey] = CustomerList(customerID, firstName, lastName);
            inserted = true;
            //cout << "added acc - " << customerID << endl;
            //int currentState = static_cast<int>(hashTable[hashKey].getState());
            customerCount++;                                                        //increase customer count
            //cout << "printing state: " << to_string(currentState) << endl;
        }

        //if spot state is either occupied or deleted, then treat like a collision.
        else {
            collisions++;
        }

    }

    return 0;
}

// ----------------------------- findInsertionPoint() ------------------------
// Description: finds hash key for customer ID, depending on number of collisions and
//              returns the index for where the customer should be inserted.
// Preconditions: customer ID, number of collisions.
// Postconditions: index of possible spot.
// ---------------------------------------------------------------------------
int CustomerAccounts::findInsertionPoint(int customerID, int collisions) {
    int hashKey = customerID % arraySize;   //hash function: ID mod arraySize (for simplicity)
    hashKey += collisions*collisions;       //quad probing: if there were collisions, sqaure it and
                                            //              to hash key
    hashKey = hashKey % arraySize;          //make sure to mod the final answer. return this.
    return hashKey;
}

// ----------------------------- removeAccount() ------------------------
// Description: remove the account of a customer.
// Preconditions: customer ID.
// Postconditions: return 0 if successful. otherwise, return -1.
// ---------------------------------------------------------------------------
int CustomerAccounts::removeAccount(int customerID) {

    try {

        //figure out if the element is even in the array
        int index = findIndexOfAccount(customerID);         //find index of the customer's account with function
        if (index == -1) {                                  //if function returned -1, that is error code.
            throw "customer account not in table.";         //throw exception.
        }
        else {
            hashTable[index].changeState(State::DELETED);   //otherwise change the state to deleted. no need to reset info
            customerCount--;                                //decrease customer count
        }
        
        //if too much space now, resize hashtable
        double newLoadFactor = static_cast<double>(customerCount) / arraySize;  //calculate load factor if new item were added
        if (newLoadFactor <= 0.125) {     //if we are down to 12.5% capacity, decrease array size with method
            shrinkArray();
        }

    }

    catch (const char* msg) {
        cout << "Error with deleting account: " << msg << endl;
        return -1;
    }

    return 0;
}

// ----------------------------- findIndexOfAccount() ------------------------
// Description: finds index of customer in hash table, give their ID.
// Preconditions: customer ID.
// Postconditions: index of the customer's spot in the hash table, or -1 as error code.
// ---------------------------------------------------------------------------
int CustomerAccounts::findIndexOfAccount(int customerID) {

    bool found = false;                 //bool variable to check whether the element has been found or not
    int collisions = 0;                 //keep track of how many collisions are happening

    //while the element has not been found...
    while (found == false) {
        
        int hashKey = findInsertionPoint(customerID, collisions);       //find hash key depending on number of collisions

        //if occupied spot matches customerID then return the index
        if (hashTable[hashKey].getState() == State::OCCUPIED) {
            if (customerID == hashTable[hashKey].getCustomerID()) {     
                found = true;
                return hashKey;
            }
        }
        //otherwise, if it's empty, then return error code
        else if (hashTable[hashKey].getState() == State::EMPTY) {
            return -1;
        }

        //otherwise, it's a collision. increase collision count.
        collisions++;
    
    }

    return -1;
}

// ----------------------------- shrinkArray() ------------------------
// Description: decreases hash table size and rehashes values.
// Preconditions: none.
// Postconditions: returns 0 if successful, and -1 if error.
// ---------------------------------------------------------------------------
int CustomerAccounts::shrinkArray() {
    
    //if we already have the smallest possible size selected, then stick to it. return.
    if (arraySizeIndex == 0) {
        return 0;
    }

    //change array size and create a new array with new size and save old size
    int oldArraySize = arraySize;                       //save old size of the array in variable
    arraySizeIndex--;                                   //increase counter for index of array size
    arraySize = possibleArraySizes[arraySizeIndex];     //change the array size (to next size in the possible sizes)
    CustomerList* oldTable = hashTable;                 //save the original hash table in a variable
    hashTable = new CustomerList[arraySize];            //create a new hashtable with the new size and save in hashTable var
    customerCount = 0;                                  //reset customer count for now. it will go back up during insertion.

    //insert all slots that are occupied into new hashtable.
    for (int i = 0; i < oldArraySize; i++) {
        if (oldTable[i].getState() == State::OCCUPIED) {
            insert(oldTable[i].getCustomerID(), oldTable[i].getFirstName(), oldTable[i].getLastName());
        }
    }

    //delete the old table
    delete[] oldTable;
    return 0;

}

// ----------------------------- containsAccount() ------------------------
// Description: returns whether an account is in the hashtable or not.
// Preconditions: customer ID.
// Postconditions: boolean value.
// ---------------------------------------------------------------------------
bool CustomerAccounts::containsAccount(int customerID) {
    if (findIndexOfAccount(customerID) != -1) {             //if the index of the account is not -1 (error code)
        return true;                                        //then return true. it is in the hash table
    }
    return false;                                           //otherwise it is not.
}

// ----------------------------- addTransForCustomer() ------------------------
// Description: adds a transaction entry to a customer's history.
// Preconditions: customer ID and transaction entry data.
// Postconditions: returns 0 if successful and -1 if not.
//                 inserts trans entry in correct customer list.
// ---------------------------------------------------------------------------
int CustomerAccounts::addTransForCustomer(int customerID, string transType, string movieType, string director, string title, int year) {
    
    if (containsAccount(customerID)) {                                                  //if customer account exists...
        int index = findIndexOfAccount(customerID);                                     //save index of customer from hash table
        hashTable[index].addTransEntry(transType, movieType, director, title, year);    //insert transaction entry
        return 0;
    }
    return -1;                                                                          //otherwise, return error code
}

// ----------------------------- checkBorrowedMovie() ------------------------
// Description: checks whether customer has borrowed a movie or not.
// Preconditions: customer ID and transaction entry data.
// Postconditions: returns 0 if successful and -1 if not.
//                 inserts trans entry in correct customer list.
// ----------------------------------------------------------------------------
bool CustomerAccounts::checkBorrowedMovie(int customerID, string movieType, string director, string title, int year) {

    if (containsAccount(customerID)) {                                              //if customer account exists...
        int index = findIndexOfAccount(customerID);                                 //save index of customer from hash table
        return hashTable[index].borrowedMovie(movieType, director, title, year);    //return whether they borrowed movie
    }

    return false;                                                                   //if customer account doesn't exit, return false

}

// ----------------------------- print() ------------------------
// Description: prints the hash table, including empty slots.
// Preconditions: none.
// Postconditions: doesn't make any changes to values.
// ---------------------------------------------------------------------------
void CustomerAccounts::print() {

    //loops through the array and calls the customer list's print method.
    for (int i = 0; i < arraySize; i++) {
        cout << "Index " << i << ": ";
        hashTable[i].print();
    }
    cout << endl;

}

//Print command for just the table
void CustomerAccounts::printCustomers() {
    //loops through the array and calls the customer list's print method.
    for (int i = 0; i < arraySize; i++) {
        if (hashTable[i].getState() == State::OCCUPIED) {
            hashTable[i].print();
        }
    }
    cout << endl;
}