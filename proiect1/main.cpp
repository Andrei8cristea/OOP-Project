//Ticket Reservation System for Cinema
#include <string>
#include <vector>
#include <iostream>

//-------------GLOBAL VARIABLES---------------------------

static int id = 0;

//-------------CLASSES------------------------------------
class Movie {

protected:
    std::string title;
    int year_of_release;
    int duration;
    float rating;

public:
    //constructor de initializare
    Movie(const std::string& title, int year, int duration, int rating);
    void showMovieInfo() const;

};

Movie::Movie(const std::string& title, int year, int duration, int rating)
        : title(title), year_of_release(year), duration(duration), rating(rating) {}

void Movie::showMovieInfo() const {
    std::cout << title << std::endl << year_of_release <<std::endl << duration <<std::endl<< rating<<std::endl<<std::endl;
}


class MovieDate :public  Movie {
private:
    int movie_id;
    int date;
    int month;
    int year;
    int hour;
    int minute;

public:
    MovieDate(const std::string& title, int year_of_release, int duration, int rating,
              int date, int month, int year, int hour, int minute);
    void showMovieDate() const;

};

MovieDate::MovieDate(const std::string &title, int year_of_release, int duration, int rating, int date, int month, int year, int hour, int minute)
    :Movie(title, year_of_release, duration, rating),movie_id(id++),date(date), month(month), year(year), hour(hour), minute(minute) {}

void MovieDate::showMovieDate() const {
    std::cout << "ID: " << movie_id << " | Date: " << date << "/" << month << "/" << year
              << " | Time: " << hour << ":" << minute << std::endl;
}



class Room {

    int room_id;
    int rows_number;
    int colums_number;
    std::vector<std::vector<char>> board;

public:

};

class Reservation {
    std::string name;
    Movie movie;


public:

};

//------------------------MAIN--------------------------------

int main() {

    ///initializing movies
    Movie amovie("Oppenheimer", 2023, 3, 8.3);
    Movie bmovie("Interstellar", 2014, 2, 8.7);
    Movie cmovie("Batman", 2022, 3, 7.8);

    amovie.showMovieInfo();
    bmovie.showMovieInfo();
    cmovie.showMovieInfo();


    ///initializing movie dates
    MovieDate amovieDate("Oppenheimer", 2023, 3, 8.3, 12, 4, 2025, 18, 30);
    MovieDate bmovieDate("Interstellar", 2014, 2, 8.7, 15, 5, 2025, 20, 00);
    MovieDate cmovieDate("Batman", 2022, 3, 7.8, 20, 6, 2025, 22, 15);

    amovieDate.showMovieDate();
    bmovieDate.showMovieDate();
    cmovieDate.showMovieDate();


    return 0;
}