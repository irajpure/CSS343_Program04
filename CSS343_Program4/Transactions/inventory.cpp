// --------------------------------- inventory.cpp -------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Inventory class. Displays full movie
//          inventory via MovieStorage::displayAll().
// -------------------------------------------------------------------------------
// Notes: setMovieStorage() must be called by Business before doTrans().
//        doTrans() calls MovieStorage::displayAll() which handles all genres
//        including any future ones added via MovieStorage::addGenre().
//        display() is intentionally empty — Inventory never logged to history.
// -------------------------------------------------------------------------------
#include "inventory.h"

// ----------------------------- Inventory() -------------------------------------
// Description: Default constructor. Initializes movieStorage pointer to nullptr.
// Preconditions: None.
// Postconditions: movieStorage = nullptr.
// -------------------------------------------------------------------------------
Inventory::Inventory() : movieStorage(nullptr) {}

// ----------------------------- ~Inventory() ------------------------------------
// Description: Destructor. Does not delete movieStorage — Business owns it.
// Preconditions: None.
// Postconditions: Inventory object destroyed. MovieStorage not affected.
// -------------------------------------------------------------------------------
Inventory::~Inventory() {}

// ----------------------------- setMovieStorage() -------------------------------
// Description: Sets pointer to Business's MovieStorage for display.
//              Must be called by Business before doTrans().
// Preconditions: storage is a valid MovieStorage owned by Business.
// Postconditions: movieStorage points to Business's MovieStorage.
// -------------------------------------------------------------------------------
void Inventory::setMovieStorage(MovieStorage* storage) {
    movieStorage = storage;
}

// ----------------------------- setData() ---------------------------------------
// Description: Skips rest of command line — I command has no extra fields.
// Preconditions: infile positioned after action code 'I'.
// Postconditions: infile advanced past current line.
// -------------------------------------------------------------------------------
void Inventory::setData(ifstream& infile) {
    string dummy;
    getline(infile, dummy);     // no fields to read for I command
}

// ----------------------------- doTrans() ---------------------------------------
// Description: Prints full movie inventory via MovieStorage::displayAll().
//              Handles all genres in order including future genres.
// Preconditions: setMovieStorage() has been called. movieStorage is valid.
// Postconditions: Full inventory printed to cout. MovieStorage unchanged.
// -------------------------------------------------------------------------------
void Inventory::doTrans(CustomerAccounts& customerAccounts) {
    if (movieStorage == nullptr) {
        cout << "ERROR: Movie storage not set." << endl;
        return;
    }
    movieStorage->displayAll();     // handles all genres in correct order
}

// ----------------------------- display() ---------------------------------------
// Description: Intentionally empty — Inventory never appears in customer history.
// Preconditions: None.
// Postconditions: Nothing printed. Object unchanged.
// -------------------------------------------------------------------------------
void Inventory::display() const {
    // intentionally empty
}