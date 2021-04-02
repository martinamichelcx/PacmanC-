#include"player.h"

Pacman::Pacman(int initialRow, int initialColumn)
{
    currentRow = initialRow;
    currentColumn = initialColumn;
    spriteShapeUp = IntRect(158, 0, 33, 33);
    spriteShapeDown = IntRect(222, 0, 33, 33);
    spriteShapeLeft = IntRect(127, 0, 33, 33);
    spriteShapeRight = IntRect(33, 0, 33, 33);
    shape.setPosition(25 + 25 * initialColumn, 25 + 25 * initialRow);
    texture.loadFromFile("sprite.png");
    shape.setTexture(texture);
    shape.setTextureRect(spriteShapeRight);
    numOfLives = 3;
    score = -10;
    highScore = 0;
}




void Pacman::move(char direction, tile_type t, bool wait, Clock pcmn)
{
    if (wait)
        return;
    else
    {
        if (direction == 'U' || direction == 'u')
        {
            if (t != rock && t != house)
            {
                currentRow--;
                shape.move(0, -25);
                animationUp(pcmn);
            }
        }
        else if (direction == 'D' || direction == 'd')
        {
            if (t != rock && t != house)
            {
                currentRow++;
                shape.move(0, 25);
                animationDown(pcmn);
            }
        }
        else if (direction == 'R' || direction == 'r')
        {
            if (t == portalR)
            {
                shape.setPosition(25, 25 + currentRow * 25);
                currentColumn = 0;
                animationRight(pcmn);
            }
            if (t != rock && t != house)
            {
                currentColumn++;
                shape.move(25, 0);
                animationRight(pcmn);
            }

        }
        else if (direction == 'L' || direction == 'l')
        {
            if (t == portalL)
            {
                shape.setPosition(25 + 25 * (COLUMNS - 1), 25 + currentRow * 25);
                currentColumn = COLUMNS - 1;
                animationLeft(pcmn);
            }
            if (t != rock && t != house)
            {
                currentColumn--;
                shape.move(-25, 0);
                animationLeft(pcmn);
            }
        }
    }
}




void Pacman::drawOnWindow(RenderWindow& window)
{
    window.draw(shape);
}




int Pacman::getRow()
{
    return currentRow;
}




int Pacman::getColumn()
{
    return currentColumn;
}




void Pacman::setDirection(char d)
{
    direction = d;
}




char Pacman::getDirection()
{
    return direction;
}




void Pacman::animationUp(Clock c)
{
    if (spriteShapeUp.left == 191)
        spriteShapeUp.left = 158;
    else
        spriteShapeUp.left += 33;

    shape.setTextureRect(spriteShapeUp);
    c.restart();
}




void Pacman::animationDown(Clock c)
{
    if (spriteShapeDown.left == 255)
        spriteShapeDown.left = 222;
    else
        spriteShapeDown.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeDown);
}




void Pacman::animationLeft(Clock c)
{
    if (spriteShapeLeft.left == 127)
        spriteShapeLeft.left = 94;
    else
        spriteShapeLeft.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeLeft);
}




void Pacman::animationRight(Clock c)
{
    if (spriteShapeRight.left == 33)
        spriteShapeRight.left = 0;
    else
        spriteShapeRight.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeRight);
}




Sprite Pacman::getShape()
{
    return shape;
}




void Pacman::respawn()
{
    shape.setPosition(25 + 25 * 16, 25 + 25 * 27);
    currentRow = 27;
    currentColumn = 16;
    shape.setTexture(texture);
    shape.setTextureRect(IntRect(33, 0, 33, 33));
    numOfLives--;
}




int Pacman::getLives()
{
    return numOfLives;
}




void Pacman::setScore(int s)
{
    score = s;
}




void Pacman::setHighScore(int hs)
{
    highScore = hs;
}




int Pacman::getScore()
{
    return score;
}




int Pacman::getHighScore()
{
    return highScore;
}
