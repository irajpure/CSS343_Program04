// --------------------------------- CustomerList.h -------------------------------------
// Isha Rajpure CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: June 2, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Customer List class - specialized linked list that stores 
// a customer's information and transaction history.
// -------------------------------------------------------------------------------
// Notes: transaction history is saved from most recent to oldest.
// -------------------------------------------------------------------------------

#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include <iostream>
using namespace std;


//TYPES OF STATES - to check whether a spot is/was being used (for traversal)
enum class State {
    EMPTY = 0,
    OCCUPIED = 1,
    DELETED = -1
};

//NODE IMPLEMENTATION - Trans Entry
struct TransEntry {

    TransEntry();       //default node constructor
    //other constructor: providing data for transaction
    TransEntry(string transType, string movieType, string director, string title, int year, TransEntry* nextEntry);
    void print();            //print command for transaction

    string transType;           //character for type of transaction
    string movieType;           //character for type of movie
    string director;            //director name
    string title;               //title of movie
    int year;                   //year movie was published
    TransEntry* nextEntry;      //link to the previous entry

};

//LINKED LIST IMPLEMENTATION - Customer List
class CustomerList {
    
    public:
        CustomerList();                                                                     //default constructor
        CustomerList(int customerID, string firstName, string lastName);                    //constructor
        ~CustomerList();                                                                    //destructor
        void addTransEntry(string transType, string movieType, string director, string title, int year);    //add a transaction to history
        bool borrowedMovie(string movieType, string director, string title, int year);      //check if customer has borrowed a movie
        void print();                                                                       //print customer information
        int getCustomerID();                                                                //return ID
        string getFirstName();                                                              //return first name
        string getLastName();                                                               //return last name
        State getState();                                                                   //return state of slot (occupied, empty, or deleted)
        void changeState(State newState);                                                   //modify state of slot
        CustomerList& operator=(const CustomerList& other);                                 //= operator, for setting a customer.
    
    private:
        int customerID;                 //key
        State slot;                     //state of the slot
        string firstName;               //customer's first name
        string lastName;                //customer's first name
        TransEntry* mostRecentEntry;    //pointer to customer's history.

};

#endif