//Ticket Reservation System for Cinema
#include <string>
#include <vector>
#include <iostream>

//-------------GLOBAL VARIABLES---------------------------

static int id = 0;
static int id2 = 0;

//-------------CLASSES------------------------------------
class Movie {

protected:
    std::string title;
    int year_of_release;
    int duration; //in minutes ,i have to change
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
    int price;
    int date;
    int month;
    int year;
    int hour;
    int minute;

public:
    MovieDate(const std::string& title, int year_of_release, int duration, int rating,
              int price, int date, int month, int year, int hour, int minute);
    void showMovieDate() const;

};

MovieDate::MovieDate(const std::string &title, int year_of_release, int duration, int rating, int price,int date, int month, int year, int hour, int minute)
    :Movie(title, year_of_release, duration, rating),movie_id(id++),price(price),date(date), month(month), year(year), hour(hour), minute(minute) {}

void MovieDate::showMovieDate() const {
    std::cout << "ID: " << movie_id << " | Date: " << date << "/" << month << "/" << year
              << " | Time: " << hour << ":" << minute << std::endl;
}



class Room {

    int room_id;
    int rows_number;
    int columns_number;
    std::vector<std::vector<char>> board;

public:
    Room(int rows_number, int colums_number);
    void showRoomInfo() const;
    void showBoard() const;
    void modifyBoard(int row_nr, int col_nr);
};

Room::Room(int rows, int columns)
:room_id(id2++),rows_number(rows),columns_number(columns),board(rows, std::vector<char>(columns, '_')){}

void Room::showRoomInfo() const {

    int cnt = 0;
    for (auto&row : board) {
        for (auto&col : row) {
            if (col == '_') {
                cnt++;
            }
        }
    }
    std::cout <<"Room ID: "<< room_id << std::endl;
    std::cout <<"Available seats: "<<cnt << std::endl;
    std::cout <<"Rows: "<< rows_number << std::endl;
    std::cout <<"Columns: "<< columns_number << std::endl;
    std::cout << std::endl;

    }

void Room::showBoard() const {
    int i, j;
    std::cout <<"-----SCREEN-----SCREEN-----SCREEN-----SCREEN-----SCREEN-----"<<"\t"<< std::endl;
    std::cout << "    ";
    for (j = 0; j < columns_number; j++) {
        std::cout << j+1 << "\t";
    }
    std::cout << std::endl;
    for (i = 0; i < rows_number; i++) {
        std::cout << i+1 << "\t";
        for (j = 0; j < columns_number; j++) {
            std::cout << board[i][j]<< "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // for (auto&row : board) {
    //     std::cout << i;
    //     i++;
    //     for (auto&col : row) {
    //         std::cout << col<<"\t";
    //     }
    //     std::cout << std::endl;

}

void Room::modifyBoard(int row_nr, int col_nr) {
    if (row_nr >= 1 && row_nr <= rows_number && col_nr >= 1 && col_nr <= columns_number) {
        if (board[row_nr-1][col_nr-1] == '#') {
           std::cout << "We're sorry, this seat is already booked..." << "\n";
        }
        else{
            board[row_nr-1][col_nr-1] = '#';
        }
    }

    else {
        std::cout << "Invalid seat position!"<<"\n";
    }
}


class Ticket {
    int movie_id;
    int room_id;
    int rows_number;
    int columns_number;



public:

};

//---------UI functions-------------------------------------

void displayMenu() {
    std::cout << "TICKET RESERVATION SYSTEM FOR CINEMA" << std::endl;
    std::cout << "Please select one of the following options:" <<std::endl;
    std::cout << "1. Show available movies" <<std::endl;
    std::cout << "2. Search for a movie" <<std::endl;
    std::cout << "3. Show movie details" <<std::endl;
    std::cout << "4. Reserve a seat" <<std::endl;
    std::cout << "5. Assign a seat automatically\n   we will provide best possible seats ;)" <<std::endl;
    std::cout << "6. Cancel a reservation"<<std::endl;
    std::cout << "7. Exit" <<std::endl;
}

void mainLoop() {
    int option;
    do {
        displayMenu();
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "";

                break;
            case 2:
                std::cout << "";

                break;
            case 3:
                std::cout << "";

                break;
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
            default:
                std::cout << "";

                break;
        }

    }while (option != 7);

}



//------------------------MAIN--------------------------------

int main() {

    ///-----------------------initializing movies----------------------------
    Movie amovie("Oppenheimer", 2023, 3, 8.3);
    Movie bmovie("Interstellar", 2014, 2, 8.7);
    Movie cmovie("Batman", 2022, 3, 7.8);

    // amovie.showMovieInfo();
    // bmovie.showMovieInfo();
    // cmovie.showMovieInfo();


    ///-------------------------initializing movie dates-------------------------
    MovieDate amovieDate("Oppenheimer", 2023, 3, 8.3, 25,12, 4, 2025, 18, 30);
    MovieDate bmovieDate("Interstellar", 2014, 2, 8.7, 30,15, 5, 2025, 20, 00);
    MovieDate cmovieDate("Batman", 2022, 3, 7.8, 20,20, 6, 2025, 22, 15);

    // amovieDate.showMovieDate();
    // bmovieDate.showMovieDate();
    // cmovieDate.showMovieDate();

    ///-------------------------initializing rooms ------------------------------
    Room aroom(10,20);
    Room broom(15,15);
    Room croom(12,14);

    aroom.showRoomInfo();
    aroom.showBoard();
    aroom.modifyBoard(3,4);
    aroom.modifyBoard(3,4);
    aroom.modifyBoard(19,35);
    aroom.showRoomInfo();
    aroom.showBoard();
    // broom.showRoomInfo();
    // croom.showRoomInfo();

    return 0;
}