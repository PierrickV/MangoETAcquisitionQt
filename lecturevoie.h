#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QDebug>


#ifndef LECTUREVOIE_H
#define LECTUREVOIE_H

class lectureVoie : public QextSerialPort
{
public:
    lectureVoie();
    lectureVoie(QString port, PortSettings configurations);
    ~lectureVoie();
    QString getMesure();
private: //Méthode

public: //Attribut
    QString reponseMesure;
private: //Méthode
    QString rqtMesure;

};

#endif // LECTUREVOIE_H
