/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * <#Name#>
 * <#Uniqname#>
 *
 * Project 4: Battleship
 *
 * <#description#>
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}


Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}


Position::Position(char row_in, char col_in) {
    row = (row_in) - '1';
    col_in = toupper(col_in);
    col = col_in - 'A';
    row = check_range(row);
    col = check_range(col);
}


int Position::get_row() {
    return row;
}


void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}


int Position::get_col() {
    return col;
}


void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}


void Position::read(istream &is) {
    char alpha;
    char placeholder;
    is >> row;
    if (is.fail()) {
        is.clear();
        is >> placeholder;
        is >> row;
        is >> placeholder;
        is >> alpha;
        is >> placeholder;
    }
    else {
        is >> alpha;
    }
    col = toupper(alpha) - 'A';
    col = check_range(col);
    row--;
    row = check_range(row);
    return;
}


void Position::write(ostream &os) {
    int newRow = row + 1;
    char newAlpha = col + 'A';
    os << "(" << newRow << ", " << newAlpha << ")";
    return;
}


int Position::check_range(int val) {
    if (val > 0 && val < MAX_GRID_SIZE) {
        return val;
    }
    else if (val <= 0) {
       return 0;
    }
    else if (val >= MAX_GRID_SIZE) {
        return MAX_GRID_SIZE - 1;
    }
    return 0;
}


// Your code goes above this line.
// Don't change the implementations below!
istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}


ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}
