#ifndef TRANSFAC_H
#define TRANSFAC_H
// --------------------------------- TransFac.h ----------------------------------
// Abigail Galung CSS343
// Creation Date: June 3, 2026
// Date of Last Modification: June 3, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for TransFac class - factory class responsible for
//          creating the correct Trans subclass object based on the action
//          code read from data4commands.txt.
// -------------------------------------------------------------------------------
// Notes: Valid action codes are 'B' (Borrow), 'R' (Return),
//        'I' (Inventory), 'H' (History).
//        Invalid codes print an error message and return nullptr.
//        Business::processTrans() checks for nullptr before calling setData/doTrans.
//        Caller (Business) is responsible for deleting the returned pointer.
// -------------------------------------------------------------------------------
#include "Trans.h"
#include "return.h"
#include "borrow.h"
#include "inventory.h"
#include "history.h"

class TransFac {
public:
    // ----------------------------- createTrans() -------------------------------
    // Description: Reads action code and returns pointer to correct Trans subclass.
    //              Returns nullptr and prints error if action code is invalid.
    // Preconditions: code is a single character read from command file.
    // Postconditions: Returns new Trans subclass pointer or nullptr if invalid.
    // ---------------------------------------------------------------------------  
    Trans* createTrans(char code) {
        if (code == 'R') return new Return();
        else if (code == 'B') return new Borrow();
        else if (code == 'I') return new Inventory();
        else if (code == 'H') return new History();
        else {
            cout << "ERROR: Invalid action code '" << code << "' — skipping command." << endl;
            return nullptr;
        }
    } 
};
#endif