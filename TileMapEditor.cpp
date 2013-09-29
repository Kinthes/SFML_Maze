#include "TileMapEditor.h"

TileMapEditor::TileMapEditor()
{
        sizeScreenWidth=1440;
        sizeScreenHeight=900;
        activeChunk=0;
        tileSize = 32;
        NbTileHor=(int)(sizeScreenWidth/tileSize);
        NbTileVert=(int)(sizeScreenHeight/tileSize);
        screen=0;
        mapWidth=1;
        mapHeight=1;
        mapIndice=0;
        mapDesc.resize(mapWidth*mapHeight);
        tileList.resize(NbTileHor * NbTileVert);
        selectedTileOffset=0;
        selectedMapTileOffset=4;

        window.create(sf::VideoMode(sizeScreenWidth,sizeScreenHeight), "TileMap_Editor v0.02");
        cursor.getCursor().setSize(sf::Vector2f(tileSize,tileSize));
}

TileMapEditor::~TileMapEditor()
{
    //dtor
}

void    TileMapEditor::EditTile_Screen()
{
    window.setTitle("TileMap_Editor v0.02 - Edit Tile Mode");
    cursor.getCapturedTile().setPosition((window.getSize().x)-tileSize*2,tileSize);

    sf::Event event;
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::F1)
                    screen=TileEdition;
                if (event.key.code == sf::Keyboard::F2)
                    screen=MapEdition;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                float mouseX = (event.mouseMove.x>>5)<<5;
                float mouseY = (event.mouseMove.y>>5)<<5;
                if(mouseX > (NbTileHor*tileSize)-tileSize) mouseX=(NbTileHor*tileSize)-tileSize;
                if(mouseY > (NbTileVert*tileSize)-tileSize) mouseY=(NbTileVert*tileSize)-tileSize;
                cursor.getCursor().setPosition(mouseX, mouseY);
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                     selectedTileOffset=(int)(cursor.getCursor().getPosition().x/tileSize)+(int)(cursor.getCursor().getPosition().y/tileSize*NbTileHor);
                     sf::IntRect cursRect(tileList[selectedTileOffset].getTileTextureCoord(), sf::Vector2i(tileSize,tileSize) );
                     cursor.getCapturedTile().setTextureRect(cursRect);
                    cursor.getTileOffset()=selectedTileOffset;

                }
                if (event.mouseButton.button == sf::Mouse::Middle)
                {

                }

            }
        }

        window.clear(sf::Color::Black);
        window.draw(tiles_spr);
        window.draw(cursor.getCapturedTile());
        text.setString(to_string(tileList[cursor.getTileOffset()].getTileType()));
        window.draw(text);
        window.draw(cursor.getCursor());

        window.display();
}//**** EditTile_Screen


//***************************************************************************************************************
void    TileMapEditor::EditMap_Screen()
{
    window.setTitle("TileMap_Editor v0.02 - Edit Map Mode");

    sf::Event event;
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::F1)
                    screen=TileEdition;
                if (event.key.code == sf::Keyboard::F2)
                    screen=MapEdition;
                if (event.key.code == sf::Keyboard::Up)
                {


                    //*
                   // PAS BON : MANQUE MISE A JOUR DES AUTRES CHUNK



                    if(chunks[activeChunk]->getUp() == -1)
                    {
                        int nextChunk = Screen::nbScreen;
                        chunks.push_back(pChunk(new Screen(NbTileHor,NbTileVert)));
                        chunks[activeChunk]->getUp() = nextChunk;
                        chunks[nextChunk]->getDown() = activeChunk;

                        if(mapIndice>=0 && mapIndice<mapWidth) //nouvelle ligne dans le tableau recap
                        {
                            mapDesc.resize(mapDesc.size()+mapWidth,-1);   //ajout d'une ligne
                            mapHeight++;
                            for(int i=(mapHeight*mapWidth)-1;i>=mapWidth;i--)
                            {
                                mapDesc[i]=mapDesc[i-mapWidth];
                                mapDesc[i-mapWidth]=-1;
                            }
                        }
                        else
                        {
                            mapIndice-=mapWidth;
                            if(mapIndice>=mapWidth && mapDesc[mapIndice-mapWidth]>=0)
                                {
                                    chunks[nextChunk]->getUp()=mapDesc[mapIndice-mapWidth];
                                    chunks[mapDesc[mapIndice-mapWidth]]->getDown()=nextChunk;
                                }

                        }
                        mapDesc[mapIndice]=nextChunk;

                        if((mapIndice%mapWidth < mapWidth-1) && (mapDesc[mapIndice+1]>=0) )
                           {
                               chunks[nextChunk]->getRight() = mapDesc[mapIndice+1];
                               chunks[mapDesc[mapIndice+1]]->getLeft()=nextChunk;
                           }

                        if(mapIndice%mapWidth>0 && (mapDesc[mapIndice-1]>=0))
                        {
                            chunks[nextChunk]->getLeft() = mapDesc[mapIndice-1];
                            chunks[mapDesc[mapIndice-1]]->getRight() = nextChunk;
                        }

                    }
                    else mapIndice-=mapWidth;
                    activeChunk = chunks[activeChunk]->getUp();
                }


                if (event.key.code == sf::Keyboard::Down)
                {
                    if(chunks[activeChunk]->getDown() == -1)
                    {
                        int nextChunk = Screen::nbScreen;
                        chunks.push_back(pChunk(new Screen(NbTileHor,NbTileVert)));
                        chunks[activeChunk]->getDown() = nextChunk;
                        chunks[nextChunk]->getUp() = activeChunk;
                        if(mapIndice>=(mapWidth*mapHeight)-mapWidth && mapIndice<mapWidth*mapHeight) //nouvelle ligne
                        {
                            mapDesc.resize(mapDesc.size()+mapWidth,-1);   //ajout d'une ligne
                            mapHeight++;
                            mapIndice+=mapWidth;
                        }
                        else
                        {
                           mapIndice+=mapWidth;
                           if((mapIndice<(mapWidth*mapHeight)-mapWidth) && (mapDesc[mapIndice+mapWidth]>=0))
                           {
                               chunks[nextChunk]->getDown() = mapDesc[mapIndice+mapWidth];
                               chunks[mapDesc[mapIndice+mapWidth]]->getUp()=nextChunk;
                           }
                        }

                        mapDesc[mapIndice]=nextChunk;

                        if(mapIndice%mapWidth>0 && (mapDesc[mapIndice-1]>=0))
                        {
                            chunks[nextChunk]->getLeft() = mapDesc[mapIndice-1];
                            chunks[mapDesc[mapIndice-1]]->getRight() = nextChunk;
                        }
                        if((mapIndice%mapWidth < mapWidth-1) && (mapDesc[mapIndice+1]>=0) )
                           {
                               chunks[nextChunk]->getRight() = mapDesc[mapIndice+1];
                               chunks[mapDesc[mapIndice+1]]->getLeft()=nextChunk;
                           }
                    }
                    else mapIndice+=mapWidth;
                    activeChunk = chunks[activeChunk]->getDown();
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    if(chunks[activeChunk]->getLeft() == -1)
                    {   //*
                        int nextChunk = Screen::nbScreen;
                        chunks.push_back(pChunk(new Screen(NbTileHor,NbTileVert)));
                        chunks[activeChunk]->getLeft() = nextChunk;
                        chunks[nextChunk]->getRight() = activeChunk;

                        if(mapIndice%mapWidth == 0) //nouvelle ligne
                        {
                            mapDesc.resize(mapDesc.size()+mapHeight,-1);   //ajout d'une ligne
                            mapWidth++;
                            int oldTab=(mapHeight*mapWidth) - mapHeight -1;
                            for(int j=mapHeight-1; j>=0; j--)
                            {
                                for(int i=mapWidth-1;i>0;i--)
                                {
                                    mapDesc[(j*mapWidth)+i]=mapDesc[oldTab];
                                    oldTab--;
                                }
                                mapDesc[j*mapWidth]=-1;
                            }
                            mapIndice=(int)(mapIndice/(mapWidth-1))*mapWidth;
                        }  //*/
                        else
                        {
                            mapIndice--;
                            if(mapIndice%mapWidth>0 && mapDesc[mapIndice-1]>=0)
                            {
                                chunks[nextChunk]->getLeft() = mapDesc[mapIndice-1];
                                chunks[mapDesc[mapIndice-1]]->getRight()=nextChunk;
                            }
                        }

                        mapDesc[mapIndice]=nextChunk;

                        if((mapIndice<(mapWidth*mapHeight)-mapWidth) && mapDesc[mapIndice+mapWidth]>=0 )
                        {
                            chunks[nextChunk]->getDown() = mapDesc[mapIndice+mapWidth];
                            chunks[mapDesc[mapIndice+mapWidth]]->getUp() = nextChunk;
                        }
                        if(mapIndice>=mapWidth && mapDesc[mapIndice-mapWidth]>=0)
                        {
                            chunks[nextChunk]->getUp() = mapDesc[mapIndice-mapWidth];
                            chunks[mapDesc[mapIndice-mapWidth]]->getDown() = nextChunk;
                        }
                    }
                    else mapIndice--;
                    activeChunk = chunks[activeChunk]->getLeft();
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    if(chunks[activeChunk]->getRight() == -1)
                    {
                        int nextChunk = Screen::nbScreen;
                        chunks.push_back(pChunk(new Screen(NbTileHor,NbTileVert)));
                        chunks[activeChunk]->getRight() = nextChunk;
                        chunks[nextChunk]->getLeft() = activeChunk;

                        if( mapIndice%mapWidth == mapWidth-1) //nouvelle ligne
                        {
                            mapDesc.resize(mapDesc.size()+mapHeight,-1);   //ajout d'une ligne
                            mapWidth++;
                            int oldTab=(mapHeight*mapWidth) - mapHeight -1;
                            for(int j=mapHeight-1; j>=0; j--)
                            {
                                mapDesc[(j*mapWidth)+(mapWidth-1)]=-1;
                                for(int i=mapWidth-2;i>=0;i--)
                                {
                                    mapDesc[(j*mapWidth)+i]=mapDesc[oldTab];
                                    oldTab--;
                                }
                            }
                            mapIndice=(int)(((mapIndice+1)/(mapWidth-1))*mapWidth)-1;
                        }  //*/
                        else
                        {
                            mapIndice++;
                            if((mapIndice%mapWidth < mapWidth-1) && (mapDesc[mapIndice+1]>=0))
                            {
                                chunks[nextChunk]->getRight() = mapDesc[mapIndice+1];
                                chunks[mapDesc[mapIndice+1]]->getLeft() = nextChunk;
                            }
                        }
                        mapDesc[mapIndice]=nextChunk;

                        if((mapIndice<(mapWidth*mapHeight)-mapWidth) && mapDesc[mapIndice+mapWidth]>=0 )
                        {
                            chunks[nextChunk]->getDown() = mapDesc[mapIndice+mapWidth];
                            chunks[mapDesc[mapIndice+mapWidth]]->getUp() = nextChunk;
                        }
                        if(mapIndice>=mapWidth && mapDesc[mapIndice-mapWidth]>=0)
                        {
                            chunks[nextChunk]->getUp() = mapDesc[mapIndice-mapWidth];
                            chunks[mapDesc[mapIndice-mapWidth]]->getDown() = nextChunk;
                        }
                    }
                    else mapIndice++;
                    activeChunk = chunks[activeChunk]->getRight();
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                float mouseX = (event.mouseMove.x>>5)<<5;
                float mouseY = (event.mouseMove.y>>5)<<5;
                if(mouseX > (NbTileHor*tileSize)-tileSize) mouseX=(NbTileHor*tileSize)-tileSize;
                if(mouseY > (NbTileVert*tileSize)-tileSize) mouseY=(NbTileVert*tileSize)-tileSize;
                 cursor.getCapturedTile().setPosition(mouseX, mouseY);
                 selectedMapTileOffset=(int)(cursor.getCapturedTile().getPosition().x/tileSize)+(int)(cursor.getCapturedTile().getPosition().y/tileSize*NbTileHor);

            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(chunks[activeChunk]->getMapTile(selectedMapTileOffset) != cursor.getTileOffset())
                    chunks[activeChunk]->setMapTile(selectedMapTileOffset,cursor.getTileOffset());
            }


        window.clear(sf::Color::Black);


        for (int i=0;i<NbTileHor*NbTileVert;i++)
        {
            if (chunks[activeChunk]->getMapTile(i) != -1)
            {
                int coordX=(int)(i%NbTileHor)*32;
                int coordY=(int)(i/NbTileHor)*32;
                sf::Sprite piece;
                piece.setPosition(coordX,coordY);
                piece.setTexture(tiles);
                sf::IntRect cursRect(tileList[chunks[activeChunk]->getMapTile(i)].getTileTextureCoord(), sf::Vector2i(tileSize,tileSize) );
                piece.setTextureRect(cursRect);

                window.draw(piece);
            }
        }

        window.draw(cursor.getCapturedTile());
        sf::Vector2f textSave=text.getPosition();
        for(int j=0;j<mapHeight;j++)
        {
          for(int i=0;i<mapWidth;i++)
            {
            text.setPosition(i*14,j*14);
            text.setString(to_string(mapDesc[i+(j*mapWidth)]));
            if(i+(j*mapWidth)==mapIndice)
                text.setColor(sf::Color::Red);
            else text.setColor(sf::Color::White);
            window.draw(text);
            }
            text.setPosition(500,500);
            text.setString(to_string(chunks[activeChunk]->getUp()));
            window.draw(text);
                        text.setPosition(480,520);
            text.setString(to_string(chunks[activeChunk]->getLeft()));
            window.draw(text);
                        text.setPosition(520,520);
            text.setString(to_string(chunks[activeChunk]->getRight()));
            window.draw(text);
                        text.setPosition(500,540);
            text.setString(to_string(chunks[activeChunk]->getDown()));
            window.draw(text);
        }
        text.setPosition(textSave);
        window.display();
}//**** EditMap_Screen

//*************************************************************************************************************
int main()
{
    TileMapEditor app;
   if(!app.getTiles().loadFromFile("data\\tiles.png"))
        return EXIT_FAILURE;

    app.getTilesSpr().setTexture(app.getTiles());

    sf::IntRect cursRect(sf::Vector2i(0,0), sf::Vector2i(app.getTileSize(),app.getTileSize()) );
    app.getCursor().getCapturedTile().setTexture(app.getTiles());
    app.getCursor().getCapturedTile().setTextureRect(cursRect);
    app.getCursor().getCapturedTile().setPosition((app.getWindow().getSize().x)-app.getTileSize()*2,app.getTileSize());//window.getSize().x - 64, 32);

    sf::Font font;
    font.loadFromFile("data\\arial.ttf");

    app.getText().setString(to_string(12));
    app.getText().setFont(font);
    app.getText().setCharacterSize(10);
    app.getText().setPosition((app.getWindow().getSize().x)-app.getTileSize()*2,100);
    app.getText().setColor(sf::Color::White);

 //*
    for(int i=0; i<app.getNbTileHor()*app.getNbTileVert(); i++)
    {
        app.getTileList(i).setTileTextureCoord(sf::Vector2i((int)(i%app.getNbTileHor())*app.getTileSize(), (int)(i/app.getNbTileHor())*app.getTileSize()));
        app.getTileList(i).setTileType(i);

    }//*/

    app.getChunks().push_back(pChunk(new Screen(app.getNbTileHor(),app.getNbTileVert())));
    app.getMapDesc(0)=0;

    app.getSelectedTileOffset()=0;


        while (app.getWindow().isOpen())
        {

            switch(app.getScreen())
            {
            case TileEdition:
                app.EditTile_Screen();
                break;
            case MapEdition:
                app.EditMap_Screen();
                break;

            }

        }

        return 0;


}
