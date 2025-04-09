//
// Created by andrei-cristea on 4/9/25.
//

#ifndef TICKET_H
#define TICKET_H
#include "MovieDate.h"
#include "Room.h"

//multiple inheritance
class Ticket: public MovieDate, public Room {
private:
    int ticketID;
    static int ticketCount;
    int seatRow;
    int seatColumn;


public:
    Ticket(const MovieDate& md, const Room& r, int seatRow, int seatColumn);

    void printTicket() const;

    //getter for ticketID
    int getTicketID() const {
        return ticketID;
    }

};


#endif //TICKET_H
