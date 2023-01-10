#include <CUnit.h>
#include <Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "Automated.h"
//#include "CUnit/Console.h"

#include "controleur_rover.h"

#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

void controleur_test_obstacle(void) {
  bool button_emergency=false;
    Capteurs capteurs = {
      .capteur_radar = {50,200,200,200,200}
    };
    OutputControler output = controleur(capteurs, button_emergency,100);
    for (int i=0; i<6; i++) {
      CU_ASSERT(output.speed_motor[i] < 0);
    }
}

void controleur_test_batterie(void) {
   bool button_emergency=false;
    Capteurs capteurs = {
      .capteur_radar = {200,200,200,200,200}
    };
    int batterie = 5;
    OutputControler output = controleur(capteurs, button_emergency, batterie);
    CU_ASSERT(output.retour_point_de_depart);
}

// void controleur_test_emergency(void) {
//     bool button_emergency=true;
//     Capteurs capteurs = {
//       .capteur_radar = {200,200,200,200,200}
//     };
//     batterie = 100;
//     retour_point_de_depart = false;
//     OutputControler output = controleur(capteurs, button_emergency);
//     flag = retour_point_de_depart==true && pas_echantillonage>=DEFAULT_PAS_ECHANTILLONAGE;
//     printf("Test %d : %s\n", cnt++, flag?"Success":"Failure");
//     CU_ASSERT(output.retour_point_de_depart);
// }

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "rover_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "controleur_test_obstacle", controleur_test_obstacle)) 
        || NULL == CU_add_test(pSuite, "controleur_test_batterie", controleur_test_batterie))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   // CU_basic_set_mode(CU_BRM_VERBOSE);
   // CU_basic_run_tests();
   // printf("\n");
   // CU_basic_show_failures(CU_get_failure_list());
   // printf("\n\n");

   // Run all tests using the automated interface
   CU_automated_run_tests();
   //CU_list_tests_to_file();

   // Run all tests using the console interface
   //CU_console_run_tests();

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}