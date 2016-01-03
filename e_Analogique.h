#include "lecturevoie.h"


#ifndef E_ANALOGIQUE_H
#define E_ANALOGIQUE_H

class e_analogique : public lectureVoie
{
public:
    e_analogique();
    ~e_analogique();

    QString getVoie1();
    QString getVoie2();
    QString getVoie3();             /*************** getVoie 1 à 8 ************/
    QString getVoie4();             /*** Récuperation des valeurs des voies ***/
    QString getVoie5();
    QString getVoie6();
    QString getVoie7();
    QString getVoie8();

private: //Méthode
    void extractionValAnalog();



public: //Attribut


private: //Attribut
    QString valAnalog1;
    QString valAnalog2;
    QString valAnalog3;            /*** Attribut Private ***/
    QString valAnalog4;            /*** valAnalog 1 à 8  ***/
    QString valAnalog5;            /*** pour utilisation ***/
    QString valAnalog6;            /**** dans la classe ****/
    QString valAnalog7;
    QString valAnalog8;

};

#endif // E_ANALOGIQUE_H
