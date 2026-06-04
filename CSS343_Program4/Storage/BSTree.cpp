// --------------------------------- bstree.cpp ----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for BSTree class. Stores Movie objects in sorted
//          order using each Movie subclass's own operator< for comparisons.
// -------------------------------------------------------------------------------
// Notes: BSTree does not know about genres — sorting is handled entirely by
//        Movie subclass operator< and operator==.
//        insert() adds stock to existing node if duplicate is found (for Classics
//        with same title but same actor entry appearing twice in movie file).
//        retrieve() returns Movie* pointer for Borrow/Return stock management.
//        display() uses in-order traversal — left, root, right — giving sorted output.
// -------------------------------------------------------------------------------
#include "BSTree.h"

// ----------------------------- BSTree() ----------------------------------------
// Description: Default constructor. Initializes root to nullptr (empty tree).
// Preconditions: None.
// Postconditions: root = nullptr. Tree is empty.
// -------------------------------------------------------------------------------
BSTree::BSTree() : root(nullptr) {}

// ----------------------------- ~BSTree() ---------------------------------------
// Description: Destructor. Recursively deletes all nodes and their Movie objects.
// Preconditions: None.
// Postconditions: All NodeData and Movie objects deleted. No memory leaks.
// -------------------------------------------------------------------------------
BSTree::~BSTree() {
    destroyHelper(root);
}

// ----------------------------- destroyHelper() ---------------------------------
// Description: Recursively deletes all nodes post-order (left, right, root).
// Preconditions: None.
// Postconditions: All nodes and Movie objects under node are deleted.
// -------------------------------------------------------------------------------
void BSTree::destroyHelper(NodeData* node) {
    if (node == nullptr) return;
    destroyHelper(node->left);      // delete left subtree
    destroyHelper(node->right);     // delete right subtree
    delete node->movie;                  // delete Movie object
    delete node;                         // delete node itself
}

// ----------------------------- isEmpty() ---------------------------------------
// Description: Returns true if the tree has no nodes.
// Preconditions: None.
// Postconditions: Returns bool. Tree unchanged.
// -------------------------------------------------------------------------------
bool BSTree::isEmpty() const {
    return root == nullptr;
}

// ----------------------------- insert() ----------------------------------------
// Description: Inserts a Movie into the BSTree in sorted position.
//              If an equal movie already exists (operator==), adds stock instead
//              of creating a duplicate node. Used for Classic movies with same
//              actor entry appearing multiple times in movie file.
// Preconditions: movie is not nullptr.
// Postconditions: Movie inserted as new node, or stock added to existing node.
// -------------------------------------------------------------------------------
void BSTree::insert(Movie* movie) {
    if (movie == nullptr) return;
    insertHelper(root, movie);
}

// ----------------------------- insertHelper() ----------------------------------
// Description: Recursive helper for insert(). Traverses tree using operator<
//              to find correct position. Adds stock if duplicate found.
// Preconditions: movie is not nullptr.
// Postconditions: Movie inserted at correct position or stock updated.
// -------------------------------------------------------------------------------
void BSTree::insertHelper(NodeData*& node, Movie* movie) {
    if (node == nullptr) {
        node = new NodeData(movie);     // empty spot found, insert here
        return;
    }
    if (*movie == *node->movie) {
        // duplicate found — add stock instead of inserting new node
        for (int i = 0; i < movie->getStock(); i++) {
            node->movie->increaseStock();
        }
        delete movie;                       // delete the duplicate movie object
        return;
    }
    if (*movie < *node->movie) {
        insertHelper(node->left, movie);    // go left if smaller
    } else {
        insertHelper(node->right, movie);   // go right if larger
    }
}

// ----------------------------- retrieve() --------------------------------------
// Description: Finds and returns a Movie* matching the target Movie object.
//              Used by Business to find the correct movie for Borrow/Return.
//              Target is a temporary Movie object with just enough fields set
//              to match via operator==.
// Preconditions: None.
// Postconditions: Returns Movie* if found, nullptr if not found. Tree unchanged.
// -------------------------------------------------------------------------------
Movie* BSTree::retrieve(const Movie& target) const {
    return retrieveHelper(root, target);
}

// ----------------------------- retrieveHelper() --------------------------------
// Description: Recursive helper for retrieve(). Uses operator< to navigate
//              the tree and operator== to confirm match.
// Preconditions: None.
// Postconditions: Returns Movie* if found, nullptr if not. Tree unchanged.
// -------------------------------------------------------------------------------
Movie* BSTree::retrieveHelper(NodeData* node, const Movie& target) const {
    if (node == nullptr) return nullptr;    // not found
    if (target == *node->movie) {
        return node->movie;                 // found — return pointer
    }
    if (target < *node->movie) {
        return retrieveHelper(node->left, target);  // search left
    } else {
        return retrieveHelper(node->right, target); // search right
    }
}

// ----------------------------- display() ---------------------------------------
// Description: Prints all movies in sorted order using in-order traversal.
//              Called by Inventory::doTrans() for each of the 3 genre trees.
// Preconditions: None.
// Postconditions: All movies printed to cout in sorted order. Tree unchanged.
// -------------------------------------------------------------------------------
void BSTree::display() const {
    displayHelper(root);
}

// ----------------------------- displayHelper() ---------------------------------
// Description: Recursive in-order traversal helper (left, root, right).
//              Calls each Movie's display() method for genre-specific formatting.
// Preconditions: None.
// Postconditions: Movies printed in sorted order. Tree unchanged.
// -------------------------------------------------------------------------------
void BSTree::displayHelper(NodeData* node) const {
    if (node == nullptr) return;
    displayHelper(node->left);       // print left subtree first
    node->movie->display();               // print this movie
    displayHelper(node->right);     // print right subtree last
}