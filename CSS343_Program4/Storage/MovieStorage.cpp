// --------------------------------- MovieStorage.cpp ----------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for MovieStorage class. Manages a vector of
//          BSTree pointers for extensible movie genre storage.
// -------------------------------------------------------------------------------
// Notes: Constructor initializes 3 trees for Comedy, Drama, Classic.
//        Classic tree is stored as ClassicBSTree for getSuggestion() access.
//        genreIndex maps genre char to vector position for O(1) lookup.
//        addGenre() allows runtime addition of new genre trees — extensible.
//        All BSTree pointers owned by MovieStorage, deleted in destructor.
// -------------------------------------------------------------------------------
#include "MovieStorage.h"

// ----------------------------- MovieStorage() ----------------------------------
// Description: Constructor. Initializes 3 BSTrees for Comedy (F), Drama (D),
//              and Classic (C). Maps genre codes to vector indices.
// Preconditions: None.
// Postconditions: 3 empty BSTrees ready. genreIndex maps F=0, D=1, C=2.
// -------------------------------------------------------------------------------
MovieStorage::MovieStorage() {
    // initialize trees for the 3 current genres
    trees.push_back(new BSTree());          // index 0 = Comedy (F)
    trees.push_back(new BSTree());          // index 1 = Drama (D)
    trees.push_back(new ClassicBSTree());   // index 2 = Classic (C) — specialized

    // map genre codes to vector indices
    genreIndex['F'] = 0;
    genreIndex['D'] = 1;
    genreIndex['C'] = 2;
}

// ----------------------------- ~MovieStorage() ---------------------------------
// Description: Destructor. Deletes all BSTree pointers in the vector.
// Preconditions: None.
// Postconditions: All BSTree objects deleted. No memory leaks.
// -------------------------------------------------------------------------------
MovieStorage::~MovieStorage() {
    for (BSTree* tree : trees) {
        delete tree;
    }
    trees.clear();
}

// ----------------------------- insertMovie() -----------------------------------
// Description: Inserts a Movie into the correct BSTree based on genre code.
//              Prints error if genre code not found in genreIndex.
// Preconditions: movie is not nullptr. genre is a valid registered genre code.
// Postconditions: Movie inserted into correct BSTree.
// -------------------------------------------------------------------------------
void MovieStorage::insertMovie(char genre, Movie* movie) {
    if (genreIndex.find(genre) == genreIndex.end()) {
        cout << "ERROR: Genre '" << genre << "' not registered." << endl;
        return;
    }
    trees[genreIndex.at(genre)]->insert(movie);
}

// ----------------------------- retrieveMovie() ---------------------------------
// Description: Retrieves Movie* from correct BSTree matching the target.
//              Returns nullptr if genre not found or movie not in tree.
// Preconditions: genre is valid. target has enough fields set for operator==.
// Postconditions: Returns Movie* or nullptr. Trees unchanged.
// -------------------------------------------------------------------------------
Movie* MovieStorage::retrieveMovie(char genre, const Movie& target) const {
    if (genreIndex.find(genre) == genreIndex.end()) {
        cout << "ERROR: Genre '" << genre << "' not registered." << endl;
        return nullptr;
    }
    return trees[genreIndex.at(genre)]->retrieve(target);
}

// ----------------------------- displayAll() ------------------------------------
// Description: Displays all movies in sorted order — Comedies first, then
//              Dramas, then Classics, then any additional genres added later.
// Preconditions: None.
// Postconditions: All movies printed to cout. Trees unchanged.
// -------------------------------------------------------------------------------
void MovieStorage::displayAll() const {
    // display in genre order: F, D, C, then any extras
    if (genreIndex.count('F')) {
        cout << "---- Comedy ----" << endl;
        trees[genreIndex.at('F')]->display();
    }
    if (genreIndex.count('D')) {
        cout << "---- Drama ----" << endl;
        trees[genreIndex.at('D')]->display();
    }
    if (genreIndex.count('C')) {
        cout << "---- Classics ----" << endl;
        trees[genreIndex.at('C')]->display();
    }
    // any future genres added via addGenre() will display here
    for (auto& pair : genreIndex) {
        if (pair.first != 'F' && pair.first != 'D' && pair.first != 'C') {
            cout << "---- " << pair.first << " ----" << endl;
            trees[pair.second]->display();
        }
    }
}

// ----------------------------- getTree() ---------------------------------------
// Description: Returns BSTree pointer for a specific genre code.
//              Used by Inventory to display a specific genre tree.
// Preconditions: genre is a valid registered genre code.
// Postconditions: Returns BSTree* or nullptr if genre not found.
// -------------------------------------------------------------------------------
BSTree* MovieStorage::getTree(char genre) const {
    if (genreIndex.find(genre) == genreIndex.end()) return nullptr;
    return trees[genreIndex.at(genre)];
}

// ----------------------------- getClassicTree() --------------------------------
// Description: Returns ClassicBSTree pointer specifically for Classic genre.
//              Used by Borrow::doTrans() to call getSuggestion() when stock is 0.
// Preconditions: None.
// Postconditions: Returns ClassicBSTree* or nullptr if Classic not registered.
// -------------------------------------------------------------------------------
ClassicBSTree* MovieStorage::getClassicTree() const {
    if (genreIndex.find('C') == genreIndex.end()) return nullptr;
    return static_cast<ClassicBSTree*>(trees[genreIndex.at('C')]);
}

// ----------------------------- addGenre() --------------------------------------
// Description: Adds a new genre BSTree to the storage for future expansion.
//              Example: addGenre('A', new BSTree()) for Adventure movies.
// Preconditions: genre code not already registered. tree is not nullptr.
// Postconditions: New genre registered and BSTree added to vector.
// -------------------------------------------------------------------------------
void MovieStorage::addGenre(char genre, BSTree* tree) {
    if (genreIndex.find(genre) != genreIndex.end()) {
        cout << "ERROR: Genre '" << genre << "' already registered." << endl;
        return;
    }
    genreIndex[genre] = trees.size();   // map genre to next available index
    trees.push_back(tree);              // add tree to vector
}