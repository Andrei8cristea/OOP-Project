//
// Created by andrei-cristea on 4/6/25.
//

#ifndef TEMPLATECLASSES_H
#define TEMPLATECLASSES_H

template <typename T>
class Repository {
private:
    std::list<T> list;
public:
    void addElement(const T& element) {
        list.push_back(element);
    }
    void deleteElement(const T& element) {
        list.remove(element);
    }
    void displayMovies() const{
        std::cout << "Showing available movies..." <<std::endl;
        std::cout << "The list with all the movies is the following:\n" << std::endl;
        for (const T& movie : list) {
            std::cout << movie << std::endl;
        }
    }

    void displayResevations() const {
        std::cout << "The list with all the reservations is the following:\n" << std::endl;

        auto printReservations = [](const T& ticket) {
            std::cout << ticket << std::endl;
        };
        std::for_each(list.begin(), list.end(), printReservations);


        // for (const S& reservation : reservations_list) {
        //     std::cout << reservation << std::endl;
        // }
    }
        //getter for the repository dates
        std::list<T>& getRepositoryDates() {
            return list;
        }

    const std::list<MovieDate>& getRepositoryDates() const { return list; }

        void displayRepositoryDates() const {
            std::cout << "The list with all the repository dates is the following:" << std::endl;
        }

};



// template <typename S>
// class Reservations {
// private:
//     std::list<S> reservations_list;
// public:
//     // void addResevation(const S& ticket) {
//     //     reservations_list.push_back(ticket);
//     // }
//     // void deleteResevation(const S& ticket) {
//     //     reservations_list.remove(ticket);
//     // }
//
// };
//
// template <typename U>
// class RepositoryDates {
// private:
//     std::list<U> repository_dates;
// public:
//     // void addRepositoryDate(const U& dates) {
//     //     repository_dates.push_back(dates);
//     // }
//     // void deleteRepositoryDate(const U& dates) {
//     //     repository_dates.remove(dates);
//     // }
//
//
//
//
// };









#endif //TEMPLATECLASSES_H
