//

#ifndef CUSTOMERACCOUNTS_H
#define CUSTOMERACCOUNTS_H

#include <iostream>
#include "CustomerList.h"
using namespace std;

//
class CustomerAccounts {

    public:
        //
        CustomerAccounts();
        ~CustomerAccounts();
        int addAccount(int customerID, string firstName, string lastName);
        int removeAccount(int customerID);
        bool containsAccount(int customerID);
        void print();


    private:
        CustomerList* hashTable;                             //the hash table (as a pointer)
        int possibleArraySizes[11] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853}; //possible sizes for array (prime numbers)
        int arraySize;      //the current size of the hash table
        int arraySizeIndex; //index of the size being used.
        int customerCount;                          //number of accounts stored in hash table

        int findInsertionPoint(int customerID, int collisions);     //calculates the hash key depending on the number of collisions (quad probing)
        int shrinkArray();                  //
        int growArray();                        //
        int insert(int customerID, string firstName, string lastName);
        int findIndexOfAccount(int customerID);
        

};


#endif
