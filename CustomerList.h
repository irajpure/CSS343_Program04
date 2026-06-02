//

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

    TransEntry();
    TransEntry(string transType, string movieType, string director, string title, int year, TransEntry* nextEntry);

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
        CustomerList();                                                                      //default constructor
        CustomerList(int customerID, string firstName, string lastName);         //constructor
        ~CustomerList();                                                                     //destructor
        void addTransEntry(string transType, string movieType, string director, string title, int year);
        bool BorrowedMovie(string movieType, string director, string title, int year);
        void print();
        int getCustomerID();
        string getFirstName();
        string getLastName();
        State getState();
        void changeState(State newState);
        CustomerList& operator=(const CustomerList& other);
    
    private:
        int customerID;         //key
        State slot;             //state of the slot
        string firstName;       //customer's first name
        string lastName;        //customer's first name
        TransEntry* mostRecentEntry;  //pointer to customer's history.

};

#endif