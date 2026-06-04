#ifndef INVENTORY_H
#define INVENTORY_H
// --------------------------------- inventory.h ---------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Inventory class - represents an Inventory (I)
//          transaction. Displays full movie inventory via MovieStorage.
// -------------------------------------------------------------------------------
// Notes: Inventory stores no extra data members beyond Trans base class.
//        setMovieStorage() must be called by Business before doTrans().
//        doTrans() calls MovieStorage::displayAll() which handles all genres
//        in order including any future genres added via addGenre().
//        display() intentionally empty — Inventory never logged to history.
// -------------------------------------------------------------------------------
#include "Trans.h"
#include "../Storage/MovieStorage.h"

class Inventory : public Trans {
public:
    Inventory();            // constructor
    virtual ~Inventory();   // destructor

    virtual void doTrans(CustomerAccounts& customerAccounts);    // prints full inventory
    virtual void setData(ifstream& infile);                     // skips rest of line
    virtual void display() const;                              // intentionally empty

    // Business passes MovieStorage pointer before calling doTrans()
    void setMovieStorage(MovieStorage* storage);

private:
    MovieStorage* movieStorage;     // pointer to Business's MovieStorage
};
#endif