#include <vector>
#include <array>
#include "column.hpp"

class Board
{
private:
    Column black_end{6, Side::BLACK};
    Column white_end{6, Side::WHITE};
    bool is_black_end = false;
    bool is_white_end = false;

    bool checkMovesFor(unsigned int column);
    bool checkMoveTo(int column, unsigned int diceIndex);
    unsigned int move(int column, unsigned int diceIndex);

    bool checkPrisonMoves();
    unsigned int moveOutOfPrison(unsigned int diceIndex);

    void eraseDice(std::vector<int> vec);

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

    bool firstSign(int column);
    void secondSign(int column);
    bool signForDouble(int column);

    bool signColumnsFor(int column);
    bool moveTo(unsigned int originColumn, unsigned int column);

    bool signColumnsForPrison();
    bool moveFromPrisonTo(unsigned int column);

    void reset();

    void parsTurn();

    bool validColumnDestination(unsigned int column);
    bool validColumn(unsigned int column);

    Column &getPrison();

    void checkIfEnd();
};
