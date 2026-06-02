//

#include "CustomerAccounts.h"
#include "CustomerList.h"

CustomerAccounts::CustomerAccounts() {
    arraySize = possibleArraySizes[0];
    arraySizeIndex = 0;
    hashTable = new CustomerList[arraySize];
    customerCount = 0;
}

CustomerAccounts::~CustomerAccounts() {
    delete[] hashTable;
}

int CustomerAccounts::addAccount(int customerID, string firstName, string lastName) {
    
    try {

        //if not enough space, resize hashtable
        double newLoadFactor = static_cast<double>(customerCount + 1) / arraySize;     //calculate load factor if new item were added
        if (newLoadFactor >= 0.5) {     //if we have reached 50% capacity, increase array size
            growArray();
        }
        if (newLoadFactor >= 1) {
            throw "not enough space in array to insert.";
        }

        //add the customer to hash table
        insert(customerID, firstName, lastName);

        return 0;

    }

    catch (const char* msg) {
        cout << "Error with adding account: " << msg << endl;
        return -1;
    }
}

//HELPER - GROW ARRAY --> need to implement
int CustomerAccounts::growArray() {


    //if already at max size possible (last element in possible array sizes), return error code.
    if (arraySizeIndex == sizeof(possibleArraySizes)/sizeof(possibleArraySizes[0])-1) {
        cout << "table is almost full." << endl;
    }

    //change array size and create a new array with new size and save old size
    int oldArraySize = arraySize;                       //save old size of the array in variable
    arraySizeIndex++;                                   //increase counter for index of array size
    arraySize = possibleArraySizes[arraySizeIndex];     //change the array size (to next size in the possible sizes)
    CustomerList* oldTable = hashTable;                 //save the original hash table in a variable
    hashTable = new CustomerList[arraySize];            //create a new hashtable with the new size and save in hashTable var
    customerCount = 0;                                  //reset customer count for now. it will go back up during insertion.

    //insert all slots that are occupied into new hashtable.
    for (int i = 0; i < oldArraySize; i++) {
        if (oldTable[i].getState() == State::OCCUPIED) {
            insert(oldTable[i].getCustomerID(), oldTable[i].getFirstName(), oldTable[i].getLastName());
        }
    }

    //delete the old table
    delete[] oldTable;
    return 0;

}

int CustomerAccounts::insert(int customerID, string firstName, string lastName) {

    
    bool inserted = false;              //bool variable to check whether the element has been inserted or not
    int collisions = 0;                 //keep track of how many collisions are happening


    //while the element has not been inserted...
    while (inserted == false) {
        
        int hashKey = findInsertionPoint(customerID, collisions);       //find hash key depending on number of collisions


        //if occupied spot and customerID already exists in table, throw error for repeated use of ID
        if (hashTable[hashKey].getState() == State::OCCUPIED) {
            if (customerID == hashTable[hashKey].getCustomerID()) {     
                throw "account creation error - repeated customer ID is being used.";
            }
        }

        //if spot is empty, then insert new customer account there
        if (hashTable[hashKey].getState() == State::EMPTY || hashTable[hashKey].getState() == State::DELETED) {
            hashTable[hashKey] = CustomerList(customerID, firstName, lastName);
            inserted = true;
            //cout << "added acc - " << customerID << endl;
            //int currentState = static_cast<int>(hashTable[hashKey].getState());
            customerCount++;                                                        //increase customer count
            //cout << "printing state: " << to_string(currentState) << endl;
        }

        //if spot state is either occupied or deleted, then treat like a collision.
        else {
            collisions++;
        }

    }

    return 0;
}

int CustomerAccounts::findInsertionPoint(int customerID, int collisions) {
    int hashKey = customerID % arraySize;
    hashKey += collisions*collisions;
    hashKey = hashKey % arraySize;
    return hashKey;
}

int CustomerAccounts::removeAccount(int customerID) {

    try {

        //figure out if the element is even in the array
        int index = findIndexOfAccount(customerID);
        if (index == -1) {
            throw "customer account not in table.";
        }
        else {
            hashTable[index].changeState(State::DELETED);
            customerCount--;
        }
        
        //if too much space, resize hashtable
        double newLoadFactor = static_cast<double>(customerCount) / arraySize;     //calculate load factor if new item were added
        if (newLoadFactor <= 0.125) {     //if we have reached 50% capacity, increase array size
            shrinkArray();
        }

    }

    catch (const char* msg) {
        cout << "Error with deleting account: " << msg << endl;
        return -1;
    }

    return 0;
}

int CustomerAccounts::findIndexOfAccount(int customerID) {

    bool found = false;                 //bool variable to check whether the element has been found or not
    int collisions = 0;                 //keep track of how many collisions are happening

    //while the element has not been inserted...
    while (found == false) {
        
        int hashKey = findInsertionPoint(customerID, collisions);       //find hash key depending on number of collisions

        //if occupied spot matches customerID then return the index
        if (hashTable[hashKey].getState() == State::OCCUPIED) {
            if (customerID == hashTable[hashKey].getCustomerID()) {     
                found = true;
                return hashKey;
            }
        }
        else if (hashTable[hashKey].getState() == State::EMPTY) {
            return -1;
        }

        collisions++;
    
    }

    return 0;
}

int CustomerAccounts::shrinkArray() {
    
    if (arraySizeIndex == 0) {
        return 0;
    }

    //change array size and create a new array with new size and save old size
    int oldArraySize = arraySize;                       //save old size of the array in variable
    arraySizeIndex--;                                   //increase counter for index of array size
    arraySize = possibleArraySizes[arraySizeIndex];     //change the array size (to next size in the possible sizes)
    CustomerList* oldTable = hashTable;                 //save the original hash table in a variable
    hashTable = new CustomerList[arraySize];            //create a new hashtable with the new size and save in hashTable var
    customerCount = 0;                                  //reset customer count for now. it will go back up during insertion.

    //insert all slots that are occupied into new hashtable.
    for (int i = 0; i < oldArraySize; i++) {
        if (oldTable[i].getState() == State::OCCUPIED) {
            insert(oldTable[i].getCustomerID(), oldTable[i].getFirstName(), oldTable[i].getLastName());
        }
    }

    //delete the old table
    delete[] oldTable;
    return 0;

}

bool CustomerAccounts::containsAccount(int customerID) {
    if (findIndexOfAccount(customerID) != -1) {             //method returns -1 if ID is not in the hash table
        return true;
    }
    return false;
}

void CustomerAccounts::print() {

    for (int i = 0; i < arraySize; i++) {
        cout << "Index " << i << ": ";
        hashTable[i].print();
    }
    cout << endl;

}