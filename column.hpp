#include "side.hpp"
class Column
{
private:
    Side side = Side::NUTHING;
    int count = 0;

public:
    Column();
    Column(int count, Side side);
    ~Column();

    Side getSide();
    int getCount();

    bool checkForLand(Side s);
    bool checkForEat(Side s);
    bool add(Side s);
    bool remove();
    bool eat(Side s);
};
