//
// Created by andrei-cristea on 4/5/25.
//

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>



class Movie {

private:

    static int id3;
    int movieID;
    std::string title;
    int year_of_release;
    int duration; //in minutes ,I have to change
    float rating;
    static int movieCount;

public:
    //initializer constructor
    Movie(const std::string& title, int year, int duration, float rating);

    //default constructor
    Movie();

    //overloaded constructor
    Movie(std::string title, int year);

    //copy constructor
    Movie(const Movie& movie);

    //operator= for copy
    Movie& operator=(const Movie& movie);

    //operator>> for output (friend fnct)
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);

    //operator<< for input (friend fnct)
    friend std::istream& operator>>(std::istream& is, Movie& movie);

    //another overloaded operator as a member function(method)
    //concatenates the titles of two movies to and makes the average rating
    Movie operator+(const Movie& movie) const;

    //destructor virtual (because this class is a superclass)
    virtual ~Movie();

    void showMovieInfo() const;

    //getter for the title
    std::string getTitle() const;

    //getter for the id
    int getmovieID() const;

    //getter for the movieCount
    static int getMovieCount(){return movieCount;}

    bool operator==(const Movie &movie1) const;


    static void printStatistics();



};



#endif //MOVIE_H