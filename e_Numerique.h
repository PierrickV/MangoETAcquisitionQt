#include "lecturevoie.h"
#ifndef E_NUMERIQUE_H
#define E_NUMERIQUE_H

class E_numerique : public lectureVoie
{
public:
    E_numerique();
    ~E_numerique();
    QString getENum1();  //Récupération de Enum1
    QString getENum2(); //Récupération de Enum2


private: //Méthode
    void extractionValENum(); //Extraction des données binaires

public: //Attribut

private: //Attribut
    QString valENum1; //Valeur de Enum1
    QString valENum2; //Valeur de Enum2
    QString ENum1;
    QString ENum2;
};

#endif // E_NUMERIQUE_H
