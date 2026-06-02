//

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

//GET CUSTOMER ID
int CustomerList::getCustomerID() {
    return customerID;
}

//GET STATE
State CustomerList::getState() {
    return slot;
}

//GET FIRST NAME
string CustomerList::getFirstName() {
    return firstName;
}

//GET LAST NAME
string CustomerList::getLastName() {
    return lastName;
}

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