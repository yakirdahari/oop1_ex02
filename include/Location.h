#pragma once

#define LIFE 3
#define PACMAN 'a'
#define SUPERPACMAN '@'
#define ENEMY '&'
#define WALL '#'
#define DOOR 'D'
#define KEY '%'
#define COOKIE '*'
#define GIFT '$'

struct Location
{
    explicit Location(int row, int col) : row(row), col(col) {}
    int row;
    int col;
};
