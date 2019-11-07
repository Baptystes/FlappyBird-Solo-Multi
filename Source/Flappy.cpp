//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include "Flappy.h"
#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Son.h"
using namespace sf;
using namespace std;
#include <iostream>
#include <vector>
#include "Level.h"

Flappy::Flappy(RenderWindow &fenetreRecois, Son &sonRecois) : fenetre(fenetreRecois), son(sonRecois)
{
    image_Flappy.loadFromFile("data/flappyPicBIGDoubleFin.png");

    texture_Flappy.loadFromImage(image_Flappy);
    texture_Flappy.setSmooth(0);
    for (int a=0; a<2; a++)
    {
        sprite_Flappy[a].setTexture(texture_Flappy);
        sprite_Flappy[a].setTextureRect(IntRect(a*40, 0, 40, 28));
        sprite_Flappy[a].setOrigin(Vector2f(20,14));
        sprite_Flappy[a].setScale(Vector2f(0.8,0.9));
    }
    sprite_Flappy[2].setTexture(texture_Flappy);
    sprite_Flappy[2].setTextureRect(IntRect(0, 0, 40, 28));
    sprite_Flappy[2].setOrigin(Vector2f(20,14));
    sprite_Flappy[2].setColor(Color(255,255,255,150));
    sprite_Flappy[2].setScale(Vector2f(0.8,0.9));

    phaseSaut = descend;


}


void Flappy :: init()
{
    positionTheoriqueY=200;
    gravity = -10;
    toucheActive = 0;
    gravityRotate =-20;
    animationKey=1; animationTime=1;
    sprite_Flappy[animationKey].setPosition(Vector2f(250, (int)positionTheoriqueY));

    //sprite_Flappy.setRotation(90);

}

void Flappy :: mouvement()
{
    if (!((animationTime+=1)%=10))
        animationKey = 1-animationKey;
    if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::RControl) || Mouse::isButtonPressed(Mouse::Left)) && getPosition_Y()>10)
    {
        if (!toucheActive){
            gravity = -6.6;//-6.5;
            toucheActive=1;
            //gravityRotate = -20;
            phaseSaut = monte;
            son.playJump();
        }
    }
    else if (toucheActive)
        toucheActive=0;
    gravity += 0.28 + (gravity<-1)*0.12;
    //gravity -= (0.28 + (gravity<1)*0.12);
    positionTheoriqueY += gravity;

    /*
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        positionTheoriqueY --;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        positionTheoriqueY ++;
    }*/

    sprite_Flappy[animationKey].setPosition(Vector2f(250, (int)positionTheoriqueY));

    if (phaseSaut == monte)
    {
        if (gravityRotate< (-20))
        {
            phaseSaut = commenceADescendre;
            gravityRotate=-19;
        }
        else if (gravityRotate >10)
            gravityRotate-=5;
        else
        gravityRotate -=3;
    }
    else if (phaseSaut == commenceADescendre)
    {
        if ((gravityRotate+=0.01) >-18.9)
            phaseSaut = descend;
    }
    else if (gravity<1)
    {
        gravityRotate +=0.3;
    }
    else if (gravityRotate < 90)
        gravityRotate +=2;

    sprite_Flappy[animationKey].setRotation(gravityRotate);
}

void Flappy :: afficherFlappy ()
{
    fenetre.draw(sprite_Flappy[animationKey]);
}

void Flappy :: afficherAutres (vector <StructureEchange*> tableau, Level &level, TexteObj &texte)
{
    for (int a=0; a<tableau.size(); a++)
    {
//        tuyauxPassed << structureRecois.pixelEnCours
        int autre_TuyauxPassed = tableau[a]->multiple;
        int autre_PixelPassed = tableau[a]->pixelEnCours;
        int positionX(0);

        positionX = (autre_TuyauxPassed * 600)+autre_PixelPassed; //autre_PixelPassed - level.getTuyauxPixelEnCours() );//- autre_PixelPassed) %600;

        int maPosition = level.getMultiple()*600 + level.getTuyauxPixelEnCours();
        //cout << "\nMaPosit+350="<<maPosition+350<<"  autre+250="<<positionX+250;
        if ((positionX+250)>=maPosition && (positionX) <(maPosition+350))
       {
            sprite_Flappy[2].setPosition(Vector2f(positionX - maPosition + 250, tableau[a]->flappy_Hauteur));
            sprite_Flappy[2].setRotation(tableau[a]->flappy_orientation);
            fenetre.draw(sprite_Flappy[2]);

            texte.affTexte((tableau[a]->nomJoueur),positionX - maPosition + 225,tableau[a]->flappy_Hauteur-30, fenetre, 15);
       }
    }
}

bool Flappy :: animationDuMort (int hauteurSol)
{
    if (gravityRotate<90)
        gravityRotate+=3;
    gravity+=0.3;
    sprite_Flappy[animationKey].setRotation(gravityRotate);


    sprite_Flappy[animationKey].setPosition(Vector2f(250, (int)(positionTheoriqueY+=gravity)));

    if ((getPosition_Y()+getHauteur())>hauteurSol)
    {
        positionTheoriqueY = hauteurSol - getHauteur()+28;
        sprite_Flappy[animationKey].setPosition(Vector2f(250, (int)(positionTheoriqueY)));
    }

    return ((getPosition_Y()+getHauteur())>hauteurSol);

}
