#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hled.h"
#include <QTimer>
#include <QMainWindow>

//Classe QextSerialPort
#include "qextserialport.h"
#include "qextserialenumerator.h"

//Classe IRIS
//Gaël
#include "mangoconfiguration.h"
#include "mangogsm.h"
#include "e_Analogique.h"
#include "e_Numerique.h"
//Pierrick
#include "s_numerique.h"
#include "sdtopc.h"
#include "iris_bdd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setNomMango();
    void setMesureVoie();


private slots:

    void on_portBox_highlighted(const QString &arg1);
    void on_lireMesure_clicked();
    void on_SetRecurence_clicked();
    void on_setNewProgrammation_clicked();
    void on_setNewContact_clicked();
    void on_setNewNbrContact_clicked();

    void on_pushButton_S1_clicked();
    void on_pushButton_S2_clicked();

    void on_pushButton_SdToPC_clicked();
    void attente();
    void port_getTailleFichier();
    void port_getFichier();
    void port_getContenuFichier();

    void on_pushButton_parseToDB_clicked();

    void on_pushButton_plusTableCapteur_clicked();

    void on_pushButton_moinTableCapteur_clicked();

    void on_pushButton_CarteMango_clicked();

    void on_pushButton_setCapteur_clicked();

    void on_pushButton_plusTableCarteMango_clicked();

    void on_pushButton_moinTableCapteur_2_clicked();

    void on_pushButton_moinTableCarteMango_clicked();

    void on_pushButton_plusTableCapteur_2_clicked();

private:
    Ui::MainWindow *ui;

    //Objet Gaël
    lectureVoie *C_lectureVoie;
    e_analogique C_eAnalog;
    E_numerique C_eNum;
    mangoConfiguration *C_MangoConfig;
    mangoGSM *C_MangoGsm;

    //Objet Pierrick
    s_Numerique *obj_SNum;
    SDToPC *obj_SD;
    IRIS_BDD *obj_BDD;


    QString tailleFichier;
    int temps_TransfertFichierInt;
    int decompteTemps_Transfert;
    double temps_TransfertFichierDouble;

    QTimer *timer;
    QString rcvString;

    //objet de lecture de port
    QList<QextPortInfo> listPorts;
    QextSerialEnumerator *enumerator;
    int i;
};

#endif // MAINWINDOW_H
