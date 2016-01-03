/*
 *  Réalisé par Pierrick VERAN
 *  VERSION : 27/05/2014
*/

#include "s_numerique.h"


//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Objet sans initialisation---------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

s_Numerique::s_Numerique()
{
    valSNum1="0";
    valSNum2="0";
    qDebug()  << "S_Numerique: Création d'un objet";

}

//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Objet avec initialisation---------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

s_Numerique::s_Numerique(QString port, PortSettings configurations):QextSerialPort(port,configurations,QextSerialPort::EventDriven)
{
    //Initialisation de la valeur des sorties
    valSNum1="0";
    valSNum2="0";

    //Affichage de la configuration
    qDebug()  << "S_Numerique: Création d'un objet";
    qDebug()  << "S_Numerique: port              " << port;
    qDebug()  << "S_Numerique: BaudRate          " << configurations.BaudRate;
    qDebug()  << "S_Numerique: DataBits          " << configurations.DataBits;
    qDebug()  << "S_Numerique: FlowControl       " << configurations.FlowControl;
    qDebug()  << "S_Numerique: Parity            " << configurations.Parity;
    qDebug()  << "S_Numerique: StopBits          " << configurations.StopBits;
    qDebug()  << "S_Numerique: Timeout_Millisec  " << configurations.Timeout_Millisec;
}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------Méthode Set : Passer les sorties TOR sur 1 --------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void s_Numerique::setNum1()
{
    //Si la sortie est à 1
    if(valSNum1.contains("1",Qt::CaseInsensitive)){
        //On la passe à 0
        valSNum1="0";
    }
    //Sinon
    else{
        //On la passe à 1
        valSNum1="1";
    }

    qDebug()  << "S_Numerique: Valeurs de Num1: " << valSNum1;

}

void s_Numerique::setNum2()
{
    //Si la sortie est à 1
    if(valSNum2.contains("1",Qt::CaseInsensitive)){

        //On la passe à 0
            valSNum2="0";
    }
    //Sinon
    else{
        //On la passe à 1
            valSNum2="1";
    }

    qDebug()  << "S_Numerique: Valeurs de Num2: " << valSNum2;
}

//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Méthode get : Récupérer les valeurs de sorties------------------------------
//-------------------------------------------------------------------------------------------------------------------------


QString s_Numerique::getSNum1()
{
    return valSNum1;
}

QString s_Numerique::getSNum2()
{
    return valSNum2;
}

//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Méthode pour préparer et envoyer la commande--------------------------------
//-------------------------------------------------------------------------------------------------------------------------


 QString s_Numerique::envoieCommand()
 {
     //On vide " send "
     send.clear();
     //On prépare la chaine à envoyer
     send="$S"+valSNum1+valSNum2+"\r\n";

     //On la retourne
     return send;
 }
