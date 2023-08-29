/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * <#Name#>
 * <#Uniqname#>
 *
 * Project 4: Battleship
 *
 * <#description#>
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int row = 0; row < MAX_GRID_SIZE; row++) {
        for (int col = 0; col < MAX_GRID_SIZE; col++) {
            grid[row][col] = EMPTY_LETTER;
        }
    }
    for (int guessrow = 0; guessrow < MAX_GRID_SIZE; ++guessrow) {
        for (int guesscol = 0; guesscol < MAX_GRID_SIZE; ++guesscol) {
            guess_grid[guessrow][guesscol] = EMPTY_LETTER;
            }
        }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    }
    else {
        ships[num_ships] = ship;
        num_ships++;
        remaining_ships++;
        
        if (ship.is_horizontal()) {
            if (ship.get_start().get_col() < ship.get_end().get_col()) {
                for (int i = ship.get_start().get_col(); i <= ship.get_end().get_col(); i++) {
                    grid[ship.get_start().get_row()][i] = SHIP_LETTER;
                }
            }
            else if (ship.get_start().get_col() >= ship.get_end().get_col()) {
                for (int i = ship.get_end().get_col(); i <= ship.get_start().get_col(); i++) {
                    grid[ship.get_start().get_row()][i] = SHIP_LETTER;
                }
            }
        }
        
        if (!ship.is_horizontal()) {
            if (ship.get_start().get_row() < ship.get_end().get_row()) {
                for (int i = ship.get_start().get_row(); i <= ship.get_end().get_row(); i++) {
                    grid[i][ship.get_start().get_col()] = SHIP_LETTER;
                }
            }
            else if (ship.get_start().get_row() >= ship.get_end().get_row()) {
                for (int i = ship.get_end().get_row(); i <= ship.get_start().get_row(); i++) {
                    grid[i][ship.get_start().get_col()] = SHIP_LETTER;
                }
            }
        }
    }
    return;
}

void Player::attack(Player &opponent, Position pos) {
    if (opponent.grid[pos.get_row()][pos.get_col()] == SHIP_LETTER) {
        opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
            for (int i = 0; i < opponent.num_ships; i++) {
                if (opponent.ships[i].has_position(pos)) {
                    opponent.ships[i].hit();
                    cout << name << " " << pos << " hit" << endl;
                    if (opponent.ships[i].has_sunk()) {
                        announce_ship_sunk(opponent.ships[i].get_size());
                        opponent.remaining_ships--;
                    }
                }
            }
        }
        else {
            opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
            guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
            cout << name << " " << pos << " miss" << endl;
        }
    return;
}

void Player::announce_ship_sunk(int size) {
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer" << endl;
    }
    else if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine" << endl;
    }
    else if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship" << endl;
    }
    else if (size == 5) {
        cout << "Congratulations " << name << "! You sunk a Carrier" << endl;
    }
    return;
}

bool Player::load_grid_file(string filename) {
    ifstream grid_file;
    grid_file.open(filename);
    
    if (!grid_file.is_open()) {
        return false;
    }

    Position start;
    Position end;
    grid_file >> start;
    grid_file >> end;

    while (!grid_file.fail()) {
        Ship ship(start, end);
        add_ship(ship);
        
        grid_file >> start;
        grid_file >> end;
    }
    return true;
}




bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    return false;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
