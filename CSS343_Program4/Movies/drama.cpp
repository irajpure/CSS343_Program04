// --------------------------------- drama.cpp -----------------------------------
// Abigail Galung CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: May 28, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Drama class. Reads drama movie data from
//          the movie file and implements sorting by director then title.
// -------------------------------------------------------------------------------
// Notes: Genre code 'D' is already read by MovieFac before setData is called.
//        Leading spaces after commas are removed with substr(1).
//        static_cast used in operator< and operator== since BSTree stores Movie*.
// -------------------------------------------------------------------------------
#include "drama.h"

// ----------------------------- Drama() -----------------------------------------
// Description: Default constructor. Sets genre to 'D' for Drama.
// Preconditions: None.
// Postconditions: genre = 'D'. Other members initialized by Movie base constructor.
// -------------------------------------------------------------------------------
Drama::Drama() { genre = 'D'; }

// ----------------------------- ~Drama() ----------------------------------------
// Description: Destructor. No dynamic memory allocated in Drama.
// Preconditions: None.
// Postconditions: Drama object destroyed.
// -------------------------------------------------------------------------------
Drama::~Drama() {}

// ----------------------------- setData() ---------------------------------------
// Description: Reads drama movie data from data4movies.txt.
//              Genre code 'D' has already been read by MovieFac before this call.
// Preconditions: infile is open and positioned after the genre code.
//                Format: D, Stock, Director, Title, Year
// Postconditions: stock, director, title, year filled from file. infile advanced.
// -------------------------------------------------------------------------------
void Drama::setData(vector<string> tokens) {
    stock = stoi(tokens[0]);      //extract stock
    director = tokens[1];         //extract director
    title = tokens[2];            //extract title
    year = stoi(tokens[3]);       //extract year
}

void Drama::setTransactionData(vector<string> tokens) {
    director = tokens[0];
    title = tokens[1];
}


// ----------------------------- operator< ---------------------------------------
// Description: Compares two Drama movies for BSTree ordering.
//              Sorts alphabetically by director first, then by title if same director.
// Preconditions: other must be a Drama object.
// Postconditions: Returns true if this movie comes before other. Both unchanged.
// -------------------------------------------------------------------------------
bool Drama::operator<(const Movie& other) const {
    const Drama& o = static_cast<const Drama&>(other);
    if (director != o.director) return director < o.director;
    return title < o.title;
}

// ----------------------------- operator== --------------------------------------
// Description: Checks equality between two Drama movies.
//              Two dramas are equal if they share the same director and title.
// Preconditions: other must be a Drama object.
// Postconditions: Returns true if equal. Both movies unchanged.
// -------------------------------------------------------------------------------
bool Drama::operator==(const Movie& other) const {
    const Drama& o = static_cast<const Drama&>(other);
    return (director == o.director && title == o.title);
}

// ----------------------------- display() ---------------------------------------
// Description: Prints drama movie information to cout.
//              Called by BSTree::display() during Inventory command.
// Preconditions: setData() has been called.
// Postconditions: Movie info printed to cout. Movie unchanged.
// -------------------------------------------------------------------------------
void Drama::display() const {
    cout << "D " << stock << " " << director << " " << title << " " << year << endl;
}