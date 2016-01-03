#include "e_analogique.h"

e_analogique::e_analogique()
{
}

e_analogique::~e_analogique()
{

}
/**********************************************************************/
/******************* Appel de l'extraction des voies ******************/
/********************* Return des valeurs sur l'IHM *******************/
/**********************************************************************/
QString e_analogique::getVoie1()
{
    extractionValAnalog();
    return  valAnalog1;
}
QString e_analogique::getVoie2()
{
    extractionValAnalog();
    return  valAnalog2;
}
QString e_analogique::getVoie3()
{
    extractionValAnalog();
    return  valAnalog3;
}
QString e_analogique::getVoie4()
{
    extractionValAnalog();
    return  valAnalog4;
}
QString e_analogique::getVoie5()
{
    extractionValAnalog();
    return  valAnalog5;
}
QString e_analogique::getVoie6()
{
    extractionValAnalog();
    return  valAnalog6;
}
QString e_analogique::getVoie7()
{
    extractionValAnalog();
    return  valAnalog7;
}
QString e_analogique::getVoie8()
{
    extractionValAnalog();
    return  valAnalog8;
}



void e_analogique::extractionValAnalog()
{
    /***************************************************************/
   /****Extraction des valeurs de voies numérique et analogique****/
  /***************************************************************/

    QString rpMesureTemp = reponseMesure;
    qDebug()<<"Releve de mesure="<<rpMesureTemp;


        //Extraction des éléments

            QStringList valvoieTemp= rpMesureTemp.split(";",QString::SkipEmptyParts);

        /*************************************************************************/
        /*********** Recuperation et traitement des voies Analogiques ************/
        /*************************************************************************/

          valAnalog1=valvoieTemp[0];
          qDebug()<<"valAnalog 1="<<valAnalog1;
          valAnalog1.replace("#","");
          qDebug()<<"Replace valAnalog 1="<<valAnalog1;
          valAnalog2=valvoieTemp[1];
          qDebug()<<"valAnalog 2="<<valAnalog2;
          valAnalog3=valvoieTemp[2];
          qDebug()<<"valAnalog 3="<<valAnalog3;
          valAnalog4=valvoieTemp[3];
          qDebug()<<"valAnalog 4="<<valAnalog4;
          valAnalog5=valvoieTemp[4];
          qDebug()<<"valAnalog 5="<<valAnalog5;
          valAnalog6=valvoieTemp[5];
          qDebug()<<"valAnalog 6="<<valAnalog6;
          valAnalog7=valvoieTemp[6];
          qDebug()<<"valAnalog 7="<<valAnalog7;
          valAnalog8=valvoieTemp[7];
          qDebug()<<"valAnalog 8="<<valAnalog8;

          rpMesureTemp.clear();

}
