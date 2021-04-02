#include"ghosts.h"

Ghosts::Ghosts(int initialRow, int initialColumn, int which)
{

    currentRow = initialRow;
    currentColumn = initialColumn;
    color = which;
    inky = IntRect(142.5, 164, 27, 25);
    blinky = IntRect(142.5, 47, 27, 25);
    clyde = IntRect(142.5, 128, 27, 25);
    pinky = IntRect(142.5, 84, 27, 25);
    blue = IntRect(0, 1, 27, 25);
    if (which == 0)
    {
        shape.setTextureRect(inky);
    }
    else if (which == 1)
    {
        shape.setTextureRect(blinky);
    }
    else if (which == 2)
    {
        shape.setTextureRect(pinky);
    }
    else if (which == 3)
    {
        shape.setTextureRect(clyde);
    }

    shape.setPosition(25 + 25 * initialColumn, 25 + 25 * initialRow);
    texture.loadFromFile("spritesheet2.png");
    shape.setTexture(texture);
    power = false;

    //shape.setSize(Vector2f(25, 25));
}




void Ghosts::drawGhost(RenderWindow& window)
{
    window.draw(shape);
}


char Ghosts::getDirection()
{
    return direction;
}




void Ghosts::setDirection(char d)
{
    direction = d;
}


void Ghosts::move(int direction, tile_type t, bool wait)
{
    if (wait)
    {
        return;
    }
    if (direction == 'U' )
    {       
        inky.left = 33;
        pinky.left = 33;
        blinky.left = 33;
        clyde.left = 33;
        if (color == 0)
        {
            shape.setTextureRect(inky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 1)
        {
            shape.setTextureRect(pinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 2)
        {
            shape.setTextureRect(blinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 3)
        {
            shape.setTextureRect(clyde);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }

        if (t != tile_type::rock)
        {
            currentRow--;
            shape.move(0, -25);
        }
    }
    else if (direction == 'D')
    {
        inky.left = 3 * 29;
        pinky.left = 3 * 20;
        blinky.left = 3 * 29;
        clyde.left = 3 * 29;
        if (color == 0)
        {
            shape.setTextureRect(inky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 1)
        {
            shape.setTextureRect(pinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 2)
        {
            shape.setTextureRect(blinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 3)
        {
            shape.setTextureRect(clyde);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (t != tile_type::rock)
        {
            currentRow++;
            shape.move(0, 25);
        }
    }
    else if (direction == 'R')
    {
        inky.left = 6 * 32.5;
        pinky.left = 6 * 32.5;
        blinky.left = 6 * 32.5;
        clyde.left = 6 * 32.5;
        if (color == 0)
        {
            shape.setTextureRect(inky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 1)
        {
            shape.setTextureRect(pinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 2)
        {
            shape.setTextureRect(blinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 3)
        {
            shape.setTextureRect(clyde);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (t == tile_type::portalR)
        {
            shape.setPosition(25, 25 + currentRow * 25);
            currentColumn = 0;
        }

        if (t != tile_type::rock)
        {
            currentColumn++;
            shape.move(25, 0);
        }
    }
    else if (direction == 'L')
    {
        inky.left = 4 * 35;
        pinky.left = 4 * 35;
        blinky.left = 4 * 35;
        clyde.left = 4 * 35;

        if (color == 0)
        {
            shape.setTextureRect(inky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 1)
        {
            shape.setTextureRect(pinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 2)
        {
            shape.setTextureRect(blinky);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (color == 3)
        {
            shape.setTextureRect(clyde);
            if (power == true)
            {
                texture.loadFromFile("deadghost.png");
                shape.setTextureRect(blue);
            }
        }
        if (t == tile_type::portalL)
        {
            shape.setPosition(25 + 25 * (COLUMNS - 1), 25 + currentRow * 25);
            currentColumn = COLUMNS - 1;
        }
        if (t != rock)
        {
            currentColumn--;
            shape.move(-25, 0);
        }
    }
}




int Ghosts::getRow()
{
    return currentRow;
}




int Ghosts::getColumn()
{
    return currentColumn;
}

int Ghosts::get_row0()
{
    return Row0;
}
int Ghosts::get_col0()
{
    return Col0;
}

void Ghosts::reset(int initialRow, int initialColumn)
{
    power = false;
    texture.loadFromFile("spritesheet2.png");
    if (color == 0)
    {
        shape.setTextureRect(inky);
    }
    else if (color == 1)
    {
        shape.setTextureRect(blinky);
    }
    else if (color == 2)
    {
        shape.setTextureRect(pinky);
    }
    else if (color == 3)
    {
        shape.setTextureRect(clyde);
    }
    currentRow = initialRow;
    currentColumn = initialColumn;
    shape.setPosition(25 + 25 * currentColumn, 25 + 25 * currentRow);
    return;
}




Sprite Ghosts::getShape()
{
    return shape;
}

void Ghosts::set_power(bool p)
{
    power = p;
    if(power==false)
        texture.loadFromFile("spritesheet2.png");

}
bool Ghosts::get_power()
{
    return power;
}

void Ghosts::get_opposite()
{
    if (direction == 'u')
        direction = 'd';
    if (direction == 'd')
        direction = 'u';
    if (direction == 'l')
        direction = 'r';
    if (direction == 'r')
        direction = 'l';
}

Ghosts::~Ghosts() {};