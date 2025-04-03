//TO DO:
//
//use case of copy constructor : identical movies but different languages
//
//Ticket Reservation System for Cinema
#include <string>
#include <vector>
#include <iostream>

//-------------GLOBAL VARIABLES---------------------------

static int id = 0;
static int id2 = 0;

//-------------CLASSES------------------------------------
class Movie {

private:
    std::string title;
    int year_of_release;
    int duration; //in minutes ,i have to change
    float rating;

public:
    //initializer constructor
    Movie(const std::string& title, int year, int duration, int rating);

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

    //destructor
    ~Movie();
    void showMovieInfo() const;

    //getter for the title
    std::string getTitle() const;


};

Movie::Movie(const std::string& title, int year, int duration, int rating)
        : title(title), year_of_release(year), duration(duration), rating(rating) {}

Movie::Movie() : title("Unknown"), year_of_release(0), duration(0), rating(0) {
    std::cout<<"default constructor called:)"<<std::endl;
}

Movie::Movie(std::string title, int year) : title(title), year_of_release(year), duration(0), rating(0) {
    std::cout <<"Overloaded constructor called :)"<< std::endl;
}

Movie::Movie(const Movie &another): title(another.title), year_of_release(another.year_of_release),duration(another.duration),rating(another.rating){
    std::cout<<"Copy constructor called :)"<<std::endl;
}

Movie& Movie::operator=(const Movie &another) {
    if (this != &another) { //for not making useless assignments
        title = another.title;
        year_of_release = another.year_of_release;
        duration = another.duration;
        rating = another.rating;
        std::cout<<"Assign copy constructor called :)"<<std::endl;
        return *this;
    }
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "Title: " << movie.title << std::endl;
    os << "Year Of Release: " << movie.year_of_release << std::endl;
    os << "Duration: " << movie.duration << " minutes" <<std::endl;
    os << "Rating: " << movie.rating << "/10" << std::endl;
    os << "writing operator friend fnct called :)" << std::endl;
    return os;

}

std::istream& operator>>(std::istream& is, Movie &movie) {
    std::cout<<"Enter title: ";
    is >>  movie.title;
    std::cout<<"Enter year of release: ";
    is >> movie.year_of_release;
    std::cout<<"Enter duration: ";
    is >> movie.duration;
    std::cout<<"Enter rating: ";
    is >> movie.rating;
    std::cout<< "reading operator friend fnct called:)" <<std::endl;
    return is;
}

Movie Movie::operator+(const Movie& movie) const {
    std::string newTitle = "The Series: " + title + " & " + movie.title;
    int newYearOfRelease = (year_of_release > movie.year_of_release ? year_of_release : movie.year_of_release);
    int newDuration = duration + movie.duration;
    float newRating = (rating + movie.rating) / 2.0f;
    std::cout<< "+operator overloaded used :)"<<std::endl;
    return Movie(newTitle, newYearOfRelease, newDuration, newRating);
}

Movie::~Movie() {
    // std::cout<<"Destructor called :)"<<std::endl;
    // std::cout<<"For the movie: "<<title<<std::endl;
}

//another overloaded operator built as a non-member function
//first i need a getter for the title date which is private
std::string Movie::getTitle() const {
    return title;
}

bool operator==(const Movie &movie1, const Movie &movie2) {
    std::cout << "friend overloaded operator used :)" << std::endl;
    return movie1.getTitle() == movie2.getTitle();
}


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
void case7(){
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
    if (film3 != film) {
        std::cout<<"Test passed\n\n";
    }
    std::cout<<"So all the requirements in the task have been met!\n\n";

}




void displayMenu() {
    std::cout << "TICKET RESERVATION SYSTEM FOR CINEMA" << std::endl;
    std::cout << "Please select one of the following options:" <<std::endl;
    std::cout << "1. Show available movies" <<std::endl;
    std::cout << "2. Search for a movie" <<std::endl;
    std::cout << "3. Show movie details" <<std::endl;
    std::cout << "4. Reserve a seat" <<std::endl;
    std::cout << "5. Assign a seat automatically\n   we will provide best possible seats ;)" <<std::endl;
    std::cout << "6. Cancel a reservation"<<std::endl;
    std::cout << "7. Work with constructors and operators\n   ()" <<std::endl;
    std::cout << "8. Exit" <<std::endl;
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
                case7();
                break;
            default:
                std::cout << "Invalid option! Plese select a valid one!\n"<<std::endl;
                break;
        }

    }while (option != 7);

}



//------------------------MAIN--------------------------------

int main() {
    ///-----------------------initializing movies----------------------------
    // Movie movie0("Oppenheimer", 2023, 181, 8.3);
    // Movie movie1("Interstellar", 2014, 179, 8.7);
    // Movie movie2("Batman", 2022, 176, 7.8);
    // Movie movie3();
    // Movie movie4();
    // Movie movie5();
    // Movie movie6();
    // Movie movie7();
    // Movie movie8();
    // Movie movie9();
    // Movie movie10();
    // Movie movie11();
    // Movie movie12();
    // Movie movie13();
    // Movie movie14();
    // Movie movie15();
    // Movie movie16();
    // Movie movie17();
    // Movie movie18();
    // Movie movie19();
    // Movie movi20();
    // amovie.showMovieInfo();
    // bmovie.showMovieInfo();
    // cmovie.showMovieInfo();


    ///-------------------------initializing movie dates-------------------------
    MovieDate amovieDate("Oppenheimer", 2023, 181, 8.3, 25,12, 4, 2025, 18, 30);
    MovieDate bmovieDate("Interstellar", 2014, 179, 8.7, 30,15, 5, 2025, 20, 00);
    MovieDate cmovieDate("Batman", 2022, 176, 7.8, 20,20, 6, 2025, 22, 15);

    // amovieDate.showMovieDate();
    // bmovieDate.showMovieDate();
    // cmovieDate.showMovieDate();

    ///-------------------------initializing rooms ------------------------------
    Room aroom(10,20);
    Room broom(15,15);
    Room croom(12,14);


    return 0;
}