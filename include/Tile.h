#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile();
        ~Tile();

        int                 getTileType() {return tileType;}
        void                setTileType(int type) {tileType=type;}
        sf::Vector2i        getTileTextureCoord() {return tileTextureCoord;}
        void                setTileTextureCoord(sf::Vector2i coord) {tileTextureCoord=coord;}
    protected:
    private:
        sf::Vector2i        tileTextureCoord; //coordonnees du sf::IntRect dans l'image des tiles
        int                 tileType;
};

#endif // TILE_H
