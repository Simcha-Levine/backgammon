#include "board.hpp"
#include <iostream>

Board::Board(Side start)
{

    turn = start;
    // seting the pieces in there place
    list[0] = Column(2, Side::BLACK);
    list[5] = Column(5, Side::WHITE);
    list[7] = Column(3, Side::WHITE);
    list[11] = Column(5, Side::BLACK);
    list[12] = Column(5, Side::WHITE);
    list[16] = Column(3, Side::BLACK);
    list[18] = Column(5, Side::BLACK);
    list[23] = Column(2, Side::WHITE);

    generateDice();
}

Board::~Board()
{
}

void Board::generateDice()
{
    dice.clear();
    int die1 = 3;
    int die2 = 4;

    int m = ((turn == Side::WHITE) ? -1 : 1);

    if (die1 == die2)
    {
        dice.push_back(die1 * m);
        dice.push_back(die1 * m);
        dice.push_back(die1 * m);
        dice.push_back(die1 * m);
    }
    else
    {
        dice.push_back(die1 * m);
        dice.push_back(die2 * m);
    }
}

bool Board::checkMoveTo(int column, unsigned int i)
{
    if (column + dice[i] >= 0 && column + dice[i] < 24)
    {
        unsigned int um = (unsigned int)(column + dice[i]);
        if (!list[um].checkForLand(turn) && !list[um].checkForEat(turn))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool Board::checkPrisonMoves()
{
    for (std::size_t i = 0; i < dice.size(); i++)
    {
        if (turn == Side::BLACK)
        {
            if (checkMoveTo(-1, i))
            {
                return true;
            }
        }
        else
        {
            if (checkMoveTo(24, i))
            {
                return true;
            }
        }
    }
    return false;
}

void Board::move(int column, unsigned int i)
{
    if (i >= dice.size())
    {
        return;
    }
    if (column >= 0 && column < 24 && column + dice[i] >= 0 && column + dice[i] < 24)
    {
        Column &org = list[(unsigned int)column];
        Column &des = list[(unsigned int)(column + dice[i])];
        if (des.checkForEat(turn))
        {
            des.eat(turn);
            org.remove();
            if (turn == Side::BLACK)
            {
                wPrison.add(Side::WHITE);
            }
            else
            {
                bPrison.add(Side::BLACK);
            }
            dice.erase(dice.begin() + i);
        }
        else if (des.checkForLand(turn))
        {
            des.add(turn);
            org.remove();
            dice.erase(dice.begin() + i);
        }
    }
}

void Board::moveOutOfPrison(unsigned int i)
{
    if (i >= dice.size())
    {
        return;
    }
    int column = (turn == Side::BLACK) ? -1 : 24;

    if (column + dice[i] >= 0 && column + dice[i] < 24)
    {
        Column &org = (turn == Side::BLACK) ? bPrison : wPrison;
        Column &des = list[(unsigned int)(column + dice[i])];
        if (des.checkForEat(turn))
        {
            des.eat(turn);
            org.remove();
            if (turn == Side::BLACK)
            {
                wPrison.add(Side::WHITE);
            }
            else
            {
                bPrison.add(Side::BLACK);
            }
            dice.erase(dice.begin() + i);
        }
        else if (des.checkForLand(turn))
        {
            des.add(turn);
            org.remove();
            dice.erase(dice.begin() + i);
        }
    }
}

bool Board::checkMovesFor(int column)
{
    if (column < 0 || column > 23)
    {
        return false;
    }
    for (std::size_t i = 0; i < dice.size(); i++)
    {
        if (checkMoveTo(column, i))
        {
            return true;
        }
    }
    return false;
}

bool Board::checkIfCanMove()
{
    if (dice.size() == 0)
    {
        return false;
    }

    if (turn == Side::BLACK)
    {
        if (bPrison.getCount() > 0)
        {
            return checkPrisonMoves();
        }
    }
    else
    {
        if (wPrison.getCount() > 0)
        {
            return checkPrisonMoves();
        }
    }

    for (std::size_t i = 0; i < list.size(); i++)
    {
        if (list[i].getSide() == turn && checkMovesFor(i))
        {
            return true;
        }
    }
    return false;
}

void Board::parsTurn()
{
    turn = (turn == Side::BLACK) ? Side::WHITE : Side::BLACK;
}

bool Board::validColumnDes(int column)
{
    return column >= 0 && column < 24 &&
           (list[(unsigned int)column].getSide() == turn ||
            list[(unsigned int)column].getSide() == Side::NUTHING ||
            list[(unsigned int)column].getCount() <= 1);
}

bool Board::validColumn(int column)
{
    return column >= 0 && column < 24 &&
           (list[(unsigned int)column].getSide() == turn ||
            list[(unsigned int)column].getSide() == Side::NUTHING);
}

Column &Board::getPrison()
{
    return (turn == Side::BLACK) ? bPrison : wPrison;
}