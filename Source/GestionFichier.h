//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Texte.h"

class Fichier{
public:
    Fichier ();
   // ~Fichier ();

    void inscriptionFichier (std::string champ[]);
    void lectureFichier (std::string champ[]);



protected:
    FILE *fichier;
    std::string identifiant_Nom;
    std::string identifiant_MotDePasse;




};


#endif
