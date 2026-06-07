// --------------------------------- classic.cpp ---------------------------------
// Abigail Galung CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: May 28, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for Classic class. Reads classic movie data from
//          the movie file and implements sorting by release date then actor name.
// -------------------------------------------------------------------------------
// Notes: Genre code 'C' is already read by MovieFac before setData is called.
//        Actor is stored as "FirstName LastName" read as two separate strings.
//        releaseYear is stored in both releaseYear and base class year.
//        static_cast used in operator< and operator== since BSTree stores Movie*.
//        Same title with different actor = different Classic object, different node.
// -------------------------------------------------------------------------------
#include "classic.h"
#include <sstream>
#include <string>

// ----------------------------- Classic() ---------------------------------------
// Description: Default constructor. Sets genre to 'C', initializes month/year to 0.
// Preconditions: None.
// Postconditions: genre = 'C', releaseMonth = 0, releaseYear = 0.
//                 Other members initialized by Movie base constructor.
// -------------------------------------------------------------------------------
Classic::Classic() : releaseMonth(0), releaseYear(0){ genre = 'C'; }

// ----------------------------- ~Classic() --------------------------------------
// Description: Destructor. No dynamic memory allocated in Classic.
// Preconditions: None.
// Postconditions: Classic object destroyed.
// -------------------------------------------------------------------------------
Classic::~Classic() {}

// ----------------------------- setData() ---------------------------------------
// Description: Reads classic movie data from data4movies.txt.
//              Genre code 'C' has already been read by MovieFac before this call.
// Preconditions: infile is open and positioned after the genre code.
//                Format: C, Stock, Director, Title, ActorFirst ActorLast Month Year
// Postconditions: stock, director, title, actor, releaseMonth, releaseYear
//                 filled from file. year set to releaseYear. infile advanced.
// -------------------------------------------------------------------------------
void Classic::setData(vector<string> tokens) {
    
    stock = stoi(tokens[0]);      //extract stock
    director = tokens[1];         //extract director
    title = tokens[2];            //extract title

    //last string in the vector will contain the actor name, month, and year.
    string line = tokens[3];
    istringstream iss(line);      //separate line by spaces
    string actorFirst, actorLast, monthString, yearString;
    iss >> actorFirst >> actorLast >> monthString >> yearString;    //save into variables

    //adjust type of variable and save info
    actor = actorFirst + " " + actorLast;
    releaseMonth = stoi(monthString);
    releaseYear = stoi(yearString);

}
void Classic::setTransactionData(vector<string> tokens) {
    releaseMonth = stoi(tokens[0]);
    releaseYear = stoi(tokens[1]);
    actor = tokens[2];

}

// ----------------------------- operator< ---------------------------------------
// Description: Compares two Classic movies for BSTree ordering.
//              Sorts by release year first, then month, then actor alphabetically.
// Preconditions: other must be a Classic object.
// Postconditions: Returns true if this movie comes before other. Both unchanged.
// -------------------------------------------------------------------------------
bool Classic::operator<(const Movie& other) const {
    const Classic& o = static_cast<const Classic&>(other);
    if (releaseYear != o.releaseYear) return releaseYear < o.releaseYear;
    if (releaseMonth != o.releaseMonth) return releaseMonth < o.releaseMonth;
    return actor < o.actor;
}

// ----------------------------- operator== --------------------------------------
// Description: Checks equality between two Classic movies.
//              Two classics are equal only if month, year, AND actor all match.
//              Same title with a different actor is a different entry.
// Preconditions: other must be a Classic object.
// Postconditions: Returns true if equal. Both movies unchanged.
// -------------------------------------------------------------------------------
bool Classic::operator==(const Movie& other) const {
    const Classic& o = static_cast<const Classic&>(other);
    return (releaseYear == o.releaseYear && releaseMonth == o.releaseMonth && actor == o.actor);
}

// ----------------------------- display() ---------------------------------------
// Description: Prints classic movie information to cout.
//              Called by BSTree::display() during Inventory command.
// Preconditions: setData() has been called.
// Postconditions: Movie info printed to cout. Movie unchanged.
// -------------------------------------------------------------------------------
void Classic::display() const {
    cout << "C " << stock << " " << director << " " << title << " " << actor << " " << releaseMonth << " " << releaseYear << endl;
}

// ----------------------------- getActor() --------------------------------------
// Description: Returns the major actor's full name.
//              Used by Borrow::doTrans() to suggest alternative actor versions.
// Preconditions: setData() has been called.
// Postconditions: Returns actor string. Movie unchanged.
// -------------------------------------------------------------------------------
string Classic::getActor() const { return actor; }

// ----------------------------- getReleaseMonth() -------------------------------
// Description: Returns the release month (1-12).
//              Used for lookup and comparison during Borrow/Return commands.
// Preconditions: setData() has been called.
// Postconditions: Returns releaseMonth. Movie unchanged.
// -------------------------------------------------------------------------------
int Classic::getReleaseMonth() const { return releaseMonth; }

// ----------------------------- getReleaseYear() --------------------------------
// Description: Returns the release year.
//              Used for lookup and comparison during Borrow/Return commands.
// Preconditions: setData() has been called.
// Postconditions: Returns releaseYear. Movie unchanged.
// -------------------------------------------------------------------------------
int Classic::getReleaseYear() const { return releaseYear; } 