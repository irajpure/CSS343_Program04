// --------------------------------- CustomerAccounts.cpp -----------------------------------
// Isha Rajpure CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: June 2, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Customer List class - specialized linked list that  
// stores a customer's information and transaction history. implements
// -------------------------------------------------------------------------------
// Notes: TransEntry is the node class for this linked list implementation
// 
//
// -------------------------------------------------------------------------------

#include "CustomerList.h"
#include <iostream>
using namespace std;

// ----------------------------- TransEntry() ------------------------------
// Description: Constructor for node, TransEntry.
// Preconditions: data for a node (transaction information).
// Postconditions: save the transaction information into variables
// -------------------------------------------------------------------------------
TransEntry::TransEntry(string transType, string movieType, string director, string title, int year, TransEntry* nextEntry) {
    this->transType = transType;
    this->movieType = movieType;
    this->director = director;
    this->title = title;
    this->year = year;
    this->nextEntry = nextEntry;
}


// ----------------------------- CustomerList() ----------------------------------
// Description: Constructor for linked list, Customer List. Initializes all data members to default.
// Preconditions: none.
// Postconditions: slot = EMPTY, mostRecentEntry (node head) = nullptr.
// -------------------------------------------------------------------------------
CustomerList::CustomerList() {
    slot = State::EMPTY;                //set to empty bc hasn't been initialized properly
    mostRecentEntry = nullptr;          //nothing in transaction history bc we just created the account
}

// ----------------------------- CustomerList(data) ------------------------------
// Description: Constructor for linked list, Customer List. creates customer list 
//              with customer data.
// Preconditions: customer ID, first name, last name.
// Postconditions: saves data in appropriate values. slot = OCCUPIED, mostRecentEntry 
//                 (node head) = nullptr.
// -------------------------------------------------------------------------------
CustomerList::CustomerList(int customerID, string firstName, string lastName) {
    this->customerID = customerID;
    this->slot = State::OCCUPIED;       //since we are adding customer data, this linked list is being used
                                        //so state should be occupied
    this->firstName = firstName;
    this->lastName = lastName;
    mostRecentEntry = nullptr;          //nothing in transaction history bc we just created the account
    //cout << "Construct: " << this << endl;
}

// ----------------------------- operator=() ------------------------------
// Description: set current customer equal to the other customer
// Preconditions: CustomerList& other (other customer list)
// Postconditions: saves data in appropriate values. slot = OCCUPIED.
// -------------------------------------------------------------------------------
CustomerList& CustomerList::operator=(const CustomerList& other) {
    this->customerID = other.customerID;
    this->slot = State::OCCUPIED;
    this->firstName = other.firstName;
    this->lastName = other.lastName;
    this->mostRecentEntry = other.mostRecentEntry; 

    return *this;
}

// ----------------------------- ~CustomerList() -----------------------------
// Description: Destructor. Array is deleted. Destructor for objects inside will be implicitly called
// Preconditions: None.
// Postconditions: CustomerAccounts (hashtable) object destroyed.
// -------------------------------------------------------------------------------
CustomerList::~CustomerList() {
    
    TransEntry* current = mostRecentEntry;      //set current to be the head node of the list

    while (current != nullptr) {                //until we reach the end of the list...
        TransEntry* saved = current;            //save the current value in a temp variable pointer (node)
        current = current->nextEntry;           //current is moved forward
        delete saved;                           //temp node is deleted
    }
    //cout << "Destroy: " << this << endl;
}

// ----------------------------- addTransEntry(transaction data) -----------------
// Description: adds transaction to customer's history
// Preconditions: transaction data
// Postconditions: saves data in appropriate values, as a node.
//                 node is added to the front of the linked list (most recent trans)
// -------------------------------------------------------------------------------
void CustomerList::addTransEntry(string transType, string movieType, string director, string title, int year) {
    //adds the mostRecentEntry to be after new entry, in the list.
    TransEntry* transaction = new TransEntry(transType, movieType, director, title, year, mostRecentEntry);
    //then changes it to be the new start of the list
    mostRecentEntry = transaction;
}

// ----------------------------- borrowedMovie(transaction data) -----------------
// Description: checks whether the customer borrowed a specific movie
// Preconditions: transaction data, minus transaction type (given that it's Borrowed)
// Postconditions: returns bool value
// -------------------------------------------------------------------------------
bool CustomerList::borrowedMovie(string movieType, string director, string title, int year) {
    
    TransEntry* current = mostRecentEntry;
    while (current != nullptr) {
        
        //if transaction is "borrow" and movie matches the details, return true
        if (current->transType == "B" && 
            current->movieType == movieType && 
            current->director == director && 
            current->title == title &&
            current->year == year) {
                return true;
        }
        
        //move on to next entry
        mostRecentEntry = mostRecentEntry->nextEntry;
    }
    
    //otherwise return false
    return false;
}

// ----------------------------- getCustomerID() --------------------------------------
// Description: Returns customer's ID.
// Preconditions: None.
// Postconditions: Returns customer's ID. CustomerList unchanged.
// -------------------------------------------------------------------------------
int CustomerList::getCustomerID() {
    return customerID;
}

// ----------------------------- getState() --------------------------------------
// Description: Returns state of linked list
// Preconditions: None.
// Postconditions: Returns linked list state (whether it stores a customer or is just null). 
//                 CustomerList unchanged.
// -------------------------------------------------------------------------------
State CustomerList::getState() {
    return slot;
}

// ----------------------------- getFirstName() --------------------------------------
// Description: Returns customer's first name.
// Preconditions: None.
// Postconditions: Returns customer's first name. CustomerList unchanged.
// -------------------------------------------------------------------------------
string CustomerList::getFirstName() {
    return firstName;
}

// ----------------------------- getLastName() --------------------------------------
// Description: Returns customer's last name.
// Preconditions: None.
// Postconditions: Returns customer's last name. CustomerList unchanged.
// -------------------------------------------------------------------------------
string CustomerList::getLastName() {
    return lastName;
}

// ----------------------------- changeState() -----------------------------------
// Description: changes linked list state.
// Preconditions: State newState.
// Postconditions: State of the CustomerList is changed.
// -------------------------------------------------------------------------------
void CustomerList::changeState(State newState) {
    slot = newState;
}

// ----------------------------- print() -----------------------------------------
// Description: prints linked list. customer info & trans entries in order (recent to oldest)
// Preconditions: none.
// Postconditions: nothing is changed.
// -------------------------------------------------------------------------------
void CustomerList::print() {
    if (slot == State::OCCUPIED) {
        cout << "Customer: " << firstName << " " << lastName << ", ";
        cout << "ID - " << customerID << endl;
    }
    else {
        cout << "empty" << endl;
    }
}