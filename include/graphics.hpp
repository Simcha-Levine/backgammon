#include <SFML/Graphics.hpp>
#include "board.hpp"

class Graphics
{
private:
    Board *board = nullptr;
    int *width = nullptr;
    int *hight = nullptr;
    int *chosen = nullptr;
    sf::Font font;

public:
    Graphics();
    Graphics(Board *b, int *w, int *h, int *c);
    ~Graphics();

    sf::ConvexShape getColumnShape(float w, float h,
                                   float x, int dir,
                                   int c, bool isSigned);

    sf::CircleShape getPice(float w, float x, float y, int dir, Side s, int chose);

    void drawColumns(sf::RenderWindow &win, float columnW, float columnH);

    void drawPicces(sf::RenderWindow &win, float columnW);

    void draw(sf::RenderWindow &win);

    void drawTurn(sf::RenderWindow &win);

    void drawDice(sf::RenderWindow &win);
};
