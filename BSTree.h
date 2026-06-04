#ifndef BSTREE_H
#define BSTREE_H
// --------------------------------- bstree.h ------------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for BSTree class - a binary search tree that stores
//          Movie objects in sorted order. Used to store and display all 3 genres.
//          Business owns 3 separate BSTree objects, one per genre.
// -------------------------------------------------------------------------------
// Notes: Sorting order is determined by each Movie subclass's operator< and
//        operator== — BSTree does not need to know the genre rules itself.
//        insert() adds a new Movie node or increases stock if movie already exists.
//        display() uses in-order traversal so output is always sorted correctly.
//        retrieve() finds a Movie* by passing a target Movie object to compare.
//        All Movie objects stored are owned by BSTree and deleted in destructor.
// -------------------------------------------------------------------------------
#include "Movie.h"

// -----------------------------------------------------------------------
// NodeData: wrapper node that holds a Movie pointer and left/right links
// -----------------------------------------------------------------------
struct NodeData {
    Movie* movie;       // pointer to movie stored in this node
    NodeData* left;     // left child
    NodeData* right;    // right child

    NodeData(Movie* m) : movie(m), left(nullptr), right(nullptr) {}
};

class BSTree {
public:
    BSTree();           // constructor
    ~BSTree();          // destructor

    void insert(Movie* movie);                    // insert movie into tree, adds stock if duplicate
    Movie* retrieve(const Movie& target) const;   // find and return movie matching target
    void display() const;                         // print all movies in sorted order (in-order)
    bool isEmpty() const;                         // returns true if tree is empty

private:
    NodeData* root;     // root of the tree

    // private helper methods
    void insertHelper(NodeData*& node, Movie* movie);                  // recursive insert helper
    Movie* retrieveHelper(NodeData* node, const Movie& target) const;  // recursive retrieve helper
    void displayHelper(NodeData* node) const;                          // recursive in-order display
    void destroyHelper(NodeData* node);                                // recursive destructor helper
};
#endif