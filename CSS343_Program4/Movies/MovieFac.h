#ifndef MOVIEFAC_H
#define MOVIEFAC_H
// --------------------------------- moviefac.h ----------------------------------
// Abigail Galung CSS343
// Creation Date: May 28, 2026
// Date of Last Modification: May 28, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for MovieFac class - factory class responsible for
//          creating the correct Movie subclass object based on genre code
//          read from data4movies.txt.
// -------------------------------------------------------------------------------
// Notes: Valid genre codes are 'F' (Comedy), 'D' (Drama), 'C' (Classic).
//        Invalid codes print an error, skip the rest of the line, return nullptr.
//        Business::buildMovie() checks for nullptr before inserting into BSTree.
//        setData() is called on the new object to read remaining fields from file.
// -------------------------------------------------------------------------------
#include "Movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"
#include <fstream>

class MovieFac {
public:
    Movie* createMovie(char genre, vector<string> tokens) {
        Movie* m = nullptr;
        if (genre == 'F') {
            m = new Comedy();
        } else if (genre == 'D') {
            m = new Drama();
        } else if (genre == 'C') {
            m = new Classic();
        } else {
            // invalid genre code, skip rest of the line
            cout << "ERROR: Invalid genre code '" << genre
                << "' — skipping entry." << endl;
            return nullptr;
        }
        if (m != nullptr) {
            m->setData(tokens);
        }
        return m;

    }
};
#endif