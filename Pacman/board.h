#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
using namespace std;
using namespace sf;

const int ROWS = 37, COLUMNS = 33;
enum tile_type { empty, pellet, power, rock, portalL, portalR, house };
struct tile
{
    RectangleShape r;
    tile_type t;
};
class Board
{
private:
    Texture  rodTexture, cornerLeftUp, cornerLeftDown, cornerRightUp, cornerRightDown, horizontalWall, verticalWall,
        powerP, winTexture, loseTexture;
    tile cell[ROWS][COLUMNS];
    int numOfEatenPellets;
    RectangleShape lose;


public:
    Board();
    tile_type getType(int rows, int cols);
    void eaten(int rows, int cols);
    void drawBoard(RenderWindow& window);
    int getEatenPellets();
    void displayLose(RenderWindow& window);
    ~Board();
};