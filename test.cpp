/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    
    return;
}

void test_position() {
    // testing Position default constructor here
    Position start_pos;
    Position end_pos;
    cout << "Testing Position::Position() - default constructor" << endl;
    cout << "start_pos, expected output: (1, A), actual output: " << start_pos << endl;
    cout << "end_pos, expected output: (1, A), actual output: " << end_pos << endl;


    // testing Position setters here
    start_pos.set_row(4);
    start_pos.set_col(5);
    Position testcase;
    testcase.set_row(0);
    testcase.set_col(20);
    Position other;
    other.set_row(2);
    other.set_col(4);
    Position moreother;
    moreother.set_row(-5);
    moreother.set_col(8);
    cout << "\nTesting Position::set_row() and Position::set_col()" << endl;
    cout << "start_pos, testcase, other, moreother, expected output: (5, F), (1, H), (3, E), (1, H), actual output: " << start_pos << " " << " " << testcase << " " << " " << other << "  " << moreother << endl;

    //testing Positing int
    cout << "\nTesting Position::Position(int row_in, int col_in)" << endl;
    cout << " Expected output: (5, F), actual output: " << Position(4, 5) << endl;
    cout << " Expected output: (1, H), actual output: " << Position(-4, 10) << endl;
    cout << " Expected output: (1, H), actual output: " << Position(0, 8) << endl;

    //testing Position char
    cout << "\nTesting Position::Position(char row_in, char col_in)";
    cout << " Expected output: (5, F), actual output: " << Position('5', 'F') << endl;
    cout << " Expected output: (6, F), actual output: " << Position('6', 'f') << endl;
    
    // testing Position read
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {
        start_pos.read(input_file);
        end_pos.read(input_file);
        cout << "\nTesting Position::read()\n";
        cout << "start_pos, expected output: (8, B), actual output: " << start_pos << endl;
        cout << "end_pos, expected output: (8, C), actual output: " << end_pos << endl << endl;
    }
    else {
        cout << "\nError opening grid1.txt\n";
    }
    return;
}

void test_ship() {
    //testing default
    Ship test;
    cout << "Testing Ship::Ship() -- default constructor" << endl;
    cout << "test, expected output: (1, A) (1, A), 0 actual: " << test.get_start() << ", " <<  test.get_end() << ", " << test.get_size()  << endl << endl;
    
    
    //testing non-default
    Position start1(2, 8);
    Position end1(0, 8);
    Ship test1(start1, end1);
    Position start10(0, 8);
    Position end10(0, 3);
    Ship test10(start10, end10);
    cout << "Testing Ship::Ship(Position start_in, Position end_in)" << endl;
    cout << "test1, expected outcome: (1, H), (1, H), 3 actual: " << test1.get_start() << ", " <<  test1.get_end() << ", " << test1.get_size() << endl;
    cout << "test10, expected outcome: (1, H), (1, D), 5 actual: " << test10.get_start() << ", " <<  test10.get_end() << ", " << test10.get_size() << endl << endl;
    
    //testing is_horizontal()
    Position start2(0, 0);
    Position end2(0, 3);
    Ship test2(start2, end2);
    cout << "Testing is_horziontal()" << endl;
    cout << "test2, expected outcome: 0, 1 actual: " << test1.is_horizontal() << ", " <<  test2.is_horizontal() << endl << endl;
    
    //testing has_position
    Position pos(0, 1);
    Position start3(0, 3);
    Position end3(0, 0);
    Ship test3(start3, end3);
    Position pos1(1, 0);
    Position start4(3, 0);
    Position end4(0, 0);
    Ship test4(start4, end4);
    cout << "Testing has_position()" << endl;
    cout << "test2, test1, test3, test4, expected outcome: 1, 0, 1, 1 actual: " << test2.has_position(pos) << ", " << test1.has_position(pos) << ", " << test3.has_position(pos) << ", " << test4.has_position(pos1) << endl << endl;
    
    //testing hit()
    Position start11(0, 8);
    Position end11(0, 3);
    Ship test11(start11, end11);
    test11.hit();
    Position start12(8, 1);
    Position end12(6, 1);
    Ship test12(start12, end12);
    test12.hit();
    test12.hit();
    test12.hit();
    cout << "Testing hit()" << endl;
    cout << "test11, expected outcome: 0, 1 actual: "
    << test11.has_sunk() << ", " << test12.has_sunk() << endl << endl;
    
    return;
}

void test_player() {
    //testing default constructor
    Player test;
    cout << "Testing Player::Player() -- default constructor" << endl;
    cout << "test, expected output: " ", 0, 0 actual: " << test.get_name() << ", " <<  test.get_num_ships() << ", " << test.get_remaining_ships() << endl << endl;
    
    //testing other constructor
    string name_val = "Molly";
    Player test1(name_val);
    cout << "Testing Player::Player(string nam_val)" << endl;
    cout << "expected output: Molly actual: " << test1.get_name() << endl << endl;
    
    //testing add_ship()
    Player test2;
    Position start2(3, 0);
    Position end2(5, 0);
    Ship ship(start2, end2);
    test2.add_ship(ship);
    
    Position start3(5, 4);
    Position end3(1, 4);
    Ship ship1(start3, end3);
    test2.add_ship(ship1);
    
    Position start4(0, 4);
    Position end4(0, 7);
    Ship ship2(start4, end4);
    test2.add_ship(ship2);
    
    Position start5(1, 5);
    Position end5(1, 6);
    Ship ship3(start5, end5);
    test2.add_ship(ship3);
    
    Position start6(7, 2);
    Position end6(7, 4);
    Ship ship4(start6, end6);
    test2.add_ship(ship4);
    
    Position start8(3, 0);
    Position end8(5, 0);
    Ship ship6(start8, end8);
    test2.add_ship(ship6);
    
    
    //testing false add
    Position start7(7, 7);
    Position end7(5, 7);
    Ship ship5(start7, end7);
    test2.add_ship(ship5);
    
    
    //testing attack()
    Player test5;
    test5.add_ship(ship);
    test5.add_ship(ship1);
    test5.add_ship(ship2);
    test5.add_ship(ship3);
    test5.add_ship(ship4);
    cout << "Actual grid" << endl;
    test5.print_grid();
    cout << "Expected outcome: same grid (no added ship5), actual:" << endl;
    //false add
    test2.print_grid();
    cout << "Passes test, no ship5" << endl;
    
    Position pos(7, 3);
    Position pos1(5, 4);
    Position pos2(4, 4);
    Position pos3(3, 4);
    Position pos4(2, 4);
    Position pos5(1, 4);
    Position pos6(0, 4);
    Position pos7(7, 3);
    Position pos8(3, 5);
    Position pos9(0, 0);
    Position pos10(7, 7);
    Position pos11(0, 3);
    Position pos12(0, 5);
    Position pos13(0, 6);
    Position pos14(0, 7);
    Position pos15(7, 2);
    Position pos17(7, 4);
    
    Player opponent;
    opponent.attack(test5, pos);
    opponent.attack(test5, pos1);
    opponent.attack(test5, pos2);
    opponent.attack(test5, pos3);
    opponent.attack(test5, pos4);
    opponent.attack(test5, pos5);
    opponent.attack(test5, pos6);
    opponent.attack(test5, pos7);
    opponent.attack(test5, pos8);
    opponent.attack(test5, pos9);
    opponent.attack(test5, pos10);
    opponent.attack(test5, pos11);
    opponent.attack(test5, pos12);
    opponent.attack(test5, pos13);
    opponent.attack(test5, pos14);
    opponent.attack(test5, pos15);
    opponent.attack(test5, pos17);
    
    opponent.print_guess_grid();
    
    Player sasha;
    Position sashaStart(0, 4);
    Position sashaEnd(0, 7);
    Ship sashaShip(sashaStart, sashaEnd);
    sasha.add_ship(sashaShip);
    
    Position sashaStart1(1, 5);
    Position sashaEnd1(1, 6);
    Ship sashaShip1(sashaStart1, sashaEnd1);
    sasha.add_ship(sashaShip1);
    
    sasha.print_grid();
    
    Position pos20(0, 4);
    Position pos21(4, 0);
    
    Player newSasha;
    newSasha.attack(sasha, pos20);
    newSasha.attack(sasha, pos21);
    
    newSasha.print_guess_grid();
    
    //testing load grid()
    Player load_grid;
    string filename = "grid1.txt";
    string badFilename = "notgrid1.txt";
    cout << "Testing load_grid_file() function" << endl;
    cout << "Expected outcome: 1, 0, actual:" << load_grid.load_grid_file(filename) << ", " << load_grid.load_grid_file(badFilename) << endl;
    
    return;
}

void test_game() {
    //testing non default constructor()
    cout << "Printing random grid p1" << endl;
    Player p1;
    Player p2;
    string grid1Bad = "";
    string grid2Bad = "";
    string grid1Good = "grid1.txt";
    string grid2Good = "grid2.txt";
    string grid1Meh = "badstring";
    string grid2Meh = "badstring";
    Game test(p1, grid1Bad, p2, grid2Bad);
    Game test1(p1, grid1Good, p2, grid2Good);
    Game test2(p1, grid1Meh, p2, grid2Meh);
    
    
    //testing getters()
    Game player;
    cout << "Testing getters() functions" << endl;
    player.get_p1();
    player.get_p2();
    string player_name = "molly";
    cout << player.get_move(player_name) << endl;
    
    //testing check_valid_move()
    string move = "1A";
    cout << "valid" << player.check_valid_move(move) << endl;
    string move1 = "1a";
    cout << "valid" << player.check_valid_move(move1) << endl;
    string move2 = "12A";
    cout << "invalid" << player.check_valid_move(move2) << endl;
    string move3 = "8H";
    cout << "valid" << player.check_valid_move(move3) << endl;
    string move4 = "4L";
    cout << "invalid" << player.check_valid_move(move4) << endl;
    string move5 = "4";
    cout << "invalid" << player.check_valid_move(move5) << endl;
    
    char difficulty = 'S';
    Player p1Start;
    Player p2Start;
    string startStringGrid1 = "grid1.txt";
    string startStringGrid2 = "grid2.txt";
    Game startTest(p1Start, startStringGrid1, p2Start, startStringGrid2);
    Player p1New = startTest.get_p2();
    Player p2New = startTest.get_p2();
    Player p1BetterNew("molly");
    Player p2BetterNew("CPU");
    startTest.get_move(p1BetterNew.get_name());
    startTest.get_move(p2BetterNew.get_name());
    int notRounds = 4;
    startTest.start(difficulty, notRounds);
    return;
}
