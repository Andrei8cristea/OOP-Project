//
// Created by andrei-cristea on 4/9/25.
//

#include "Ticket.h"
#include "MovieDate.h"


#include <iostream>


Ticket::Ticket(const MovieDate& md, const Room& r, int seatRow, int seatColumn)
    : ticketID(ticketCount++),MovieDate(md), Room(r), seatRow(seatRow), seatColumn(seatColumn){}

void Ticket::printTicket() const {
//     Seat Row: 🪑🔢 📏 📌 🚪
//
// Seat Number: 🔢 🎟️ #️⃣ 🏷️ 🔠

    std::cout << "+----------------------------------------+\n";
    std::cout << "|                 TICKET                 |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << "Reserved seat info:\n";
    std::cout<< "🪑 SEAT ROW : " << seatRow << std::endl;
    std::cout<< "🔢 SEAT COLUMN : " << seatColumn << std::endl;
    this->showMovieDate();

    //std::cout << "Reserved Seat: Row "<< seatRow<<" Column "<<seatColumn<<std::endl;
    //std::cout<<"......\n"<<std::endl;

}








