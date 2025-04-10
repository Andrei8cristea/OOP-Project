//
// Created by andrei-cristea on 4/5/25.
//

#ifndef ROOM_H
#define ROOM_H
#include <vector>

static int id2 = 0;

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
    void freeSeat(int row_nr, int col_nr);

    //getter for room_id
    int getRoomId() const;
};



#endif //ROOM_H
