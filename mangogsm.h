#include "qextserialenumerator.h"
#include "qextserialport.h"
#include <QString>
#include <QTimer>
#include <QStringList>
#include <QDebug>

#ifndef MANGOGSM_H
#define MANGOGSM_H

class mangoGSM : public QextSerialPort
{
public://Méthode
    mangoGSM();
    mangoGSM(QString port, PortSettings configurations);
    ~mangoGSM();

    QString miseON();
    //Méthode pour le nombre de contact enregistrer dans Mango
    QString setNbrContact(); //Ecriture du nombre de personne a contacté en expedition
    QString getNbrContact(); //Lecture du nombre de contact

    //Méthode de lecture et d'ecriture du repertoire en memoire dans mango
    QString setRepertoire();
    QString getRepertoire();

    //Méthode pour programmer l'utilisation du GSM en expedition
    QString setProgrammation();
    QString getProgrammation();

    //Permet de rentrer le code PIN
    QString setPIN();

    //Méthode d'envoie de sms de test
    QString setTest();


private://Méthode
    void traitementNbrContact();

    void traitementRepertoire();



public://Attribut
    QString nbrNumContact;
    QString rpsRepertoire;
    QString numero;
    QString prenom;
    QString nom;
    QString jour;
    QString mois;
    QString annee;
    QString heure;
    QString minute;
    QString recurence;
    QString nbrSms;
    QString pin;
    QString programmationGsm;



private://Attribut
    QString miseOn;
    QString rqtNbrContact;
    QString rqtRepertoire;
    QString rqtProgrammation;
    QString setPin;
    QString gsmTst;

};

#endif // MANGOGSM_H
