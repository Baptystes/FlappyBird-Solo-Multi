//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include "Level.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include "Son.h"

using namespace sf;
using namespace std;

Level::Level(RenderWindow &fenetreRecois, int &scoreRecois, Son &sonRecois): fenetre(fenetreRecois), score(scoreRecois), son(sonRecois)
{
    texture_Sol.loadFromFile("data/sol2.jpg"); //12
    sprite_Sol.setTexture(texture_Sol);
    sprite_Sol.setScale(Vector2f(1.47,1));

    texture_Fond.loadFromFile("data/fond.jpg");
    sprite_Fond.setTexture(texture_Fond);
    //sprite_Fond.setScale(Vector2f(1.0, 1.0));
    sprite_Fond.setPosition(Vector2f(0,0));

    image_Tuyaux.loadFromFile("data/tuyauxColor2bis.png");

    texture_Tuyaux.loadFromImage(image_Tuyaux);

    for (int a=0; a<2; a++){
        sprite_Tuyaux[a].setTexture(texture_Tuyaux);
        sprite_Tuyaux[a].setTextureRect(IntRect(313, 16, 66, 524));
        sprite_Tuyaux[a].setScale(Vector2f(0.85, 0.9));
    }


    sprite_Tuyaux[0].setOrigin(Vector2f(0,524));
    sprite_Tuyaux[1].setOrigin(Vector2f(0,0));

    for (int a=0; a<3; a++)
    {
        for (int b=0; b<2; b++)
            positions[a][b]= 0;

    }

    for (int a=0; a<100; a++)
        tuyaux[a]=0;
    tuyauEnCours=0;
    tuyauxpixelEnCours=0;


    fenetre.setSize(Vector2u(1.4 * 320, 500));
    vitesseDefilement = 2;
}

Level::~Level()
{
    //dtor
}


void Level::initGame(int tuyauxRecois [100]){



    for (int a=0; a<100; a++)
    {
        //packetRecois >> tuyaux[a];
        tuyaux[a] = tuyauxRecois[a];
       //cout << endl<< tuyaux[a];
    }

    for (int a=0; a<3; a++){
        positions[a][0]=a*188+500;
        //positions[a][0]=a*200+5;
        positions[a][1]=tuyaux[a];
       // positions[a][1]=a*200;

    }
    //cout << "\n0="<<positions[0][1];
    tuyauEnCours=0; // tuyaux passés
    tuyauxpixelEnCours=0;
    multiple = 0;
    sprite_Sol.setPosition(Vector2f(0, fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
    score=0;

}
void Level::initGameOffline(){


    for (int a=0; a<100; a++)
    {
        //packetRecois >> tuyaux[a];
        tuyaux[a]=rand()%240+45;
       //cout << endl<< tuyaux[a];
    }

    for (int a=0; a<3; a++){
        positions[a][0]=a*188+500;  //250
        //positions[a][0]=a*200+5;
        positions[a][1]=tuyaux[a];
       // positions[a][1]=a*200;

    }
    //cout << "\n0="<<positions[0][1];
    tuyauEnCours=0; // tuyaux passés
    tuyauxpixelEnCours=0;
    multiple = 0;
    sprite_Sol.setPosition(Vector2f(0, fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
    score=0;

}



bool Level:: defilement(FloatRect flappySurface){
   // {
        bool flappyToucheTuyau(0);
        fenetre.draw(sprite_Fond);

//if (Keyboard::isKeyPressed(Keyboard::Space)) /////
//{
        tuyauxpixelEnCours+=vitesseDefilement;
        if (tuyauxpixelEnCours > 600)
        {
            tuyauxpixelEnCours =0;
            multiple++;
        }
//}                                             //////

           for (int a=0; a<3; a++){
        //if (Keyboard::isKeyPressed(Keyboard::Space)) ///////////
        //{

                positions[a][0]= (positions[a][0] - vitesseDefilement);
                if (positions[a][0]<=-60){
                        tuyauEnCours++;

                        positions[a][0]+=564;//760;
                        positions[a][1]=tuyaux[tuyauEnCours+3];
                }
                else if (abs(positions[a][0] - 252)<2)
                {
                    score++;
                    //tuyauxpixelEnCours= 252 - positions[a][0];
                    son.playPoint();
                }
        //}                          /////////////////////

                sprite_Tuyaux[0].setPosition(Vector2f(positions[a][0],positions[a][1]));
                sprite_Tuyaux[1].setPosition(Vector2f(positions[a][0],positions[a][1]+95));
                fenetre.draw(sprite_Tuyaux[0]);
                fenetre.draw(sprite_Tuyaux[1]);
                if (sprite_Tuyaux[0].getGlobalBounds().intersects(flappySurface) || sprite_Tuyaux[1].getGlobalBounds().intersects(flappySurface))
                    {
                        flappyToucheTuyau=1;
                        //std::cout <<std::endl<<a<<"   :"<<sprite_Tuyaux[0].getGlobalBounds().intersects(flappySurface)<<"   :"<<sprite_Tuyaux[1].getGlobalBounds().intersects(flappySurface)<<"   X="<<flappySurface.left<<"  Y="<<flappySurface.top;

                    }
            }
        sprite_Sol.setPosition(Vector2f(((int)sprite_Sol.getPosition().x-vitesseDefilement)%23, fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
        fenetre.draw(sprite_Sol);
    //}

    return flappyToucheTuyau;
    //return 0;

}

void Level::afficherLevel (bool levelMovement)
{
    fenetre.draw(sprite_Fond);
        if (levelMovement)
            sprite_Sol.setPosition(Vector2f(((int)sprite_Sol.getPosition().x-vitesseDefilement), fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
        else{
            sprite_Sol.setPosition(Vector2f(((int)sprite_Sol.getPosition().x), fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
            for (int a=0; a<3; a++){
                    sprite_Tuyaux[0].setPosition(Vector2f(positions[a][0],positions[a][1]));
                    sprite_Tuyaux[1].setPosition(Vector2f(positions[a][0],positions[a][1]+95));
                    fenetre.draw(sprite_Tuyaux[0]);
                    fenetre.draw(sprite_Tuyaux[1]);
            }

        }
        fenetre.draw(sprite_Sol);
}
/*
void Level :: affLevel ()
{
    //for (int a=0; a<12; a++)
    //{

        fenetre.draw(sprite_Fond);
        for (int a=0; a<3; a++){
                    sprite_Tuyaux[0].setPosition(Vector2f(positions[a][0],positions[a][1]));
                    sprite_Tuyaux[1].setPosition(Vector2f(positions[a][0],positions[a][1]+115));
                    fenetre.draw(sprite_Tuyaux[0]);
                    fenetre.draw(sprite_Tuyaux[1]);
        }
        /////sprite_Sol.setPosition(Vector2f(((int)sprite_Sol.getPosition().x-vitesseDefilement)%29, fenetre.getSize().y - sprite_Sol.getGlobalBounds().height));
        fenetre.draw(sprite_Sol);

    //}
}
*/
