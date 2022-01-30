#include "../include/graphics.hpp"
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

Graphics::Graphics()
{
    board = nullptr;
    width = nullptr;
    hight = nullptr;
    chosen = nullptr;
    font.loadFromFile("font.ttf");
}

Graphics::Graphics(Board *b, int *w, int *h, int *c)
{
    board = b;
    width = w;
    hight = h;
    chosen = c;
    font.loadFromFile("font.ttf");
}

Graphics::~Graphics()
{
}

sf::ConvexShape Graphics::getColumnShape(float w, float h,
                                         float x, int dir,
                                         int c, bool isSigned)
{
    sf::ConvexShape convex(3);
    x += 5.f;
    w -= 10.f;

    if (dir == 0)
    {
        convex.setPoint(0, sf::Vector2f(x, 0));
        convex.setPoint(1, sf::Vector2f(x + w, 0));
        convex.setPoint(2, sf::Vector2f(x + w * 0.5f, h));
    }
    else
    {
        convex.setPoint(0, sf::Vector2f(x, *hight));
        convex.setPoint(1, sf::Vector2f(x + w, *hight));
        convex.setPoint(2, sf::Vector2f(x + w * 0.5f, *hight - h));
    }

    sf::Color co = (c % 2 == 0) ? sf::Color::White : sf::Color::Black;
    convex.setFillColor(co);

    convex.setOutlineThickness(5.f);
    co = (isSigned) ? sf::Color::Yellow : sf::Color::White;
    convex.setOutlineColor(co);
    return convex;
}

sf::CircleShape Graphics::getPice(float w, float x, float y,
                                  int dir, Side s, int chose)
{
    sf::CircleShape ci(w * 0.5f - 5.f);
    if (dir == 0)
    {
        ci.setPosition(x, y + 3.f);
    }
    else
    {
        ci.setPosition(x, *hight - y + 3.f);
    }
    sf::Color co = (s == Side::BLACK) ? sf::Color::Black : sf::Color::White;
    ci.setFillColor(co);

    ci.setOutlineThickness(5.f);
    co = (s == Side::BLACK) ? sf::Color::White : sf::Color::Black;
    co = (chose == 0) ? co : sf::Color::Cyan;
    ci.setOutlineColor(co);

    return ci;
}

void Graphics::drawColumns(sf::RenderWindow &win, float columnW, float columnH)
{
    for (int i = 0; i < 12; i++)
    {
        bool t = board->list[i].isSigned();
        win.draw(getColumnShape(columnW, columnH, i * columnW, 0, i, t));
    }
    for (int i = 0; i < 13; i++)
    {
        bool t = board->list[i + 11].isSigned();
        float x = *width - i * columnW;
        win.draw(getColumnShape(columnW, columnH, x, 1, i + 1, t));
    }
}

void Graphics::drawPicces(sf::RenderWindow &win, float columnW)
{
    for (int i = 0; i < 12; i++)
    {
        Column &col = board->list[i];
        for (int j = 0; j < col.getCount(); j++)
        {
            float w = columnW * 0.75f;
            float x = i * columnW + columnW * 0.125f;
            int cho = (i == *chosen) ? 1 : 0;
            win.draw(getPice(w, x, j * w, 0, col.getSide(), cho));
        }
    }
    for (int i = 0; i < 13; i++)
    {
        Column &col = board->list[i + 11];
        for (int j = 0; j < col.getCount(); j++)
        {
            float w = columnW * 0.75f;
            float x = *width - i * columnW + columnW * 0.125f;
            int cho = (i + 11 == *chosen) ? 1 : 0;
            win.draw(getPice(w, x, j * w + w, 1, col.getSide(), cho));
        }
    }
}

void Graphics::draw(sf::RenderWindow &win)
{
    win.clear(sf::Color::Black);

    float columnW = *width / 12;
    float columnH = *hight / 2 - 100;

    drawColumns(win, columnW, columnH);

    drawPicces(win, columnW);

    drawTurn(win);

    win.display();
}

void Graphics::drawTurn(sf::RenderWindow &win)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, *hight / 2);

    std::ostringstream str;

    if (board->turn == Side::WHITE)
    {
        str << "WHITE ;";
    }
    else
    {
        str << "BLACK ;";
    }

    str << "    dice: ";
    for (int i : board->dice)
    {
        str << abs(i) << " , ";
    }

    str << ";        white prison:" << board->wPrison.getCount() << ';';
    str << "        black prison:" << board->bPrison.getCount() << ';';
    text.setString(str.str());

    win.draw(text);
}
