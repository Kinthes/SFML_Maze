#include "../include/cursor.h"

Cursor::Cursor()
{
    curseur.setFillColor(sf::Color::Transparent);
    curseur.setOutlineColor(sf::Color::White);
    curseur.setOutlineThickness(3);
    curseur.setPosition(250,150);
}

Cursor::Cursor(int tileSize)
{
    curseur.setSize(sf::Vector2f(tileSize,tileSize));
    curseur.setFillColor(sf::Color::Transparent);
    curseur.setOutlineColor(sf::Color::White);
    curseur.setOutlineThickness(3);
    curseur.setPosition(250,150);
}

Cursor::~Cursor()
{

}
