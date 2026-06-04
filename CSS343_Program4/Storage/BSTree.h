#ifndef BSTREE_H
#define BSTREE_H
// --------------------------------- BSTree.h ------------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for BSTree class - binary search tree storing Movie
//          objects in sorted order. Used as base class for ClassicBSTree.
// -------------------------------------------------------------------------------
// Notes: root and NodeData are protected so ClassicBSTree can access them.
//        Sorting determined entirely by Movie subclass operator< and operator==.
//        insert() adds stock to existing node if duplicate found.
//        retrieve() finds Movie* by passing a target Movie to compare.
//        display() uses in-order traversal for sorted output.
//        All Movie objects owned by BSTree, deleted in destructor.
// -------------------------------------------------------------------------------
#include "../Movies/Movie.h"

// -----------------------------------------------------------------------
// NodeData: wrapper node holding Movie pointer and left/right child links
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
    virtual ~BSTree();  // virtual destructor for safe inheritance

    void insert(Movie* movie);                      // insert movie, adds stock if duplicate
    Movie* retrieve(const Movie& target) const;     // find movie matching target
    void display() const;                           // print all movies sorted in-order
    bool isEmpty() const;                           // returns true if tree is empty

protected:
    NodeData* root;     // root of tree — protected so ClassicBSTree can access

private:
    // private recursive helpers
    void insertHelper(NodeData*& node, Movie* movie);
    Movie* retrieveHelper(NodeData* node, const Movie& target) const;
    void displayHelper(NodeData* node) const;
    void destroyHelper(NodeData* node);
};
#endif