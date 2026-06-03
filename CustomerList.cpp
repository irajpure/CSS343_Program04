// --------------------------------- CustomerAccounts.cpp -----------------------------------
// Isha Rajpure CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: June 2, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Customer List class - specialized linked list that  
// stores a customer's information and transaction history. implements
// -------------------------------------------------------------------------------
// Notes:
// 
//
// -------------------------------------------------------------------------------

#include "CustomerList.h"
#include <iostream>
using namespace std;

//NODE CONSTRUCTOR
TransEntry::TransEntry(string transType, string movieType, string director, string title, int year, TransEntry* nextEntry) {
    this->transType = transType;
    this->movieType = movieType;
    this->director = director;
    this->title = title;
    this->year = year;
    this->nextEntry = nextEntry;
}


//DEFAULT CONSTRUCTOR
CustomerList::CustomerList() {
    slot = State::EMPTY;                //set to empty bc hasn't been initialized properly
    mostRecentEntry = nullptr;          //nothing in transaction history bc we just created the account
}

//CONSTRUCTOR
CustomerList::CustomerList(int customerID, string firstName, string lastName) {
    this->customerID = customerID;
    this->slot = State::OCCUPIED;
    this->firstName = firstName;
    this->lastName = lastName;
    mostRecentEntry = nullptr;          //nothing in transaction history bc we just created the account
    //cout << "Construct: " << this << endl;
}

CustomerList& CustomerList::operator=(const CustomerList& other) {
    this->customerID = other.customerID;
    this->slot = State::OCCUPIED;
    this->firstName = other.firstName;
    this->lastName = other.lastName;
    this->mostRecentEntry = other.mostRecentEntry; 

    return *this;
}

//DESTRUCTOR 
CustomerList::~CustomerList() {
    TransEntry* current = mostRecentEntry;
    while (current != nullptr) {
        TransEntry* saved = current;
        current = current->nextEntry;
        delete saved;
    }
    //cout << "Destroy: " << this << endl;
}

//ADD TRANSACTION ENTRY - adds a transaction as the most recent event
void CustomerList::addTransEntry(string transType, string movieType, string director, string title, int year) {
    //adds the mostRecentEntry to be after new entry, in the list.
    TransEntry* transaction = new TransEntry(transType, movieType, director, title, year, mostRecentEntry);
    //then changes it to be the new start of the list
    mostRecentEntry = transaction;
}

//BORROWED MOVIE - checks whether the customer borrowed a specific movie
bool CustomerList::BorrowedMovie(string movieType, string director, string title, int year) {
    
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
// Description: Returns customer's ID.
// Preconditions: None.
// Postconditions: Returns customer's ID. CustomerList unchanged.
// -------------------------------------------------------------------------------
State CustomerList::getState() {
    return slot;
}

// ----------------------------- getFirstName() --------------------------------------
// Description: Returns customer's ID.
// Preconditions: None.
// Postconditions: Returns customer's ID. CustomerList unchanged.
// -------------------------------------------------------------------------------
string CustomerList::getFirstName() {
    return firstName;
}

// ----------------------------- getLastName() --------------------------------------
// Description: Returns customer's ID.
// Preconditions: None.
// Postconditions: Returns customer's ID. CustomerList unchanged.
// -------------------------------------------------------------------------------
string CustomerList::getLastName() {
    return lastName;
}

// ----------------------------- changeState() --------------------------------------
// Description: Returns customer's ID.
// Preconditions: State.
// Postconditions: State of the CustomerList is changed.
// -------------------------------------------------------------------------------
void CustomerList::changeState(State newState) {
    slot = newState;
}

//FUNCTION TO SEE CUSTOMER INFORMATION. WILL LATER BE FOUND WITH HISTORY TRANSACTION.
void CustomerList::print() {
    if (slot == State::OCCUPIED) {
        cout << "Customer: " << firstName << " " << lastName << ", ";
        cout << "ID - " << customerID << endl;
    }
    else {
        cout << "empty" << endl;
    }
}