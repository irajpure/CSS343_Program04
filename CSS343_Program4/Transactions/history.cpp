// --------------------------------- history.cpp ---------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for History class. Displays all transactions for
//          a specific customer from most recent to oldest.
// -------------------------------------------------------------------------------
// Notes: setData() only reads customerID — H command has no other fields.
//        doTrans() validates customer exists then calls CustomerList::print()
//        via CustomerAccounts to display the full transaction history.
//        movie* stays nullptr since History doesn't target a specific movie.
//        display() is intentionally empty — History is never logged to history.
// -------------------------------------------------------------------------------
#include "history.h"

// ----------------------------- History() ---------------------------------------
// Description: Default constructor. No extra data members to initialize.
// Preconditions: None.
// Postconditions: customerID and movie initialized by Trans base constructor.
// -------------------------------------------------------------------------------
History::History() {}
 
// ----------------------------- ~History() --------------------------------------
// Description: Destructor. No dynamic memory allocated in History.
// Preconditions: None.
// Postconditions: History object destroyed.
// -------------------------------------------------------------------------------
History::~History() {}

// ----------------------------- doTrans() ---------------------------------------
// Description: Prints full transaction history for the customer.
//              Validates customer exists first. Calls CustomerAccounts to
//              find customer and print their history newest to oldest.
// Preconditions: setData() has been called. customerAccounts is valid.
// Postconditions: Customer history printed to cout. Nothing changed.
// -------------------------------------------------------------------------------
void History::doTrans(CustomerAccounts& customerAccounts) {
    if (!customerAccounts.containsAccount(customerID)) {
        cout << "ERROR: Customer" << customerID << " not found." << endl;
        return;
    }
    cout << "History for Customer " << customerID << ":" << endl;
    customerAccounts.print(); // print history for this customer
}

// ----------------------------- setData() ---------------------------------------
// Description: Reads customerID from command file after action code 'H'.
//              H command only has one field — the customer ID.
// Preconditions: infile is open and positioned after action code 'H'.
//                Format: H customerID
// Postconditions: customerID filled. infile advanced.
// -------------------------------------------------------------------------------
void History::setData(ifstream& infile) {
    infile >> customerID; // read customer ID — only field for H command
}

// ----------------------------- display() ---------------------------------------
// Description: Not used for History — History command itself is never logged
//              to a customer's transaction history.
// Preconditions: None.
// Postconditions: Nothing printed. Object unchanged.
// -------------------------------------------------------------------------------
void History::display() const {
    // intentionally empty — History is never logged to customer history
}