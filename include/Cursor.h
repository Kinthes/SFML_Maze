#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>

class Cursor
{
    public:
        Cursor();
        Cursor(int);
        ~Cursor();

        sf::RectangleShape  & getCursor() {return curseur;}
        sf::Sprite          & getCapturedTile() {return capturedTile;}
        int                 & getTileOffset() {return tileOffset;}
    protected:
    private:
        sf::RectangleShape  curseur;
        sf::Sprite          capturedTile;
        int                 tileOffset;
};

#endif // CURSOR_H
