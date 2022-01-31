#include "../include/board.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Board::Board(Side start)
{

    turn = Side::WHITE;
    // seting the pieces in there place
    list[0] = Column(2, Side::BLACK);
    list[5] = Column(5, Side::WHITE);
    list[7] = Column(3, Side::WHITE);
    list[11] = Column(5, Side::BLACK);
    list[12] = Column(5, Side::WHITE);
    list[16] = Column(3, Side::BLACK);
    list[18] = Column(5, Side::BLACK);
    list[23] = Column(2, Side::WHITE);

    list[22] = Column(1, Side::BLACK);
    list[21] = Column(1, Side::BLACK);
    list[20] = Column(1, Side::BLACK);
    list[19] = Column(1, Side::BLACK);

    srand(time(0));

    generateDice();
}

Board::~Board()
{
}

void Board::generateDice()
{
    dice.clear();
    int die1 = std::rand() % (6) + 1;
    int die2 = std::rand() % (6) + 1;

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
    unsigned int um = (unsigned int)(column + dice[i]);

    if (um < 24)
    {
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

unsigned int Board::move(int column, unsigned int i)
{
    if (i >= dice.size())
    {
        std::cout << i << " is bigger than dice size" << std::endl;
        exit(3);
    }
    if (column < 24 && column + dice[i] < 24)
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
        }
        else if (des.checkForLand(turn))
        {
            des.add(turn);
            org.remove();
        }
    }
    return (unsigned int)(column + dice[i]);
}

bool Board::checkMovesFor(unsigned int column)
{
    if (!validColumn(column))
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

bool Board::validColumnDestination(unsigned int column)
{
    return column < 24 &&
           (list[(unsigned int)column].getSide() == turn ||
            list[(unsigned int)column].getSide() == Side::NUTHING ||
            list[(unsigned int)column].getCount() <= 1);
}

bool Board::validColumn(unsigned int column)
{
    return column < 24 &&
           (list[(unsigned int)column].getSide() == turn);
}

Column &Board::getPrison()
{
    return (turn == Side::BLACK) ? bPrison : wPrison;
}

unsigned int Board::moveOutOfPrison(unsigned int i)
{
    if (i >= dice.size())
    {
        std::cout << i << " is bigger than dice size\n";
        exit(3);
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
        }
        else if (des.checkForLand(turn))
        {
            des.add(turn);
            org.remove();
        }
    }
    return (unsigned int)(dice[i] - 1);
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

bool Board::firstSign(int column)
{
    bool success = false;
    for (std::size_t i = 0; i < dice.size(); i++)
    {
        if (checkMoveTo(column, i))
        {
            unsigned int um = (unsigned int)(column + dice[i]);
            list[um].sign({static_cast<int>(i)});
            list[um].setSigned(true);
            success = true;
        }
    }
    return success;
}

void Board::secondSign(int column)
{
    if (column + dice[0] < 0 || column + dice[1] < 0)
    {
        return;
    }
    unsigned int um1 = (unsigned int)(column + dice[0]);
    unsigned int um2 = (unsigned int)(column + dice[1]);
    if (list[um1].isSigned())
    {
        if (checkMoveTo(um1, 1))
        {
            unsigned int un = (unsigned int)(um1 + dice[1]);
            list[un].sign({0, 1});
            list[un].setSigned(true);
        }
    }
    else if (list[um2].isSigned())
    {
        if (checkMoveTo(um2, 0))
        {
            unsigned int un = (unsigned int)(um2 + dice[0]);
            list[un].sign({1, 0});
            list[un].setSigned(true);
        }
    }
}

bool Board::signForDouble(int column)
{
    bool success = false;
    std::vector<int> indexes;
    int um = column;
    for (std::size_t i = 0; i < dice.size(); i++)
    {
        if (checkMoveTo(um, static_cast<unsigned int>(i)))
        {
            indexes.push_back(static_cast<unsigned int>(i));
            um = (unsigned int)(um + dice[i]);
            list[um].sign(indexes);
            list[um].setSigned(true);
            success = true;
        }
        else
        {
            break;
        }
    }
    return success;
}

bool Board::signColumnsFor(int column)
{
    bool success = false;

    if (dice.size() >= 2)
    {
        if (dice[0] == dice[1])
        {
            success = signForDouble(column);
        }
        else
        {
            if (firstSign(column))
            {
                secondSign(column);
                success = true;
            }
        }
    }
    else
    {
        success = firstSign(column);
    }

    return success;
}

bool Board::moveTo(unsigned int originColumn, unsigned int DestinationColumn)
{
    if (!validColumnDestination(DestinationColumn) || !validColumn(originColumn))
    {
        reset();
        return false;
    }

    bool success = false;

    for (auto diceIndex : list[DestinationColumn].diceIndexes)
    {
        originColumn = move(originColumn, diceIndex);
        success = true;
    }

    std::vector<int> v = list[DestinationColumn].diceIndexes;
    std::sort(v.begin(), v.end(), std::greater<int>());
    for (auto diceIndex : v)
    {
        dice.erase(dice.begin() + diceIndex);
    }

    reset();
    return success;
}

bool Board::signColumnsForPrison()
{
    bool success = false;
    for (std::size_t i = 0; i < dice.size(); i++)
    {
        if (turn == Side::BLACK)
        {
            success = signColumnsFor(-1);
        }
        else
        {
            success = signColumnsFor(24);
        }
    }
    return success;
}

bool Board::moveFromPrisonTo(unsigned int column)
{
    if (!validColumnDestination(column))
    {
        reset();
        return false;
    }

    bool success = false;

    int originColumn = -1;
    bool first = true;

    for (auto diceIndex : list[column].diceIndexes)
    {
        std::cout << "first B\n";

        if (first)
        {
            // std::cout << "first A\n";
            originColumn = moveOutOfPrison(diceIndex);
            // std::cout << "first B\n";
            first = false;
            success = true;
        }
        else
        {
            // std::cout << "second A\n";
            originColumn = move(originColumn, diceIndex);
            // std::cout << "second B\n";
        }
    }
    std::cout << "B\n";

    std::vector<int> v = list[column].diceIndexes;
    std::sort(v.begin(), v.end(), std::greater<int>());
    for (auto diceIndex : v)
    {
        dice.erase(dice.begin() + diceIndex);
    }
    reset();
    return success;
}

void Board::reset()
{
    for (std::size_t i = 0; i < list.size(); i++)
    {
        list[i].sign({});
        list[i].setSigned(false);
    }
}
