//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include "GestionFichier.h"
using namespace sf;
using namespace std;

Fichier :: Fichier ()
{
    fichier = NULL;
    if (!(fichier = fopen("data/fichier.txt", "r+")))
    {
        fichier = fopen("data/fichier.txt", "w");
        fclose(fichier);
        fichier = fopen("data/fichier.txt", "r+");
        fprintf(fichier, "==  Pseudo  ==\n#Joueur *\n\n\n==  Infos  ==\nIP serveur @localhost");
        fclose(fichier);
    }
}

void Fichier :: inscriptionFichier (string champ[])
{
    string fichierTemp="";
    fichier = fopen("data/fichier.txt", "w+");
    //rewind(fichier);
    fichierTemp+="==  Pseudo  ==\n#";
    fichierTemp+=champ[1];
    fichierTemp+=" ";
    fichierTemp+=champ[2];
    fichierTemp+="\n==  Infos  ==\nIP serveur @";
    fichierTemp+= champ[0];
    fichierTemp+="\n&";
    fputs(fichierTemp.c_str(), fichier);

    fclose(fichier);
}

void Fichier :: lectureFichier (string champ[])
{
    char caractereEnCours = 0;
    fichier = fopen("data/fichier.txt", "r+");
    rewind(fichier);
    char nomTemporaire[20];
    char mdpTemporaire[20];
    char ipAdressTemporaire[60];

    while ((caractereEnCours=fgetc(fichier)) != EOF)
    {
        if (caractereEnCours == '#')
        {
            fscanf(fichier, "%s %s", nomTemporaire, mdpTemporaire);
            champ[1] = nomTemporaire;
            champ[2] = mdpTemporaire;
            cout <<"\nSalut "<<champ[1]<<" (mdp:"<<champ[2]<<")" <<"  -   Modifiable dans le fichier data/fichier.txt";
        }
        else if (caractereEnCours == '@')
        {
            fscanf(fichier, "%s",ipAdressTemporaire);
            champ[0] = ipAdressTemporaire;
        }
    }

    fclose(fichier);

    if (champ[1][0]==0 || champ[2][0]==0 || champ[1].size()>=11 ||champ[2].size()>=9 || champ[0][0]==0 || champ[0].size()>=31)
    {
        remove ("data/fichier.txt");
        exit(-1);
    }
}
