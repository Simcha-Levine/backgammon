#include <iostream>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "../include/graphics.hpp"
#include <unistd.h>

Board board(Side::BLACK);
int width = 800;
int hight = 700;
int chosen = -1;
Graphics graphics(&board, &width, &hight, &chosen);

void drawTerminal(Board &board);
void test();

void turns()
{
    if (!board.checkIfCanMove())
    {
        board.parsTurn();
        board.generateDice();
    }
}

int getColumn(sf::Vector2i p)
{
    int col = -1;
    if (p.y < hight / 2 - 100)
    {
        col = p.x / (width / 12);
    }
    else if (p.y > hight - (hight / 2 - 100))
    {
        col = 12 - p.x / (width / 12) + 11;
    }
    return col;
}

int getUsedDiceIndex(int col, int chosen)
{
    int stepSize = col - chosen;

    for (size_t i = 0; i < board.dice.size(); i++)
    {
        if (board.dice[i] == stepSize)
        {
            return i;
        }
    }
    return -1;
}

void chose(sf::RenderWindow &win)
{
    turns();

    sf::Vector2i p = sf::Mouse::getPosition(win);
    int col = getColumn(p);

    if (chosen == -1 && board.getPrison().getCount() == 0)
    {
        if (board.validColumn(col))
        {
            chosen = col;
            board.signColumnsFor(chosen);
        }
    }
    else if (board.getPrison().getCount() > 0)
    {
        // if (board.validColumnDestination(col))
        // {
        //     diceUsedIndex = getUsedDiceIndex(col, chosen);

        //     int t = (board.turn == Side::BLACK) ? -1 : 24;

        //     if (diceUsedIndex != -1 && board.checkMoveTo(t, diceUsedIndex))
        //     {
        //         board.moveOutOfPrison(diceUsedIndex);
        //         turns();
        //     }
        //     chosen = -1;
        // }
    }
    else
    {
        if (board.validColumnDestination(col))
        {

            if (board.moveTo(chosen, col))
            {
                turns();
            }
            chosen = -1;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, hight), "backgammon");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    chose(window);
                }
            }
        }

        graphics.draw(window);
    }
}
