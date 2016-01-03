#include "lecturevoie.h"

lectureVoie::lectureVoie()
{
}

lectureVoie::lectureVoie(QString port,PortSettings configurations):QextSerialPort(port,configurations,QextSerialPort::EventDriven)
{
    //constructeur avec passage de parametre de port COM
}

lectureVoie::~lectureVoie()
{

}

QString lectureVoie::getMesure()
{
    /**********************************************************************/
   /**** !!! Pour l'utilisation de cette methode include un Timer !!! ****/
  /**** !!! Sinon la méthode n'a pas le temps de lire la valeur  !!! ****/
 /*********** !!! retourner par la carte d'acquisition !!! *************/
/**********************************************************************/
    rqtMesure="$M?\r\n";
    qDebug()<<"rqtMesure="<<rqtMesure;
    return rqtMesure;
}
