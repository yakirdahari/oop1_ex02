#pragma once

#define PACMAN 'a'
#define SUPERPACMAN '@'
#define GHOST '&'
#define WALL '#'
#define DOOR 'D'
#define KEY '%'
#define COOKIE '*'
#define GIFT '$'

struct Location
{
    explicit Location(int col, int row) : col(col), row(row) {}
    int row;
    int col;
};
