/*
 *  Réalisé par Pierrick VERAN
 *  VERSION : 27/05/2014
*/

#ifndef SDTOPC_H
#define SDTOPC_H

#include <QDebug>
#include <QString>

//Pour la manipulation du fichier
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QIODevice>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>



//Pour la communication
#include"qextserialport.h"
#include "qextserialenumerator.h"

class SDToPC: public QextSerialPort
{
public:
    SDToPC();

    SDToPC(QString port, PortSettings configurations);
    //Envoie la requête qui permet d'aller lire le fichier sur la carte
    QString lectureFichier();
    //Envoie la requête qui permet d'aller lire la taille du fichier sur la carte
    QString lectureTailleFichier();
    //Fonction de calcul du temps de transfert
    int getTempsTransfert(QString tailleFichier);
    //Fonction qui permet d'aller sauvegarder le fichier après transfert
    void sauvegardeFichier(QString rcvString);
    void setCheminFichier(QString cheminVersTXT);


private:
    //Chemin
    QString cheminFichier;
    //Manipulation avant enregistrement
    int tailleFichier;
    int ContenuFichier;
    int tempsTransfert;
    //Requête
    QString LectureTailleFichier;
    QString LectureFichier;
    QString sendString;
    QString rcvString;


};

#endif // SDTOPC_H
