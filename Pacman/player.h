#include"board.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
using namespace std;
using namespace sf;

class Pacman
{
private:
    int currentRow;
    int currentColumn;
    Sprite shape;
    Texture texture;
    char direction;
    IntRect spriteShapeUp, spriteShapeDown, spriteShapeLeft, spriteShapeRight;
    int numOfLives, score, highScore;


public:
    Pacman() {};
    Pacman(int initialRow, int initialColumn);
    void move(char direction, tile_type t, bool wait, Clock pcmn);
    void drawOnWindow(RenderWindow& window);
    int getRow();
    int getColumn();
    void setRow(int x);
    void setCols(int x);
    char getDirection();
    void setDirection(char d);
    void animationUp(Clock c);
    void animationDown(Clock c);
    void animationLeft(Clock c);
    void animationRight(Clock c);
    Sprite getShape();
    void respawn();
    int getLives();
    void setScore(int s);
    void setHighScore(int hs);
    int getScore();
    int getHighScore();
    ~Pacman() {};
};