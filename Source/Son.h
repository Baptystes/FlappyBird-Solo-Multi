//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#ifndef SON_H
#define SON_H
#include <SFML/Audio.hpp>

class Son
{
    public:
        Son();
        void playVictoire ();
        void playJump ();
        void playPoint ();

    protected:
        sf::SoundBuffer buffer_Victoire;
        sf::Sound son_Victoire;

        sf::SoundBuffer buffer_Jump;
        sf::Sound son_Jump;

        sf::SoundBuffer buffer_Point;
        sf::Sound son_Point;


    private:
};

#endif // SON_H
