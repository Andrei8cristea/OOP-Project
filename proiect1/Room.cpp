//
// Created by andrei-cristea on 4/5/25.
//

#include "Room.h"
#include "Exceptions.h"
#include <iostream>

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
            throw Exceptions("We're sorry, this seat is already booked...\n\n");
        }
        else{
            board[row_nr-1][col_nr-1] = '#';
        }
    }

    else {
        std::cout << "Invalid seat position!"<<"\n";
    }
}

int Room::getRoomId() const {
    return room_id;
}