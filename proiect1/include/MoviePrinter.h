//
// Created by andrei-cristea on 4/26/25.
//

#ifndef MOVIEPRINTER_H
#define MOVIEPRINTER_H

#include <memory>
#include <iostream>
#include "Movie.h"

class IMoviePrinter {
public:
    virtual ~IMoviePrinter() = default;
    virtual void printMovie() const = 0;
    virtual std::string getTags() const { return "";}
    virtual const Movie& getMovie() const = 0;

};

class MoviePrinter : public IMoviePrinter {
protected:
    const Movie& movie;
public:
    MoviePrinter(const Movie& movie) : movie(movie) {}

    void printMovie() const override {
        std::cout << getTags() << movie << std::endl;
    }
    std::string getTags() const override {
        return "";
    }

    const Movie& getMovie() const override {
        return movie;
    }
};

class MoviePrinterDecorator: public IMoviePrinter {
protected:
    std::unique_ptr<IMoviePrinter> moviePrinter;
public:
    MoviePrinterDecorator(std::unique_ptr<IMoviePrinter> mP): moviePrinter(std::move(mP)) {}

    void printMovie() const override {
        std::cout << getTags();
        std::cout << moviePrinter->getMovie() << std::endl;
    }
    std::string getTags() const override {
        return moviePrinter->getTags();
    }

    const Movie& getMovie() const override {
        return moviePrinter->getMovie();
    }
};

class NewReleaseDecorator: public MoviePrinterDecorator {
public:
    using MoviePrinterDecorator::MoviePrinterDecorator;

    // void printMovie() const override {
    //     std::cout << "                        🆕 NEW RELEASE 🆕 \n";
    //
    //     moviePrinter->printMovie();
    // }

    std::string getTags() const override {
        return " _________________\n/🆕 NEW RELEASE 🆕\\\n"+ moviePrinter->getTags();;
    }

};

class TopRatedDecorator: public MoviePrinterDecorator {
    public:
    using MoviePrinterDecorator::MoviePrinterDecorator;

    // void printMovie() const override {
    //     std::cout << "                        🌟 TOP RATED 🌟 \n";
    //
    //     moviePrinter->printMovie();
    // }

    std::string getTags() const override {
        return "                         _______________\n                        /🌟 TOP RATED 🌟\\\n"+ moviePrinter->getTags();
    }

};



#endif //MOVIEPRINTER_H
