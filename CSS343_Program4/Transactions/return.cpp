// --------------------------------- return.cpp ----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Return class. Handles returning a DVD by
//          validating prior borrow, incrementing stock, and logging transaction.
// -------------------------------------------------------------------------------
// Notes: setData() reads customerID, mediaType, movieType, then movie ID fields.
//        doTrans() checks customer previously borrowed this movie before
//        incrementing stock. Prints error and skips if never borrowed.
//        Transaction logged via CustomerAccounts::addTransForCustomer() on success.
//        customerAccounts reference is passed in from Business::processTrans().
// -------------------------------------------------------------------------------
#include "return.h"

// ----------------------------- Return() ----------------------------------------
// Description: Default constructor. Initializes mediaType and movieType to empty.
// Preconditions: None.
// Postconditions: mediaType = "", movieType = ' '.
//                 customerID and movie initialized by Trans base constructor.
// -------------------------------------------------------------------------------
Return::Return() : mediaType(""), movieType(' ') {}

// ----------------------------- ~Return() ---------------------------------------
// Description: Destructor. No dynamic memory allocated in Return.
// Preconditions: None.
// Postconditions: Return object destroyed.
// -------------------------------------------------------------------------------
Return::~Return() {}

// ----------------------------- doTrans() ---------------------------------------
// Description: Executes the return transaction. Checks customer previously
//              borrowed this movie before incrementing stock. Prints error
//              and skips if movie was never borrowed by this customer.
//              Logs transaction to customer history on success.
// Preconditions: movie pointer is set and valid. customer is valid.
// Postconditions: movie stock incremented by 1 if valid. Transaction logged.
// -------------------------------------------------------------------------------
void Return::doTrans(CustomerAccounts& customerAccounts) {
    if (movie == nullptr) {
        cout << "ERROR: Movie not found in inventory." << endl;
        return;
    }
    if (!customerAccounts.containsAccount(customerID)) {
        cout << "ERROR: Customer " << customerID << " not found." << endl;
        return;
    }
    if (!customerAccounts.checkBorrowedMovie(customerID, string(1, movieType), 
        movie->getDirector(), movie->getTitle(), movie->getYear())) {
            cout << "ERROR: Customer " << customerID << " never borrowed " << movie->getTitle() << endl;
            return;
    }
    movie->increaseStock(); // increment stock by 1
    // log transaction to customer history
    customerAccounts.addTransForCustomer(customerID, "R", string(1, movieType), 
        movie->getDirector(), movie->getTitle(), movie->getYear());
}

// ----------------------------- setData() ---------------------------------------
// Description: Reads remaining fields from command file after action code 'R'.
//              Stores customerID, mediaType, and movieType. Movie lookup is
//              handled by Business which passes the movie pointer to this object.
// Preconditions: infile is open and positioned after action code 'R'.
//                Format: R customerID mediaType movieType movieIDfields
// Postconditions: customerID, mediaType, movieType filled. infile advanced.
// -------------------------------------------------------------------------------
void Return::setData(vector<string> tokens) {
    customerID = stoi(tokens[0]);   // read customer ID
    mediaType = tokens[1];    // read media type ('D' for DVD)
    movieType = tokens[2][0];    // read movie genre code ('F', 'D', 'C')
}

// ----------------------------- display() ---------------------------------------
// Description: Prints return transaction info to cout.
//              Called by CustomerList when printing customer history.
// Preconditions: setData() and doTrans() have been called.
// Postconditions: Transaction info printed to cout. Object unchanged.
// -------------------------------------------------------------------------------
void Return::display() const {
    cout << "Return: " << mediaType << " " << movie->getTitle() << endl;
}