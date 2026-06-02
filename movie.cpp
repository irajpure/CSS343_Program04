// --------------------------------- movie.cpp -----------------------------------
// Abigail Galung CSS343
// Creation Date: May 27, 2026
// Date of Last Modification: May 27, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Movie class - abstract base class for all
//          movie types. Implements shared getters and stock management methods.
// -------------------------------------------------------------------------------
// Notes: setData, operator<, operator==, and display are not implemented here
//        since they are pure virtual. Each subclass handles them differently
//        based on genre format and sorting rules.
// -------------------------------------------------------------------------------
#include "movie.h"

// ----------------------------- Movie() -----------------------------------------
// Description: Default constructor. Initializes all data members to defaults.
// Preconditions: None.
// Postconditions: genre = ' ', stock = 0, director/title = "", year = 0.
// -------------------------------------------------------------------------------
Movie::Movie() : genre(' '), stock(0), director(""), title(""), year(0) {}

// ----------------------------- ~Movie() ----------------------------------------
// Description: Destructor. No dynamic memory allocated in base class.
// Preconditions: None.
// Postconditions: Movie object destroyed.
// -------------------------------------------------------------------------------
Movie::~Movie() {}

// ----------------------------- getStock() --------------------------------------
// Description: Returns the current number of available copies.
// Preconditions: None.
// Postconditions: Returns stock. Movie unchanged.
// -------------------------------------------------------------------------------
int Movie::getStock() const { return stock; }

// ----------------------------- getTitle() --------------------------------------
// Description: Returns the movie title.
// Preconditions: None.
// Postconditions: Returns title. Movie unchanged.
// -------------------------------------------------------------------------------
string Movie::getTitle() const { return title; }

// ----------------------------- getDirector() -----------------------------------
// Description: Returns the director name.
// Preconditions: None.
// Postconditions: Returns director. Movie unchanged.
// -------------------------------------------------------------------------------
string Movie::getDirector() const { return director; }

// ----------------------------- getGenre() --------------------------------------
// Description: Returns the genre code ('F', 'D', or 'C').
// Preconditions: None.
// Postconditions: Returns genre. Movie unchanged.
// -------------------------------------------------------------------------------
char Movie::getGenre() const { return genre; }

// ----------------------------- increaseStock() ---------------------------------
// Description: Increases stock by 1. Called by Return::doTrans() after
//              validating that the customer previously borrowed this movie.
// Preconditions: None.
// Postconditions: stock incremented by 1.
// -------------------------------------------------------------------------------
void Movie::increaseStock() { stock++; }

// ----------------------------- decreaseStock() ---------------------------------
// Description: Decreases stock by 1. Called by Borrow::doTrans() after
//              confirming stock is greater than 0.
// Preconditions: stock > 0 (caller is responsible for checking).
// Postconditions: stock decremented by 1. No change if stock is already 0.
// -------------------------------------------------------------------------------
void Movie::decreaseStock() { if (stock > 0) stock--; }