#ifndef HISTORY_H
#define HISTORY_H
// --------------------------------- history.h -----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for History class - represents a History (H) transaction.
//          Inherits from Trans. Displays all transactions for a specific customer
//          from most recent to oldest.
// -------------------------------------------------------------------------------
// Notes: History only needs customerID — no movie* needed (stays nullptr).
//        doTrans() looks up customer in CustomerAccounts and calls print()
//        to display their full transaction history newest to oldest.
//        setData() only reads customerID since H command has no other fields.
//        display() is not used since History itself is not logged to history.
// -------------------------------------------------------------------------------
#include "Trans.h"

class History : public Trans {
public:
    History();                                                 // constructor
    virtual ~History();                                        // destructor
    virtual void doTrans(CustomerAccounts& customerAccounts); // prints customer history
    virtual void setData(vector<string> tokens);                   // reads customerID from command file
    virtual void display() const;                             // not used for History
};
#endif