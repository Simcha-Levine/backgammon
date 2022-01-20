#include "column.hpp"

Column::Column()
{
    count = 0;
    side = Side::NUTHING;
}

Column::Column(int count, Side side)
{
    this->side = side;
    this->count = count;
}

Column::~Column()
{
}

Side Column::getSide()
{
    return side;
}

int Column::getCount()
{
    return count;
}

bool Column::checkForLand(Side s)
{
    return (side == s || side == Side::NUTHING);
}

bool Column::checkForEat(Side s)
{
    return (count == 1 && side != s);
}

bool Column::add(Side s)
{
    if (checkForLand(s))
    {
        count++;
        side = s;
        return true;
    }
    return false;
}

bool Column::remove()
{
    if (count > 0)
    {
        count--;

        if (count == 0)
        {
            side = Side::NUTHING;
        }
        return true;
    }

    return false;
}

bool Column::eat(Side s)
{
    if (checkForEat(s))
    {
        side = s;
        return true;
    }
    return false;
}