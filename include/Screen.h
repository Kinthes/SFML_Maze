#ifndef __SCREEN_H
#define __SCREEN_H

#include <vector>

class Screen
{
    public:
        static int          nbScreen;

        Screen(int, int);
        virtual ~Screen();
        int                 getMapTile(int i) {return mapTile[i];}
        void                setMapTile(int i, int value) {mapTile[i]=value;}
        int &               getLeft() {return left;}
        int &               getRight() {return right;}
        int &               getUp() {return up;}
        int &               getDown() {return down;}
    protected:
    private:
        int                 left,right,up,down;
        int                 NbTileHor, NbTileVert;
        std::vector<int>    mapTile;
};

#endif // __SCREEN_H
