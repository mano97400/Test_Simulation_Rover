#ifndef MAX_H
#define MAX_H


typedef struct OutputControler{
    float speed_motor[6];
    bool retour_point_de_depart;
} OutputControler;

typedef struct Capteurs{
    float capteur_pression;
    float capteur_temperature;
    float capteur_radar[5];
} Capteurs;


extern OutputControler controleur(Capteurs capteurs,bool button_emergency, int batterie);
#endif