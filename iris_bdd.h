/*
 *  Réalisé par Pierrick VERAN
 *  VERSION : 28/05/2014
 *  Note: Ne pas oublier de modifier : "QT +=  sql" dans le .pro de votre projet.
 *  Sinon il ne compilera pas
 *
*/
#ifndef IRIS_BDD_H
#define IRIS_BDD_H

#include "QFile"
#include "QTextStream"
#include "QDebug"
#include <QtSql/QtSql>
#include <QTimer>

class IRIS_BDD
{

private: //Attributs privés

    //Déclaration de l'objet "ma base de donnée":
    QSqlDatabase myDB;

    //Chemin:
    QString cheminFichier;
    QString cheminBDD;

    //Donnnées du fichier de mesure:
    QString Date;
    QString Heure;
    QString Voie1;
    QString Voie2;
    QString Voie3;
    QString Voie4;
    QString Voie5;
    QString Voie6;
    QString Voie7;
    QString Voie8;
    QString eTor_1;
    QString eTor_2;
    QString sTor_1;
    QString sTor_2;
    QString Alti;
    QString Latitude;
    QString Hemisphere;
    QString Longitude;
    QString Elongation;
    QString St;
    QString Loc;

    //Données autre:
    QString NomCarteMango;
    QString TypeCarteMango;
    QString NumeroSerieCarteMango;

    QString NomRepertoire;
    QString PrenomRepertoire;
    QString NumeroTelRepertoire;

    QString NomCapteur;
    QString TypeCapteur;
    QString VoieCapteur;
    QString NomFichierConversionCapteur;

    //Indicateurs du nombre de ligne:
    int nbreLignes_Fichier;
    int numeroLigneFichier;

    int nbreLignes_TableMesure;
    int nbreLignes_TablePositionGPS;
    int nbreLignes_TableRepertoire;
    int nbreLignes_TableCarteMango;
    int nbreLignes_TableCapteur;

    int numeroLigne_TableMesure;
    int numeroLigne_TablePositionGPS;
    int numeroLigne_TableRepertoire;
    int numeroLigne_TableCarteMango;
    int numeroLigne_TableCapteur;

    int nbreErreurLignes_Fichier;
    int nbreBonneLignes_Fichier;


private: //Méthode privé

    void ouvertureBDD();
    void fermetureBDD();

    //Méthode de lecture des tables:
    void lireTableMesure();
    void lireTablePositionGPS();
    void lireTableRepertoire();
    void lireTableCarteMango();
    void lireTableCapteur();

    //Méthode de calcul du nombre de ligne que compose une table:
    void calculNbreLignes_TableMesure();
    void calculNbreLignes_TablePositionGPS();
    void calculNbreLignes_TableRepertoire();
    void calculNbreLignes_TableCarteMango();
    void calculNbreLignes_TableCapteur();



public: //Méthode public

    //Constructeur sans initialisation
    IRIS_BDD();

    //Constructeur avec initialisation
    IRIS_BDD(QString cheminVersBDD);
    IRIS_BDD(QString cheminVersBDD, QString cheminVersTXT);

    //Destructeur
    ~IRIS_BDD();


    //Méthode pour supprimer le contenu des tables
    void viderBDD();
    void viderTable_TableMesure();
    void viderTable_TablePositionGPS();
    void viderTable_TableRepertoire();
    void viderTable_TableCarteMango();
    void viderTable_TableCapteur();



    //Méthode d'écriture dans la base de données
    void parseToDB(); //Méthode pour l'extraction des données du fichier vers la base de donnée

    // Méthode " set " pour écrire dans les tables de la base de données

    void setTableMesure(QString myDate,QString myHeure, QString myVoie1, QString myVoie2,QString myVoie3,QString myVoie4,QString myVoie5,QString myVoie6, QString myVoie7, QString myVoie8, QString myeTor_1,QString myeTor_2,QString mysTor_1,QString mysTor_2);
    void setTablePositionGPS(QString myDate, QString myHeure, QString myAlti, QString myLatitude, QString myHemisphere, QString myLongitude, QString myElongation, QString mySt, QString myLoc);
    void setTableCarteMango(QString myNomCarteMango,QString myTypeCarteMango,QString myNumeroSerieCarteMango);
    void setTableRepertoire(QString myNomRepertoire, QString myPrenomRepertoire,QString myNumeroTelRepertoire);
    void setTableCapteur(QString myNomCapteur,QString mytypeCapteur,QString myNomFichierConversionCapteur, QString myVoieCapteur);

    void setCheminFichier(QString cheminVersTXT);


    //Méthode de lecture de la base de données
    //Méthode " get "

    QString getDate();
    QString getHeure();
    QString getVoie1();
    QString getVoie2();
    QString getVoie3();
    QString getVoie4();
    QString getVoie5();
    QString getVoie6();
    QString getVoie7();
    QString getVoie8();
    QString geteTor_1();
    QString geteTor_2();
    QString getsTor_1();
    QString getsTor_2();
    QString getAlti();
    QString getLatitude();
    QString getHemisphere();
    QString getLongitude();
    QString getElongation();
    QString getSt();
    QString getLoc();

    QString getNomCarteMango();
    QString getTypeCarteMango();
    QString getNumeroSerieCarteMango();

    QString getNomRepertoire();
    QString getPrenomRepertoire();
    QString getNumeroTelRepertoire();

    QString getNomCapteur();
    QString getTypeCapteur();
    QString getVoieCapteur();
    QString getNomFichierConversionCapteur();

    int getNbreLignes_TableMesure();
    int getNbreLignes_TablePositionGPS();
    int getNbreLignes_TableRepertoire();
    int getNbreLignes_TableCarteMango();
    int getNbreLignes_TableCapteur();

    int getNbreLignes_Fichier();
    int getNumeroLigneFichier();

    int getNumeroLigne_TableMesure();
    int getNumeroLigne_TablePositionGPS();
    int getNumeroLigne_TableRepertoire();
    int getNumeroLigne_TableCarteMango();
    int getNumeroLigne_TableCapteur();


    int getNbreErreurLignes_Fichier();
    int getNbreBonneLignes_Fichier();

    QString getCheminFichier();
    QString getCheminBDD();


    //Méthode pour se deplacer dans la BDD

    void lignePrecedente_TableMesure();
    void lignePrecedente_TablePositionGPS();
    void lignePrecedente_TableRepertoire();
    void lignePrecedente_TableCarteMango();
    void lignePrecedente_TableCapteur();

    void ligneSuivante_TableMesure();
    void ligneSuivante_TablePositionGPS();
    void ligneSuivante_TableRepertoire();
    void ligneSuivante_TableCarteMango();
    void ligneSuivante_TableCapteur();


};

#endif // IRIS_BDD_H
