#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "controleur_rover.h"


#define REDUCTION_TAUX_ECHANTILLONAGE 0.5 //   en %
#define DEFAULT_PAS_ECHANTILLONAGE 0.1 //   en s
#define REDUCTION_VITESSE 0.4 //   en %
#define CONSIGNE_VITESSE 0.5 //  en m/s
#define RAYON_ROUE 20 //  en cm
#define CONSIGNE_VITESSE_MOTOR CONSIGNE_VITESSE* 360.0 / (2.0 * 3.14 * RAYON_ROUE) //  en rad/s

int batterie = 100;
bool retour_point_de_depart=false;
float pas_echantillonage;
int var=50;

OutputControler controleur(Capteurs capteurs,bool button_emergency, int batterie){
    float output_speed_motor[6];
    OutputControler output;
    for(int i=0;i<6;i++){
        output.speed_motor[i] = CONSIGNE_VITESSE;
    }
    pas_echantillonage = DEFAULT_PAS_ECHANTILLONAGE;
    for(int i=0;i<5;i++){
        // Cas où l'on est dans la zone de sécurité
        if(capteurs.capteur_radar[i] < 100){
            pas_echantillonage = DEFAULT_PAS_ECHANTILLONAGE*REDUCTION_TAUX_ECHANTILLONAGE;
            for(int j=0;j<6;j++){
                output.speed_motor[j] = -1 * CONSIGNE_VITESSE_MOTOR * REDUCTION_VITESSE;
            }
            break;
        }
    }

    if(button_emergency || (batterie < 10)) {
        // Lancement de l'itinéraire de retour
        output.retour_point_de_depart = true;
    }

    return output;
}

// void DebugOuput(OutputControler output){
//     printf("\n");
//     printf("DEBUG OUTPUT:\n");
//     for(int i=0;i<6;i++){
//         printf("%f       ",output.speed_motor[i]);
//     }
//     printf("\n");
// }

// void DebugInput(Capteurs capteurs){
//     printf("\n");
//     printf("DEBUG INPUT:\n");
//     printf("pression: %f       \n",capteurs.capteur_pression);
//     printf("temperature: %f       \n",capteurs.capteur_temperature);
//     printf("radar:\n");
//     for(int i=0;i<5;i++){
//         printf("%f       ",capteurs.capteur_radar[i]);
//     }
//     printf("\n");
// }

// void test () {
//   int cnt = 0;
//   bool flag;



//   if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = false;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==false && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     for (int i=0; i<5; i++) {
//       if (output.speed_motor[i] < 0){
//         flag = false;
//         break;
//       }
//     }
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {50,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = false;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==false && pas_echantillonage<DEFAULT_PAS_ECHANTILLONAGE;
//     for (int i=0; i<5; i++) {
//       if (output.speed_motor[i] > 0){
//         flag = false;
//         break;
//       }
//     }
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 5;
//     retour_point_de_depart = false;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==true && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=true;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = false;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==true && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }
  


// if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = true;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==false && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     for (int i=0; i<5; i++) {
//       if (output.speed_motor[i] < 0){
//         flag = false;
//         break;
//       }
//     }
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {50,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = true;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==false && pas_echantillonage<DEFAULT_PAS_ECHANTILLONAGE;
//     for (int i=0; i<5; i++) {
//       if (output.speed_motor[i] > 0){
//         flag = false;
//         break;
//       }
//     }
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=false;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 5;
//     retour_point_de_depart = true;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==true && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }

//   if (true) {
//     bool button_emergency=true;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = true;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==true && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//   }
// }

