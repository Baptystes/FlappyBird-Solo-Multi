//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Structures.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "Texte.h"
#include "windows.h"
using namespace sf;
using namespace std;
#define VERSION 1


Echange :: Echange ()
{
}

Echange :: ~Echange ()
{
    for (int a=0; a<10; a++);
}

bool Echange :: connexion (RenderWindow &fenetre, sf::Image &captureEcran, string champ[])
{

    bool erreurConnexion=0;
    identifiant_Nom = champ[1];
    identifiant_MotDePasse = champ[2];


    TexteObj texte;
    Texture texture_CaptureEcran;
    texture_CaptureEcran.loadFromImage(captureEcran);
    Sprite sprite_CaptureEcran;
    sprite_CaptureEcran.setTexture(texture_CaptureEcran);
    sprite_CaptureEcran.setPosition(Vector2f(0,0));

    string phraseEtat="";

    //
   // else


    fenetre.clear();
    fenetre.draw(sprite_CaptureEcran);
    phraseEtat += "Recherche du serveur...";
    cout<<"Recherche du serveur...";
    texte.affTexte(phraseEtat, 5,138,fenetre,15);
    fenetre.display();

    status = socket.connect(champ[0], 53000, sf::seconds(3));
    if (status != Socket::Done)
    {
        phraseEtat +="\nServeur introuvable.\n";
        cout <<"\nServeur introuvable.\n";
        texte.affTexte(phraseEtat, 5,138,fenetre,15);
        fenetre.display();
        erreurConnexion=1;
    }
    else
    {
        packet.clear();
        phraseEtat +=" Ok!\nEnvoi du pseudo...";
        cout <<" Ok!\nEnvoi du pseudo...";
        texte.affTexte(phraseEtat, 5,138,fenetre,15);
        fenetre.display();

        double versionDuJeu=VERSION;
        packet<<identifiant_Nom<<versionDuJeu<<identifiant_MotDePasse;
        while (socket.send(packet) != Socket::Done);
        phraseEtat +=" Ok!\nReception du niveau...\n\nGet Ready...";
        cout <<" Ok!\nReception du niveau...\n\nGet Ready...";
        texte.affTexte(phraseEtat, 5,138,fenetre,15);
        fenetre.display();

        packet.clear();
        if (socket.receive(packet) != Socket::Done)
        {
            phraseEtat+="\nErreur: Mettre a jour le jeu\nou Entrer un bon mot de passe !\n";
            cout <<"\nErreur: Jeu pas à jour\nou mot de passe incorrect.\n";
            erreurConnexion=1;
            texte.affTexte(phraseEtat, 5,138,fenetre,15);
            fenetre.display();
            Sleep(1000);
        }
        else
        {
            for (int a=0; a<100; a++)
                packet>>tuyaux[a];

            meilleurScore=0;
            packet>>meilleurScore;
            ////////////////////////////////
            cout <<" CONNECTED !";


            nombreDeJoueurs=0;
            socket.setBlocking(false);

            tonScore = "Moi :";

            phraseEtat +=" Go !";
            texte.affTexte(phraseEtat, 5,138,fenetre,15);
            fenetre.display();
        }
    }
    return erreurConnexion;
}

void Echange :: donnees_Envoi (StructureEchange structureToSend)
{
    packet.clear();
    structureToSend.nomJoueur = identifiant_Nom;
    packet << structureToSend;
    socket.send(packet);
}


void Echange :: donnees_Reception (vector <StructureEchange*> &flappyAdverses)
{

    packet.clear();
    status = socket.receive(packet);

    if (status == Socket::Done)
    {
        for (int a=0; a<nombreDeJoueurs; a++)
            delete flappyAdverses[a];

        packet>>nombreDeJoueurs;
        /*for (int a=0; a<flappyAdverses.size(); a++)
        {
            delete flappyAdverses[a];
        }*/
        flappyAdverses.clear();
        for (int a=0; a<nombreDeJoueurs; a++)
        {
            StructureEchange *structure = new StructureEchange;
            packet>>*structure;
            flappyAdverses.push_back(structure);
        }
        int topTroisRecu(0);
        packet>>topTroisRecu;
        //cout << "\nRECU="<<topTroisRecu;
        if (topTroisRecu == 1)
        {
            for (int a=0; a<3; a++)
                packet>>meilleursJoueurs[a];
        }

    }
    else
    {
        nombreDeJoueurs = 0;
    }


}

void Echange :: afficherTopTrois (sf::RenderWindow &fenetre, TexteObj &texte, int &meilleurScoreRecois)
{
    for (int a=0; a<3; a++)
    {
        if (meilleursJoueurs[2-a].score>0)
        {
            texte.affTexte(meilleursJoueurs[2-a].nom, a*12+10, 453 + a*15, fenetre, 13);
            texte.affTexte(meilleursJoueurs[2-a].score, a*12 + 110, 453 + a*15, fenetre,13);
        }
    }
    texte.affTexte(tonScore, 310, 467, fenetre, 17);
    texte.affTexte(meilleurScoreRecois, 360, 467, fenetre, 17);
}



void Echange :: affInfos (const StructureEchange &structure)
{
    cout << "Passed="<<structure.multiple << "  PixelEnCours="<<structure.pixelEnCours<<"  Hauteur="<<structure.flappy_Hauteur<<"  Orientation"<<structure.flappy_orientation<<endl;
}



