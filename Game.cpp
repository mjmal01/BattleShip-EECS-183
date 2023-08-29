/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
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

#include "Game.h"


Game::Game() {
    Player p1;
    Player p2;
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    bool correctP1 = p1.load_grid_file(grid1);
    bool correctP2 = p2.load_grid_file(grid2);
    if ((grid1 == "") || (!(correctP1))) {
        generate_random_grid(p1);
        cout << "Generating random grid for " << p1.get_name() << endl;
    }
    if ((grid2 == "") || (!(correctP2))) {
        generate_random_grid(p2);
        cout << "Generating random grid for " << p2.get_name() << endl;
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    cout << player_name << " enter your move: ";
    string input;
    cin >> input;
    return input;
}

bool Game::check_valid_move(string move) {
    if (move.length() != 2) {
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    
    char row = move.at(0);
    char col = move.at(1);
    
    if (row < '1' || row > '8') {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }
    col = toupper(col);
    if (col < 'A' || col > 'H') {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }
    else {
        return true;
    }
}

void Game::start(char difficulty, int max_num_rounds) {
    int num_rounds = 0;
    while ((num_rounds < max_num_rounds)) {
        string newString = get_move(p1.get_name());
        cout << endl;
        while (!(check_valid_move(newString))) {
            newString = get_move(p1.get_name());
            cout << endl;
        }
        char row = newString.at(0);
        char col = newString.at(1);
        Position pos(row, col);
        p1.attack(p2, pos);
        num_rounds++;
        
        bool p1Win = p2.destroyed();
        bool p2Win = p1.destroyed();
        
        if ((!p1Win) && (!p2Win)) {
            opponent_make_move(difficulty);
        }
        
        cout << "Your grid" << endl;
        p1.print_grid();
        cout << "CPU's grid" << endl;
        p1.print_guess_grid();
        
        if (p2Win) {
            cout << "Game over, winner is " << p2.get_name() << " in " << num_rounds << " rounds" << endl;
            break;
        }
        if (p1Win) {
            cout << "Game over, winner is " << p1.get_name() << " in " << num_rounds << " rounds" << endl;
            break;
        }
        if (num_rounds == max_num_rounds) {
            cout << "Game over, winner is no one in " << num_rounds << " rounds" << endl;
            break;
        }
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

