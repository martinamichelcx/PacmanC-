#pragma once
#include"board.h"
#include<SFML/Graphics.hpp>
class fruits
{
private:
	sf::Texture texture;
	sf::Sprite shape; 
	int Row;
	int Col;
public:
	fruits(int fruit, int row, int col);
	void drawfruits(RenderWindow& window);
	Sprite getShape();
};

