// --------------------------------- borrow.cpp ----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Borrow class. Handles borrowing a DVD by
//          validating stock, decrementing it, and logging the transaction.
// -------------------------------------------------------------------------------
// Notes: setData() reads customerID, mediaType, movieType, then movie ID fields.
//        doTrans() checks stock > 0 before decrementing.
//        For Classic movies with 0 stock, suggests alternative actor version.
//        Transaction logged via CustomerAccounts::addTransForCustomer() on success.
//        customerAccounts reference is passed in from Business::processTrans().
// -------------------------------------------------------------------------------
#include "borrow.h"
#include "../Movies/classic.h"

// ----------------------------- Borrow() ----------------------------------------
// Description: Default constructor. Initializes mediaType and movieType to empty.
// Preconditions: None.
// Postconditions: mediaType = "", movieType = ' '.
//                 customerID and movie initialized by Trans base constructor.
// -------------------------------------------------------------------------------
Borrow::Borrow() : mediaType(""), movieType(' ') {}

// ----------------------------- ~Borrow() ---------------------------------------
// Description: Destructor. No dynamic memory allocated in Borrow.
// Preconditions: None.
// Postconditions: Borrow object destroyed.
// -------------------------------------------------------------------------------
Borrow::~Borrow() {}

// ----------------------------- doTrans() ---------------------------------------
// Description: Executes the borrow transaction. Checks customer exists and stock
//              is greater than 0 before decrementing. Prints error if stock is 0.
//              For Classic movies with 0 stock, suggests alternative actor version.
//              Logs transaction to customer history via CustomerAccounts on success.
// Preconditions: movie pointer is set and valid. customerAccounts is valid.
// Postconditions: movie stock decremented by 1 if valid. Transaction logged.
// -------------------------------------------------------------------------------
void Borrow::doTrans(CustomerAccounts& customerAccounts) {
    if (movie == nullptr) {
        cout << "ERROR: Movie not found in inventory." << endl;
        return;
    }
    if (!customerAccounts.containsAccount(customerID)) {
        cout << "ERROR: Customer " << customerID << " not found." << endl;
        return;
    }
    if (movie->getStock() <= 0) {
        cout << "ERROR: " << movie->getTitle() << " is currently out of stock." << endl;
        // for classic movies, suggest alternative actor version if available
        if (movie->getGenre() == 'C') {
            cout << "Suggestion: try another actor's version of this title." << endl;
        }
        return;
    }
    movie->decreaseStock(); // decrement stock by 1
    // log transaction to customer history
    customerAccounts.addTransForCustomer(customerID, "B", string(1, movieType), 
        movie->getDirector(), movie->getTitle(), movie->getYear());
}

// ----------------------------- setData() ---------------------------------------
// Description: Reads remaining fields from command file after action code 'B'.
//              Stores customerID, mediaType, and movieType. Movie lookup is
//              handled by Business which passes the movie pointer to this object.
// Preconditions: infile is open and positioned after action code 'B'.
//                Format: B customerID mediaType movieType movieIDfields
// Postconditions: customerID, mediaType, movieType filled. infile advanced.
// -------------------------------------------------------------------------------
void Borrow::setData(vector<string> tokens) {
    customerID = stoi(tokens[0]);       // read customer ID
    mediaType = tokens[1];        // read media type (currently always 'D' for DVD)
    movieType = tokens[2][0];        // read movie genre code ('F', 'D', 'C') 
    if (movieType == 'C') {
        //releaseMonth = stoi(tokens[3]);
    }
}

// ----------------------------- display() ---------------------------------------
// Description: Prints borrow transaction info to cout.
//              Called by CustomerList when printing customer history.
// Preconditions: setData() and doTrans() have been called.
// Postconditions: Transaction info printed to cout. Object unchanged.
// -------------------------------------------------------------------------------
void Borrow::display() const {
    cout << "Borrow: " << mediaType << " " << movie->getTitle() << endl;
}