#include "fruits.h"
fruits::fruits(int fruit, int row, int col)
{

    Row = row;
    Col = col;
    if (fruit == 0)
    {
        shape.setPosition(25 + 25 * Col, 25 + 25 * Row);
        shape.setTextureRect(IntRect(1, 1, 27, 25));
        texture.loadFromFile("cherry.png");
        shape.setTexture(texture);
    }

    if (fruit == 1)
    {

        shape.setTextureRect(IntRect(1, 1, 27, 25));
        texture.loadFromFile("orange.png");
        shape.setTexture(texture);
        shape.setPosition(25 + 25 * Col, 25 + 25 * Row);
    }
}
void fruits::drawfruits(RenderWindow& window)
{
    window.draw(shape);
}
Sprite fruits::getShape()
{
    return shape;
}
