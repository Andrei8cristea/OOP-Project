//
// Created by andrei-cristea on 4/5/25.
//

#include "Movie.h"

int Movie::id3 = 0;

int Movie::movieCount = 0; // static init

Movie::Movie(const std::string& title, int year, int duration, float rating)
        : movieID(id3++),title(title), year_of_release(year), duration(duration), rating(rating) {++movieCount;}

Movie::Movie() :movieID(-1), title("Unknown"), year_of_release(0), duration(0), rating(0) {
   // std::cout<<"default constructor called:)"<<std::endl;
    ++movieCount;
}

Movie::Movie(std::string title, int year) : title(title), year_of_release(year), duration(0), rating(0) {
    //std::cout <<"Overloaded constructor called :)"<< std::endl;
    ++movieCount;
}

Movie::Movie(const Movie &another): movieID(another.movieID),title(another.title), year_of_release(another.year_of_release),duration(another.duration),rating(another.rating){
    //std::cout<<"Copy constructor called :)"<<std::endl;
    ++movieCount;
}

Movie& Movie::operator=(const Movie &another) {
    if (this != &another) { //for not making useless assignments
        movieID = another.movieID;
        title = another.title;
        year_of_release = another.year_of_release;
        duration = another.duration;
        rating = another.rating;
        //std::cout<<"Assign copy constructor called :)"<<std::endl;

    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "+----------------------------------------+\n";
    os << "|             MOVIE DETAILS              |\n";
    os << "+----------------------------------------+\n";

    os << " 🆔 MOVIE ID     : " << movie.movieID << "\n";
    os << " 🎬 MOVIE TITLE  : " << movie.title << "\n";
    os << " 📅 RELEASE YEAR: " << movie.year_of_release << "\n";
    os << " ⏳ DURATION     : " << movie.duration << " min\n";
    os << " ⭐ RATING       : " << movie.rating << "/10🌟\n";
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
    // if(movie.year_of_release < 1800 || movie.year_of_release > 2030) {
    //     throw Exceptions("Year of release is out of range!");
    // }
    // if (movie.duration < 1 || movie.duration > 10000) {
    //     throw Exceptions("Duration is out of range!");
    // }
    // if (movie.rating < 0 || movie.rating > 10) {
    //     throw Exceptions("Rating is out of range!");
    // }

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

// bool operator==(const Movie &movie1, const Movie &movie2) {
//     std::cout << "friend overloaded operator used :)" << std::endl;
//     return movie1.getTitle() == movie2.getTitle();
// }
bool Movie::operator==(const Movie &movie1) const{
    return title == movie1.title;
}

int Movie::getmovieID() const {
    return movieID;
}


void Movie::showMovieInfo() const {
    std::cout << "+----------------------------------------+\n";
    std::cout << "|             MOVIE DETAILS              |\n";
    std::cout << "+----------------------------------------+\n";

    std::cout << " 🎬 MOVIE TITLE : " << title << "\n";
    std::cout << " 📅 RELEASE YEAR: " << year_of_release << "\n";
    std::cout << " ⏳ DURATION    : " << duration << " min\n";
    std::cout << " ⭐ RATING      : " << rating << "/10\n";}
