#include "e_numerique.h"

E_numerique::E_numerique()
{
}
E_numerique::~E_numerique()
{

}

QString E_numerique::getENum1()
{
    extractionValENum();
    return ENum1;
}

QString E_numerique::getENum2()
{
    extractionValENum();
    return ENum2;
}

void E_numerique::extractionValENum()
{
        /***************************************************************/
       /****Extraction des valeurs de voies numérique et analogique****/
      /***************************************************************/

    QString rpMesureTemp = reponseMesure;
    qDebug()<<"Releve de mesure Numclasse="<<rpMesureTemp;

    //Extraction des éléments

    QStringList valvoie= rpMesureTemp.split(";",QString::SkipEmptyParts);

       /***************************************************************/
      /***********Recuperation et traitement de valvoie[8]************/
     /***************************************************************/

    QStringList valBin=valvoie[8].split("",QString::SkipEmptyParts);

    ENum1=valBin[4];
    ENum2=valBin[5];
}
