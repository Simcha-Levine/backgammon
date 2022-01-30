#include "side.hpp"
#include <vector>
class Column
{
private:
    Side side = Side::NUTHING;
    int count = 0;
    bool _signed = false;

public:
    std::vector<int> diceIndexes{};

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
    void sign(std::vector<int> indexes);
    bool isSigned();
    void setSigned(bool u);
};
