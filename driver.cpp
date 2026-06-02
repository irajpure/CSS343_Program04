#include "CustomerList.h"
#include "CustomerAccounts.h"
#include <iostream>

int main() {

    //creating customers & empty customers & seeing whether we can access their state.
    CustomerAccounts accountsList;
    accountsList.addAccount(1234, "John", "Smith");
    accountsList.print();
    cout << endl;

    accountsList.removeAccount(1234);
    accountsList.print();
    cout << endl;

    accountsList.addAccount(1234, "John", "Smith");
    accountsList.addAccount(1201, "Isha", "Smith");
    accountsList.addAccount(1202, "Veronica", "Jules");
    accountsList.addAccount(1191, "Chutki", "Cat");
    accountsList.addAccount(1180, "Soham", "Human");
    accountsList.print();
    cout << endl;
    accountsList.addAccount(1789, "Sabrina", "Carpenter");
    accountsList.print();

    accountsList.removeAccount(1202);
    accountsList.removeAccount(1201);
    accountsList.removeAccount(1234);
    accountsList.removeAccount(1191);
    accountsList.removeAccount(1180);
    accountsList.print();
    cout << endl;

    //accountsList.addAccount(1234, "John", "Smith");

    return 0;
}