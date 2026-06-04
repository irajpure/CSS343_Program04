#ifndef COMEDY_H
#define COMEDY_H
// --------------------------------- comedy.h ------------------------------------
// Abigail Galung CSS343
// Creation Date: May 27, 2026
// Date of Last Modification: May 27, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Comedy class - represents a Comedy (F) genre movie.
//          Inherits from Movie and implements sorting by title then year.
// -------------------------------------------------------------------------------
// Notes: Input format from data4movies.txt: F, Stock, Director, Title, Year
//        Sorting rule: alphabetically by title first, then by year oldest to newest.
//        Two comedies are equal if they share the same title and year.
// -------------------------------------------------------------------------------
#include "Movie.h"

class Comedy : public Movie {
public:
    Comedy();                // constructor
    virtual ~Comedy();       // destructor

    virtual bool operator <(const Movie& other) const;    // sorts by title then year
    virtual bool operator ==(const Movie& other) const;   // equal if title and year match
    virtual void setData(ifstream& infile);               // reads comedy data from file
    virtual void display() const;                         // prints comedy info
    void setSearchData(string t, int y) { title = t; year = y; }
};
#endif