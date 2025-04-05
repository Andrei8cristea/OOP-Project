//TO DO:
//
//use case of copy constructor movie: identical movies but different languages
//use case of + operator movie : series of movies eg: batman1, batman2...
//make some tasks available only for the staff that will necessit a password
/*
 * apply discounts
 * add movies
 * asssign automatically a seat
 */
//adjust price


//Ticket Reservation System for Cinema
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <list>
#include <algorithm>
#include "Movie.h"
#include "MovieDate.h"
#include "Room.h"

//-------------GLOBAL VARIABLES---------------------------




//-------------CLASSES------------------------------------


template <typename T>
class Repository {
private:
    std::list<T> movies;
public:
    void addMovie(const T& movie) {
        movies.push_back(movie);
    }
    void deleteMovie(const T& movie) {
        movies.remove(movie);
    }
    void displayMovies() const{
        std::cout << "Showing available movies..." <<std::endl;
        std::cout << "The list with all the movies is the following:\n" << std::endl;
        for (const T& movie : movies) {
            std::cout << movie << std::endl;
        }
    }
};

template <typename S>
class Reservations {
    private:
        std::list<S> reservations_list;
    public:
    void addResevation(const S& ticket) {
        reservations_list.push_back(ticket);
    }
    void deleteResevation(const S& ticket) {
        reservations_list.remove(ticket);
    }
    void displayResevations() const{
        std::cout << "The list with all the reservations is the following:\n" << std::endl;

        auto printReservations = [](const S& ticket) {
            std::cout << ticket << std::endl;
        };
        std::for_each(reservations_list.begin(), reservations_list.end(), printReservations);


        // for (const S& reservation : reservations_list) {
        //     std::cout << reservation << std::endl;
        // }
    }
};

template <typename U>
class RepositoryDates {
private:
    std::list<U> repository_dates;
public:
    void addRepositoryDate(const U& dates) {
        repository_dates.push_back(dates);
    }
    void deleteRepositoryDate(const U& dates) {
        repository_dates.remove(dates);
    }

    //getter for the repository dates
    const std::list<U>& getRepositoryDates() const {
        return repository_dates;
    }

    void displayRepositoryDates() const {
        std::cout << "The list with all the repository dates is the following:" << std::endl;
    }


};

class Ticket {
private:
    int movie_id;
    int room_id;
    int rows_number;
    int columns_number;



public:

};



//---------UI functions-------------------------------------

void showMovieDatesForMovieTitle(const RepositoryDates<MovieDate> & repo)
{
    std::string movieTitle;
    std::cout << "Please enter the movie you want to watch: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);
    std::cout <<"Searching for the movie "<<movieTitle<<" ..."<< std::endl;
    bool found = false;
    for (const auto& md : repo.getRepositoryDates()) {
        if (md.getTitle() == movieTitle) {
            md.showMovieDate();
            found = true;
        }
    }
    if (!found) {
        std::cout<<"We're sorry! No showtime found for the movie: "<<movieTitle<<std::endl;
    }
}

void showMovieDatesForMovieID(const RepositoryDates<MovieDate> & repo) {
    std::cout << "Please enter the ID of the movie you want to watch: ";

    int movieid;
    std::cin.ignore();

    std::cin >> movieid;
    std::cout <<"Searching for the movie "<<movieid<<" ..."<< std::endl;
    bool found = false;
    for (const auto& md : repo.getRepositoryDates()) {
        if (md.getmovieID() == movieid) {
            md.showMovieDate();
            found = true;
        }
    }
    if (!found) {
        std::cout<<"We're sorry! No showtime found for the movie: "<<movieid<<std::endl;
    }
}

void reserveSeat(const RepositoryDates<MovieDate> & repo, std::vector<Room>& rooms) {
    std::string movieTitle;
    std::cout << "Please enter the movie you want to watch: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);

    const MovieDate* selectedDate = nullptr;
    for (const auto& md : repo.getRepositoryDates()) {
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
    std::vector<const MovieDate*> filteredDates;
    for (const auto& md : repo.getRepositoryDates()) {
        if (md.getTitle() == movieTitle) {
            std::cout<<"["<<index<<"]"<<std::endl;
            md.showMovieDate();
            std::cout<<std::endl;
            filteredDates.push_back(&md);
            index++;
        }
    }
    if (!filteredDates.size()) {
        std::cout<<"No runtimes availavle for "<<movieTitle<<"."<<std::endl;
        return;
    }

    int selectedIndex;
    std::cout<<"Please enter the index of the showtime you want: ";
    std::cin >> selectedIndex;
    while (selectedIndex < 0 || selectedIndex >= static_cast<int>(filteredDates.size())) {
        std::cout<<"Invalid showtime selection. Please enter a valid index: ";
        std::cin >> selectedIndex;
    }

    const MovieDate* selectedDatePtr = filteredDates[selectedIndex];

    int roomID= selectedDate->getRoomId();

    Room* selectedRoom = nullptr;
    for (auto& room : rooms) {
        if (room.getRoomId()==roomID) {
            selectedRoom = &room;
            break;
        }
    }

    if (!selectedRoom) {
        std::cout<<"No room was found for the selected showtime."<<std::endl;
    }

    std::cout<<"Room info: \n"<<std::endl;
    selectedRoom->showRoomInfo();
    selectedRoom->showBoard();
    std::cout<<std::endl;

    //
    //  int room_id = selectedDate->getRoomId();
    // Room* selectedRoom = nullptr;
    // for (auto&room : rooms) {
    //     if (room.getRoomId() == room_id) {
    //         selectedRoom = &room;
    //         break;
    //     }
    // }
    // if (!selectedRoom) {
    //     std::cout<<"Room not found for the selected runtime!";
    //     return;
    // }

    int row, column;
    std::cout << "Enter the seat row number you want to reserve: ";
    std::cin >> row;
    std::cout << "Enter column number: ";
    std::cin >> column;

    try {
        selectedRoom->modifyBoard(row, column);
        std::cout<<"Seat reserved succesfully\n\n";
    }
    catch (const std::exception& e) {
        std::cout<<"Error: "<<e.what();
    }
}


void case8(){
    std::cout << "Constructors and operators for the class \"Movie\":\n\n";
    std::cout <<"Firstly i will use the default constructor,\nand after every modification i will print the object\n"<< std::endl;
    Movie film;
    std :: cout<< film<<std::endl;

    std::cout << "Now I will use the overload constructor:" << std::endl;
    Movie film2("Titanic", 1997);
    std :: cout<< film2<<std::endl;

    std::cout<<"Now i will use the copy constructor:\n";
    Movie film3(film2);
    std :: cout<< film3<<std::endl;

    std::cout<<"Now i will use the copy operator:\n";
    film2 = film;
    std::cout <<film2<<std::endl;

    std::cout<<"Now i will use the movie operator\n";
    std::cin >> film3;
    std::cout<<film3<<std::endl;

    std::cout<<"Now i will use the '+' operator:\n";
    std::cout << film3+film2<<std::endl;

    std::cout<<"Now i will use the '==' operator:\n";
    if (&film2 == &film) {
        std::cout<<"Test passed\n\n";
    }
    std::cout<<"So all the requirements in the task have been met!\n\n";

}

void displayMenu() {
    std::cout << "TICKET RESERVATION SYSTEM FOR CINEMA" << std::endl;
    std::cout << "Please select one of the following options:" <<std::endl;
    std::cout << "1. Show available movies" <<std::endl;
    std::cout << "2. Show available runtimes for a movie" <<std::endl;
    std::cout << "3. Reserve a seat" <<std::endl;
    std::cout << "4. Assign a seat automatically\n   we will provide best possible seats ;)" <<std::endl;
    std::cout << "5. Cancel a reservation"<<std::endl;
    std::cout << "6. Staff menu" <<std::endl;
    std::cout << "7. Work with constructors and operators\n   ()" <<std::endl;
    std::cout << "8. Exit" <<std::endl;
}





//------------------------MAIN--------------------------------

int main() {
    ///-----------------------initializing repo------------------------------
    Repository<Movie> movies_list;
    RepositoryDates<MovieDate> movies_dates;
    Reservations<Ticket> tickets_list;
    std::vector<Room> rooms;




    ///-----------------------initializing movies----------------------------
    Movie* movie1 = new Movie("Oppenheimer",2023,180,8.3);
    Movie* movie2 = new Movie("The Godfather", 1972,175,9.2);
    Movie* movie3 = new Movie("The Dark Knight",2008,152,9.0);
    Movie* movie4 = new Movie("Schindler's List",1993,195,9.0);
    Movie* movie5 = new Movie("Inception",2010,148,8.8);
    Movie* movie6 = new Movie("The Matrix",	1999,136,8.7);
    Movie* movie7 = new Movie("Interstellar",2014,169,8.7);
    Movie* movie8 = new Movie("The Lion King",1994,88,8.5);
    Movie* movie9 = new Movie("Gladiator",2000,155,8.5	);
    Movie* movie10 = new Movie("Gladiator II", 2024,148,6.6);

    movies_list.addMovie(*movie1);
    movies_list.addMovie(*movie2);
    movies_list.addMovie(*movie3);
    movies_list.addMovie(*movie4);
    movies_list.addMovie(*movie5);
    movies_list.addMovie(*movie6);
    movies_list.addMovie(*movie7);
    movies_list.addMovie(*movie8);
    movies_list.addMovie(*movie9);
    movies_list.addMovie(*movie10);


    //movies_list.displayMovies();
    ///-------------------------initializing movie dates-------------------------



    MovieDate* moviedate1  = new MovieDate(movie1, 1, 20.30, 12, 4, 2025, 19, 15);
    MovieDate* moviedate2  = new MovieDate(movie2, 2, 18.50, 14, 4, 2025, 20, 00);
    MovieDate* moviedate3  = new MovieDate(movie3, 3, 22.00, 17, 4, 2025, 21, 45);
    MovieDate* moviedate4  = new MovieDate(movie4, 4, 19.99, 20, 4, 2025, 18, 30);
    MovieDate* moviedate5  = new MovieDate(movie5, 1, 15.00, 24, 4, 2025, 17, 20);

    MovieDate* moviedate6  = new MovieDate(movie6, 2, 18.75, 28, 4, 2025, 21, 10);
    MovieDate* moviedate7  = new MovieDate(movie7, 3, 23.50, 1, 5, 2025, 19, 45);
    MovieDate* moviedate8  = new MovieDate(movie8, 4, 20.00, 5, 5, 2025, 16, 50);
    MovieDate* moviedate9  = new MovieDate(movie9, 1, 17.99, 9, 5, 2025, 20, 15);
    MovieDate* moviedate10 = new MovieDate(movie10, 2, 21.50, 13, 5, 2025, 18, 40);

    MovieDate* moviedate11 = new MovieDate(movie1, 3, 16.75, 17, 5, 2025, 22, 00);
    MovieDate* moviedate12 = new MovieDate(movie2, 4, 19.99, 21, 5, 2025, 17, 30);
    MovieDate* moviedate13 = new MovieDate(movie3, 1, 14.25, 25, 5, 2025, 21, 50);
    MovieDate* moviedate14 = new MovieDate(movie4, 2, 23.00, 29, 5, 2025, 18, 10);
    MovieDate* moviedate15 = new MovieDate(movie5, 3, 20.75, 2, 6, 2025, 19, 30);

    MovieDate* moviedate16 = new MovieDate(movie6, 4, 25.99, 6, 6, 2025, 22, 20);
    MovieDate* moviedate17 = new MovieDate(movie7, 1, 18.50, 10, 6, 2025, 16, 45);
    MovieDate* moviedate18 = new MovieDate(movie8, 2, 22.99, 14, 6, 2025, 20, 55);
    MovieDate* moviedate19 = new MovieDate(movie9, 3, 17.75, 18, 6, 2025, 19, 10);
    MovieDate* moviedate20 = new MovieDate(movie10, 4, 19.50, 22, 6, 2025, 21, 35);

    MovieDate* moviedate21 = new MovieDate(movie1, 1, 24.00, 26, 6, 2025, 18, 40);
    MovieDate* moviedate22 = new MovieDate(movie2, 2, 21.25, 30, 6, 2025, 22, 00);
    MovieDate* moviedate23 = new MovieDate(movie3, 3, 15.50, 3, 7, 2025, 20, 30);
    MovieDate* moviedate24 = new MovieDate(movie4, 4, 26.00, 7, 7, 2025, 17, 55);
    MovieDate* moviedate25 = new MovieDate(movie5, 1, 22.75, 11, 7, 2025, 19, 20);

    movies_dates.addRepositoryDate(*moviedate1);
    movies_dates.addRepositoryDate(*moviedate2);
    movies_dates.addRepositoryDate(*moviedate3);
    movies_dates.addRepositoryDate(*moviedate4);
    movies_dates.addRepositoryDate(*moviedate5);
    movies_dates.addRepositoryDate(*moviedate6);
    movies_dates.addRepositoryDate(*moviedate7);
    movies_dates.addRepositoryDate(*moviedate8);
    movies_dates.addRepositoryDate(*moviedate9);
    movies_dates.addRepositoryDate(*moviedate10);
    movies_dates.addRepositoryDate(*moviedate11);
    movies_dates.addRepositoryDate(*moviedate12);
    movies_dates.addRepositoryDate(*moviedate13);
    movies_dates.addRepositoryDate(*moviedate14);
    movies_dates.addRepositoryDate(*moviedate15);
    movies_dates.addRepositoryDate(*moviedate16);
    movies_dates.addRepositoryDate(*moviedate17);
    movies_dates.addRepositoryDate(*moviedate18);
    movies_dates.addRepositoryDate(*moviedate19);
    movies_dates.addRepositoryDate(*moviedate20);
    movies_dates.addRepositoryDate(*moviedate21);
    movies_dates.addRepositoryDate(*moviedate22);
    movies_dates.addRepositoryDate(*moviedate23);
    movies_dates.addRepositoryDate(*moviedate24);
    movies_dates.addRepositoryDate(*moviedate25);


    // MovieDate amovieDate("Oppenheimer", 2023, 181, 8.3, 25,12, 4, 2025, 18, 30);
    // MovieDate bmovieDate("Interstellar", 2014, 179, 8.7, 30,15, 5, 2025, 20, 00);
    // MovieDate cmovieDate("Batman", 2022, 176, 7.8, 20,20, 6, 2025, 22, 15);


    // Movie* obj = new MovieDate();
    // displayMovieFullInfo(obj);
    // delete obj;
    // Movie m;
    // std::cin>>m;
    // bmovieDate.showMovieDate();
    // cmovieDate.showMovieDate();

    ///-------------------------initializing rooms ------------------------------
    Room room1(10,20);
    Room room2(15,15);
    Room room3(12,14);
    Room room4(20,20);
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    rooms.push_back(room4);


    //--------------------------Main Loop----------------------------------
        int option;
        do {
            displayMenu();
            std::cout << "Your option: ";
            std::cin >> option;

            switch (option) {
                case 1:{
                    movies_list.displayMovies();
                    break;
                }
                case 2:{
                    //showMovieDatesForMovieID(movies_dates);
                    showMovieDatesForMovieTitle(movies_dates);
                    break;
                }
                case 3: {
                    reserveSeat(movies_dates, rooms);
                }
                case 4:
                    std::cout << "";
                break;
                case 5:
                    std::cout << "";

                break;
                case 6:
                    std::cout << "";

                break;
                case 7:
                    std::cout << "";
                break;
                case 8:
                    case8();
                break;
                case 9:
                    std::cout << "Exiting..." <<std::endl;
                break;
                default:
                    std::cout << "Invalid option! Please select a valid one!\n"<<std::endl;
                break;
            }

        }while (option != 9);




    delete movie1;
    delete movie2;
    delete movie3;
    delete movie4;
    delete movie5;
    delete movie6;
    delete movie7;
    delete movie8;
    delete movie9;
    delete movie10;

    delete moviedate1;
    delete moviedate2;
    delete moviedate3;
    delete moviedate4;
    delete moviedate5;
    delete moviedate6;
    delete moviedate7;
    delete moviedate8;
    delete moviedate9;
    delete moviedate10;
    delete moviedate11;
    delete moviedate12;
    delete moviedate13;
    delete moviedate14;
    delete moviedate15;
    delete moviedate16;
    delete moviedate17;
    delete moviedate18;
    delete moviedate19;
    delete moviedate20;
    delete moviedate21;
    delete moviedate22;
    delete moviedate23;
    delete moviedate24;
    delete moviedate25;


    return 0;
}