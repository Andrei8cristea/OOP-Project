//
// Created by andrei-cristea on 4/5/25.
//

#ifndef MOVIEDATE_H
#define MOVIEDATE_H

static int id = 0;

class MovieDate :public  Movie {

private:
    int moviedate_id;
    int room_id;
    float price;
    int date;
    int month;
    int year;
    int hour;
    int minute;

public:

    //default constructor
    MovieDate() = default;

    //initialization constructor from 0
    MovieDate(const std::string& title, int year_of_release, int duration, int rating,
              float price, int date, int month, int year, int hour, int minute);

    //initialization constructor from basemovie
    MovieDate(const Movie* baseMovie,int room_id, float price, int date, int month, int year, int hour, int minute)
    :Movie(*baseMovie),
    moviedate_id(id++),room_id(room_id), price(price),date(date),month(month),
    year(year), hour(hour), minute(minute){};

    //overridden copy constructor
    MovieDate(const MovieDate& another);

    //overridden operator=
    MovieDate& operator=(const MovieDate& movie);

    //upcast
    void showMovieDate() const;

    //static_cast
    void adjustPrice(float discount);

    //destructor (non-virtual because this class doesn't have any subclasses)
    ~MovieDate();

};



#endif //MOVIEDATE_H
