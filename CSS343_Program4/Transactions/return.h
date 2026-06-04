#ifndef RETURN_H
#define RETURN_H
// --------------------------------- return.h ------------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Return class - represents a Return (R) transaction.
//          Inherits from Trans. Increases movie stock by 1 and logs transaction.
// -------------------------------------------------------------------------------
// Notes: mediaType is always 'D' for DVD currently but stored for extensibility.
//        doTrans() checks customer previously borrowed this movie before
//        incrementing stock. If never borrowed, prints error and skips.
//        setData() reads customerID, mediaType, movieType, and movie ID fields.
// -------------------------------------------------------------------------------
#include "Trans.h"
#include "CustomerAccounts.h"

class Return : public Trans {
public:
    Return();                                                 // constructor
    virtual ~Return();                                        // destructor
    virtual void doTrans(CustomerAccounts& customerAccounts); // increase stock, logs transaction
    virtual void setData(ifstream& infile);                   // reads command fields from file
    virtual void display() const;                             // prints return info
    char getMovieType() const { return movieType; }
    void setMovie(Movie* m) { movie = m; }

private:
    string mediaType; // media format (always ‘D’ for DVD, extensible for future types)
    char movieType;   // genre code for the movie being returned ('F', 'D', 'C')

};
#endif