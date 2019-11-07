//Par Baptystes
//Youtube : https://www.youtube.com/user/Baptystes
//© Baptystes 2014

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Texte.h"
typedef struct StructureEchange StructureEchange;
struct StructureEchange
{
    int multiple, pixelEnCours, flappy_Hauteur, flappy_orientation, score;
    std::string nomJoueur;

};

inline sf::Packet& operator <<(sf::Packet& packet, const StructureEchange& structureRecois)
{
    //return packet << structureRecois.multiple << structureRecois.pixelEnCours << structureRecois.flappy_Hauteur << structureRecois.flappy_orientation << structureRecois.nomJoueur << structureRecois.score;
    return packet << structureRecois.multiple << structureRecois.pixelEnCours << structureRecois.flappy_Hauteur << structureRecois.flappy_orientation << structureRecois.score;
}

inline sf::Packet& operator >>(sf::Packet& packet, StructureEchange& structureRecois)
{
    return packet >> structureRecois.multiple >> structureRecois.pixelEnCours >> structureRecois.flappy_Hauteur >> structureRecois.flappy_orientation >> structureRecois.nomJoueur >> structureRecois.score;
}

typedef struct StructureTopTrois StructureTopTrois;
struct StructureTopTrois
{
    std::string nom; int score;
};
inline sf::Packet& operator <<(sf::Packet& packet, const StructureTopTrois& structureRecois)
{
    return packet << structureRecois.nom << structureRecois.score;
}

inline sf::Packet& operator >>(sf::Packet& packet, StructureTopTrois& structureRecois)
{
    return packet >> structureRecois.nom >> structureRecois.score;
}


class Echange{
public:
    Echange ();
    ~Echange ();

    bool connexion(sf::RenderWindow &fenetre,sf::Image &captureEcran, std::string champ[]);

    //void sendStructJeu (StructureEchange &structure);
    //void recoisStructJeu ();
   // void clientaAccepter ();

    int *getTuyaux () {return tuyaux;}

    void donnees_Envoi (StructureEchange structureToSend);
    void donnees_Reception  (std::vector <StructureEchange*> &flappyAdverses);
    int getBestScore () {return meilleurScore;}

    void affInfos (const StructureEchange &structure);
    int getNombreDeJoueurs() {return nombreDeJoueurs;}
    void afficherTopTrois (sf::RenderWindow &fenetre, TexteObj &texte, int &meilleurScoreRecois);



protected:
    sf::TcpListener listener;
    sf::TcpSocket socket;
    sf::Socket::Status status;

    //sf::TcpSocket clientSocketType;
    //std::vector <sf::TcpSocket*> clientSocket;
    std::vector <StructureEchange*> clientSauvegarde;


    sf::Packet packet;

    int tuyaux[100];

    int nombreDeJoueurs;


    FILE *fichier;
    std::string identifiant_Nom;
    std::string identifiant_MotDePasse;

    StructureTopTrois meilleursJoueurs[3];

    std::string tonScore;
    int meilleurScore;





};



#endif // STRUCTURES_H
