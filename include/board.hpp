#include <vector>
#include <array>
#include "column.hpp"

class Board
{
private:
    // remember
    Column black_end{6, Side::BLACK};
    Column white_end{6, Side::WHITE};

public:
    std::array<Column, 24> list{};
    Side turn = Side::BLACK;
    std::vector<int> dice{};

    Column wPrison{0, Side::WHITE};
    Column bPrison{0, Side::BLACK};

    Board(Side start);
    ~Board();

    void generateDice();

    bool checkMoveTo(int column, unsigned int diceIndex);
    // bool checkMoves(std::vector<int> diceIndcis);
    bool checkPrisonMoves();

    void move(int column, unsigned int diceIndex);
    void moveOutOfPrison(unsigned int diceIndex);

    bool checkMovesFor(int column);
    bool checkIfCanMove();

    void parsTurn();

    bool validColumnDestination(int column);
    bool validColumn(int column);

    Column &getPrison();
};
