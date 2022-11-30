#pragma once

// basic game definitions
#define PACMAN 'a'
#define SUPERPACMAN '@'
#define GHOST '&'
#define WALL '#'
#define DOOR 'D'
#define KEY '%'
#define COOKIE '*'
#define GIFT '$'

//directions to move ghost
#define TOP_LEFT 1
#define TOP_RIGHT 2
#define BOTTOM_LEFT 3
#define BOTTOM_RIGHT 4

struct Location
{
    explicit Location(int col, int row) : col(col), row(row) {}
    int row;
    int col;

    bool operator == (const Location& other) const
    {
        if (this->col == other.col && this->row == other.row)
        {
            return true;
        }
        return false;
    }
};