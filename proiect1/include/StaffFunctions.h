//
// Created by andrei-cristea on 4/6/25.
//

#ifndef STAFFFUNCTIONS_H
#define STAFFFUNCTIONS_H


#include "include/Movie.h"
#include "include/Exceptions.h"
#include "include/MovieDate.h"
#include "include/TemplateClasses.h"


void staffAddMovie(Repository<Movie>& moviesRepo) {
    Movie movie;
    std::cout<<"Enter the details of the movie you want to add: \n";
    try {
        std::cin>>movie;
    }catch (const Exceptions& e) {
        throw e;
    }

    moviesRepo.addElement(movie);
    std::cout<<"Movie "<<movie.getTitle()<<" added succesfully"<<std::endl;
}


void staffAdjustPrice(Repository<MovieDate>& repo) {

    //i m searching now through the movieDates list
    //the same algorithm as in reserveSeat function

    std::string movieTitle;
    std::cout << "Please enter the movie you want to adjust the price for: ";
    std::getline(std::cin, movieTitle);

    const MovieDate* selectedDate = nullptr;
    for (auto& md : repo.getRepositoryDates()) {
        if (md.getTitle() == movieTitle) {
            selectedDate = &md;
            break;
        }
    }
    if (!selectedDate) {
        std::cout<<"No showtime for movie with the title: "<<movieTitle<<std::endl;
        return;
    }

    std::cout << "\n Available showtimes for the movie: "<<movieTitle<<std::endl;
    int index = 0;
    std::vector<MovieDate*> filteredDates;
    for (auto& md : repo.getRepositoryDates()) {
        if (md.getTitle() == movieTitle) {
            std::cout<<"["<<index<<"]"<<std::endl;
            md.showMovieDate();
            std::cout<<std::endl;
            filteredDates.push_back(&md);
            index++;
        }
    }
    if (!filteredDates.size()) {
        std::cout<<"No runtimes available for "<<movieTitle<<"."<<std::endl;
        return;
    }

    int selectedIndex;
    std::cout<<"Please enter the index of the showtime you want to adjust the price for: ";
    std::cin >> selectedIndex;
    while (selectedIndex < 0 || selectedIndex >= static_cast<int>(filteredDates.size())) {
        std::cout<<"Invalid showtime selection. Please enter a valid index: ";
        std::cin >> selectedIndex;
    }

    float discount;
    std::cout << "Enter discount factor: ";
    std::cin >> discount;
    std::cout<<std::endl;

   filteredDates[selectedIndex]->adjustPrice(discount);
    //selectedderef.adjustGlobalPrice(repo, movieTitle,discount);
    std::cout<<"Modified showtime:"<<std::endl;
    //selectedderef.showMovieDate();
    filteredDates[selectedIndex]->showMovieDate();
    std::cout<<std::endl;

}
Movie findMovieInRepository(Repository<Movie>& repo, std::string title) {
    for (const auto& movie :repo.getRepositoryDates()) {
        if (movie.getTitle() == title) {
            return movie;
        }
    }
    throw Exceptions("Movie with title \""+ title +"\" not found");
}



void staffCreateSeries(Repository<Movie>& moviesRepo) {
    std::string  title1, title2;
    std::cout<<"Please enter the first movie title: ";
    std::getline(std::cin,title1);
    std::cout<<"Please enter the second movie title: ";
    std::getline(std::cin,title2);

    Movie movie1 = findMovieInRepository(moviesRepo, title1);
    Movie movie2 = findMovieInRepository(moviesRepo, title2);

    Movie seriesMovie = movie1 + movie2;

    std::cout<<"\n Created the series movie:"<<std::endl;
    std::cout<<seriesMovie<<std::endl;
    moviesRepo.addElement(seriesMovie);
}



void  staffDeleteMovies(Repository<Movie>& moviesRepo) {
    std::cout << "Please enter the ID of the movie you want to delete: ";

    int movieid;

    std::cin >> movieid;
    std::cout <<"Searching for the movie "<<movieid<<" ..."<< std::endl;
    bool found = false;
    for (const auto& md : moviesRepo.getElements()) {
        if (md.getmovieID() == movieid) {
            moviesRepo.deleteElement(md);
            found = true;
            std::cout<<"Successfully deleted the movie "<<md.getTitle()<<" ."<<std::endl;
            break;
        }
    }
    if (!found) {
        std::cout<<"We're sorry! No Movie found for the ID: "<<movieid<<std::endl;
    }
}

#endif //STAFFFUNCTIONS_H
