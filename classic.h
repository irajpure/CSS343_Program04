#ifndef CLASSIC_H
#define CLASSIC_H
// --------------------------------- classic.h -----------------------------------
// Abigail Galung CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: May 28, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Classic class - represents a Classic (C) genre movie.
//          Inherits from Movie and implements sorting by release date then actor.
// -------------------------------------------------------------------------------
// Notes: Input format: C, Stock, Director, Title, ActorFirst ActorLast Month Year
//        Sorting rule: by release year, then month, then actor name alphabetically.
//        Same title can have multiple Classic objects with different actors —
//        each is a separate node in the BSTree with its own stock count.
//        Two classics are equal only if month, year, AND actor all match.
//        releaseYear is also stored in base class year for consistency.
// -------------------------------------------------------------------------------
#include "movie.h"

class Classic : public Movie {
public:
    Classic();                // constructor
    virtual ~Classic();       // destructor

    virtual bool operator <(const Movie& other) const;    // sorts by year, month, actor
    virtual bool operator ==(const Movie& other) const;   // equal if year, month, and actor match
    virtual void setData(ifstream& infile);               // reads classic data from file
    virtual void display() const;                         // prints classic info
    
    // getters needed for Borrow/Return lookup and alternative suggestion
    string getActor() const;            // returns major actor name
    int getReleaseMonth() const;        // returns release month
    int getReleaseYear() const;         // returns release year
 
private:
    string actor;         // major actor (first + last name)
    int releaseMonth;     // release month (1-12)
    int releaseYear;      // release year
};
#endif