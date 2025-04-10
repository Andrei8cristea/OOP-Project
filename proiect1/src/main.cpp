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
#include <termios.h>
#include <unistd.h>
#include <fstream>

#include "include/Movie.h"
#include "include/MovieDate.h"
#include "include/Room.h"
#include "include/Exceptions.h"
#include "include/StaffFunctions.h"
#include "include/TemplateClasses.h"
#include "include/Ticket.h"

//--------Global variables--------------------------------


//---------UI functions-------------------------------------

void showMovieDatesForMovieTitle(const Repository<MovieDate> & repo)
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

void showMovieDatesForMovieID(const Repository<MovieDate> & repo) {
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

void reserveSeat(Repository<MovieDate> & repo,Repository<Ticket> & tickets_list, std::vector<Room>& rooms) {
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
        std::cout<<"No runtimes available for "<<movieTitle<<"."<<std::endl;
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


    std::cout << "Please enter how many seats you want to reserve: ";
    int number;
    std::cin >> number;
    for (int i = 0; i < number; i++) {

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

            Ticket t(*selectedDate, *selectedRoom, row, column);
            t.printTicket();
            tickets_list.addElement(t);
            std::cout<<std::endl;

        }
        catch (const std::exception& e) {
            std::cout<<"Error: "<<e.what();
        }
    }
}

void disableEchoMode() {
    termios t;//create a termios struct that holds terminal settings
    tcgetattr(STDIN_FILENO, &t);//with this getter I put current terminal atributes in t
    t.c_lflag &= ~ECHO;//I modify t so that will disable the echo flag
    //bitwise not operation for echo because echo is a bit flag(and only one bit long)
    tcsetattr(STDIN_FILENO, TCSANOW, &t);//apply changes that I have just made
}

void enableEchoMode() {
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

bool verifyPassword(const std::string& staffName, const std::string& password) {
    std::ifstream file("/home/andrei-cristea/Desktop/Facultate/Anul I/Semestrul 2/POO/proiect1/build/passwords.txt");
    std::string line;

    if (!file) {
        throw Exceptions( "ERROR: File \"passwords.txt\" has not been found!");

    }

    while (std::getline(file,line)) {
        if (line == (staffName + ":" + password)) {
            return true;
        }
    }
    return false;
}



void staffMenu(Repository<Movie>& movies_list, Repository<MovieDate>& dates_list) {
    std::string name;
    std::string password;
    int attempts = 3;

    std::cout<<"Welcome to the staff menu."<<std::endl;
    std::cin.ignore(10000, '\n');
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //here I empty the buffer because otherwise the input will be required
    //before the needed output text

    while (attempts>-0) {
        std::cout<<"Please login below."<<std::endl<<"Please enter your name: ";
        std::getline(std::cin, name);

        std::cout<<"Please enter your password: ";
        disableEchoMode();
        std::getline(std::cin, password);
        enableEchoMode();
        std::cout<<std::endl;

        if (verifyPassword(name, password) == true) {
            std::cout<<"Login succesful, "<<name<<".\n"<<std::endl;
            int staffOption;
            do {


                std::cout <<"Staff menu:"<<std::endl;
                std::cout<<"1. Add a movie"<<std::endl;
                std::cout<<"2. Adjust price for a showtime"<<std::endl;
                std::cout<<"3. Create a movie series"<<std::endl;
                std::cout<<"4. Delete a movie"<<std::endl;
                std::cout<<"5. See statistics"<<std::endl;
                std::cout<<"6. Exit"<<std::endl;
                std::cout<<"Enter your option: ";
                std::cin>>staffOption;
                std::cin.ignore(10000, '\n');
                switch (staffOption) {
                    case 1: {
                        staffAddMovie(movies_list);
                        break;
                    }
                    case 2: {
                        staffAdjustPrice(dates_list);
                        break;
                    }
                    case 3:{
                        staffCreateSeries(movies_list);
                        break;
                     }
                    case 4: {
                        staffDeleteMovies(movies_list);
                        break;
                    }
                    case 5: {
                        Movie::printStatistics();
                        break;
                    }
                    case 6: {

                        break;
                    }
                }
            }while (staffOption!=6);
            return;

        }
        else {
            std::cout<<"Login failed. You have "<<attempts-1<<" more tries."<<std::endl;
            attempts--;
            std::cin.sync();
            //synchronizing the input buffer
        }
    }
    std::cout << "Access denied. No more attempts left." << std::endl;


}

void cancelTicket(Repository<Ticket>& ticketsRepo, std::vector<Room>& rooms) {
    int ticketID;
    std::cout<<"Enter your ticket ID you want to cancel: ";
    std::cin>>ticketID;

    bool found = false;
    for (auto& it: ticketsRepo.getElements()) {
        if (it.getTicketID() == ticketID) {
            found = true;
            int roomID= it.getRoomID();
            int row = it.getRow();
            int col = it.getColumn();

            Room* ticketRoom = nullptr;
            for (auto& room : rooms) {
                if (room.getRoomId()==roomID) {
                    ticketRoom = &room;
                    break;
                }
            }

            if (ticketRoom != nullptr) {
                ticketRoom->freeSeat(row,col);
                std::cout<<"Your seat has been freed in room with id: "<<roomID<<std::endl;
            }
            else {
                std::cout<<"Room hasn't been found!"<<std::endl;
            }

            //I also have to delete the ticket from the tickets repository
            ticketsRepo.deleteElement(it);
            std::cout<<"Your ticket, with ID "<<ticketID<< " has been deleted.\n\n\n"<<std::endl;
            break;
        }
    }
    if (!found) {
        std::cout<<"The ticket ID you have entered has not been found in our list.\n";
    }

}




void case6(){
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

void sortShowtimesByPrice(Repository<MovieDate>& repo) {
    auto& showtimes = repo.getElements();
    std::vector<MovieDate> vec(showtimes.begin(), showtimes.end());
    std::sort(vec.begin(), vec.end(),[](const MovieDate&a, const MovieDate&b) {
        return a.getPrice() < b.getPrice();
    });
    std::cout<<"This are the showtimes sorted by price: "<<std::endl;
    for (const auto& md : vec) {
        md.showMovieDate();
    }
}

void displayMenu() {
    std::cout << "TICKET RESERVATION SYSTEM FOR CINEMA" << std::endl;
    std::cout << "Please select one of the following options:" <<std::endl;
    std::cout << "1. Show available movies" <<std::endl;
    std::cout << "2. Show available runtimes for a movie" <<std::endl;
    std::cout << "3. All showtimes (sorted by price)" <<std::endl;
    std::cout << "4. Reserve a seat" <<std::endl;
    std::cout << "5. Cancel a reservation"<<std::endl;
    std::cout << "6. Staff menu" <<std::endl;
    std::cout << "7. Work with constructors and operators (just for exemplification)" <<std::endl;
    std::cout << "8. Exit" <<std::endl;
}





//------------------------MAIN--------------------------------

int main() {
    ///-----------------------initializing repo------------------------------
    Repository<Ticket> tickets_list;
    Repository<Movie> movies_list;
    Repository<MovieDate> movies_dates;
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

    movies_list.addElement(*movie1);
    movies_list.addElement(*movie2);
    movies_list.addElement(*movie3);
    movies_list.addElement(*movie4);
    movies_list.addElement(*movie5);
    movies_list.addElement(*movie6);
    movies_list.addElement(*movie7);
    movies_list.addElement(*movie8);
    movies_list.addElement(*movie9);
    movies_list.addElement(*movie10);

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

    movies_dates.addElement(*moviedate1);
    movies_dates.addElement(*moviedate2);
    movies_dates.addElement(*moviedate3);
    movies_dates.addElement(*moviedate4);
    movies_dates.addElement(*moviedate5);
    movies_dates.addElement(*moviedate6);
    movies_dates.addElement(*moviedate7);
    movies_dates.addElement(*moviedate8);
    movies_dates.addElement(*moviedate9);
    movies_dates.addElement(*moviedate10);
    movies_dates.addElement(*moviedate11);
    movies_dates.addElement(*moviedate12);
    movies_dates.addElement(*moviedate13);
    movies_dates.addElement(*moviedate14);
    movies_dates.addElement(*moviedate15);
    movies_dates.addElement(*moviedate16);
    movies_dates.addElement(*moviedate17);
    movies_dates.addElement(*moviedate18);
    movies_dates.addElement(*moviedate19);
    movies_dates.addElement(*moviedate20);
    movies_dates.addElement(*moviedate21);
    movies_dates.addElement(*moviedate22);
    movies_dates.addElement(*moviedate23);
    movies_dates.addElement(*moviedate24);
    movies_dates.addElement(*moviedate25);

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
                    sortShowtimesByPrice(movies_dates);
                    break;
                }
                case 4: {
                    reserveSeat(movies_dates,tickets_list, rooms);
                    break;
                }
                case 5: {
                    cancelTicket(tickets_list, rooms);
                    break;
                }
                case 6:{
                    staffMenu(movies_list,movies_dates);
                    break;
                }
                case 7:{
                    std::cout << "";
                    case6();
                    break;
                }
                case 8:
                    std::cout << "Exiting..." <<std::endl;
                break;
                default:
                    std::cout << "Invalid option! Please select a valid one!\n"<<std::endl;
                break;
            }

        }while (option != 8);


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