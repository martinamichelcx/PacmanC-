#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "board.h"
#include"player.h"
#include"ghosts.h"
#include <stdexcept>
#include<fstream>
#include "BFS.h"
#include "BFS2.h"
#include "BFS4.h"
#include"BFS3.h"
#include"fruits.h"

int main()
{
    Event e;
    RenderWindow window;
    Board b;
    srand(unsigned(time(NULL)));
    bool p = true;
    bool drawReady = true;
    bool wait = true;
    bool power = false;
    bool bonus1 = true;
    bool bonus2 = true;

    int arr[37][33];
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
                if (arr[i][j] == 5 || arr[i][j] == 4)
                    arr[i][j] = 0;
            }
        }
    }
    inputFile.close();


    Sound pacmanEating, pacmanIntro, pacmanDie, eatFruit, eatGhost;
    SoundBuffer eatBuffer, introBuffer, dieBuffer, fruitBuffer, ghostBuffer;
    eatBuffer.loadFromFile("pacman_chomp.ogg");
    pacmanEating.setBuffer(eatBuffer);
    introBuffer.loadFromFile("pacmanIntro.ogg");
    pacmanIntro.setBuffer(introBuffer);
    dieBuffer.loadFromFile("pacman_death.ogg");
    pacmanDie.setBuffer(dieBuffer);
    fruitBuffer.loadFromFile("pacman_eatfruit.ogg");
    eatFruit.setBuffer(fruitBuffer);
    ghostBuffer.loadFromFile("pacman_eatghost.ogg");
    eatGhost.setBuffer(ghostBuffer);

    Pacman player(27, 16);
    Ghosts g1(13, 16, 0);
    Ghosts g2(16, 16, 1);
    Ghosts g3(16, 15, 2);
    Ghosts g4(16, 17, 3);
    fruits cherry(0, 5, 16);
    fruits orange(1, 19, 16);

    window.create(VideoMode(875, 1025), "Pacman Game");

    Text scoreT, readyT, numLives, win;
    Font scoreF;
    scoreF.loadFromFile("font.ttf");
    scoreT.setFont(scoreF);
    readyT.setFont(scoreF);
    numLives.setFont(scoreF);
    win.setFont(scoreF);

    scoreT.setCharacterSize(25);
    readyT.setCharacterSize(25);
    numLives.setCharacterSize(25);
    win.setCharacterSize(25);
    readyT.setString("READY !");
    win.setString("You Win");
    win.setFillColor(Color::Yellow);
    readyT.setFillColor(Color::Yellow);


    readyT.setPosition(25 + 25 * 13, 25 + 25 * 19);
    win.setPosition(25 + 25 * 13, 25 + 25 * 19);
    scoreT.setPosition(50, 50 + 25 * 37);
    numLives.setPosition(25 + 25 * 13, 50 + 25 * 37);


    sf::Clock game;
    sf::Clock ghost1;
    sf::Clock ghost2;
    sf::Clock ghost3;
    sf::Clock ghost4;
    sf::Clock powerT;
    sf::Clock pcmn;

    game.restart();
    ghost1.restart();
    ghost2.restart();
    ghost3.restart();
    ghost4.restart();
    pcmn.restart();
    powerT.restart();

    int blinkySpeed = 250;

    pacmanIntro.play();

    while (window.isOpen())
    {
        int x1;
        int x2;
        int x3;
        int x4;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            //The next part removes ready screen and unpause the game when the spacebar is pressed.
            else if (e.key.code == Keyboard::Space)
            {
                wait = false;
                drawReady = false;
                game.restart();
            }
            //Setting pacman's direction based on keyboard
            else if (e.type == Event::KeyPressed && wait == false)
            {
                switch (e.key.code)
                {
                case Keyboard::Up:
                    if (b.getType(player.getRow() - 1, player.getColumn()) != rock && b.getType(player.getRow() - 1, player.getColumn()) != house)
                        player.setDirection('U');
                    break;

                case Keyboard::Down:
                    if (b.getType(player.getRow() + 1, player.getColumn()) != rock && b.getType(player.getRow() + 1, player.getColumn()) != house)
                        player.setDirection('D');
                    break;
                case Keyboard::Right:
                    if (b.getType(player.getRow(), player.getColumn() + 1) != rock && b.getType(player.getRow(), player.getColumn() + 1) != house)
                        player.setDirection('R');
                    break;
                case Keyboard::Left:
                    if (b.getType(player.getRow(), player.getColumn() - 1) != rock && b.getType(player.getRow(), player.getColumn() - 1) != house)
                        player.setDirection('L');
                    break;
                }
            }
        }

        //Checks the next direction before setting the direction in the move function to avoid collisions with walls
         //The clock also adjust pacman's speed so it keeps moving instead of moving one step at a time
        if (pcmn.getElapsedTime().asMilliseconds() > 125)
        {
            switch (player.getDirection())
            {
            case('U'):
            {
                player.move('U', b.getType(player.getRow() - 1, player.getColumn()), wait, pcmn);
                break;
            }
            case('D'):
            {
                player.move('D', b.getType(player.getRow() + 1, player.getColumn()), wait, pcmn);
                break;
            }
            case('L'):
            {
                player.move('L', b.getType(player.getRow(), player.getColumn() - 1), wait, pcmn);
                break;
            }
            case('R'):
            {
                player.move('R', b.getType(player.getRow(), player.getColumn() + 1), wait, pcmn);
                break;
            }

            }
            pcmn.restart();
        }

        //this function adds score for when pacman eats a pellet and plays the eating music

        if (b.getType(player.getRow(), player.getColumn()) == tile_type::pellet)
        {
            b.eaten(player.getRow(), player.getColumn());
            pacmanEating.play();
            player.setScore(player.getScore() + 10);
        }

        // when pacman eats a fruit (bonus) if increases the score by 50 and plays fruit eating music
        //it also stops the fruit from getting drawn again

        if (cherry.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
        {
            eatFruit.play();
            player.setScore(player.getScore() + 100);
            bonus1 = false;
        }
        // does the same thing but with the orange fruit

        if (orange.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
        {
            eatFruit.play();
            player.setScore(player.getScore() + 100);
            bonus2 = false;
        }

        //this function turns on power mode when pacman eats a power pellet, and increases the score for each one eaten
        //It also resets the power clock to recount starting from 0 to 10 seconds
        if (b.getType(player.getRow(), player.getColumn()) == tile_type::power)
        {
            b.eaten(player.getRow(), player.getColumn());
            pacmanEating.play();
            player.setScore(player.getScore() + 50);
            g1.set_power(true);
            g2.set_power(true);
            g3.set_power(true);
            g4.set_power(true);
            powerT.restart();
        }

        //this function turns off power mode after 10 seconds pass
        if (powerT.getElapsedTime().asMilliseconds() >= 7000)
        {
            g1.set_power(false);
            g2.set_power(false);
            g3.set_power(false);
            g4.set_power(false);
        }

        //this function calls the shortest path to pacman while power mode is off
        if (g1.get_power() == false)
        {
            x1 = bfs(arr, g1.getRow(), g1.getColumn(), player.getRow(), player.getColumn());
        }

        //this function calls the shortest path away from pacman to a corner when power is on
        if (g1.get_power() == true)
        {
            x1 = bfs(arr, g1.getRow(), g1.getColumn(), 1, 1);
        }

        //this function calls the path to pacman for ghost 4 but with 8 steps in between
        if (g4.get_power() == false)
        {
            x4 = bfsv4(arr, g4.getRow(), g4.getColumn(), player.getRow(), player.getColumn());
        }


        //calls the path to a corner when powermode is on
        if (g4.get_power() == true)
        {
            x4 = bfs(arr, g4.getRow(), g4.getColumn(), 1, 31);
        }

        //this function gets pacman's directions and hand them to ghost's two algorithm to chance pacman
        //from 4 steps ahead
        if (g2.get_power() == false)
        {
            switch (player.getDirection())
            {
            case('U'):
            {
                x2 = bfsv2(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn(), 'U');
                break;
            }
            case('D'):
            {             x2 = bfsv2(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn(), 'D');

            break;
            }
            case('L'):
            {
                x2 = bfsv2(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn(), 'L');
                break;
            }
            case('R'):
            {
                x2 = bfsv2(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn(), 'R');
                break;
            }
            default:
                x2 = bfsv2(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn(), 'U');
                break;

            }
        }

        //this function makes ghost 2 go towards a corner with power mode is on
        if (g2.get_power() == true)
        {
            x2 = bfs(arr, g2.getRow(), g2.getColumn(), 35, 1);
        }

        //gets pacman's direction to make ghost 3 go 8 steps behind him to catch him
        if (g3.get_power() == false)
        {
            switch (player.getDirection())
            {
            case('U'):
            {
                x3 = bfsv3(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn(), 'U');
                break;
            }
            case('D'):
            {             x3 = bfsv3(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn(), 'D');

            break;
            }
            case('L'):
            {
                x3 = bfsv3(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn(), 'L');
                break;
            }
            case('R'):
            {
                x3 = bfsv3(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn(), 'R');
                break;
            }
            default:
                x3 = bfsv2(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn(), 'U');
                break;

            }
        }

        //makes ghost 3 go to a corner in power mode
        if (g3.get_power() == true)
        {
            x3 = bfs(arr, g3.getRow(), g3.getColumn(), 35, 31);
        }

        switch (x1)
        {
        case 0:
            if (b.getType(g1.getRow() - 1, g1.getColumn()) != rock && wait == false)
            {
                g1.setDirection('U');
            }
            break;
        case 1:
            if (b.getType(g1.getRow() + 1, g1.getColumn()) != rock && wait == false)
                g1.setDirection('D');
            break;
        case 2:
            if (b.getType(g1.getRow(), g1.getColumn() + 1) != rock && wait == false)
                g1.setDirection('R');
            break;
        case 3:
            if (b.getType(g1.getRow(), g1.getColumn() - 1) != rock && wait == false)
                g1.setDirection('L');
            break;
        }

        //sets ghost 1's movement based on called algorithm and checks the clock as
        //blinky speed increases as the game's time passes.
        if (ghost1.getElapsedTime().asMilliseconds() >= blinkySpeed)
        {
            switch (g1.getDirection())
            {
            case('U'):
            {
                g1.move('U', b.getType(g1.getRow() - 1, g1.getColumn()), wait);
                break;
            }
            case('D'):
            {
                g1.move('D', b.getType(g1.getRow() + 1, g1.getColumn()), wait);
                break;
            }
            case('L'):
            {
                g1.move('L', b.getType(g1.getRow(), g1.getColumn() - 1), wait);
                break;
            }
            case('R'):
            {
                g1.move('R', b.getType(g1.getRow(), g1.getColumn() + 1), wait);
                break;
            }
            }
            ghost1.restart();
        }

        //sets ghost's two directions based on previous algorithm call
        switch (x2)
        {
        case 0:
            if (b.getType(g2.getRow() - 1, g2.getColumn()) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g2.setDirection('U');
            break;
        case 1:
            if (b.getType(g2.getRow() + 1, g2.getColumn()) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g2.setDirection('D');
            break;
        case 2:
            if (b.getType(g2.getRow(), g2.getColumn() + 1) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g2.setDirection('R');
            break;
        case 3:
            if (b.getType(g2.getRow(), g2.getColumn() - 1) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g2.setDirection('L');
            break;
        }

        //this function gives movement orders to ghost after a certain time pass to slow ghost down
        if (ghost2.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g2.getDirection())
            {
            case('U'):
            {
                g2.move('U', b.getType(g2.getRow() - 1, g2.getColumn()), wait);
                break;
            }
            case('D'):
            {
                g2.move('D', b.getType(g2.getRow() + 1, g2.getColumn()), wait);
                break;
            }
            case('L'):
            {
                g2.move('L', b.getType(g2.getRow(), g2.getColumn() - 1), wait);
                break;
            }
            case('R'):
            {
                g2.move('R', b.getType(g2.getRow(), g2.getColumn() + 1), wait);
                break;
            }
            }
            ghost2.restart();
        }

        //sets ghost 3 directions based on previous algorithm calls
        switch (x3)
        {
        case 0:
            if (b.getType(g3.getRow() - 1, g3.getColumn()) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 5000)
                g3.setDirection('U');
            break;
        case 1:
            if (b.getType(g3.getRow() + 1, g3.getColumn()) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g3.setDirection('D');
            break;
        case 2:
            if (b.getType(g3.getRow(), g3.getColumn() + 1) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g3.setDirection('R');
            break;
        case 3:
            if (b.getType(g3.getRow(), g3.getColumn() - 1) != rock && wait == false && game.getElapsedTime().asMilliseconds() >= 2000)
                g3.setDirection('L');
            break;
        }

        //gives movement orders after a certain time
        if (ghost3.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g3.getDirection())
            {
            case('U'):
            {
                g3.move('U', b.getType(g3.getRow() - 1, g3.getColumn()), wait);
                break;
            }
            case('D'):
            {
                g3.move('D', b.getType(g3.getRow() + 1, g3.getColumn()), wait);
                break;
            }
            case('L'):
            {
                g3.move('L', b.getType(g3.getRow(), g3.getColumn() - 1), wait);
                break;
            }
            case('R'):
            {
                g3.move('R', b.getType(g3.getRow(), g3.getColumn() + 1), wait);
                break;
            }
            }
            ghost3.restart();
        }

        //sets directions based on algorithm calls
        switch (x4)
        {
        case 0:
            if (b.getType(g4.getRow() - 1, g4.getColumn()) != rock && wait == false)
                g4.setDirection('U');
            break;
        case 1:
            if (b.getType(g4.getRow() + 1, g4.getColumn()) != rock && wait == false)
                g4.setDirection('D');
            break;
        case 2:
            if (b.getType(g4.getRow(), g4.getColumn() + 1) != rock && wait == false)
                g4.setDirection('R');
            break;
        case 3:
            if (b.getType(g4.getRow(), g4.getColumn() - 1) != rock && wait == false)
                g4.setDirection('L');
            break;
        }


        //gives order after a certain time
        if (ghost4.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g4.getDirection())
            {
            case('U'):
            {
                g4.move('U', b.getType(g4.getRow() - 1, g4.getColumn()), wait);
                break;
            }
            case('D'):
            {
                g4.move('D', b.getType(g4.getRow() + 1, g4.getColumn()), wait);
                break;
            }
            case('L'):
            {
                g4.move('L', b.getType(g4.getRow(), g4.getColumn() - 1), wait);
                break;
            }
            case('R'):
            {
                g4.move('R', b.getType(g4.getRow(), g4.getColumn() + 1), wait);
                break;
            }
            }
            ghost4.restart();
        }


        //checks if pacman and ghost 1 intesects
        if (player.getShape().getGlobalBounds().intersects(g1.getShape().getGlobalBounds()) && g1.get_power() == false)
        {
            p = false;
        }

        //checks if pacman intersects with ghost 1 while power mode is on
        //resets ghost to original place and adds score
        if (player.getShape().getGlobalBounds().intersects(g1.getShape().getGlobalBounds()) && g1.get_power() == true)
        {
            eatGhost.play();
            player.setScore(player.getScore() + 200);
            g1.reset(13, 16);
            g1.set_power(false);
        }


        //checks if pacman and ghost 2 intersects
        if (player.getShape().getGlobalBounds().intersects(g2.getShape().getGlobalBounds()) && g2.get_power() == false)
        {
            p = false;
        }

        //check if they instesect while power to add score and reset ghost
        if (player.getShape().getGlobalBounds().intersects(g2.getShape().getGlobalBounds()) && g2.get_power() == true)
        {
            eatGhost.play();
            player.setScore(player.getScore() + 200);
            g2.reset(16, 16);
            g2.set_power(false);
        }

        //same for ghost 3
        if (player.getShape().getGlobalBounds().intersects(g3.getShape().getGlobalBounds()) && g3.get_power() == false)
        {
            p = false;
        }

        //same for ghost 3 while power mode
        if (player.getShape().getGlobalBounds().intersects(g3.getShape().getGlobalBounds()) && g3.get_power() == true)
        {
            eatGhost.play();
            player.setScore(player.getScore() + 200);
            g3.reset(16, 15);
            g3.set_power(false);
        }

        //same for ghost 4
        if (player.getShape().getGlobalBounds().intersects(g4.getShape().getGlobalBounds()) && g4.get_power() == false)
        {
            p = false;
        }

        //same for ghost 4 while power
        if (player.getShape().getGlobalBounds().intersects(g4.getShape().getGlobalBounds()) && g4.get_power() == true)
        {
            eatGhost.play();
            player.setScore(player.getScore() + 200);
            g4.reset(16, 17);
            g4.set_power(false);
        }


        window.clear(Color::Black);

        //draws word ready at the start of the game and after losing
        if (drawReady)
            window.draw(readyT);


        b.drawBoard(window);

        //draws score
        scoreT.setString("Score " + to_string(player.getScore()));
        window.draw(scoreT);

        //draws number of lives
        numLives.setString("Lives " + to_string(player.getLives()));
        window.draw(numLives);


        //when a ghost eats pacman game restarts and both pacman and ghosts reset to original places
        //if 4 lives are not over a life is substracted
        if (p == false)
        {

            pacmanDie.play();
            player.respawn();
            g1.reset(13, 16);
            g2.reset(16, 16);
            g3.reset(16, 15);
            g4.reset(16, 17);
            wait = true;
            drawReady = true;
            p = true;
        }


        player.drawOnWindow(window);
        g1.drawGhost(window);
        g2.drawGhost(window);
        g3.drawGhost(window);
        g4.drawGhost(window);

        //after 10 seconds pass, first fruit is drawn and stays there for 20 seconds
        if (game.getElapsedTime().asMilliseconds() > 10000 && game.getElapsedTime().asMilliseconds() < 20000 && bonus1 == true && wait == false)
        {
            cherry.drawfruits(window);
        }

        //after 40 seconds pass, second fruit is drawn and stays there for 10 seconds
        if (game.getElapsedTime().asMilliseconds() > 40000 && game.getElapsedTime().asMilliseconds() < 50000 && bonus2 == true && wait == false)
        {
            orange.drawfruits(window);
        }

        //if pacman eats all pellets, show win screen
        if (b.getEatenPellets() == 359)
        {

            window.draw(win);
            wait = true;
        }

        //if all lives are over, a lose screen is shown
        if (player.getLives() == 0)
        {
            b.displayLose(window);
        }

        //speeds up blinky's speed after 40 secons into the game
        if (game.getElapsedTime().asMilliseconds() >= 40000)
            blinkySpeed = 200;

        window.display();

    }


    return 0;
}

