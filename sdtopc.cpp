/*
 *  Réalisé par Pierrick VERAN
 *  VERSION : 27/05/2014
*/
#include "sdtopc.h"

SDToPC::SDToPC()
{
}

SDToPC::SDToPC(QString port, PortSettings configurations):QextSerialPort(port,configurations,QextSerialPort::EventDriven)
{

    //Affichage de la configuration du port
    qDebug()  << "SDToPC: Création d'un objet";
    qDebug()  << "SDToPC: port              " << port;
    qDebug()  << "SDToPC: BaudRate          " << configurations.BaudRate;
    qDebug()  << "SDToPC: DataBits          " << configurations.DataBits;
    qDebug()  << "SDToPC: FlowControl       " << configurations.FlowControl;
    qDebug()  << "SDToPC: Parity            " << configurations.Parity;
    qDebug()  << "SDToPC: StopBits          " << configurations.StopBits;
    qDebug()  << "SDToPC: Timeout_Millisec  " << configurations.Timeout_Millisec;

    //Initialisation
    cheminFichier="D:/MangoAcqQt/MANGO.txt";
    LectureFichier="$U\r\n";
    LectureTailleFichier="$T?\r\n";
}

QString SDToPC::lectureTailleFichier() {

    return LectureTailleFichier;
}

QString SDToPC::lectureFichier() {

    return LectureFichier;
}

int SDToPC::getTempsTransfert(QString tailleFichier){

    qDebug()<<"SDToPC: tailleFichier.toInt()" << tailleFichier.toInt();

    //Calcul du temps de transfert.
    //On Divisie la taille du fichier par 10
    //Puis on ajoute le temps minimum pour un transfert c'est à dire 500
    //500 Est une marge de sécurité pour être sur de recevoir tout le fichier
    tempsTransfert=(tailleFichier.toInt()/10)+500;

    return tempsTransfert;
}

void SDToPC::setCheminFichier(QString cheminVersTXT){

   cheminFichier=cheminVersTXT;

   qDebug()  << "SDToPC : EXECUTION DE : setCheminFichier("<< cheminFichier <<")";
}

void SDToPC::sauvegardeFichier(QString rcvString) {

    qDebug()  << "SDToPC : Chemin vers le fichier(" << cheminFichier <<")" ;

    //Check file pour vérifier l'existence du fichier
    QFileInfo checkFile(cheminFichier);
    if(checkFile.isFile()){
         qDebug() << "SDToPC : Le fichier existe";
    }
     else{
        qDebug() << "SDToPC : Le fichier n'existe pas il va être créé automatiquement ";
        }

    // Création d'un objet QFile avec initialisation sur le chemin de notre fichier
    QFile file(cheminFichier);
    // Ouverture du fichier en lecture seule

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Création d'un objet QTextStream à partir de notre objet QFile
        QTextStream flux(&file);
        // Le flux permet d'écrire ce que notre QString dans le fichier
        flux << rcvString;
        // Fermeture du fichier
        file.close();

        qDebug()  << "SDToPC : Enregistrement terminé" ;
    }
    else{
        qDebug()  << "SDToPC : Echec de l'enregistrement" ;
    }
}




