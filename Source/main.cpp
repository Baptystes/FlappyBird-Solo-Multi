//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Structures.h"
#include "Level.h"
#include "Flappy.h"
#include "Texte.h"
#include "Son.h"
#include <iostream>
#include "windows.h"
using namespace sf;
using namespace std;
#include <vector>
#include <ctime>

#include "GestionFichier.h"


StructureEchange genererStructureMoi(Flappy &flappy, Level &level, int score)
{
    StructureEchange structure;
    structure.flappy_Hauteur = (int) flappy.getPositions_InGame().y;
    structure.flappy_orientation = flappy.getRotation();
    structure.pixelEnCours = level.getTuyauxPixelEnCours();
    structure.score = score;
   // cout <<"SOCRE="<<score;
    //structure.tuyauxPassed = score;//level.getTuyauxEnCours();
    structure.multiple = level.getMultiple();
    return structure;
}

bool champsValides (string champ[])
{
     return (champ[0].size()>0 && champ[1].size()>2 && champ[2].size()>2);
}

int main()
{
    Texture texture_Menu;
    Image image_Menu;
    image_Menu.loadFromFile("data/menu.png");

    for (int a=0; a<image_Menu.getSize().y; a++)
    {
        for (int b=0; b<image_Menu.getSize().x; b++)
        {
            if (image_Menu.getPixel(b,a) == Color(255,0,0) )
                image_Menu.setPixel(b,a, Color::Transparent);
        }
    }
    texture_Menu.loadFromImage(image_Menu);

    Sprite sprite_fondMenu, sprite_Chiffre[11], sprite_Selecteur, sprite_RectangleSelection, sprite_BoutonValider, sprite_BoutonValiderSelection;

    sprite_fondMenu.setTexture(texture_Menu);
    sprite_fondMenu.setTextureRect(IntRect(0,0,448,500));
    sprite_fondMenu.setPosition(Vector2f(0,0));

    sprite_Selecteur.setTexture(texture_Menu);
    sprite_Selecteur.setTextureRect(IntRect(452,0,66,42));

    for (int a=0; a<11; a++)
    {
        sprite_Chiffre[a].setTexture(texture_Menu);
        sprite_Chiffre[a].setTextureRect(IntRect(449+a*16,57,16,21));
    }

    sprite_RectangleSelection.setTexture(texture_Menu);
    sprite_RectangleSelection.setTextureRect(IntRect(449,96,40,381));
    //sprite_RectangleSelection.setOrigin(38,390);
    sprite_RectangleSelection.setRotation(270);

    sprite_BoutonValider.setTexture(texture_Menu);
    sprite_BoutonValiderSelection.setTexture(texture_Menu);
    sprite_BoutonValider.setTextureRect(IntRect(449,43,81,24));
    sprite_BoutonValiderSelection.setTextureRect(IntRect(449,67,81,24));

    srand(time(0));
    //RenderWindow fenetre(VideoMode(600,500,32), "Flappy Bat !  - Baptystes -  0.8", Style::Close);//, sf::ContextSettings(24, 8, 0, 3, 3));
    RenderWindow fenetre;
    fenetre.setVerticalSyncEnabled(0);
    //fenetre.setFramerateLimit(60);

    TexteObj texte;
    Son son;
    Fichier fichier;

    int score(0);
    Level level(fenetre, score, son);
    Flappy flappy(fenetre, son);
    Event event;

    string champ[3];

    fenetre.create(VideoMode(448,500,32), "Flappy Bat !  - Baptystes -  0.9" );//, Style::Titlebar);
    fenetre.setActive(1);
    fenetre.setFramerateLimit(60);
    //fenetre.setFramerateLimit(60);

    int quitter = 0;
    int choix = 0;
    while (quitter != 2)
    {

        //{  = avant Menu =
        fenetre.draw(sprite_fondMenu);
        sprite_Selecteur.setPosition(Vector2f(191,102));
        fenetre.draw(sprite_Selecteur);

        fichier.lectureFichier(champ);
        if (champ[0].size()<34)
            texte.affTexteMiddle(champ[0], 224,296, fenetre);
        else
            texte.affTexteMiddle(champ[0], 224,302, fenetre, 11);
        texte.affTexteMiddle(champ[1], 224,375, fenetre);
        texte.affTexteMiddle(champ[2], 224,456, fenetre);

        texte.affTexteo("Baptystes", 0,0, fenetre, 20);

        fenetre.display();

        //}
        string champEnCours="";
        bool finMenu=0;

        int champSelection = 0;
        bool champSaisieEnCours = 0;
        bool boutonValideVise=0;
        bool champASupprimer=1;
        score=0;

        quitter = 0;
        while (fenetre.isOpen() && !finMenu && quitter != 2)
        {
            fenetre.waitEvent(event);
            if (event.type == Event::Resized)
                exit(0);
            fenetre.clear();
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                choix=3;
                fenetre.close();
                quitter = 2;
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
            {
                choix--;
                if (choix<0)
                    choix+=2;
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
            {
                choix++;
                if (choix>1)
                    choix-=2;
            }
            else if (event.type == Event::MouseMoved)
            {
                if (event.mouseMove.x >= 182 && event.mouseMove.x <= 258)
                {
                    if (event.mouseMove.y>= 104 && event.mouseMove.y<= 140)
                        choix=0;
                    else if (event.mouseMove.y>= 168 && event.mouseMove.y<= 202)
                        choix=1;
                }
                if (event.mouseMove.x >= 37 && event.mouseMove.x <= 413 && !champSaisieEnCours)
                {
                    if (event.mouseMove.y>= 291 && event.mouseMove.y<= 326)
                        champSelection = 1;
                    else if (event.mouseMove.y>= 369 && event.mouseMove.y<= 404)
                        champSelection = 2;
                    else if (event.mouseMove.y>= 444 && event.mouseMove.y<= 479)
                        champSelection = 3;
                    else if (champSelection)
                        champSelection=0;
                }
                else if (champSelection && !champSaisieEnCours)
                        champSelection=0;

                if ((event.mouseMove.x >= 333 && event.mouseMove.x <= 413) && (event.mouseMove.y >=(262 + 79*(champSelection-1)) && event.mouseMove.y <=(286 + 79*(champSelection-1))) && champSaisieEnCours)
                    boutonValideVise=1;
                else if (boutonValideVise)
                    boutonValideVise=0;

            }

            if (event.type == sf::Event::MouseButtonPressed || event.type == Event::KeyPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left || event.key.code == Keyboard::Return)
                {
                    if (champSelection && !champSaisieEnCours)
                    {
                        champSaisieEnCours=1;
                    }

                   // cout <<event.mouseMove.x<<"\n";
                    if ((event.key.code == Keyboard::Return && champSaisieEnCours) || ((event.mouseButton.x >= 333 && event.mouseButton.x <= 413) && (event.mouseButton.y >=(262 + 79*(champSelection-1)) && event.mouseButton.y <=(286 + 79*(champSelection-1))) && boutonValideVise))
                    {
                        champSaisieEnCours=0;
                        boutonValideVise=0;
                        champSelection=0;
                        champASupprimer=1;
                        if (champsValides(champ))
                            fichier.inscriptionFichier(champ);
                        //exit(0);
                    }
                    else if (((((event.mouseButton.y>= 104 && event.mouseButton.y<= 140) || (event.mouseButton.y>= 168 && event.mouseButton.y<= 202)) && event.mouseButton.x >= 182 && event.mouseButton.x <= 258) || (event.key.code == Keyboard::Return && !champSaisieEnCours))  && ((choix==1 && champsValides(champ)) || choix==0))
                    {
                        finMenu=1;
                        if (choix != 0)
                            fichier.inscriptionFichier(champ);
                    }

                }
            }

            /*
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
            {
                if (champSaisieEnCours)
                {
                    champSaisieEnCours=0;
                    boutonValideVise=0;
                    champSelection=0;
                    champASupprimer=1;
                    fichier.inscriptionFichier(champ);
                }
                else if ((((choix==1 && champ[0].size()>0) && champ[1].size()>2 && champ[2].size()>2) || choix==0) && !champSaisieEnCours)
                {
                    finMenu=1;
                    fichier.inscriptionFichier(champ);
                }
            }
            */

            fenetre.draw(sprite_fondMenu);

            if (champSelection)
            {
                sprite_RectangleSelection.setPosition(Vector2f(35,329 + 79*(champSelection-1)));
                fenetre.draw(sprite_RectangleSelection);
            }
            if (champSaisieEnCours)
            {
                sprite_BoutonValider.setPosition(Vector2f(333, 262+79*(champSelection-1)));
                fenetre.draw(sprite_BoutonValider);
                if (champASupprimer)
                {
                    //champ[champSelection-1]="";
                    champASupprimer=0;
                }
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::BackSpace)
                    {
                        champ[champSelection-1] = champ[champSelection-1].substr(0,champ[champSelection-1].size()-1);
                        //fenetre.pollEvent(event);
                    }
                }
                else if (event.type == sf::Event::TextEntered)
                {
                    if ((event.text.unicode>=33 && event.text.unicode <= 126) && ((champSelection==2 && champ[champSelection-1].size()<10) || (champSelection==3 && champ[champSelection-1].size()<8) || (champSelection==1 && champ[champSelection-1].size()<60)))
                        champ[champSelection-1]+=static_cast<char>(event.text.unicode);
                }


            }
            else if (choix==1 && !champsValides(champ))
            {
                sprite_RectangleSelection.setColor(Color::Red);
                if (champ[0].size()==0)
                {
                    sprite_RectangleSelection.setPosition(Vector2f(35,329));
                    fenetre.draw(sprite_RectangleSelection);
                }
                else if (champ[1].size()<=2)
                {
                    sprite_RectangleSelection.setPosition(Vector2f(35,329 + 79*1));
                    fenetre.draw(sprite_RectangleSelection);
                }
                else if (champ[2].size()<=2)
                {
                    sprite_RectangleSelection.setPosition(Vector2f(35,329 + 79*2));
                    fenetre.draw(sprite_RectangleSelection);
                }
                sprite_RectangleSelection.setColor(Color::White);
            }




            if (boutonValideVise)
            {
                sprite_BoutonValiderSelection.setPosition(Vector2f(333, 262+79*(champSelection-1)));
                fenetre.draw(sprite_BoutonValiderSelection);
            }


            sprite_Selecteur.setPosition(Vector2f(191,choix*63+102));
            fenetre.draw(sprite_Selecteur);

            if (champ[0].size()<34)
                texte.affTexteMiddle(champ[0], 224,296, fenetre);
            else
                texte.affTexteMiddle(champ[0], 224,302, fenetre, 11);

            texte.affTexteMiddle(champ[1], 224,375, fenetre);
            texte.affTexteMiddle(champ[2], 224,456, fenetre);

            texte.affTexteo("Baptystes", 0,0, fenetre, 20);
            fenetre.display();
        }

        //system("pause");
        if (choix==1) // Online
        {
            Image captureEcran = fenetre.capture();
            Echange echange;
            vector <StructureEchange*> flappyAdverses;
            int meilleurScore = 0;
            if (!echange.connexion(fenetre, captureEcran, champ))  //Connexion reussie
            {
                level.initGame(echange.getTuyaux());
                level.afficherLevel();
                flappy.init();

                meilleurScore = echange.getBestScore();

                Packet packet;
                echange.donnees_Envoi(genererStructureMoi(flappy, level, -1));
            }
            else
            {
                fenetre.pollEvent(event);
                //sleep(Time::asMilliseconds(10));
                Sleep(1600);
                quitter=1;
            }

            while (!quitter)
            {
                //fenetre.pollEvent(event);
                while (fenetre.pollEvent(event))
                {
                    if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                        quitter=1;
                }

                fenetre.clear();
                if (level.defilement(FloatRect(flappy.getPosition_X()+7,flappy.getPosition_Y()+10,flappy.getLargeur()-19,flappy.getHauteur()-15)) || (flappy.getPosition_Y()+flappy.getHauteur())>level.getHauteurSol())
                {
                    son.playVictoire();
                    while (!flappy.animationDuMort(level.getHauteurSol()))
                    {

                        level.afficherLevel(0);
                        flappy.afficherFlappy();
                        texte.affTexte(score, 215,200, fenetre, 60);

                        echange.donnees_Envoi(genererStructureMoi(flappy, level, score));
                        echange.donnees_Reception(flappyAdverses);
                        echange.afficherTopTrois(fenetre, texte, meilleurScore);
                        flappy.afficherAutres(flappyAdverses, level, texte);
                        fenetre.display();
                        while (fenetre.pollEvent(event));
                        //system("pause");

                    }

                    echange.donnees_Envoi(genererStructureMoi(flappy, level, -score-1));
                    if (score > meilleurScore)
                        meilleurScore = score;
                    // echange.donnees_RecoisTopTrois();

                    while (!(Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::RControl) || Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape )))
                    {
                        level.afficherLevel(0);
                        flappy.afficherFlappy();
                        texte.affTexte(score, 215,200, fenetre, 60);


                        echange.donnees_Envoi(genererStructureMoi(flappy, level, score));
                        echange.donnees_Reception(flappyAdverses);
                        //cout <<"\n" <<echange.getNombreDeJoueurs();
                        //for (int e=0; e<echange.getNombreDeJoueurs(); e++);
                        //echange.affInfos(*flappyAdverses[0]);
                        //cout << "Passed="<<structure.tuyauxPassed << "  PixelEnCours="<<structure.pixelEnCours<<"  Hauteur="<<structure.flappy_Hauteur<<"  Orientation"<<structure.flappy_orientation<<endl;
                        echange.afficherTopTrois(fenetre, texte, meilleurScore);
                        flappy.afficherAutres(flappyAdverses, level, texte);
                        fenetre.display();
                        while (fenetre.pollEvent(event));

                    }
                    level.initGame(echange.getTuyaux());
                    level.afficherLevel(0);
                    flappy.init();
                }

                echange.donnees_Envoi(genererStructureMoi(flappy, level, score));
                echange.donnees_Reception(flappyAdverses);
                echange.afficherTopTrois(fenetre, texte, meilleurScore);
                flappy.afficherAutres(flappyAdverses, level, texte);
                flappy.mouvement();

                texte.affTexte(score, 215,453, fenetre, 50);
                texte.affTexteo("Baptystes", 0,0, fenetre, 20);

                flappy.afficherFlappy();
                fenetre.display();
            }

            for (int a=0; a<flappyAdverses.size(); a++)
            {
                delete flappyAdverses[a];
            }
       // system("pause");
    }//Multiplayers==1

        else if (choix == 0)
        {

            level.initGameOffline();
            level.afficherLevel();
            flappy.init();

            int meilleurScore = 0;
            while (!quitter)
            {

                while (fenetre.pollEvent(event))
                {
                    if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                        quitter=1;
                }

                fenetre.clear();
                if ((level.defilement(FloatRect(flappy.getPosition_X()+7,flappy.getPosition_Y()+10,flappy.getLargeur()-19,flappy.getHauteur()-15)) || (flappy.getPosition_Y()+flappy.getHauteur())>level.getHauteurSol()) && 1)
                {
                    son.playVictoire();
                    while (!flappy.animationDuMort(level.getHauteurSol()) && !Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        level.afficherLevel(0);
                        flappy.afficherFlappy();
                        texte.affTexte(score, 215,200, fenetre, 60);
                        texte.affTexteo("Baptystes", 0,0, fenetre, 20);
                        fenetre.display();
                        while (fenetre.pollEvent(event));

                    }
                    if (score > meilleurScore)
                        meilleurScore = score;

                    while (!(Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::RControl) || Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape )))
                    {
                        level.afficherLevel(0);
                        flappy.afficherFlappy();
                        texte.affTexte(score, 215,200, fenetre, 60);
                        texte.affTexteo("Baptystes", 0,0, fenetre, 20);
                        fenetre.display();
                        while (fenetre.pollEvent(event));

                    }
                    level.initGameOffline();
                    level.afficherLevel(0);
                    flappy.init();
                }

                flappy.mouvement();

                texte.affTexte(score, 215,453, fenetre, 50);
                texte.affTexteo("Baptystes", 0,0, fenetre, 20);

                flappy.afficherFlappy();
                fenetre.display();

            }
        }    //Multiplayers==0
    }
    return 0;
}
