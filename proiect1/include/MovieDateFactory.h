//
// Created by andrei-cristea on 4/25/25.
//

#ifndef MOVIEDATEFACTORY_H
#define MOVIEDATEFACTORY_H

#include "MovieDate.h"
#include <memory>


class MovieDateFactory {
public:
    virtual ~MovieDateFactory()= default;

    virtual std::unique_ptr<MovieDate>
    createMovieDate(const Movie* baseMovie,
                    int roomId,
                    float price,
                    int day, int month, int year,
                    int hour, int minute) = 0;
};

class DefaultMovieDateFactory : public MovieDateFactory {
public:
    std::unique_ptr<MovieDate> createMovieDate(const Movie* baseMovie,
                                                int roomId,
                                                float price,
                                                int day, int month, int year,
                                                int hour, int minute) override{
        return std::make_unique<MovieDate>(baseMovie, roomId, price, day, month, year, hour, minute);
    };
};

#endif //MOVIEDATEFACTORY_H
