#ifndef CLASSICBSTREE_H
#define CLASSICBSTREE_H
// --------------------------------- ClassicBSTree.h -----------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for ClassicBSTree - a specialized BSTree subclass for
//          Classic genre movies. Overrides insert() to handle the unique case
//          where the same Classic title can have multiple actor entries, each
//          with their own stock tracked separately.
// -------------------------------------------------------------------------------
// Notes: Classic movies are uniquely identified by month + year + actor.
//        Same title with different actor = different node in the tree.
//        Same title + same actor appearing twice = stock added to existing node.
//        getSuggestion() searches tree for alternative actor when stock is 0.
//        Inherits display() and retrieve() from BSTree — no changes needed.
// -------------------------------------------------------------------------------
#include "BSTree.h"
#include "classic.h"

class ClassicBSTree : public BSTree {
public:
    ClassicBSTree();            // constructor
    virtual ~ClassicBSTree();   // destructor
    // searches tree for alternative actor version of same title with stock > 0
    Movie* getSuggestion(const string& title) const;

private:
    // recursive helper — traverses tree looking for same title, stock > 0
    Movie* findAlternative(NodeData* node, const string& title) const;
};
#endif