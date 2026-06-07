// --------------------------------- CustomerAccounts.h -------------------------------------
// Isha Rajpure CSS343
// Creation Date: May 30, 2026
// Date of Last Modification: June 2, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Customer Accounts class - hash table that stores customer 
// information and transaction history
// -------------------------------------------------------------------------------
// Notes: Can only store up to 12853 accounts.
// -------------------------------------------------------------------------------

#ifndef CUSTOMERACCOUNTS_H
#define CUSTOMERACCOUNTS_H

#include <iostream>
#include "CustomerList.h"
using namespace std;

//
class CustomerAccounts {

    public:
        //
        CustomerAccounts();                                                 //constructor
        ~CustomerAccounts();                                                //destructor
        int addAccount(int customerID, string firstName, string lastName);  //add customer account to table (after considering load factor)
        int removeAccount(int customerID);                                  //remove an account from the table
        bool containsAccount(int customerID);                               //search whether an account is stored in the table
        
        //insert a transaction entry for a customer
        int addTransForCustomer(int customerID, string transType, string movieType, string director, string title, int year);
        //check if a customer borrowed a movie
        bool checkBorrowedMovie(int customerID, string movieType, string director, string title, int year);


        void print();                                                       //print hash table (including empty slots)
        void printCustomers();


    private:
        CustomerList* hashTable;                                                                //the hash table (as a pointer)
        int possibleArraySizes[11] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853};  //possible sizes for array (prime numbers)
        int arraySize;                                                                          //the current size of the hash table
        int arraySizeIndex;                                                                     //index of the size being used.
        int customerCount;                                                                      //number of accounts stored in hash table

        int findInsertionPoint(int customerID, int collisions);     //calculates the hash key depending on the number of collisions (quad probing)
        int shrinkArray();                                                                      //shrinks table space if excessive number of spots
        int growArray();                                                                        //increases table space if not enough space
        int insert(int customerID, string firstName, string lastName);                          //creates customer and adds to hash table
        int findIndexOfAccount(int customerID);                                                 //find index of customer in hash table
        

};


#endif
