//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include "Son.h"
#include <SFML/Audio.hpp>
using namespace sf;

Son::Son()
{
    buffer_Victoire.loadFromFile("data/sons/victoire.wav");
    son_Victoire.setBuffer(buffer_Victoire);

    buffer_Jump.loadFromFile("data/sons/jump.caf");
    son_Jump.setBuffer(buffer_Jump);

    buffer_Point.loadFromFile("data/sons/point.aif");
    son_Point.setBuffer(buffer_Point);

}

void Son :: playVictoire ()
{
    son_Victoire.play();
}

void Son :: playJump ()
{
    son_Jump.play();
}

void Son :: playPoint()
{
    son_Point.play();
}

