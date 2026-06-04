// --------------------------------- ClassicBSTree.cpp ---------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Implementation file for ClassicBSTree. Handles the unique behavior
//          of Classic movies where same title can have multiple actor entries.
// -------------------------------------------------------------------------------
// Notes: insert() and retrieve() inherited from BSTree work correctly for
//        Classics because Classic::operator== checks month + year + actor,
//        meaning same title different actor will always be a separate node.
//        getSuggestion() traverses tree to find alternative actor version
//        when the requested Classic is out of stock.
// -------------------------------------------------------------------------------
#include "ClassicBSTree.h"

// ----------------------------- ClassicBSTree() ---------------------------------
// Description: Default constructor. Calls BSTree base constructor.
// Preconditions: None.
// Postconditions: Empty ClassicBSTree ready to store Classic movies.
// -------------------------------------------------------------------------------
ClassicBSTree::ClassicBSTree() : BSTree() {}

// ----------------------------- ~ClassicBSTree() --------------------------------
// Description: Destructor. BSTree destructor handles all node cleanup.
// Preconditions: None.
// Postconditions: ClassicBSTree destroyed. All nodes and Movies deleted.
// -------------------------------------------------------------------------------
ClassicBSTree::~ClassicBSTree() {}

// ----------------------------- getSuggestion() ---------------------------------
// Description: Searches the Classic BSTree for an alternative actor version
//              of the same title when the requested version is out of stock.
//              Used by Borrow::doTrans() to suggest alternatives to customer.
// Preconditions: title is the title of the out-of-stock Classic movie.
// Postconditions: Returns Movie* of alternative with stock > 0, or nullptr.
//                 Tree unchanged.
// -------------------------------------------------------------------------------
Movie* ClassicBSTree::getSuggestion(const string& title) const {
    return findAlternative(root, title);
}

// ----------------------------- findAlternative() -------------------------------
// Description: Recursive helper for getSuggestion(). Traverses entire tree
//              looking for a Classic with same title but stock > 0.
// Preconditions: None.
// Postconditions: Returns Movie* if alternative found, nullptr otherwise.
// -------------------------------------------------------------------------------
Movie* ClassicBSTree::findAlternative(NodeData* node, const string& title) const {
    if (node == nullptr) return nullptr;

    Classic* c = static_cast<Classic*>(node->movie);
    // check if this node has same title and stock available
    if (c->getTitle() == title && c->getStock() > 0) {
        return node->movie;
    }

    // search both subtrees since we need to check all entries
    Movie* left  = findAlternative(node->left, title);
    if (left != nullptr) return left;   // found in left subtree

    Movie* right = findAlternative(node->right, title);
    return right;                       // found in right subtree or nullptr
}