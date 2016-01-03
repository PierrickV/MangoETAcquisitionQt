/*
   Réalisé par Pierrick VERAN
   VERSION : 28/05/2014
*/

#include "iris_bdd.h"

//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Objet sans initialisation---------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

IRIS_BDD::IRIS_BDD()
{
       //Initialisation des chemins
       cheminFichier="D:/MangoAcqQt/MANGO_test.txt";
       cheminBDD="D:/MangoAcqQt/BDDMango.sqlite";

       //Initialisation de la position dans la base de donnée

       numeroLigne_TableCapteur=0;
       numeroLigne_TableCarteMango=0;
       numeroLigne_TableMesure=0;
       numeroLigne_TablePositionGPS=0;
       numeroLigne_TableRepertoire=0;

       nbreLignes_Fichier=0;

       //Création d'un objet "Base de donnée"
       myDB = QSqlDatabase::addDatabase("QSQLITE");
       myDB.setDatabaseName(cheminBDD);

       qDebug() << "DB : Creation de l'objet SANS initialisation réussi ";
       qDebug() << "DB : Chemin vers la base de données: " << cheminBDD;

}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Objet avec initialisation--------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

IRIS_BDD::IRIS_BDD(QString cheminVersBDD) // Initialisation avec base de donnée
{
   //Initialisation des chemins
   cheminBDD=cheminVersBDD;
   cheminFichier="D:/MangoAcqQt/MANGO.txt";

   //Initialisation de la position dans la base de donnée
   numeroLigne_TableCapteur=0;
   numeroLigne_TableCarteMango=0;
   numeroLigne_TableMesure=0;
   numeroLigne_TablePositionGPS=0;
   numeroLigne_TableRepertoire=0;

   //Création d'un objet "Base de donnée"
   myDB= QSqlDatabase::addDatabase("QSQLITE");
   myDB.setDatabaseName(cheminBDD);

   qDebug() << "DB : Creation de l'objet AVEC initialisation réussi ";
   qDebug() << "DB : Chemin vers la base de données: " << cheminBDD;
}

IRIS_BDD::IRIS_BDD(QString cheminVersBDD, QString cheminVersTXT)// Initialisation avec base de donnée + fichier
{
   //Initialisation des chemins
   cheminFichier=cheminVersTXT;
   cheminBDD=cheminVersBDD;

   //Initialisation de la position dans la base de donnée

   numeroLigne_TableCapteur=0;
   numeroLigne_TableCarteMango=0;
   numeroLigne_TableMesure=0;
   numeroLigne_TablePositionGPS=0;
   numeroLigne_TableRepertoire=0;

   //Création d'un objet "Base de donnée"
   myDB= QSqlDatabase::addDatabase("QSQLITE");
   myDB.setDatabaseName(cheminBDD);

   qDebug() << "DB : Creation de l'objet AVEC initialisation réussi ";
   qDebug() << "DB : Chemin vers la base de données: " << cheminBDD;

}



//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Méthode d'ouverture de la base de donnée------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::ouvertureBDD(){
       QFileInfo checkFile(cheminBDD);
       if(checkFile.isFile()){
           //qDebug() << "DB :ouvertureBDD(): La base de données existe";
           if(!myDB.isOpen()){
               myDB.open();
               //qDebug() << "DB : --Open--";
               //qDebug() << "DB : {";

               //Pas de message de debug à l'ouverture ou lors du checkFile car chaque fonction de la classe ouvre et ferme la base de donnée
               //La présence de qDebug dans cette fonction rend alors peu lisible la console de sortie d'application

           }
      }
       else{
           qDebug() << "DB : La base de données ne peut être ouverte. Elle n'existe pas";

      }

}

//-------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------Méthode de fermeture de la base de donnée-----------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::fermetureBDD(){
   if (myDB.isOpen()){
       myDB.close();
       //qDebug() << "DB : }";
       //qDebug() << "DB : --Close--";

   }
   else{

       qDebug() << "DB : Impossible de fermer la base de donnée";
   }
}

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Méthode pour remplir la base de donnée depuis le fichier TXT------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::parseToDB()
{

         // Initialisation des variables
        nbreLignes_Fichier=0;
        nbreBonneLignes_Fichier=0;
        nbreErreurLignes_Fichier=0;


        //Contrôle l'existance du fichier avant de lancer le traitement
        //Si elle existe on lance le traitement sinon on ne fais rien
        QFileInfo checkFile(cheminBDD);

       if(checkFile.isFile()){

           //OUVERTURE ET LECTURE DU FICHIER

           //Ouverture
           QFile fichier(cheminFichier);
           fichier.open(QIODevice::ReadOnly | QIODevice::Text);
           qDebug()  << "DB : EXECUTION DE : parseToDB";
           if(fichier.isOpen())
           {
               //Lecture
               QTextStream flux(&fichier);
               QString contenuFichier = flux.readAll();
               //Fermeture
               fichier.close();
               // Controle d'erreur
               qDebug()  << "DB : parseToDB fonctionne "  ;
               qDebug()  << "DB : Chemin vers le fichier :" << cheminFichier ;

           // DECOUPAGE DU FICHIER TXT ET REMPLISSAGE BDD

             // Extraction des lignes
              QStringList listLigne= contenuFichier.split("\n",QString::SkipEmptyParts);
              nbreLignes_Fichier=listLigne.count();
              //QSqlQuery SQL_requetteRemplissage;

               //Extraction des éléments

               for (numeroLigneFichier=1;numeroLigneFichier<nbreLignes_Fichier;numeroLigneFichier++)
               {
                   int tailleLigne=listLigne[numeroLigneFichier].length();

                   qDebug()  << "_______________________________________________" ;
                   qDebug()  << "                                               " ;
                   qDebug()  << "DB : Valeurs de listLigne["<<numeroLigneFichier<<"]:" << listLigne[numeroLigneFichier];
                   qDebug()  << "DB : Valeurs de tailleLigne["<<numeroLigneFichier<<"]:"<< tailleLigne;
                   qDebug()  << "                                               " ;

                   if(tailleLigne==113||tailleLigne==112)
                   {
                       nbreBonneLignes_Fichier++;

                       // Extraction des éléments

                       QStringList listElement=listLigne[numeroLigneFichier].split(";",QString::SkipEmptyParts);

                       // Traitement sur les éléments
                       listElement[0].replace("#","");


                       // Extraction des valeurs binaires
                       QStringList listBinaire= listElement[10].split("",QString::SkipEmptyParts);

                       qDebug()  << "------------------ELEMENT----------------------" ;

                       qDebug()  << "DB : Parse de la ligne n°" << numeroLigneFichier ;
                       qDebug()  << "DB : listElement[0]  : " << listElement[0];
                       qDebug()  << "DB : listElement[1]  : " << listElement[1];
                       qDebug()  << "DB : listElement[2]  : " << listElement[2];
                       qDebug()  << "DB : listElement[3]  : " << listElement[3];
                       qDebug()  << "DB : listElement[4]  : " << listElement[4];
                       qDebug()  << "DB : listElement[5]  : " << listElement[5];
                       qDebug()  << "DB : listElement[6]  : " << listElement[6];
                       qDebug()  << "DB : listElement[7]  : " << listElement[7];
                       qDebug()  << "DB : listElement[8]  : " << listElement[8];
                       qDebug()  << "DB : listElement[9]  : " << listElement[9];
                       qDebug()  << "DB : listElement[10] : " << listElement[10];
                       qDebug()  << "DB : listElement[11] : " << listElement[11];
                       qDebug()  << "DB : listElement[12] : " << listElement[12];
                       qDebug()  << "DB : listElement[13] : " << listElement[13];
                       qDebug()  << "DB : listElement[14] : " << listElement[14];
                       qDebug()  << "DB : listElement[15] : " << listElement[15];
                       qDebug()  << "DB : listElement[16] : " << listElement[16];
                       qDebug()  << "DB : listElement[17] : " << listElement[17];

                       qDebug()  << "--------------------BINAIRE--------------------" ;

                       qDebug()  << "DB : listBinaire[0]  : " << listBinaire[0];
                       qDebug()  << "DB : listBinaire[1]  : " << listBinaire[1];
                       qDebug()  << "DB : listBinaire[2]  : " << listBinaire[2];
                       qDebug()  << "DB : listBinaire[3]  : " << listBinaire[3];
                       qDebug()  << "DB : listBinaire[4]  : " << listBinaire[4];
                       qDebug()  << "DB : listBinaire[5]  : " << listBinaire[5];
                       qDebug()  << "DB : listBinaire[6]  : " << listBinaire[6];
                       qDebug()  << "DB : listBinaire[7]  : " << listBinaire[7];

                       qDebug()  << "_______________________________________________" ;

                       qDebug()  << "                                               " ;


                       // Remplissage de la base de donnée

                       IRIS_BDD::setTableMesure(listElement[0],listElement[1],listElement[2],listElement[3], listElement[4],listElement[5],listElement[6],listElement[7],listElement[8],listElement[9],listBinaire[4],listBinaire[5],listBinaire[6], listBinaire[7]);

                       IRIS_BDD::setTablePositionGPS(listElement[0],listElement[1],listElement[11],listElement[12],listElement[13],listElement[14],listElement[15],listElement[16],listElement[17]);

//                       SQL_requetteRemplissage.exec();

                   }


                   else
                   {
                    nbreErreurLignes_Fichier++;
                    qDebug()  << "-----------------------------------------------" ;
                    qDebug()  << "DB : La ligne" << numeroLigneFichier << "ne respecte pas la bonne taille. Elle  sera ignorée." ;
                    qDebug()  << "-----------------------------------------------" ;

                   }
               }

               qDebug()  << "------------------BILAN------------------------" ;
               qDebug()  << "DB : Nombre de ligne total:" << nbreLignes_Fichier ;
               qDebug()  << "DB : Nombre de ligne traité:" << nbreBonneLignes_Fichier ;
               qDebug()  << "DB : Nombre de ligne ignoré:" << nbreErreurLignes_Fichier ;

               qDebug()  << "DB : Note: La premiére ligne ne contenant pas de mesure elle n'est pas traitée" ;

               qDebug()  << "_______________________________________________" ;

                          }
           else
           {
               qDebug()  << "DB : parseToDB n'a pas fonctionné: impossible d'accéder au fichier de mesure à cette adresse" << cheminFichier;
                        }
       }

        else{

           qDebug() << "DB : Le programme n'a pas pu trouver la base de donnée à cette adresse' "<< cheminBDD;               
       }
}


//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie méthode " Set "-----------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::setTableMesure(QString myDate,QString myHeure, QString myVoie1, QString myVoie2,QString myVoie3,QString myVoie4,QString myVoie5,QString myVoie6, QString myVoie7, QString myVoie8, QString myeTor_1,QString myeTor_2,QString mysTor_1,QString mysTor_2){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   // On créé la requette
   QSqlQuery SQL_requetteRemplissage;

   // Remplissage de la base de donnée
   SQL_requetteRemplissage.prepare("INSERT  INTO Mesure VALUES('"+myDate+"\', '"+myHeure+"\', '"+myVoie1+"\', '"+myVoie2+"\', '"+myVoie3+"\' , '"+myVoie4+"\', '"+myVoie5+"\', '"+myVoie6+"\', '"+myVoie7+"\', '"+myVoie8+"\', '"+myeTor_1+"\', '"+myeTor_2+"\', '"+mysTor_1+"\', '"+mysTor_2+"\')");

   SQL_requetteRemplissage.exec();
   qDebug()  << "DB : EXECUTION DE : setTableMesure("<< myDate << myHeure << myVoie1 << myVoie2 << myVoie3 << myVoie4 << myVoie5 << myVoie6 << myVoie7 << myVoie8 << myeTor_1 << myeTor_2 << mysTor_1 << mysTor_2 <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();

}

void IRIS_BDD::setTablePositionGPS(QString myDate, QString myHeure, QString myAlti, QString myLatitude, QString myHemisphere, QString myLongitude, QString myElongation, QString mySt, QString myLoc){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   // On créé la requette
   QSqlQuery SQL_requetteRemplissage;

   //DATE HEURE
   SQL_requetteRemplissage.prepare("INSERT INTO PositionGPS VALUES('"+myDate+"\','"+myHeure+"\','"+myAlti+"\', '"+myLatitude+"\', '"+myHemisphere+"\', '"+myLongitude+"\', '"+myElongation+"\', '"+mySt+"\', '"+myLoc+"\')");
   SQL_requetteRemplissage.exec();

   qDebug()  << "DB : EXECUTION DE : setTablePositionGPS("<< myDate << myHeure << myAlti << myLatitude << myHemisphere << myLongitude << myElongation << mySt << myLoc <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();

}


void IRIS_BDD::setTableCarteMango(QString myNomCarteMango, QString myTypeCarteMango, QString myNumeroSerieCarteMango){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   // On créé la requette
   QSqlQuery SQL_requetteRemplissage;

   // On la prépare
   SQL_requetteRemplissage.prepare("INSERT INTO CarteMango VALUES('"+myNomCarteMango+"\','"+myTypeCarteMango+"\','"+myNumeroSerieCarteMango+"\')");

   //On l'éxécute
   SQL_requetteRemplissage.exec();

   // On vérifie les parametres via une QDebug
   qDebug()  << "DB : EXECUTION DE : setTableCarteMango("<< myNomCarteMango << myTypeCarteMango << myNumeroSerieCarteMango <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::setTableRepertoire(QString myNomRepertoire, QString myPrenomRepertoire, QString myNumeroTelRepertoire){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_requetteRemplissage;
   SQL_requetteRemplissage.prepare("INSERT INTO Répertoire VALUES('"+myNomRepertoire+"\','"+myPrenomRepertoire+"\','"+myNumeroTelRepertoire+"\')");
   SQL_requetteRemplissage.exec();


   qDebug()  << "DB : EXECUTION DE : setTableRepertoire("<< myNomRepertoire << myPrenomRepertoire << myNumeroTelRepertoire <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();

}

void IRIS_BDD::setTableCapteur(QString myNomCapteur, QString mytypeCapteur, QString myNomFichierConversionCapteur, QString myVoieCapteur){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_requetteRemplissage;
   SQL_requetteRemplissage.prepare("INSERT INTO Capteur VALUES('"+myNomCapteur+"\','"+mytypeCapteur+"\','"+myNomFichierConversionCapteur+"\','"+myVoieCapteur+"\')");
   SQL_requetteRemplissage.exec();


   qDebug()  << "DB : EXECUTION DE : setTableCapteur( "<< myNomCapteur << mytypeCapteur << myNomFichierConversionCapteur << myVoieCapteur  <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


void IRIS_BDD::setCheminFichier(QString cheminVersTXT){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   cheminFichier=cheminVersTXT;

   qDebug()  << "DB : EXECUTION DE : setCheminFichier("<< cheminFichier <<")";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Méthode pour effacé le contenu de la base de donnée---------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::viderBDD(){


    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM Mesure");
   SQL_effacerContenuBDD.exec("DELETE FROM PositionGPS");
   SQL_effacerContenuBDD.exec("DELETE FROM Capteur");
   SQL_effacerContenuBDD.exec("DELETE FROM Répertoire");
   SQL_effacerContenuBDD.exec("DELETE FROM CarteMango");

   qDebug()  << "DB : EXECUTION DE : viderBDD ";

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();

}

void IRIS_BDD::viderTable_TableMesure(){
    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM Mesure");

   qDebug()  << "DB : EXECUTION DE : viderTable_TableMesure ";
   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();

}

void IRIS_BDD::viderTable_TablePositionGPS(){
    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM PositionGPS");

   qDebug()  << "DB : EXECUTION DE : viderTable_TablePositionGPS ";
   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::viderTable_TableRepertoire(){
    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM Capteur");

   qDebug()  << "DB : EXECUTION DE : viderTable_TableRepertoire ";
   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::viderTable_TableCarteMango(){
    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM Répertoire");

   qDebug()  << "DB : EXECUTION DE : viderTable_TableCarteMango ";
   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::viderTable_TableCapteur(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQuery SQL_effacerContenuBDD;
   SQL_effacerContenuBDD.exec("DELETE FROM CarteMango");

   qDebug()  << "DB : EXECUTION DE : viderTable_TableCapteur ";
   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Méthode pour la de lecture de la base de donnnée------------------------------------
//-------------------------------------------------------------------------------------------------------------------------


void IRIS_BDD::lireTableMesure(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTableMesure;
   SQL_lireTableMesure.setQuery("SELECT * FROM Mesure");

   //Seléction du contenu chaque colone de la table en fonction du numéro de ligne choisis par l'utilisateurs
   Date = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Date").toString();
   Heure = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Heure").toString();
   Voie1 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_1").toString();
   Voie2 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_2").toString();
   Voie3 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_3").toString();
   Voie4 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_4").toString();
   Voie5 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_5").toString();
   Voie6 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_6").toString();
   Voie7 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_7").toString();
   Voie8 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("Voie_8").toString();
   eTor_1 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("eTor_1").toString();
   eTor_2 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("eTor_2").toString();
   sTor_1 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("sTor_1").toString();
   sTor_2 = SQL_lireTableMesure.record(numeroLigne_TableMesure).value("sTor_2").toString();


   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::lireTablePositionGPS(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTablePositionGPS;
   SQL_lireTablePositionGPS.setQuery("SELECT * FROM PositionGPS");

   //Séléction du contenu chaque colone de la table en fonction du numéro de ligne choisis par l'utilisateurs

   Alti = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Alti").toString();
   Latitude = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Latitude").toString();
   Hemisphere = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Hemisphere").toString();
   Longitude = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Longitude").toString();
   Elongation = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Elongation").toString();
   St = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("St").toString();
   Loc = SQL_lireTablePositionGPS.record(numeroLigne_TablePositionGPS).value("Loc").toString();

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


void IRIS_BDD::lireTableRepertoire(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTableRepertoire;
   SQL_lireTableRepertoire.setQuery("SELECT * FROM Répertoire");

   //Séléction du contenu chaque colone de la table en fonction du numéro de ligne choisis par l'utilisateurs

   NomRepertoire = SQL_lireTableRepertoire.record(numeroLigne_TableRepertoire).value("Nom").toString();
   PrenomRepertoire = SQL_lireTableRepertoire.record(numeroLigne_TableRepertoire).value("Prénom").toString();
   NumeroTelRepertoire = SQL_lireTableRepertoire.record(numeroLigne_TableRepertoire).value("NuméroTéléphone").toString();


   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::lireTableCarteMango(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   //Création du modÃ¨le de requette
   QSqlQueryModel SQL_lireTableCarteMango;

   //Initialisation de la requette
   SQL_lireTableCarteMango.setQuery("SELECT * FROM CarteMango");

   //Séléction du contenu chaque colone de la table en fonction du numéro de ligne choisis par l'utilisateurs

   NomCarteMango = SQL_lireTableCarteMango.record(numeroLigne_TableCarteMango).value("Nom").toString();
   TypeCarteMango = SQL_lireTableCarteMango.record(numeroLigne_TableCarteMango).value("Type").toString();
   NumeroSerieCarteMango = SQL_lireTableCarteMango.record(numeroLigne_TableCarteMango).value("NuméroDeSerie").toString();

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::lireTableCapteur(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTableCapteur;
   SQL_lireTableCapteur.setQuery("SELECT * FROM Capteur");

   //Séléction du contenu chaque colone de la table en fonction du numéro de ligne choisis par l'utilisateurs

   NomCapteur = SQL_lireTableCapteur.record(numeroLigne_TableCapteur).value("Nom").toString();
   TypeCapteur = SQL_lireTableCapteur.record(numeroLigne_TableCapteur).value("Type").toString();
   NomFichierConversionCapteur = SQL_lireTableCapteur.record(numeroLigne_TableCapteur).value("NomFichierConversion").toString();
   VoieCapteur = SQL_lireTableCapteur.record(numeroLigne_TableCapteur).value("Voie").toString();

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


//-------------------------------------------------------------------------------------------------------------------------
//---------------------------Méthode pour le calcul du nombre de ligne qui compose la base de donnée-----------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::calculNbreLignes_TableMesure(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTableMesure;
   SQL_lireTableMesure.setQuery("SELECT * FROM Mesure");

   //Fonction pour 'rowCount()' pour compter le nombre de ligne

   //Ces deux lignes sont donné dans la documentation
   //Sans elle Rowcount renvoie au maximum 256
   //while(model->canFetchMore())
   //model->fetchMore();

   while(SQL_lireTableMesure.canFetchMore())
       SQL_lireTableMesure.fetchMore();
   nbreLignes_TableMesure = SQL_lireTableMesure.rowCount();
   //nbreLignes_TableMesure=SQL_lireTableMesure.record();

   //qDebug()  << "DB : EXECUTION DE : calculNbreLignes_TableMesure()" << nbreLignes_TableMesure  ;

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::calculNbreLignes_TablePositionGPS(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTablePositionGPS;
   SQL_lireTablePositionGPS.setQuery("SELECT * FROM PositionGPS");

   //Fonction pour 'rowCount()' pour compter le nombre de ligne

   //Ces deux lignes sont donné dans la documentation
   //Sans elle Rowcount renvoie au maximum 256

   while(SQL_lireTablePositionGPS.canFetchMore())
       SQL_lireTablePositionGPS.fetchMore();

   nbreLignes_TablePositionGPS = SQL_lireTablePositionGPS.rowCount();

   //qDebug()  << "DB : EXECUTION DE : calculNbreLignes_TablePositionGPS()" << nbreLignes_TablePositionGPS  ;

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::calculNbreLignes_TableRepertoire(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   //Création du modÃ¨le de requette
   QSqlQueryModel SQL_lireTableRepertoire;

   //Initialisation de la requette
   SQL_lireTableRepertoire.setQuery("SELECT * FROM Répertoire");

   //Fonction pour 'rowCount()' pour compter le nombre de ligne

   //Ces deux lignes sont donné dans la documentation
   //Sans elle Rowcount renvoie au maximum 256
   while(SQL_lireTableRepertoire.canFetchMore())
       SQL_lireTableRepertoire.fetchMore();

   nbreLignes_TableRepertoire = SQL_lireTableRepertoire.rowCount();

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


void IRIS_BDD::calculNbreLignes_TableCarteMango(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   //Création du modÃ¨le de requette
   QSqlQueryModel SQL_lireTableCarteMango;

   //Initialisation de la requette
   SQL_lireTableCarteMango.setQuery("SELECT * FROM CarteMango");


   //Fonction pour 'rowCount()' pour compter le nombre de ligne

   //Ces deux lignes sont donné dans la documentation
   //Sans elle Rowcount renvoie au maximum 256
   while(SQL_lireTableCarteMango.canFetchMore())
       SQL_lireTableCarteMango.fetchMore();

   nbreLignes_TableCarteMango = SQL_lireTableCarteMango.rowCount();

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}

void IRIS_BDD::calculNbreLignes_TableCapteur(){

    // Ouverture de la base de donnée
    IRIS_BDD::ouvertureBDD();

   QSqlQueryModel SQL_lireTableCapteur;
   SQL_lireTableCapteur.setQuery("SELECT * FROM Capteur");

   //Fonction pour 'rowCount()' pour compter le nombre de ligne

   //Ces deux lignes sont donné dans la documentation
   //Sans elle Rowcount renvoie au maximum 256
   while(SQL_lireTableCapteur.canFetchMore())
       SQL_lireTableCapteur.fetchMore();

   nbreLignes_TableCapteur = SQL_lireTableCapteur.rowCount();

   //qDebug()  << "DB : EXECUTION DE : calculNbreLignes_TableCapteur()" << nbreLignes_TableCapteur  ;

   // Fermeture de la base de donnée
   IRIS_BDD::fermetureBDD();
}


//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Méthode pour se déplacé vers la ligne précédente------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

void IRIS_BDD::lignePrecedente_TableMesure(){
    numeroLigne_TableMesure--;
    qDebug()  << "DB : EXECUTION DE : lignePrecedente_TableMesure()" << numeroLigne_TableMesure;
}
void IRIS_BDD::lignePrecedente_TablePositionGPS(){
    numeroLigne_TablePositionGPS--;
    qDebug()  << "DB : EXECUTION DE : lignePrecedente_TablePositionGPS()" << numeroLigne_TablePositionGPS;
}
void IRIS_BDD::lignePrecedente_TableRepertoire(){
    numeroLigne_TableRepertoire--;
    qDebug()  << "DB : EXECUTION DE : lignePrecedente_TableRepertoire()" << numeroLigne_TableRepertoire;
}
void IRIS_BDD::lignePrecedente_TableCarteMango(){
    numeroLigne_TableCarteMango--;
    qDebug()  << "DB : EXECUTION DE : lignePrecedente_TableCarteMango()" << numeroLigne_TableCarteMango;
}
void IRIS_BDD::lignePrecedente_TableCapteur(){
    numeroLigne_TableCapteur--;
    qDebug()  << "DB : EXECUTION DE : lignePrecedente_TableCapteur()" << numeroLigne_TableCapteur;
}


//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------Méthode pour se déplacé vers la ligne suivante--------------------------------------
//-------------------------------------------------------------------------------------------------------------------------


void IRIS_BDD::ligneSuivante_TableMesure(){
    numeroLigne_TableMesure++;
    qDebug()  << "DB : EXECUTION DE : ligneSuivante_TableMesure()" << numeroLigne_TableMesure;
}
void IRIS_BDD::ligneSuivante_TablePositionGPS(){
    numeroLigne_TablePositionGPS++;
    qDebug()  << "DB : EXECUTION DE : ligneSuivante_TablePositionGPS()" << numeroLigne_TablePositionGPS;
}
void IRIS_BDD::ligneSuivante_TableRepertoire(){
    numeroLigne_TableRepertoire++;
    qDebug()  << "DB : EXECUTION DE : ligneSuivante_TableRepertoire()" << numeroLigne_TableRepertoire;
}
void IRIS_BDD::ligneSuivante_TableCarteMango(){
    numeroLigne_TableCarteMango++;
    qDebug()  << "DB : EXECUTION DE : ligneSuivante_TableCarteMango()" << numeroLigne_TableCarteMango;
}
void IRIS_BDD::ligneSuivante_TableCapteur(){
    numeroLigne_TableCapteur++;
    qDebug()  << "DB : EXECUTION DE : ligneSuivante_TableCapteur()" << numeroLigne_TableCapteur;
}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------Méthode get pour récupéré les valeurs de la base de donnée-----------------------------
//-------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture des chemins-------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

QString IRIS_BDD::getCheminFichier(){
    qDebug()  << "DB : EXECUTION DE : getCheminFichier()" << cheminFichier;
    return cheminFichier;

}

QString IRIS_BDD::getCheminBDD(){
    qDebug()  << "DB : EXECUTION DE : getCheminBDD()" << cheminBDD;
    return cheminBDD;

}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture du nombre de ligne------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

//Le nombre de ligne correspond au total du nombre de ligne qui compose une table ou un fichier

int IRIS_BDD::getNbreLignes_Fichier(){

    qDebug()  << "DB : EXECUTION DE : getNbreLignes_Fichier";

    //Dans le cas ou le nombre de ligne est déjà calculé
    if(nbreLignes_Fichier<0)
    {
        qDebug()  << "DB : Nombre de ligne déjà calculé:" << nbreLignes_Fichier;
    }

    //Dans le cas ou le nombre de ligne n'est pas encore calculé
    //On le calcul:

    else{
        //OUVERTURE ET LECTURE DU FICHIER

        //Ouverture
        QFile fichier(cheminFichier);
        qDebug()  << "DB : getNbreLignes_Fichier: Chemin Fichier:"<< cheminFichier;
        fichier.open(QIODevice::ReadOnly | QIODevice::Text);
        //Si l'ouverture du fichier a réussi
        if(fichier.isOpen())
        {
            //Lecture
            QTextStream flux(&fichier);
            QString contenuFichier = flux.readAll();
            //Fermeture
            fichier.close();
            //Calcul du nombre de ligne
           QStringList listLigne= contenuFichier.split("\n",QString::SkipEmptyParts);
           nbreLignes_Fichier=listLigne.count();
           qDebug()  << "DB : Nombre de ligne calculé par la fonction:" << nbreLignes_Fichier;

        }
        //Sinon
        else{



            qDebug()  << "DB : Impossible de calculer le nombre de ligne. Vérifier que le fichier existe";
        }
    }

    return nbreLignes_Fichier;
}

int IRIS_BDD::getNbreLignes_TableMesure(){
   calculNbreLignes_TableMesure();
   qDebug()  << "DB : EXECUTION DE : getNbreLignes_TableMesure()" <<nbreLignes_TableMesure;
   return nbreLignes_TableMesure;
}

int IRIS_BDD::getNbreLignes_TablePositionGPS(){
   calculNbreLignes_TablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getNbreLignes_TablePositionGPS()" << nbreLignes_TablePositionGPS;
   return nbreLignes_TablePositionGPS;
}

int IRIS_BDD::getNbreLignes_TableRepertoire(){

   calculNbreLignes_TableRepertoire();
   qDebug()  << "DB : EXECUTION DE : getNbreLignes_TableRepertoire()" << nbreLignes_TableRepertoire;
   return nbreLignes_TableRepertoire;
}

int IRIS_BDD::getNbreLignes_TableCarteMango(){

   calculNbreLignes_TableCarteMango();
   qDebug()  << "DB : EXECUTION DE : getNbreLignes_TableCarteMango()" << nbreLignes_TableCarteMango;
   return nbreLignes_TableCarteMango;
}

int IRIS_BDD::getNbreLignes_TableCapteur(){

   calculNbreLignes_TableCapteur();
   qDebug()  << "DB : EXECUTION DE : getNbreLignes_TableCapteur()" << nbreLignes_TableCapteur;
   return nbreLignes_TableCapteur;
}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture du numéro de ligne------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

//Le numéro de ligne correpond à la position de l'utilisateurs dans le fichier ou dans la base de données

int IRIS_BDD::getNumeroLigneFichier(){
   qDebug()  << "DB : EXECUTION DE : getNumeroLigneFichier()" << numeroLigneFichier;
   return numeroLigneFichier;
}
int IRIS_BDD::getNumeroLigne_TableMesure(){
    qDebug()  << "DB : EXECUTION DE : getNumeroLigneFichier()" << numeroLigne_TableMesure;
    return numeroLigne_TableMesure;
}
int IRIS_BDD::getNumeroLigne_TablePositionGPS(){
    qDebug()  << "DB : EXECUTION DE : getNumeroLigne_TablePositionGPS()" << numeroLigne_TablePositionGPS;
    return numeroLigne_TablePositionGPS;
}
int IRIS_BDD::getNumeroLigne_TableRepertoire(){
    qDebug()  << "DB : EXECUTION DE : getNumeroLigne_TableRepertoire()" << numeroLigne_TableRepertoire;
    return numeroLigne_TableRepertoire;
}
int IRIS_BDD::getNumeroLigne_TableCarteMango(){
    qDebug()  << "DB : EXECUTION DE : getNumeroLigne_TableCarteMango()" << numeroLigne_TableCarteMango;
    return numeroLigne_TableCarteMango;
}
int IRIS_BDD::getNumeroLigne_TableCapteur(){
    qDebug()  << "DB : EXECUTION DE : getNumeroLigne_TableCapteur()" << numeroLigne_TableCapteur;
    return numeroLigne_TableCapteur;
}

int IRIS_BDD::getNbreErreurLignes_Fichier(){
   qDebug()  << "DB : EXECUTION DE : getNbreErreurLignes_Fichier()" << nbreErreurLignes_Fichier;
   return nbreErreurLignes_Fichier;
}

int IRIS_BDD::getNbreBonneLignes_Fichier(){
   qDebug()  << "DB : EXECUTION DE : getNbreBonneLignes_Fichier()" << nbreBonneLignes_Fichier;
   return nbreBonneLignes_Fichier;
}


//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture de la table Mesure------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------


QString IRIS_BDD::getDate(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getDate()" << Date  ;
   return Date;
}

QString IRIS_BDD::getHeure(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getHeure()" << Heure  ;
   return Heure;
}

QString IRIS_BDD::getVoie1(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie1()" << Voie1;
   return Voie1;
}

QString IRIS_BDD::getVoie2(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie2()" << Voie2;
   return Voie2;
}

QString IRIS_BDD::getVoie3(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie3()" << Voie3;
   return Voie3;
}

QString IRIS_BDD::getVoie4(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie4()" << Voie4;
   return Voie4;
}

QString IRIS_BDD::getVoie5(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie5()"<< Voie5;
   return Voie5;
}

QString IRIS_BDD::getVoie6(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie6()" << Voie6;
   return Voie6;
}

QString IRIS_BDD::getVoie7(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie7()" << Voie7;
   return Voie7;
}

QString IRIS_BDD::getVoie8(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getVoie8()" << Voie8;
   return Voie8;
}

QString IRIS_BDD::geteTor_1(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : geteTor_1()" << eTor_1;
   return eTor_1;
}

QString IRIS_BDD::geteTor_2(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : geteTor_2()" << eTor_1;
   return eTor_2;
}

QString IRIS_BDD::getsTor_1(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getsTor_1()" << eTor_1;
   return sTor_1;
}

QString IRIS_BDD::getsTor_2(){
   lireTableMesure();
   qDebug()  << "DB : EXECUTION DE : getsTor_2()" << eTor_1;
   return sTor_2;
}


//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture de la table PositionGPS-------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

QString IRIS_BDD::getAlti(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getAlti()" << Alti;
   return Alti;
}

QString IRIS_BDD::getLatitude(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getLatitude()" << Latitude;
   return Latitude;
}

QString IRIS_BDD::getHemisphere(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getHemisphere()" << Hemisphere;
   return Hemisphere;
}

QString IRIS_BDD::getLongitude(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getLongitude()" << Longitude;
   return Longitude;
}

QString IRIS_BDD::getElongation(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getElongation()" << Elongation;
   return Elongation;
}

QString IRIS_BDD::getSt(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getSt()" << St;
   return St;
}

QString IRIS_BDD::getLoc(){
   lireTablePositionGPS();
   qDebug()  << "DB : EXECUTION DE : getLoc()" << Loc;
   return Loc;
}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture de la table CarteMango--------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

QString IRIS_BDD::getNomCarteMango(){
   //Lecture de la table
   lireTableCarteMango();
   qDebug()  << "DB : EXECUTION DE : getNomCarteMango()" << NomCarteMango;
   return NomCarteMango;
}

QString IRIS_BDD::getTypeCarteMango(){
   lireTableCarteMango();
   qDebug()  << "DB : EXECUTION DE : getTypeCarteMango()" << TypeCarteMango;
   return TypeCarteMango;
}
QString IRIS_BDD::getNumeroSerieCarteMango(){
   lireTableCarteMango();
   qDebug()  << "DB : EXECUTION DE : getNumeroSerieCarteMango()" << NumeroSerieCarteMango;
   return NumeroSerieCarteMango;
}


//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture de la table Repertoire--------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

QString IRIS_BDD::getNomRepertoire(){
   lireTableRepertoire();
   qDebug()  << "DB : EXECUTION DE : getNomRepertoire()" << NomRepertoire;
   return NomRepertoire;
}
QString IRIS_BDD::getPrenomRepertoire(){
   lireTableRepertoire();
   qDebug()  << "DB : EXECUTION DE : getPrenomRepertoire()" << PrenomRepertoire;
   return PrenomRepertoire;
}
QString IRIS_BDD::getNumeroTelRepertoire(){
   lireTableRepertoire();
   qDebug()  << "DB : EXECUTION DE : getNumeroTelRepertoire()" << NumeroTelRepertoire;
   return NumeroTelRepertoire;
}

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------Partie lecture de la table Capteurs----------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

QString IRIS_BDD::getNomCapteur(){
   lireTableCapteur();
   qDebug()  << "DB : EXECUTION DE : getNomCapteur()" << NomCapteur;
   return NomCapteur;
}
QString IRIS_BDD::getTypeCapteur(){
   lireTableCapteur();
   qDebug()  << "DB : EXECUTION DE : getTypeCapteur()" << TypeCapteur;
   return TypeCapteur;
}
QString IRIS_BDD::getVoieCapteur(){
   lireTableCapteur();
   qDebug()  << "DB : EXECUTION DE : getVoieCapteur()" << VoieCapteur;
   return VoieCapteur;
}

QString IRIS_BDD::getNomFichierConversionCapteur(){
   lireTableCapteur();
   qDebug()  << "DB : EXECUTION DE : getNomFichierConversionCapteur()" << NomFichierConversionCapteur;
   return NomFichierConversionCapteur;
}

//-------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------Destructeur---------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

IRIS_BDD::~IRIS_BDD()
{

}

