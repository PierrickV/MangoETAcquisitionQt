#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Mise a Off des led & initialisation de l'IHM
    ui->led1->turnOff();
    ui->led2->turnOff();
    ui->gsmLed->turnOff();
    ui->actual->setEnabled(false);
    ui->MangoName->setEnabled(false);

    //Lecture des ports et stockage dans une liste:
    listPorts = enumerator->getPorts();
    for(i=0; i<listPorts.size(); i++)
    {
        ui->portBox->addItem(listPorts.at(i).portName);
        qDebug() << "Port n°" << i <<":"<< listPorts.at(i).enumName;
    }

    //configuration des objets servant de "port"

    PortSettings settings = {BAUD115200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    //Gaël
    C_lectureVoie= new lectureVoie(ui->portBox->currentText(),settings);
    C_MangoConfig= new mangoConfiguration(ui->portBox->currentText(),settings);
    C_MangoGsm = new mangoGSM(ui->portBox->currentText(),settings);

    //Pierrick
    obj_BDD=new IRIS_BDD;
    obj_SD=new SDToPC(ui->portBox->currentText(),settings);
    obj_SNum=new s_Numerique(ui->portBox->currentText(),settings);

    //Pierrick initialisation

    //affichage de la table Mesure
    ui->label_date_2->setText(obj_BDD->getDate());
    ui->label_heure_2->setText(obj_BDD->getHeure());
    ui->label_voie1_2->setText(obj_BDD->getVoie1());
    ui->label_voie2_2->setText(obj_BDD->getVoie2());
    ui->label_voie3_2->setText(obj_BDD->getVoie3());
    ui->label_voie4_2->setText(obj_BDD->getVoie4());
    ui->label_voie5_2->setText(obj_BDD->getVoie5());
    ui->label_voie6_2->setText(obj_BDD->getVoie6());
    ui->label_voie7_2->setText(obj_BDD->getVoie7());
    ui->label_voie8_2->setText(obj_BDD->getVoie8());

    ui->label_eTor1_2->setText(obj_BDD->geteTor_1());
    ui->label_eTor2_2->setText(obj_BDD->geteTor_2());

    ui->label_sTor1_2->setText(obj_BDD->getsTor_1());
    ui->label_sTor2_2->setText(obj_BDD->getsTor_2());
    ui->label_ligneActu_tableMesure_2->setNum((obj_BDD->getNumeroLigne_TableMesure()));
    ui->label_nbreLigne_tableMesure_2->setNum(obj_BDD->getNbreLignes_TableMesure());

    //affichage de la table GPS

    ui->label_alti_2->setText(obj_BDD->getAlti());
    ui->label_latitude_2->setText(obj_BDD->getLatitude());
    ui->label_hemisphere_2->setText(obj_BDD->getLongitude());
    ui->label_longitude_2->setText(obj_BDD->getLongitude());
    ui->label_elongation_2->setText(obj_BDD->getElongation());
    ui->label_st_2->setText(obj_BDD->getSt());
    ui->label_loc_2->setText(obj_BDD->getLoc());
    ui->label_nbreLigne_tableGPS_2->setNum(obj_BDD->getNbreLignes_TablePositionGPS());
    ui->label_ligneActu_tableGPS_2->setNum(obj_BDD->getNumeroLigne_TablePositionGPS());

    //affichage info fichier

    ui->lineEdit_MesureGPS_cheminFichier->setText(obj_BDD->getCheminFichier());
    ui->lineEdit_MesureGPS_cheminBDD->setText(obj_BDD->getCheminBDD());
    ui->lineEdit_MesureGPS_cheminBDD->setEnabled(false);
    ui->label_nbreLigneFichier_2->setNum(obj_BDD->getNbreLignes_Fichier());
    ui->label_tempsTraitement_2->setNum((obj_BDD->getNbreLignes_Fichier())/3.5);

    //affichage des infos capteurs

    ui->label_VoieCapteur_2->setText(obj_BDD->getVoieCapteur());
    ui->label_typeCapteur_2->setText(obj_BDD->getTypeCapteur());
    ui->label_NomFichierConversionCapteur_2->setText((obj_BDD->getNomFichierConversionCapteur()));
    ui->label_NomCapteur_2->setText(obj_BDD->getNomCapteur());

    ui->label_nbreLigne_TableCapteur2->setNum(obj_BDD->getNbreLignes_TableCapteur());
    ui->label_ligneActu_TableCapteur_2->setNum(obj_BDD->getNumeroLigne_TableCapteur());



    //affichage des infos carte

    ui->label_NomCarteMango_2->setText(obj_BDD->getNomCarteMango());
    ui->label_TypeCarteMango_2->setText(obj_BDD->getTypeCarteMango());
    ui->label_NumeroSerieCarteMango_2->setText(obj_BDD->getNumeroSerieCarteMango());

    ui->label_ligneActu_TableCarteMango_2->setNum(obj_BDD->getNumeroLigne_TableRepertoire());
    ui->label_nbreLigne_TableCarteMango_2->setNum(obj_BDD->getNbreLignes_TableRepertoire());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_portBox_highlighted(const QString &arg1)
{
//Lecture de la config actuelle et affichage du nom/Nombre de recurence/GSM actif à la selection du port dans le comboBox
    if(arg1=="COM23")
    {
        if (!C_MangoConfig->isOpen())
        {
        C_MangoConfig->open(QIODevice::ReadWrite);
        qDebug()<<"Port Ouvert";
        C_MangoConfig->write(C_MangoConfig->getNom().toLatin1());
        QTimer::singleShot(500,this,SLOT(setNomMango()));
        }
    }
}

void MainWindow::setNomMango()
{
    //Lecture de la réponse de la carte
    if (C_MangoConfig->bytesAvailable()) {
        C_MangoConfig->reponseNom=(QString::fromLatin1(C_MangoConfig->readAll()));

        qDebug()<<"reponse nom="<<C_MangoConfig->reponseNom;
    }
    else
    {
        //Si pas de réponse affichage du message d'allerte
        QMessageBox::warning(this,"Attention","Attention vous avez selectionné un mauvais port COM");
    }
    //Si réponse traitement et affichage sur l'IHM
    ui->MangoName->setText(C_MangoConfig->setNom());
    ui->actual->setText(C_MangoConfig->getRecurence());
    if(C_MangoConfig->activiteGSM()=="0")
    {
        ui->gsmLed->turnOff();
    }
    if(C_MangoConfig->activiteGSM()=="1")
    {
        ui->gsmLed->turnOn();
    }
    C_MangoConfig->close();
}

void MainWindow::on_lireMesure_clicked()
{
    //Vérification que le port sois fermer  puis ouverture pour pouvoir ecrire dessus
    if (!C_lectureVoie->isOpen())
    {
        C_lectureVoie->open(QIODevice::ReadWrite);
        qDebug()<<"Port Ouvert";
        C_lectureVoie->write(C_lectureVoie->getMesure().toLatin1());
        QTimer::singleShot(500,this,SLOT(setMesureVoie()));
    }
    //Fermeture du port s'il est deja ouvert et restart de la mesure
    else
    {
        C_lectureVoie->close();
        qDebug()<<"Port Fermer";
        on_lireMesure_clicked();
        qDebug()<<"restart de la mesure";
    }
}

void MainWindow::setMesureVoie()
{
    //Lecture de la réponse du port
    if (C_lectureVoie->bytesAvailable())
    {
        C_lectureVoie->reponseMesure=(QString::fromLatin1(C_lectureVoie->readAll()));
        //Transfert de la réponse au classe E_num & e_Analog
        C_eNum.reponseMesure=C_lectureVoie->reponseMesure;
        C_eAnalog.reponseMesure=C_lectureVoie->reponseMesure;

        qDebug()<<"releveMesure LectureVoie="<<C_lectureVoie->reponseMesure;
        qDebug()<<"releveMesure E_Analog="<<C_eAnalog.reponseMesure;
        qDebug()<<"releveMesure E_Num="<<C_eNum.reponseMesure;
    }


    if(C_lectureVoie->reponseMesure.length()==59)
    {
        //Traitement & affichage des voies Analogique
        ui->Analog1->setText(C_eAnalog.getVoie1());

        ui->Analog2->setText(C_eAnalog.getVoie2());

        ui->Analog3->setText(C_eAnalog.getVoie3());

        ui->Analog4->setText( C_eAnalog.getVoie4());

        ui->Analog5->setText(C_eAnalog.getVoie5());

        ui->Analog6->setText(C_eAnalog.getVoie6());

        ui->Analog7->setText(C_eAnalog.getVoie7());

        ui->Analog8->setText(C_eAnalog.getVoie8());

        //Traitement & affichage des voies Numérique
        if(C_eNum.getENum1()=="0")
        {
            ui->led1->turnOff();
        }
        if(C_eNum.getENum1()=="1")
        {
            ui->led1->turnOn();

        }

        if(C_eNum.getENum2()=="0")
        {
            ui->led2->turnOff();
        }
        if(C_eNum.getENum2()=="1")
        {
            ui->led2->turnOn();
        }

        //Fermeture du port aprés utilisation
        C_lectureVoie->close();
        qDebug()<<"Port Fermer";
    }
    else
    {
        //Si le port est deja ouvert, fermeture et restart de la méthode
        C_lectureVoie->close();
        qDebug()<<"Port Fermer";
        on_lireMesure_clicked();
    }
}

void MainWindow::on_SetRecurence_clicked()
{
    //Lecture de la valeur donnée l'utilisateur
    C_MangoConfig->recurence=ui->recMesure->text();

    if (!C_MangoConfig->isOpen())
    {
        C_MangoConfig->open(QIODevice::ReadWrite);
        qDebug()<<"Port Ouvert";
        if(C_MangoConfig->setRecurence().length()!=9)
        {
            //Vérification de la valeur entrée par l'utilisateur
            QMessageBox::warning(this,"Erreur","Veuillez rentrer une valeur sous le format 00001");
        }
        else
        {
            //Envoie de la commande à la carte
            C_MangoConfig->write(C_MangoConfig->setRecurence().toLatin1());
        }

    }
    else
    {
        //Fermeture du port si deja ouvert et restart de la méthode
        C_MangoConfig->close();
        on_SetRecurence_clicked();
    }
}

void MainWindow::on_setNewProgrammation_clicked()
{
    //Enregistrement dans les atributs de la classe mangoGSM des valeurs rentrées par l'utilisateur
    C_MangoGsm->jour=ui->day->text();
    C_MangoGsm->mois=ui->month->text();
    C_MangoGsm->annee=ui->years->text();
    C_MangoGsm->heure=ui->hours->text();
    C_MangoGsm->minute=ui->minute->text();
    C_MangoGsm->recurence=ui->recurence->text();
    C_MangoGsm->nbrSms=ui->nbrSms->text();

    //Ouverture du port et ecriture de la requete
    if (!C_MangoGsm->isOpen())
    {
        C_MangoGsm->open(QIODevice::ReadWrite);
        C_MangoGsm->write(C_MangoGsm->setProgrammation().toLatin1());
    }
    //Fermeture du port s'il est deja ouvert et restart de la méthode
    else
    {
        C_MangoGsm->close();
        on_setNewProgrammation_clicked();
    }
}

void MainWindow::on_setNewContact_clicked()
{
    //Idem que la methode precedente (on_setNewProgrammation_clicked) mais pour enregistrer un contact
    C_MangoGsm->prenom=ui->prenom->text();
    C_MangoGsm->nom=ui->Nom->text();
    C_MangoGsm->numero=ui->numero->text();

    if (!C_MangoGsm->isOpen())
    {
        C_MangoGsm->open(QIODevice::ReadWrite);
        C_MangoGsm->write(C_MangoGsm->setRepertoire().toLatin1());
    }
    else
    {
        C_MangoGsm->close();
        on_setNewContact_clicked();
    }

    obj_BDD->setTableRepertoire(ui->Nom->text(),ui->prenom->text(),ui->numero->text());
}

void MainWindow::on_setNewNbrContact_clicked()
{
    C_MangoGsm->nbrNumContact=ui->newNbrContact->text();
    if (!C_MangoGsm->isOpen())
    {
        C_MangoGsm->open(QIODevice::ReadWrite);
        C_MangoGsm->write(C_MangoGsm->setNbrContact().toLatin1());
    }
    else
    {
        C_MangoGsm->close();
        on_setNewNbrContact_clicked();
    }

}

void MainWindow::on_pushButton_S1_clicked()
{
    // Modification de la valeur de la sortie dans la classe
    obj_SNum->setNum1();
    //Si le port n'est pas ouvert
    if (!obj_SNum->isOpen())
    {
        // Définition du port choisi sur l'IHM comme étant celui à utiliser
        obj_SNum->setPortName(ui->portBox->currentText());
        // Ouverture
        obj_SNum->open(QIODevice::ReadWrite);
        qDebug()<< "MW: Port" << obj_SNum->portName() << "Ouvert";
        //On écrit sur le port la commande permettant de changer la valeur des sorties
        obj_SNum->write(obj_SNum->envoieCommand().toLatin1());
        qDebug()<<"MW: Ecriture sur le port:" << obj_SNum->envoieCommand().toLatin1() ;
        // Fermeture
        obj_SNum->close();
        qDebug()<<"MW: Port fermé";
        //On modifie l'affichage du bouton pour que l'utilisateur
        //sache sur quelle valeur est la sortie
        ui->pushButton_S1->setText(obj_SNum->getSNum1());
    }
    else
    {
        //Sinon : Le port était déjà ouvert
        // Fermeture
        obj_SNum->close();
        qDebug()<<"Port fermé";
        //Puis on relance la fonction
        on_pushButton_S1_clicked();
    }
}

//Les commentaires de cette fonction sont identiques à ceux de la fonction précédente
void MainWindow::on_pushButton_S2_clicked()
{

    obj_SNum->setNum2();

    if (!obj_SNum->isOpen())
    {
        obj_SNum->setPortName(ui->portBox->currentText());
        obj_SNum->open(QIODevice::ReadWrite);
        qDebug()<< "MW: Port" << obj_SNum->portName() << "Ouvert";
        obj_SNum->write(obj_SNum->envoieCommand().toLatin1());
        qDebug()<<"MW: Ecriture sur le port:" << obj_SNum->envoieCommand().toLatin1() ;
        obj_SNum->close();
        qDebug()<<"MW: Port fermé";
        ui->pushButton_S2->setText(obj_SNum->getSNum2());
    }
    else
    {
        obj_SNum->close();
        qDebug()<<"Port fermé";
        on_pushButton_S2_clicked();
    }
}

void MainWindow::on_pushButton_SdToPC_clicked()
{
    //----------------------------------------------------------------------
    //---------------------------Taille du Fichier--------------------------
    //----------------------------------------------------------------------

        //OUVERTURE DU PORT
        obj_SD->setPortName(ui->portBox->currentText());
        obj_SD->open(QIODevice::ReadWrite);
        qDebug()<< "MW: Port" << obj_SD->portName() << "Ouvert";

        //ECRITURE SUR LE PORT
        obj_SD->write(obj_SD->lectureTailleFichier().toLatin1());
        qDebug()<<"MW: Ecriture sur le port:" << obj_SD->lectureTailleFichier().toLatin1() ;

        //LECTURE DU PORT
        QTimer::singleShot(500,this,SLOT(port_getTailleFichier()));
}

void MainWindow::port_getTailleFichier()
{
    if (obj_SD->bytesAvailable())
    {
        qDebug()<<"MW: getTailleFichier()";

        tailleFichier=QString::fromLatin1(obj_SD->readAll());
        tailleFichier.replace("#","");

        qDebug()<<"MW: tailleFichier" << tailleFichier;
        qDebug()<<"MW: tailleFichier.toInt()" << tailleFichier.toInt();

        temps_TransfertFichierInt=obj_SD->getTempsTransfert(tailleFichier);

        decompteTemps_Transfert=temps_TransfertFichierInt;
        decompteTemps_Transfert=(decompteTemps_Transfert/temps_TransfertFichierInt)*100;

        timer = new QTimer(this);

        timer->start(temps_TransfertFichierInt/100);
        connect(timer,SIGNAL(timeout()),this,SLOT(attente()));

        //Calcul du temps de transfert pour l'utilisateur
        temps_TransfertFichierDouble=temps_TransfertFichierInt;
        qDebug()<<"MW: temps_TransfertFichierInt en milliseconde" << temps_TransfertFichierDouble;
        qDebug()<<"MW: temps_TransfertFichierInt en seconde" << temps_TransfertFichierDouble/1000;
        qDebug()<<"MW: temps_TransfertFichierInt en minute" << (temps_TransfertFichierDouble/1000)/60;


        //FERMETURE DU PORT
        obj_SD->close();
        qDebug()<<"MW: Port fermer par getTailleFichier() ";


        if(tailleFichier.toInt()!=0){

            QTimer::singleShot(600,this,SLOT(port_getFichier()));

        }
        else{
            qDebug()<<"La taille du fichier n'est pas bonne. Relancer le transfert.";
            qDebug()<<"La carte ne contient peut être pas de fichier?";
        }
       }

       else{

       qDebug()<<"MW: Lecture du port: Rien sur le port. Verifier la connexion avec la carte et relancer"  ;
    }


}

void MainWindow::attente()
{

    decompteTemps_Transfert--;
    ui->progressBar_SdToPC->setValue(100-decompteTemps_Transfert);
}

void MainWindow::port_getFichier()
{
    //----------------------------------------------------------------------
    //---------------------------Transfert du Fichier-----------------------
    //----------------------------------------------------------------------

    if (!obj_SD->isOpen())
    {
        //OUVERTURE DU PORT
        obj_SD->setPortName(ui->portBox->currentText());
        obj_SD->open(QIODevice::ReadWrite);
        qDebug()<< "MW: Port" << obj_SD->portName() << "Ouvert";

        //ECRITURE SUR LE PORT
        obj_SD->write(obj_SD->lectureFichier().toLatin1());
        qDebug()<<"MW: Ecriture sur le port:" << obj_SD->lectureFichier() ;

        //LECTURE DU PORT
        //Lance l'application qui va aller lire sur le port quand le temps de transfert est terminé
        QTimer::singleShot(temps_TransfertFichierInt,this,SLOT(port_getContenuFichier()));

    }

    else
    {
        //FERMETURE DU PORT (Dans le cas où il était resté ouvert)
        obj_SD->close();
        qDebug()<<"Le port était ouvert et a été fermé";

    }
}

void MainWindow::port_getContenuFichier(){
    timer->disconnect();

    if (obj_SD->bytesAvailable())
    {
        qDebug()<<"MW: port_getContenuFichier()";
        qDebug()<<"MW: obj_SD->size():" << obj_SD->size() ;

        // CONTRÔLE DE LA TAILLE DU FICHIER

        //Si le fichier reçu est plus grand que ce qui était attendu
        //On estime qu'il est complet
        if (obj_SD->size()>tailleFichier.toInt())
        {
            qDebug()<<"MW: Le fichier est complet " ;
        }

        //Si le fichier reçu est plus petit que ce qui était attendu
        //On estime que le fichier est incomplet
        else
        {
            qDebug()<<"MW: Le fichier n'est pas complet " ;
        }

        // Enregistrement de ce qu'il y a sur le port dans un QString
        rcvString=QString::fromLatin1(obj_SD->readAll());
        qDebug()<<"MW: Lecture du port" << rcvString ;
        obj_SD->sauvegardeFichier(rcvString);

        //FERMETURE DU PORT
        obj_SD->close();
        qDebug()<<"MW: Port fermer par port_getContenuFichier() ";

        }
        else{
        qDebug()<<"MW: Lecture du port: Rien sur le port"  ;
    }
}

void MainWindow::on_pushButton_parseToDB_clicked()
{


    if(ui->lineEdit_MesureGPS_cheminFichier->text()==obj_BDD->getCheminFichier()){
        qDebug()<<"MW: Le chemin du fichier n'a pas été modifié"  ;
        obj_BDD->parseToDB();
    }
    else{
        qDebug()<<"MW: Le chemin du fichier a été modifié"  ;
        obj_BDD->parseToDB();
    }
    ui->labelnbreErreurLigneFichier_2->setNum(obj_BDD->getNbreErreurLignes_Fichier());
    ui->label_nbreBonneLigneFichier_2->setNum(obj_BDD->getNbreBonneLignes_Fichier());
}

void MainWindow::on_pushButton_plusTableCapteur_clicked()
{
    //AFFICHAGE TABLE MESURE
    obj_BDD->ligneSuivante_TableMesure();
    ui->label_date_2->setText(obj_BDD->getDate());
    ui->label_heure_2->setText(obj_BDD->getHeure());
    ui->label_voie1_2->setText(obj_BDD->getVoie1());
    ui->label_voie2_2->setText(obj_BDD->getVoie2());
    ui->label_voie3_2->setText(obj_BDD->getVoie3());
    ui->label_voie4_2->setText(obj_BDD->getVoie4());
    ui->label_voie5_2->setText(obj_BDD->getVoie5());
    ui->label_voie6_2->setText(obj_BDD->getVoie6());
    ui->label_voie7_2->setText(obj_BDD->getVoie7());
    ui->label_voie8_2->setText(obj_BDD->getVoie8());

    ui->label_eTor1_2->setText(obj_BDD->geteTor_1());
    ui->label_eTor2_2->setText(obj_BDD->geteTor_2());

    ui->label_sTor1_2->setText(obj_BDD->getsTor_1());
    ui->label_sTor2_2->setText(obj_BDD->getsTor_2());

    ui->label_ligneActu_tableMesure_2->setNum((obj_BDD->getNumeroLigne_TableMesure()));

    //AFFICHAGE TABLE GPS
    obj_BDD->ligneSuivante_TablePositionGPS();
    ui->label_alti_2->setText(obj_BDD->getAlti());
    ui->label_latitude_2->setText(obj_BDD->getLatitude());
    ui->label_hemisphere_2->setText(obj_BDD->getLongitude());
    ui->label_longitude_2->setText(obj_BDD->getLongitude());
    ui->label_elongation_2->setText(obj_BDD->getElongation());
    ui->label_st_2->setText(obj_BDD->getSt());
    ui->label_loc_2->setText(obj_BDD->getLoc());

    ui->label_ligneActu_tableGPS_2->setNum(obj_BDD->getNumeroLigne_TablePositionGPS());

}

void MainWindow::on_pushButton_moinTableCapteur_clicked()
{

    //AFFICHAGE TABLE MESURE

    obj_BDD->lignePrecedente_TableMesure();

    ui->label_date_2->setText(obj_BDD->getDate());
    ui->label_heure_2->setText(obj_BDD->getHeure());
    ui->label_voie1_2->setText(obj_BDD->getVoie1());
    ui->label_voie2_2->setText(obj_BDD->getVoie2());
    ui->label_voie3_2->setText(obj_BDD->getVoie3());
    ui->label_voie4_2->setText(obj_BDD->getVoie4());
    ui->label_voie5_2->setText(obj_BDD->getVoie5());
    ui->label_voie6_2->setText(obj_BDD->getVoie6());
    ui->label_voie7_2->setText(obj_BDD->getVoie7());
    ui->label_voie8_2->setText(obj_BDD->getVoie8());

    ui->label_eTor1_2->setText(obj_BDD->geteTor_1());
    ui->label_eTor2_2->setText(obj_BDD->geteTor_2());

    ui->label_sTor1_2->setText(obj_BDD->getsTor_1());
    ui->label_sTor2_2->setText(obj_BDD->getsTor_2());

    ui->label_ligneActu_tableMesure_2->setNum((obj_BDD->getNumeroLigne_TableMesure()));

    //AFFICHAGE TABLE GPS

    obj_BDD->lignePrecedente_TablePositionGPS();
    ui->label_alti_2->setText(obj_BDD->getAlti());
    ui->label_latitude_2->setText(obj_BDD->getLatitude());
    ui->label_hemisphere_2->setText(obj_BDD->getLongitude());
    ui->label_longitude_2->setText(obj_BDD->getLongitude());
    ui->label_elongation_2->setText(obj_BDD->getElongation());
    ui->label_st_2->setText(obj_BDD->getSt());
    ui->label_loc_2->setText(obj_BDD->getLoc());

    ui->label_ligneActu_tableGPS_2->setNum(obj_BDD->getNumeroLigne_TablePositionGPS());
}

void MainWindow::on_pushButton_CarteMango_clicked()
{
    obj_BDD->setTableCarteMango(ui->lineEdit_NomCarteMango->text(),ui->lineEdit_TypeCarteMango->text(),ui->lineEdit_NumeroSerieCarteMango->text());

}

void MainWindow::on_pushButton_setCapteur_clicked()
{
    obj_BDD->setTableCapteur(ui->lineEdit_NomCapteur->text(),ui->lineEdit_typeCapteur->text(),ui->lineEdit_NomFichierConversionCapteur->text(),ui->lineEdit_VoieCapteur->text());

}

void MainWindow::on_pushButton_plusTableCarteMango_clicked()
{

    obj_BDD->ligneSuivante_TableCarteMango();
    ui->label_NomCarteMango_2->setText(obj_BDD->getNomCarteMango());
    ui->label_TypeCarteMango_2->setText(obj_BDD->getTypeCarteMango());
    ui->label_NumeroSerieCarteMango_2->setText(obj_BDD->getNumeroSerieCarteMango());

    ui->label_ligneActu_TableCarteMango_2->setNum(obj_BDD->getNumeroLigne_TableCarteMango());
}

void MainWindow::on_pushButton_moinTableCarteMango_clicked()
{
    obj_BDD->lignePrecedente_TableCarteMango();
    ui->label_NomCarteMango_2->setText(obj_BDD->getNomCarteMango());
    ui->label_TypeCarteMango_2->setText(obj_BDD->getTypeCarteMango());
    ui->label_NumeroSerieCarteMango_2->setText(obj_BDD->getNumeroSerieCarteMango());

    ui->label_ligneActu_TableCarteMango_2->setNum(obj_BDD->getNumeroLigne_TableCarteMango());
}

void MainWindow::on_pushButton_moinTableCapteur_2_clicked()
{

    obj_BDD->lignePrecedente_TableCapteur();
    ui->label_VoieCapteur_2->setText(obj_BDD->getVoieCapteur());
    ui->label_typeCapteur_2->setText(obj_BDD->getTypeCapteur());
    ui->label_NomFichierConversionCapteur_2->setText((obj_BDD->getNomFichierConversionCapteur()));
    ui->label_NomCapteur_2->setText(obj_BDD->getNomCapteur());

    ui->label_ligneActu_TableCapteur_2->setNum(obj_BDD->getNumeroLigne_TableCapteur());
}



void MainWindow::on_pushButton_plusTableCapteur_2_clicked()
{
    obj_BDD->ligneSuivante_TableCapteur();
    ui->label_VoieCapteur_2->setText(obj_BDD->getVoieCapteur());
    ui->label_typeCapteur_2->setText(obj_BDD->getTypeCapteur());
    ui->label_NomFichierConversionCapteur_2->setText((obj_BDD->getNomFichierConversionCapteur()));
    ui->label_NomCapteur_2->setText(obj_BDD->getNomCapteur());

    ui->label_ligneActu_TableCapteur_2->setNum(obj_BDD->getNumeroLigne_TableCapteur());
}
