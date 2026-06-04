#ifndef MOVIE_H
#define MOVIE_H
// --------------------------------- Movie.h -------------------------------------
// Abigail Galung CSS343
// Creation Date: May 27, 2026
// Date of Last Modification: May 27, 2026
// -------------------------------------------------------------------------------
// Purpose: Header file for Movie class - abstract base class for all movie types
//          (Comedy, Drama, Classic). Defines the common interface and shared data
//          members that every movie type must have.
// -------------------------------------------------------------------------------
// Notes: genre, stock, director, title, and year are shared across all subtypes.
//        operator< and setData are pure virtual — each subclass sorts differently
//        and reads different fields from the input file.
//        increaseStock/decreaseStock are called by Return and Borrow transactions.
// -------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Movie {
public:
    Movie();                // constructor
    virtual ~Movie();       // destructor

    //pure virtual methods, each subclass must implement these
    virtual bool operator <(const Movie& other) const = 0;  // for BSTree sorting
    virtual bool operator ==(const Movie& other) const = 0; //for movie lookup
    virtual void setData(ifstream& infile) = 0;             // reads from file
    virtual void display() const = 0;                       // prints movie info 

    //getters used by borrow/return for stock management
    int getStock() const;
    string getTitle() const;
    string getDirector() const;
    char getGenre() const;
    int getYear() const;

    //stock management
    void increaseStock();   // called on valid return
    void decreaseStock();   // called on valid borrow

protected:
    char genre;             // genre code: F for comedy, D for drama, C for classic
    int stock;              // number of copies available
    string director;        // director name
    string title;           // movie title
    int year;               // release year
};  
#endif