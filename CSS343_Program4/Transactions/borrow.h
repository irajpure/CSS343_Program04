#ifndef BORROW_H
#define BORROW_H
// --------------------------------- borrow.h ------------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Borrow class - represents a Borrow (B) transaction.
//          Inherits from Trans. Decreases movie stock by 1 and logs transaction.
// -------------------------------------------------------------------------------
// Notes: mediaType is always 'D' for DVD currently but stored for extensibility.
//        doTrans() takes CustomerAccounts reference to log transaction and
//        validate customer exists. Checks stock > 0 before decrementing.
//        If stock is 0 and movie is Classic, suggests alternative actor version.
//        setData() reads customerID, mediaType, movieType from command file.
// -------------------------------------------------------------------------------
#include "Trans.h"
#include "../Customers/CustomerAccounts.h"

class Borrow : public Trans {
public:
    Borrow();                                                 // constructor
    virtual ~Borrow();                                        // destructor
    virtual void doTrans(CustomerAccounts& customerAccounts); // decrease stock, logs transaction
    virtual void setData(vector<string> tokens);                   // reads command fields from file
    virtual void display() const;                             // prints borrow info
    char getMovieType() const { return movieType; }
    void setMovie(Movie* m) { movie = m; }

private:
    string mediaType; // media format (always ‘D’ for DVD, extensible for future types)
    char movieType;   // genre code for the movie being returned ('F', 'D', 'C')
};
#endif