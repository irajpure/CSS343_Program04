#ifndef TRANS_H
#define TRANS_H
// --------------------------------- Trans.h -------------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Trans class - abstract base class for all transaction
//          types (Borrow, Return, Inventory, History). Defines the common
//          interface and shared data members every transaction must have.
// -------------------------------------------------------------------------------
// Notes: customerID and movie* are the only shared data members.
//        movie* is null for Inventory since it doesn't target a specific movie.
//        mediaType is NOT here — it belongs only in Borrow and Return.
//        doTrans, setData, and display are pure virtual — each subclass
//        implements them differently based on what the transaction does.
//        Business calls setData() then doTrans() on every transaction object.
// -------------------------------------------------------------------------------
#include "../Movies/Movie.h"
#include "../Customers/CustomerAccounts.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Trans {
public:
    Trans();            // constructor
    virtual ~Trans();   // destructor

    //pure virtual methods, all subclasses must implement these
    virtual void doTrans(CustomerAccounts& customerAccounts) = 0;   // executes the transaction
    virtual void setData(vector<string> tokens) = 0; // reads remaining fields from command file
    virtual void display() const = 0;           // prints transaction info
    void setMovie(Movie* other);

protected:
    int customerID;     //ID for the customer performing the transaction
    Movie* movie;       //pointer to the movie involved (null for inventory)
};
#endif