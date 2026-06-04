// --------------------------------- inventory.cpp -------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Inventory class. Displays the full movie
//          inventory across all 3 genre BSTrees in sorted order.
// -------------------------------------------------------------------------------
// Notes: Inventory has no extra data members — movie* and customerID unused.
//        setTrees() must be called by Business before doTrans() to pass the 3 trees.
//        doTrans() prints Comedies first, then Dramas, then Classics.
//        Each BSTree::display() handles its own in-order sorted output.
//        display() is a no-op since Inventory doesn't appear in customer history.
// -------------------------------------------------------------------------------
#include "inventory.h"

// ----------------------------- Inventory() -------------------------------------
// Description: Default constructor. Initializes tree pointers to nullptr.
// Preconditions: None.
// Postconditions: comedyTree = dramaTree = classicTree = nullptr.
//                 customerID and movie initialized by Trans base constructor.
// -------------------------------------------------------------------------------
Inventory::Inventory() : comedyTree(nullptr), dramaTree(nullptr), classicTree(nullptr) {}

// ----------------------------- ~Inventory() ------------------------------------
// Description: Destructor. Does not delete trees — Business owns them.
// Preconditions: None.
// Postconditions: Inventory object destroyed. BSTrees not affected.
// -------------------------------------------------------------------------------
Inventory::~Inventory() {}

// ----------------------------- setTrees() --------------------------------------
// Description: Sets pointers to Business's 3 BSTrees so doTrans() can display them.
//              Must be called by Business before calling doTrans().
// Preconditions: comedy, drama, classic are valid BSTree objects owned by Business.
// Postconditions: comedyTree, dramaTree, classicTree point to Business's trees.
// -------------------------------------------------------------------------------
void Inventory::setTrees(BSTree& comedy, BSTree& drama, BSTree& classic) {
    comedyTree  = &comedy;      // point to Business's comedy tree
    dramaTree   = &drama;       // point to Business's drama tree
    classicTree = &classic;     // point to Business's classic tree
}

// ----------------------------- setData() ---------------------------------------
// Description: Reads rest of command line after action code 'I'.
//              No extra fields for Inventory command — just skips the line.
// Preconditions: infile is open and positioned after action code 'I'.
// Postconditions: infile advanced past current line.
// -------------------------------------------------------------------------------
void Inventory::setData(ifstream& infile) {
    string dummy;
    getline(infile, dummy);     // skip rest of line, no fields to read for I
}

// ----------------------------- doTrans() ---------------------------------------
// Description: Prints full movie inventory across all 3 genre trees in order.
//              Prints Comedies first, then Dramas, then Classics.
//              Each genre is sorted by its own rules via BSTree::display().
// Preconditions: setTrees() has been called. All 3 tree pointers are valid.
// Postconditions: Full inventory printed to cout. Trees unchanged.
// -------------------------------------------------------------------------------
void Inventory::doTrans(CustomerAccounts& customerAccounts) {
    cout << "---- Comedy ----" << endl;
    if (comedyTree != nullptr)  comedyTree->display();

    cout << "---- Drama ----" << endl;
    if (dramaTree != nullptr)   dramaTree->display();

    cout << "---- Classics ----" << endl;
    if (classicTree != nullptr) classicTree->display();
}

// ----------------------------- display() ---------------------------------------
// Description: Not used for Inventory — Inventory never appears in customer
//              history so this method is intentionally empty.
// Preconditions: None.
// Postconditions: Nothing printed. Object unchanged.
// -------------------------------------------------------------------------------
void Inventory::display() const {
    // intentionally empty — Inventory does not appear in customer history
}