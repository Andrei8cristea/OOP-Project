//TO DO:
//
//use case of copy constructor movie: identical movies but different languages
//use case of + operator movie : series of movies eg: batman1, batman2...
//make some tasks available only for the staff that will necessit a password
/*
 * apply discounts
 * add movies
 */
//adjust price


//Ticket Reservation System for Cinema
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <list>
#include <algorithm>

//-------------GLOBAL VARIABLES---------------------------

static int id = 0;
static int id2 = 0;

//-------------CLASSES------------------------------------
class Exceptions : public std::exception {
private:
    std::string message;

public:
    Exceptions(const std::string& msg) : message(msg) {}
    //overriding what method from std::exception
    const char* what() const noexcept override {
        return message.c_str();
    //c_str returns the string from the pointer message
    }
};

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


class Movie {

private:
    std::string title;
    int year_of_release;
    int duration; //in minutes ,I have to change
    float rating;
    static int movieCount;

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

    //destructor virtual (because this class is a superclass)
    virtual ~Movie();

    void showMovieInfo() const;

    //getter for the title
    std::string getTitle() const;

    //getter for the movieCount
    static int getMovieCount(){return movieCount;}


};

int Movie::movieCount = 0; // static init

Movie::Movie(const std::string& title, int year, int duration, int rating)
        : title(title), year_of_release(year), duration(duration), rating(rating) {++movieCount;}

Movie::Movie() : title("Unknown"), year_of_release(0), duration(0), rating(0) {
   // std::cout<<"default constructor called:)"<<std::endl;
    ++movieCount;
}

Movie::Movie(std::string title, int year) : title(title), year_of_release(year), duration(0), rating(0) {
    //std::cout <<"Overloaded constructor called :)"<< std::endl;
    ++movieCount;
}

Movie::Movie(const Movie &another): title(another.title), year_of_release(another.year_of_release),duration(another.duration),rating(another.rating){
    //std::cout<<"Copy constructor called :)"<<std::endl;
    ++movieCount;
}

Movie& Movie::operator=(const Movie &another) {
    if (this != &another) { //for not making useless assignments
        title = another.title;
        year_of_release = another.year_of_release;
        duration = another.duration;
        rating = another.rating;
        //std::cout<<"Assign copy constructor called :)"<<std::endl;
        return *this;
    }
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    std::cout << "+----------------------------------------+\n";
    std::cout << "|             MOVIE DETAILS              |\n";
    std::cout << "+----------------------------------------+\n";

    std::cout << " 🎬 MOVIE TITLE : " << movie.title << "\n";
    std::cout << " 📅 RELEASE YEAR: " << movie.year_of_release << "\n";
    std::cout << " ⏳ DURATION    : " << movie.duration << " min\n";
    std::cout << " ⭐ RATING      : " << movie.rating << "/10\n";
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


    //checking and throwing exceptions
    if(movie.year_of_release < 1800 || movie.year_of_release > 2030) {
        throw Exceptions("Year of release is out of range!");
    }
    if (movie.duration < 1 || movie.duration > 10000) {
        throw Exceptions("Duration is out of range!");
    }
    if (movie.rating < 0 || movie.rating > 10) {
        throw Exceptions("Rating is out of range!");
    }

    std::cout<< "reading operator friend fnct called:)" <<std::endl;
    return is;
}

Movie Movie::operator+(const Movie& movie) const {
    std::string newTitle = "The Series: " + title + " & " + movie.title;
    int newYearOfRelease = (year_of_release > movie.year_of_release ? year_of_release : movie.year_of_release);
    int newDuration = duration + movie.duration;
    float newRating = (rating + movie.rating) / 2.0f;
    //std::cout<< "+operator overloaded used :)"<<std::endl;
    return Movie(newTitle, newYearOfRelease, newDuration, newRating);
}

Movie::~Movie() {
    // std::cout<<"Destructor called :)"<<std::endl;
    // std::cout<<"For the movie: "<<title<<std::endl;
}

//another overloaded operator built as a non-member function
//first I need a getter for the title date which is private
std::string Movie::getTitle() const {
    return title;
}

bool operator==(const Movie &movie1, const Movie &movie2) {
    std::cout << "friend overloaded operator used :)" << std::endl;
    return movie1.getTitle() == movie2.getTitle();
}


void Movie::showMovieInfo() const {
    std::cout << "+----------------------------------------+\n";
    std::cout << "|             MOVIE DETAILS              |\n";
    std::cout << "+----------------------------------------+\n";

    std::cout << " 🎬 MOVIE TITLE : " << title << "\n";
    std::cout << " 📅 RELEASE YEAR: " << year_of_release << "\n";
    std::cout << " ⏳ DURATION    : " << duration << " min\n";
    std::cout << " ⭐ RATING      : " << rating << "/10\n";}


class MovieDate :public  Movie {

private:
    int movie_id;
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
    movie_id(id++),room_id(room_id), price(price),date(date),month(month),
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

MovieDate::MovieDate(const std::string &title, int year_of_release, int duration, int rating, float price,int date, int month, int year, int hour, int minute)
    :Movie(title, year_of_release, duration, rating),movie_id(id++),price(price),date(date), month(month), year(year), hour(hour), minute(minute) {}

MovieDate::MovieDate(const MovieDate &another)
    :Movie(another), //call for copy constructor from Movie class
    movie_id (another.movie_id),
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
        movie_id = movie.movie_id;
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

    std::cout << "+----------------------------------------+\n";
    std::cout << "|             SHOWTIME INFO              |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << " 💰 PRICE      : $" << price << "\n";
    std::cout << " 🏠ROOM NUMBER : " << room_id << "\n";
    std::cout << " 📅 DATE       : " << (date < 10 ? "0" : "") << date << "/"
             << (month < 10 ? "0" : "") << month << "/" << year << "\n";
    std::cout << " ⏰ TIME       : " << (hour < 10 ? "0" : "") << hour << ":"
              << (minute < 10 ? "0" : "") << minute << "\n";

    std::cout << "+----------------------------------------+\n";
    std::cout << "|           ENJOY YOUR MOVIE!            |\n";
    std::cout << "+----------------------------------------+\n";
}

void MovieDate::adjustPrice(float discount) {

    price = static_cast<int>(price * discount);
}

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
           //std::cout << "We're sorry, this seat is already booked..." << "\n";
            throw Exceptions("We're sorry, this seat is already booked...");
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
private:
    int movie_id;
    int room_id;
    int rows_number;
    int columns_number;



public:

};



//---------UI functions-------------------------------------



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
    if (film3 != film) {
        std::cout<<"Test passed\n\n";
    }
    std::cout<<"So all the requirements in the task have been met!\n\n";

}

void displayMenu() {
    std::cout << "TICKET RESERVATION SYSTEM FOR CINEMA" << std::endl;
    std::cout << "Please select one of the following options:" <<std::endl;
    std::cout << "1. Show available movies" <<std::endl;
    std::cout << "2. Show available runtimes for a movie" <<std::endl;
    std::cout << "3. Show movie details" <<std::endl;
    std::cout << "4. Reserve a seat" <<std::endl;
    std::cout << "5. Assign a seat automatically\n   we will provide best possible seats ;)" <<std::endl;
    std::cout << "6. Cancel a reservation"<<std::endl;
    std::cout << "7. Staff menu" <<std::endl;
    std::cout << "8. Work with constructors and operators\n   ()" <<std::endl;
    std::cout << "9. Exit" <<std::endl;
}





//------------------------MAIN--------------------------------

int main() {
    ///-----------------------initializing repo------------------------------
    Repository<Movie> movies_list;
    Reservations<Ticket> tickets_list;



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
    Room aroom(10,20);
    Room broom(15,15);
    Room croom(12,14);
    aroom.modifyBoard(2,3);
   // aroom.modifyBoard(2,3);

    //--------------------------Main Loop----------------------------------
        int option;
        do {
            displayMenu();
            std::cin >> option;

            switch (option) {
                case 1:
                    std::cout << "Showing available movies..." <<std::endl;
                    movies_list.displayMovies();
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
                case 8:
                    case8();
                break;
                case 9:
                    std::cout << "";
                break;
                default:
                    std::cout << "Invalid option! Please select a valid one!\n"<<std::endl;
                break;
            }

        }while (option != 9);




    return 0;
}