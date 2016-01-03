/*
 *  Réalisé par Pierrick VERAN
 *  VERSION : 27/05/2014
*/

#ifndef S_NUMERIQUE_H
#define S_NUMERIQUE_H

#include <QPlainTextEdit>
#include <QDebug>
#include <QString>
#include"qextserialport.h"
#include "qextserialenumerator.h"

class s_Numerique : public QextSerialPort
{
public:
    s_Numerique();
    s_Numerique(QString port, PortSettings configurations);

    void setNum1();
    void setNum2();

    QString getSNum1();
    QString getSNum2();

    QString envoieCommand();

private:
    QString valSNum1;
    QString valSNum2;
    QString send;


};

#endif // S_NUMERIQUE_H
