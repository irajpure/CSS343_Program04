#ifndef MOVIESTORAGE_H
#define MOVIESTORAGE_H
// --------------------------------- MovieStorage.h ------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for MovieStorage class - manages a vector of BSTree
//          pointers, one per movie genre. Designed for extensibility so new
//          movie types can be added without changing Business logic.
// -------------------------------------------------------------------------------
// Notes: genre codes map to vector indices:
//        'F' (Comedy)  → index 0
//        'D' (Drama)   → index 1
//        'C' (Classic) → index 2 (stored as ClassicBSTree for extra functionality)
//        addGenre() allows new genres to be added in the future (e.g. 'A' Adventure)
//        Business uses getTree() to insert and retrieve movies by genre code.
//        MovieStorage owns all BSTree pointers and deletes them in destructor.
// -------------------------------------------------------------------------------
#include "BSTree.h"
#include "ClassicBSTree.h"
#include <vector>
#include <map>
using namespace std;

class MovieStorage {
public:
    MovieStorage();     // constructor — initializes trees for F, D, C
    ~MovieStorage();    // destructor — deletes all BSTree pointers

    // insert a movie into the correct BSTree based on genre code
    void insertMovie(char genre, Movie* movie);

    // retrieve a movie from the correct BSTree
    Movie* retrieveMovie(char genre, const Movie& target) const;

    // display all movies — Comedies, then Dramas, then Classics
    void displayAll() const;

    // get BSTree pointer for a specific genre (used by Inventory)
    BSTree* getTree(char genre) const;

    // get ClassicBSTree specifically for suggestion feature
    ClassicBSTree* getClassicTree() const;

    // add a new genre BSTree — for future expansion (e.g. Adventure)
    void addGenre(char genre, BSTree* tree);

private:
    vector<BSTree*> trees;          // stores all genre BSTrees
    map<char, int> genreIndex;      // maps genre code to vector index
};
#endif