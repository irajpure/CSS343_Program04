// --------------------------------- Trans.cpp -----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Trans class - abstract base class for all
//          transaction types. Implements constructor and destructor only.
// -------------------------------------------------------------------------------
// Notes: doTrans, setData, and display are pure virtual and not implemented here.
//        Each subclass (Borrow, Return, Inventory, History) handles them
//        differently based on what the transaction needs to do.
// -------------------------------------------------------------------------------
#include "Trans.h"

// ----------------------------- Trans() -----------------------------------------
// Description: Default constructor. Initializes customerID to 0 and movie to
//              nullptr. Subclasses fill these via setData().
// Preconditions: None.
// Postconditions: customerID = 0, movie = nullptr.
// -------------------------------------------------------------------------------
Trans::Trans() : customerID(0), movie(nullptr) {}

void Trans::setMovie(Movie* other) {
    movie = other;
}

// ----------------------------- ~Trans() ----------------------------------------
// Description: Destructor. Does not delete movie pointer — Business owns
//              the Movie objects and is responsible for their deletion.
// Preconditions: None.
// Postconditions: Trans object destroyed. Movie object not affected.
// -------------------------------------------------------------------------------
Trans::~Trans() {}
