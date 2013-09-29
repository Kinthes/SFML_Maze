#include "..\include\Screen.h"

int Screen::nbScreen=0;

Screen::Screen(int xLength, int yLength)
{
    NbTileHor=xLength;
    NbTileVert=yLength;
    nbScreen++;
    left=-1;
    right=-1;
    up=-1;
    down=-1;
    mapTile.reserve(NbTileHor*NbTileVert);
    for(int i=0;i<NbTileHor*NbTileVert;i++)
    {
        mapTile[i]=-1;
    }
}

Screen::~Screen()
{
    //dtor
}
