//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Son.h"

class Level
{
    public:
        Level(sf::RenderWindow &fenetreRecois, int &scoreRecois, Son &sonRecois);
        ~Level();
        bool defilement(sf::FloatRect flappySurface);
        void afficherLevel(bool levelMovement = 0);
        void affLevel();
        void initGame(int tuyauxRecois [100]);
        void initGameOffline();

        int getTuyauxPixelEnCours () {return tuyauxpixelEnCours;}
        int getTuyauxEnCours () {return tuyauEnCours;}
        int getMultiple () {return multiple;}

        int getPosititTuyauxIndice (int indice) {return positions[indice][0];}

        int getHauteurSol () {return sprite_Sol.getGlobalBounds().top;}

    protected:
    sf::Texture texture_Sol;
    sf::Sprite sprite_Sol;

    sf::Texture texture_Fond;
    sf::Sprite sprite_Fond;

    sf::Image image_Tuyaux;
    sf::Texture texture_Tuyaux;
    sf::Sprite sprite_Tuyaux[2];


    sf::RenderWindow &fenetre;
    Son &son;

    int vitesseDefilement;

    int tuyaux[100];
    int tuyauEnCours;
    int tuyauxpixelEnCours;
    int positions[3][2];

    int multiple;

    int &score;


};

#endif // LEVEL_H
