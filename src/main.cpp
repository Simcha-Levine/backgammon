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
bool pause1 = true;

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

void chose(sf::RenderWindow &win)
{
    sf::Vector2i p = sf::Mouse::getPosition(win);
    int col = getColumn(p);
    int t = -1;

    if (chosen == -1)
    {
        if (board.validColumn(col))
        {
            if (board.getPrison().getCount() > 0)
            {
                // col = board.getPrison();
            }
            chosen = col;
        }
    }
    else
    {
        if (board.validColumnDes(col))
        {
            int r = col - chosen;
            for (size_t i = 0; i < board.dice.size(); i++)
            {
                if (board.dice[i] == r)
                {
                    t = i;
                    break;
                }
            }
        }
        if (t != -1 && board.validColumnDes(col) && board.checkMoveTo(chosen, t))
        {
            board.move(chosen, t);
            turns();
        }
        chosen = -1;
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
                    pause1 = true;
                }
            }
        }

        graphics.draw(window);
    }
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//

// debuging tools
void printVec(std::vector<int> &vec)
{
    std::cout << "[ ";

    for (int i : vec)
    {
        std::cout << i << " , ";
    }
    std::cout << "]\n";
}
void test()
{
    for (int y = 0; y < 6; y++)
    {
        drawTerminal(board);
        std::cout << ((board.turn == Side::BLACK) ? "black\n" : "white\n");
        std::cout << board.dice[0] << " , " << board.dice[1] << '\n';
        if (board.checkIfCanMove())
        {
            std::cout << "enter a column : \n";
            int column;
            std::cin >> column;
            if (board.validColumn(column))
            {
                if (board.checkMovesFor(column))
                {
                    std::cout << "enter dice\n";
                    unsigned int i;
                    std::cin >> i;
                    if (board.checkMoveTo(column, i))
                    {
                        board.move(column, i);
                    }
                    else
                    {
                        std::cout << "can't\n";
                    }
                }
            }
            else
            {
                std::cout << "not yours\n";
            }
        }
        else
        {
            board.parsTurn();
            board.generateDice();
        }
    }
}
void drawTerminal(Board &board)
{

    for (int i = 7; i >= 0; i--)
    {
        std::cout << '|';

        for (Column c : board.list)
        {
            char d = (c.getSide() == Side::BLACK) ? 'X' : 'O';
            if (i < c.getCount())
            {
                std::cout << d << '|';
            }
            else
            {
                std::cout << " |";
            }
        }
        std::cout << '\n';
    }
}