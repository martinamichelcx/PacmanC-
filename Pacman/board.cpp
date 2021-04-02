#include "board.h"

Board::Board()
{
    verticalWall.loadFromFile("verticalWall.png");
    horizontalWall.loadFromFile("Wall.png");
    cornerLeftUp.loadFromFile("cornerLeftUp.png");
    cornerLeftDown.loadFromFile("cornerLeftDown.png");
    cornerRightUp.loadFromFile("cornerRightUp.png");
    cornerRightDown.loadFromFile("cornerRightDown.png");
    rodTexture.loadFromFile("rod.jpeg");
    powerP.loadFromFile("pPellet.png");


    //scoreT.setPosition(0, 0);
    //scoreT.setCharacterSize(25);


    numOfEatenPellets = 0;



    loseTexture.loadFromFile("lose.png");
    lose.setSize(Vector2f(875, 484));
    lose.setTexture(&loseTexture);
    lose.setPosition(0, 309);


    int arr[ROWS][COLUMNS];
    ifstream inputFile;
    inputFile.open("Board.txt");
    if (inputFile.is_open())
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (!inputFile.eof())
                    inputFile >> arr[i][j];
            }
        }
    }
    inputFile.close();


    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
        {
            cell[i][j].r.setPosition(25 + 25 * j, 25 + 25 * i);
            cell[i][j].r.setSize(Vector2f(25, 25));

            if (arr[i][j] == 16)
            {
                cell[i][j].r.setTexture(&verticalWall);
                cell[i][j].t = rock;
            }
            else if (arr[i][j] == 5)
            {
                cell[i][j].r.setPosition(25 + 25 * j, 25 + (25 * i + 7));
                cell[i][j].r.setSize(Vector2f(25, 10));
                cell[i][j].r.setTexture(&rodTexture);
                cell[i][j].t = house;
            }
            else if (arr[i][j] == 11)
            {
                cell[i][j].r.setTexture(&cornerLeftUp);
                cell[i][j].t = rock;
            }
            else if (arr[i][j] == 12)
            {
                cell[i][j].r.setTexture(&cornerLeftDown);
                cell[i][j].t = rock;
            }
            else if (arr[i][j] == 13)
            {
                cell[i][j].r.setTexture(&cornerRightUp);
                cell[i][j].t = rock;
            }
            else if (arr[i][j] == 14)
            {
                cell[i][j].r.setTexture(&cornerRightDown);
                cell[i][j].t = rock;
            }
            else if (arr[i][j] == 15)
            {
                cell[i][j].r.setTexture(&horizontalWall);
                cell[i][j].t = rock;
            }

            else if (arr[i][j] == 9)
            {
                cell[i][j].r.setPosition(25 + (25 * j), 25 + (25 * i));
                cell[i][j].r.setSize(Vector2f(25, 25));
                cell[i][j].r.setTexture(&powerP);
                cell[i][j].r.setFillColor(Color::White);
                cell[i][j].t = power;
            }
            else if (arr[i][j] == 0)
            {
                cell[i][j].r.setPosition(25 + ((25 * j) + 10), 25 + ((25 * i) + 10));
                cell[i][j].r.setSize(Vector2f(6, 6));
                cell[i][j].r.setFillColor(Color::White);
                cell[i][j].t = pellet;
            }
            else if (arr[i][j] == 98)
            {
                cell[i][j].r.setFillColor(Color::Black);
                cell[i][j].t = portalR;
            }
            else if (arr[i][j] == 99)
            {
                cell[i][j].r.setFillColor(Color::Black);
                cell[i][j].t = portalL;
            }
            else if (arr[i][j] == 4)
            {
                cell[i][j].r.setFillColor(Color::Black);
                cell[i][j].t = house;
            }
            else
            {
                cell[i][j].r.setFillColor(Color::Black);
                cell[i][j].t = rock;
            }
        }
}




void Board::drawBoard(RenderWindow& window)
{
    // window.draw(scoreT);

    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COLUMNS; j++)
        {
            window.draw(cell[i][j].r);
        }
    }
}




tile_type Board::getType(int rows, int cols)
{
    return cell[rows][cols].t;
}




void Board::eaten(int rows, int cols)
{
    cell[rows][cols].t = tile_type::empty;
    cell[rows][cols].r.setFillColor(Color::Black);
    numOfEatenPellets++;

}



int Board::getEatenPellets()
{
    return numOfEatenPellets;
}









void Board::displayLose(RenderWindow& window)
{
    window.clear(Color::Black);
    window.draw(lose);
}
Board::~Board()
{};
