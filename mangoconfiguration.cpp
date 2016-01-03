#include "mangoconfiguration.h"

mangoConfiguration::mangoConfiguration()
{
}
mangoConfiguration::mangoConfiguration(QString port, PortSettings configurations):QextSerialPort(port,configurations,QextSerialPort::EventDriven)
{

}
mangoConfiguration::~mangoConfiguration()
{

}

QString mangoConfiguration::setRecurence()
{
    qDebug()<<"recurence="<<recurence;
    setRec="$R"+recurence+"\r\n";
    qDebug()<<"setRec="<<setRec;
    if(setRec.length()!=9)
    {
        return errorString();
    }
    else
    {
        return setRec;
    }
}


QString mangoConfiguration::getNom()
{
    /**********************************************************************/
   /**** !!! Pour l'utilisation de cette methode include un Timer !!! ****/
  /**** !!! Sinon la méthode n'a pas le temps de lire la valeur  !!! ****/
 /*********** !!! retourner par la carte d'acquisition !!! *************/
/**********************************************************************/
    rqtNom="$C?\r\n";
    qDebug()<<"rqtNom="<<rqtNom;
    return rqtNom;

}

QString mangoConfiguration::setNom()
{
    extractionNom();
    return nomMango;
}

QString mangoConfiguration::getRecurence()
{
    extractionNom();
    return recurence;
}
QString mangoConfiguration::activiteGSM()
{
    return actvGSM;
}

void mangoConfiguration::extractionNom()
{
    /***************************************************************/
   /************ Extraction des elements de la réponse ************/
  /***************************************************************/

    QString rpNomTemp = reponseNom;
    qDebug()<<"Releve Nom="<<rpNomTemp;

    //Extraction des éléments

    QStringList valNomTemp= rpNomTemp.split("=",QString::SkipEmptyParts);

   /***************************************************************/
  /************ Suppression des caractéres en trop ***************/
 /***************************************************************/
    valNomTemp[2].replace("E","");
    valNomTemp[2].replace("R","");

    valNomTemp[3].replace("G","");
    valNomTemp[3].replace("S","");
    valNomTemp[3].replace("M","");

    valNomTemp[4].replace("\r","");
    valNomTemp[4].replace("\n","");

    qDebug()<<"nom="<<valNomTemp[2];

    nomMango=valNomTemp[2];
    recurence=valNomTemp[3];
    actvGSM=valNomTemp[4];

}
