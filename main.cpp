#include <SFML/Graphics.hpp>

int main()
{
    int map[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
               0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
               0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
               1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    float xE=150, yE=150;
    float vY=0.0, vX=0.0;
    float gravity=1.1;
    int inertia=4;

    bool isJumping=false, isFalling=false;
    bool right=false, left=false;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "The Maze Project v0.001");

    sf::Clock clock;
    sf::RectangleShape Emile(sf::Vector2f(32, 32));
    Emile.setPosition(xE,yE);
    Emile.setFillColor(sf::Color(180,50,70));

    sf::Time elapsed=clock.restart();
    while (window.isOpen())
    {
        elapsed=clock.getElapsedTime();
        sf::Event event;

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    vX=4; if(isJumping)vX*=2;
                    inertia=15;
                    right=true;
                }
            else right=false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    vX=-4; if(isJumping) vX*=2;
                    inertia=15;
                    left=true;
                }
            else left=false;


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  && !isFalling && !isJumping)
            {
                vY=-20;
                vX*=2;
                isJumping=true;
            }

        }

        if (elapsed.asSeconds() > 0.02)
        {
            elapsed=clock.restart();
            if (vX && !left && !right)
                    {
                        if(inertia==0) vX=0;
                        else {
                                vX/=2;
                                inertia--;
                        }
                    }

            int yInd=(int)((yE+35)/32);
                if(!map[(yInd)*32 + (int)((xE+5)/32)] && !map[(yInd)*32 + (int)((xE+27)/32)])
                    isFalling=true;

            if (isJumping || isFalling)
            {
                if (vY<25)vY += gravity;
                yE += vY;  // * elapsed.asSeconds();
                int yInd=(int)((yE+32)/32);
                int xInd = (int)((xE+16)/32);
                if (vY >=0 && map[(yInd+1)*32 + xInd])
                    {
                        yE=yInd*32;
                        vY = 0; if(!isFalling)vX/=2;
                        isJumping = false;
                        isFalling=false;
                    }
                else if (vY<0 && map[(yInd-1)*32 + xInd])
                    {
                    yE = yInd*32;
                    vY=0; if(!isFalling)vX/=2;
                    }
            }
            if (vX)
            {
                int yInd=(int)((yE+16)/32);
                int xInd=(int)((xE)/32);
                if(vX >=0 && map[yInd*32 + xInd+1])
                {
                    xE=xInd*32;
                    vX=0;
                }
                if (vX<0 && map[yInd*32 + xInd])
                {
                    vX=0;
                }

                xE+=vX;

            }

            Emile.setPosition(xE,yE);
        }

        window.clear(sf::Color::Black);

        for(int j=0;j<24;++j)
        {
            for(int i=0;i<32;++i)
            {
                if(map[i+j*32])
                {
                    sf::RectangleShape rectangle(sf::Vector2f(32, 32));
                    rectangle.setPosition(i*32,j*32);
                    rectangle.setFillColor(sf::Color(50,80,180));
                    window.draw(rectangle);
                }
                else
                {
                    sf::RectangleShape rectangle(sf::Vector2f(32, 32));
                    rectangle.setPosition(i*32,j*32);
                    rectangle.setFillColor(sf::Color(150+50*((i+j)%2),150+50*((i+j)%2), 150+50*((i+j)%2)));
                    window.draw(rectangle);
                }

            }
        }

        window.draw(Emile);
        window.display();
    }
    return EXIT_SUCCESS;
}
