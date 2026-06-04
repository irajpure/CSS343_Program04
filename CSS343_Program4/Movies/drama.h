#ifndef DRAMA_H
#define DRAMA_H
// --------------------------------- drama.h -------------------------------------
// Abigail Galung CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: May 28, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Drama class - represents a Drama (D) genre movie.
//          Inherits from Movie and implements sorting by director then title.
// -------------------------------------------------------------------------------
// Notes: Input format from data4movies.txt: D, Stock, Director, Title, Year
//        Sorting rule: alphabetically by director first, then by title.
//        Two dramas are equal if they share the same director and title.
//        Command file identifies dramas by director and title (no year needed).
// -------------------------------------------------------------------------------
#include "Movie.h"

class Drama : public Movie {
public:
    Drama();                // constructor
    virtual ~Drama();       // destructor

    virtual bool operator <(const Movie& other) const;    // sorts by director then title
    virtual bool operator ==(const Movie& other) const;   // equal if title and year match
    virtual void setData(ifstream& infile);               // reads drama data from file
    virtual void display() const;                         // prints drama info
    void setSearchData(string dir, string t) { director = dir; title = t; }
};
#endif