//
// Created by andrei-cristea on 4/5/25.
//


#include "include/Movie.h"
#include "include/MovieDate.h"
#include <string>
#include <iostream>
#include <list>


MovieDate::MovieDate(const std::string &title, int year_of_release, int duration, int rating, float price,int date, int month, int year, int hour, int minute)
    :Movie(title, year_of_release, duration, rating),moviedate_id(id++),price(price),date(date), month(month), year(year), hour(hour), minute(minute) {}

MovieDate::MovieDate(const MovieDate &another)
    :Movie(another), //call for copy constructor from Movie class
    moviedate_id (another.moviedate_id),
    room_id(another.room_id),
    price (another.price),
    date (another.date),
    month (another.month),
    year (another.year),
    hour (another.hour),
    minute (another.minute) {
    //std::cout << "Copy constructor for MovieDate called :)" << std::endl;

}

MovieDate& MovieDate::operator=(const MovieDate &movie)  {
    if (this != &movie) {
        Movie::operator=(movie); //assigning the superclass part
        room_id = movie.room_id;
        moviedate_id = movie.moviedate_id;
        price = movie.price;
        date = movie.date;
        month = movie.month;
        year = movie.year;
        hour = movie.hour;
        minute = movie.minute;
    }
    return *this;
}

void MovieDate::showMovieDate() const {
    std::cout <<*this; //I am using the <<(overridden) operator from the superclass
    //std::cout << moviedate_id << std::endl;
    std::cout << "+----------------------------------------+\n";
    std::cout << "|             SHOWTIME INFO              |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << "🆔MOVIEDATE ID   : "<<moviedate_id<<std::endl;
    std::cout << " 💰 PRICE        : $" << price << "\n";
    std::cout << " 🏠ROOM NUMBER   : " << room_id << "\n";
    std::cout << " 📅 DATE         : " << (date < 10 ? "0" : "") << date << "/"
             << (month < 10 ? "0" : "") << month << "/" << year << "\n";
    std::cout << " ⏰ TIME         : " << (hour < 10 ? "0" : "") << hour << ":"
              << (minute < 10 ? "0" : "") << minute << "\n";

    std::cout << "+----------------------------------------+\n";
    std::cout << "|           ENJOY YOUR MOVIE!            |\n";
    std::cout << "+----------------------------------------+\n\n\n";
}

void MovieDate::adjustPrice(float discount) {

    price = static_cast<int>(price * discount);
}

// void MovieDate::adjustGlobalPrice(std::list<MovieDate*>& movieDates, const std::string& movieTitle, float discountFactor) {
//     for (auto mdPtr : movieDates) {
//         if (mdPtr->getTitle() == movieTitle) {
//             mdPtr->adjustPrice(discountFactor);
//         }
//     }
//     std::cout << "Global price adjusted for movie: " << movieTitle << std::endl;
// }

MovieDate::~MovieDate() {
    //std::cout<<"MovieDate destructor called :)"<<std::endl;
}

void displayMovieFullInfo(Movie* moviePtr) {
    std::cout<<"Basic Movie Info:"<<std::endl<<*moviePtr<<std::endl;
    //here I try the downcasting
    MovieDate* movieDatePtr = dynamic_cast<MovieDate*>(moviePtr);
    //if moviePtr is  MovieDate I will output the essential info
    //else if it was just a Movie -> unlucky
    if (movieDatePtr != nullptr) {
        std::cout<<"Downcast succeeded"<<std::endl;
        movieDatePtr->showMovieDate();
    }
    else {
        std::cout<<"Not a MovieDate object :("<<std::endl;
    }
}

int MovieDate::getRoomId() const {
    return room_id;
}

