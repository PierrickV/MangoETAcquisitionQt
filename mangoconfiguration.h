#include "qextserialenumerator.h"
#include "qextserialport.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QMessageBox>

#ifndef MANGOCONFIGURATION_H
#define MANGOCONFIGURATION_H

class mangoConfiguration : public QextSerialPort
{
public://Méthode
    mangoConfiguration();
    mangoConfiguration(QString port, PortSettings configurations);
    ~mangoConfiguration();
    QString setRecurence();
    QString getRecurence();
    QString getNom();
    QString setNom();
    QString activiteGSM();

private: //Méthode
    void extractionNom();
public://Attribut
    QString recurence;
    QString reponseNom;

private://Attribut
    QString rqtNom;
    QString nomMango;
    QString setRec;
    QString actvGSM;
};

#endif // MANGOCONFIGURATION_H
