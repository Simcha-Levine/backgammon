#include <vector>
#include <array>
#include "column.hpp"

class Board
{
private:
    Column black_end{6, Side::BLACK};
    Column white_end{6, Side::WHITE};

    bool checkMovesFor(unsigned int column);
    bool checkMoveTo(int column, unsigned int diceIndex);
    unsigned int move(unsigned int column, unsigned int diceIndex);

    bool checkPrisonMoves();
    unsigned int moveOutOfPrison(unsigned int diceIndex);

public:
    std::array<Column, 24> list{};
    Side turn = Side::BLACK;
    std::vector<int> dice{};

    Column wPrison{0, Side::WHITE};
    Column bPrison{0, Side::BLACK};

    Board(Side start);
    ~Board();

    void generateDice();

    bool checkIfCanMove();

    bool signColumnsFor(unsigned int column);
    bool moveTo(unsigned int originColumn, unsigned int column);

    bool signColumnsForPrison();
    bool moveFromPrisonTo(unsigned int column);

    void reset();

    void parsTurn();

    bool validColumnDestination(unsigned int column);
    bool validColumn(unsigned int column);

    Column &getPrison();
};
