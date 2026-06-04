// --------------------------------- comedy.cpp ----------------------------------
// Abigail Galung CSS343
// Creation Date: May 27, 2026
// Date of Last Modification: May 27, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Comedy class. Reads comedy movie data from
//          the movie file and implements sorting by title then year.
// -------------------------------------------------------------------------------
// Notes: Genre code 'F' is already read by MovieFac before setData is called.
//        Leading spaces after commas are removed with substr(1).
//        static_cast used in operator< and operator== since BSTree stores Movie*.
// -------------------------------------------------------------------------------
#include "comedy.h"

// ----------------------------- Comedy() ----------------------------------------
// Description: Default constructor. Sets genre to 'F' for Comedy.
// Preconditions: None.
// Postconditions: genre = 'F'. Other members initialized by Movie base constructor.
// -------------------------------------------------------------------------------
Comedy::Comedy() { genre = 'F'; }

// ----------------------------- ~Comedy() ---------------------------------------
// Description: Destructor. No dynamic memory allocated in Comedy.
// Preconditions: None.
// Postconditions: Comedy object destroyed.
// -------------------------------------------------------------------------------
Comedy::~Comedy() {}

// ----------------------------- setData() ---------------------------------------
// Description: Reads comedy movie data from data4movies.txt.
//              Genre code 'F' has already been read by MovieFac before this call.
// Preconditions: infile is open and positioned after the genre code.
//                Format: F, Stock, Director, Title, Year
// Postconditions: stock, director, title, year filled from file. infile advanced.
// -------------------------------------------------------------------------------
void Comedy::setData(ifstream& infile) {
    char comma;
    infile >> stock;    // read stock
    infile >> comma;    // read comma
    getline(infile, director, ',');  // read director until comma
    director = director.substr(1);           // remove leading space
    getline(infile, title, ',');     // read title until comma
    title = title.substr(1);                 // remove leading space
    infile >> year;     // read year
}

// ----------------------------- operator< ---------------------------------------
// Description: Compares two Comedy movies for BSTree ordering.
//              Sorts alphabetically by title first, then by year if titles match.
// Preconditions: other must be a Comedy object.
// Postconditions: Returns true if this movie comes before other. Both unchanged.
// -------------------------------------------------------------------------------
bool Comedy::operator<(const Movie& other) const {
    const Comedy& o = static_cast<const Comedy&>(other);
    if (title != o.title) return title < o.title;
    return year < o.year;
}

// ----------------------------- operator== --------------------------------------
// Description: Checks equality between two Comedy movies.
//              Two comedies are equal if they share the same title and year.
// Preconditions: other must be a Comedy object.
// Postconditions: Returns true if equal. Both movies unchanged.
// -------------------------------------------------------------------------------
bool Comedy::operator==(const Movie& other) const {
    const Comedy& o = static_cast<const Comedy&>(other);
    return (title == o.title && year == o.year);
}

// ----------------------------- display() ---------------------------------------
// Description: Prints comedy movie information to cout.
//              Called by BSTree::display() during Inventory command.
// Preconditions: setData() has been called.
// Postconditions: Movie info printed to cout. Movie unchanged.
// -------------------------------------------------------------------------------
void Comedy::display() const {
    cout << "F " << stock << " " << director << " " << title << " " << year << endl;
}