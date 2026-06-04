#ifndef INVENTORY_H
#define INVENTORY_H
// --------------------------------- inventory.h ---------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Inventory class - represents an Inventory (I)
//          transaction. Inherits from Trans. Displays full movie inventory
//          across all 3 genre BSTrees in sorted order.
// -------------------------------------------------------------------------------
// Notes: Inventory stores no extra data members beyond Trans base class.
//        movie* and customerID are not used (nullptr and 0) since Inventory
//        does not target a specific customer or movie.
//        doTrans() takes the 3 BSTrees from Business and calls display() on each.
//        setData() just skips the rest of the line since I has no extra fields.
// -------------------------------------------------------------------------------
#include "trans.h"
#include "bstree.h"

class Inventory : public Trans {
public:
    Inventory();            // constructor
    virtual ~Inventory();   // destructor

    virtual void doTrans(CustomerAccounts& customerAccounts);   // prints full inventory
    virtual void setData(ifstream& infile);                     // skips rest of line (no fields)
    virtual void display() const;                              // not used for Inventory

    // Business passes its 3 BSTrees so Inventory can display them
    void setTrees(BSTree& comedy, BSTree& drama, BSTree& classic);

private:
    BSTree* comedyTree;     // pointer to Business's Comedy BSTree
    BSTree* dramaTree;      // pointer to Business's Drama BSTree
    BSTree* classicTree;    // pointer to Business's Classic BSTree
};
#endif