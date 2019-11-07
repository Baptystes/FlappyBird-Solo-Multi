//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#ifndef FLAPPY_H
#define FLAPPY_H
#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Son.h"
#include <vector>
#include "Level.h"
#include "Texte.h"
enum phaseDeSautEnum{
    monte,
    commenceADescendre,
    descend
};
class Flappy
{
    public:
        Flappy(sf::RenderWindow &fenetreRecois, Son &sonRecois);


        void init();
        void mouvement();
        bool animationDuMort(int hauteurSol);


        void afficherFlappy();
        void afficherAutres (std::vector <StructureEchange*> tableau, Level &level, TexteObj &texte);

        sf::FloatRect getGlobalBound() {return sprite_Flappy[animationKey].getGlobalBounds();}
        float getLargeur () {return sprite_Flappy[animationKey].getGlobalBounds().width;}
        float getHauteur () {return sprite_Flappy[animationKey].getGlobalBounds().height;}

        float getPosition_X () {return sprite_Flappy[animationKey].getGlobalBounds().left;}
        float getPosition_Y () {return sprite_Flappy[animationKey].getGlobalBounds().top;}

        sf::Vector2f getPositions_InGame () {return sprite_Flappy[animationKey].getPosition();}

        int getRotation () {return sprite_Flappy[animationKey].getRotation();}

    protected:
    sf::RenderWindow &fenetre;
    Son &son;

    sf::Image image_Flappy;
    sf::Texture texture_Flappy;
    sf::Sprite sprite_Flappy[3];

    int positionY; float positionTheoriqueY, gravity, gravityRotate, phaseSaut;
    int animationKey, animationTime;

    bool toucheActive;
};

#endif // FLAPPY_H
