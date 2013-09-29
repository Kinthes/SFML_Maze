#ifndef __TILEMAPEDITOR_H
#define __TILEMAPEDITOR_H

#include "include/cursor.h"
#include "include/tile.h"
#include "include/screen.h"

#include <sstream>
#include <boost/shared_ptr.hpp>

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}

typedef boost::shared_ptr<Screen> pChunk;
enum { TileEdition, MapEdition};

class TileMapEditor
{
    public:
        TileMapEditor();
        virtual ~TileMapEditor();
        void    EditTile_Screen();
        void    EditMap_Screen();

        sf::Texture &       getTiles() {return tiles;}
        sf::Sprite &        getTilesSpr() {return tiles_spr;}
        int &               getTileSize() {return tileSize;}
        Cursor &            getCursor() {return cursor;}
        sf::RenderWindow &  getWindow() {return window;}
        sf::Text &          getText() {return text;}
        int &               getNbTileHor() {return NbTileHor;}
        int &               getNbTileVert() {return NbTileVert;}
        Tile &              getTileList(int g) {return tileList[g];}
        std::vector<pChunk> &getChunks() {return chunks;}
        int &               getMapDesc(int g) {return mapDesc[g];}
        int &               getSelectedTileOffset() {return selectedTileOffset;}
        int &               getScreen() {return screen;}
    protected:
    private:
        int                 sizeScreenWidth;
        int                 sizeScreenHeight;
        int                 activeChunk;

        sf::RenderWindow    window;//(sf::VideoMode(sizeScreenWidth,sizeScreenHeight), "TileMap_Editor v0.02");
        sf::Texture         tiles;
        sf::Text            text;
        sf::Sprite          tiles_spr;

        int                 tileSize;
        int                 NbTileHor;
        int                 NbTileVert;

        int                 screen;
        int                 mapWidth, mapHeight, mapIndice;
        std::vector<int>    mapDesc;
        Cursor              cursor;//(tileSize);

        std::vector<Tile>   tileList;
        int                 selectedTileOffset;
        int                 selectedMapTileOffset;

        std::vector<pChunk> chunks;
};

#endif // __TILEMAPEDITOR_H
