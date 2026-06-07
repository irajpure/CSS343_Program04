#include "Business.h"
#include "Customers/CustomerAccounts.h"
#include "Customers/CustomerList.h"
#include "Storage/MovieStorage.h"
#include "Movies/MovieFac.h"
#include "Transactions/TransFac.h"

#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


int Business::processCustomerData(ifstream& file) {

    try {

        string line;
        while (getline(file, line)) {   //while there are still lines to be read...

            vector<string> tokens;      //vector for tokens. 
            istringstream iss(line);    //
            string token;               //variable in which we will extract tokens

            while (iss >> token) {
                tokens.push_back(token); //add the token to the vector
            }

            int customerID = stoi(tokens[0]);
            string firstName = tokens[1];
            string lastName = tokens[2];

            accounts.addAccount(customerID, firstName, lastName);

        }

    }

    catch (const char* msg) {
        cout << "Customer Data Population failed: " << msg << endl;
        return -1;
    }

    return 0;

}

int Business::processMoviesData(ifstream& file) {
    
    try {

        MovieFac factory;
        
        //use "line" to extract entire lines of the file
        string line;
        while (getline(file, line)) {           //while there are still lines to be extracted

            char genre = line[0];               //extract 1st character

            vector<string> tokens;
            istringstream iss(line.substr(2));  //iss (new line) contains everything after the genre

            string token;

            while (getline(iss, token, ',')) {  //turn new line into a string vector, with commas as delimiter

                if (!token.empty() && token[0] == ' ') {    //removing white space in front of the variable
                    token.erase(0, 1);
                }

                tokens.push_back(token);                    //then adding token to vector
            }

            Movie* m = factory.createMovie(genre, tokens);
            if (m != nullptr) {
                moviesCollection.insertMovie(genre, m);
            }

        }

    }

    catch (const char* msg) {
        cout << "Customer Data Population failed: " << msg << endl;
        return -1;
    }

    return 0;
}

int Business::processTransactionData(ifstream& file) {
    
    try {

        string line;
        while (getline(file, line)) {

            //extract transaction type & create transaction accordingly
            //ex: B 1234 D F Pirates, 2003
            //extracting the first character
            char code = line[0];
            TransFac transFactory;
            Trans* transaction = transFactory.createTrans(code);
            vector<string> tokens; 

            if (code == 'H' || code == 'B' || code == 'R') {
                //remove the transType character from the beginning
                //ex: 1234 D F Pirates, 2003
                line = line.substr(2);
                //if history, then the rest is only the id. so we are good. to send in vector.
                if (code == 'H') {
                    tokens.push_back(line);
                    transaction->setData(tokens);
                }
            }

            string movieType;

            if (code == 'B' || code == 'R') {
                //extract the customer id, until you get to the space
                //ex: B 1234 D F Pirates, 2003
                //extracting 1234
                string idString;
                while (line[0] != ' ') {
                    idString += line[0];
                    line = line.substr(1);
                }
                tokens.push_back(idString);

                //remove the extra space now
                //ex: D F Pirates, 2003
                line = line.substr(1);

                //extract mediaType
                //ex: D F Pirates, 2003
                //extracting D
                string mediaType;
                mediaType += line[0];
                tokens.push_back(mediaType);

                //remove the mediaType character from the beginning
                //ex: 1234 D F Pirates, 2003
                line = line.substr(2);

                //extract movieType
                //ex. F Pirates, 2003
                //extracting F
                movieType += line[0];
                tokens.push_back(movieType);
                line = line.substr(2);
            }

            //if movie type is classic
            if (movieType == "C") {
                
                //get the release month
                string releaseMonth;
                releaseMonth += line[0];
                tokens.push_back(releaseMonth);
                line = line.substr(2);

                //get the release year
                string releaseYear;
                while (line[0] != ' ') {
                    releaseYear += line[0];
                    line = line.substr(1);
                }
                tokens.push_back(releaseYear);
                line = line.substr(1);

                //remaining line is the major actor. add to vector as well
                tokens.push_back(line);

            }
            else if (movieType == "D") {
                
            }

        }


    }

    catch(const char* msg) {

    }
    
    return 0;
}



void Business::displayCustomers() {
    accounts.print();
}

void Business::displayAllMovies() {
    moviesCollection.displayAll();
}