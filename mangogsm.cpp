#include "mangogsm.h"

mangoGSM::mangoGSM()
{
}
mangoGSM::mangoGSM(QString port, PortSettings configurations):QextSerialPort(port,configurations,QextSerialPort::EventDriven)
{

}
mangoGSM::~mangoGSM()
{

}

QString mangoGSM::miseON()
{
    miseOn="$GSMO\r\n$PGSMP\r\n";
    return miseOn;
}

QString mangoGSM::setNbrContact()
{
    rqtNbrContact="$GSMT"+nbrNumContact+"\r\n";
    return rqtNbrContact;

}

QString mangoGSM::getNbrContact()
{
    rqtNbrContact="$GSMT?\r\n";
    return rqtNbrContact;
    traitementNbrContact();
    return nbrNumContact;
}

void mangoGSM::traitementNbrContact()
{
    qDebug()<<nbrNumContact;
    nbrNumContact.replace("#","");
    nbrNumContact.replace("\r","");
    nbrNumContact.replace("\n","");
}

QString mangoGSM::setRepertoire()
{
    rpsRepertoire="$GSMR"+numero+prenom+" "+nom+"\r\n";
    return rpsRepertoire;

}

QString mangoGSM::getRepertoire()
{
    rqtRepertoire="$GSMR?\r\n";
    return rqtRepertoire;

    traitementRepertoire();
}

void mangoGSM::traitementRepertoire()
{
    // Traitement a voir avec les profs
    qDebug()<<rpsRepertoire;
}

QString mangoGSM::setProgrammation()
{
    programmationGsm="$GSMPD="+jour+"/"+mois+"/"+annee+"@"
            +heure+":"+minute+"R="+recurence+"N="+nbrSms+"\r\n";
    qDebug()<<programmationGsm;
    return programmationGsm;
}

QString mangoGSM::getProgrammation()
{
    rqtProgrammation="$GSMP?\r\n";
    return rqtProgrammation;
}
QString mangoGSM::setPIN()
{
    setPin="$GSMPIN"+pin+"\r\n";
    qDebug()<<setPin;
    return setPin;
}

QString mangoGSM::setTest()
{
    gsmTst="$GSMTST\r\n";

    return gsmTst;
}
