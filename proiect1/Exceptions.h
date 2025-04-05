//
// Created by andrei-cristea on 4/5/25.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

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



#endif //EXCEPTIONS_H
