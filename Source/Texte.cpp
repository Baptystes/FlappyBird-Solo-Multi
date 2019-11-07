//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "Texte.h"
#include <string>
using namespace std;
using namespace sf;

TexteObj :: TexteObj()
{
    if (!font.loadFromFile("data/SansSerifShaded.ttf"))
        exit(1);
    if (!fontNames.loadFromFile("data/names.ttf"))
        exit(1);

    m_texte.setFont(font);
    m_texte.setCharacterSize(20);
    m_texte.setColor(Color::Black);
    m_texte.setColor(Color :: Black);

    m_texteNames.setFont(fontNames);
    m_texteNames.setCharacterSize(25);
    m_texteNames.setColor(Color::Black);



}



void TexteObj :: affTexte(string &texte, int positionX, int positionY, RenderWindow &fenetre,int taille, int rotation)
{
    m_texteNames.setString(texte);
    m_texteNames.setRotation(rotation);
    m_texteNames.setCharacterSize(taille);
    m_texteNames.setPosition(Vector2f(positionX, positionY));
    fenetre.draw(m_texteNames);
   // m_texte.setPosition()
}

void TexteObj :: affTexteMiddle(string &texte, int positionX, int positionY, RenderWindow &fenetre,int taille, int rotation)
{
    m_texteNames.setString(texte);
    m_texteNames.setRotation(rotation);
    m_texteNames.setCharacterSize(taille);
    m_texteNames.setPosition(Vector2f(positionX - (int)(m_texteNames.getGlobalBounds().width/2), positionY));
    fenetre.draw(m_texteNames);
   // m_texte.setPosition()
}


void TexteObj :: affTexteo(char texte[], int positionX, int positionY, RenderWindow &fenetre,int taille, int rotation)
{
    string texteAff = texte;
    m_texte.setString(texte);
    m_texte.setRotation(rotation);
    m_texte.setCharacterSize(taille);
    m_texte.setPosition(Vector2f(positionX, positionY));
    fenetre.draw(m_texte);
   // m_texte.setPosition()
}

void TexteObj :: affTexte(int chiffre, int positionX, int positionY, RenderWindow &fenetre,int taille, int rotation)
{
    ostringstream texte_Converti;

    texte_Converti.seekp(0);
    texte_Converti<<chiffre;
    Text texteAff;
    m_texteNames.setString(texte_Converti.str());

    m_texteNames.setRotation(rotation);
    m_texteNames.setCharacterSize(taille);
    m_texteNames.setPosition(Vector2f(positionX, positionY));
    fenetre.draw(m_texteNames);
   // texteAff.setPosition()
}

