/* 
 * Demo.c
 *
 * Example use of Netica API Programmer's Library
 *
 * This is a combination of the first 2 examples in the Netica API
 * Reference Manual.  It can be used to test if the installation is successful.
 *
 * Copyright (C) 1992-2010 by Norsys Software Corp.
 * The software in this file may be copied, modified, and/or included in 
 * derivative works without charge or obligation.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Netica.h"
#include "NeticaEx.h"

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

extern environ_ns *env;

int main (void){
        net_bn *net;
        node_bn *Estado_Actual, *Health, *Weapons, *OpponentWeapons, *HearSound, *NumberEnemies, *ProximateWeapons, *ProximateHealing, *Estado_Futuro;
        double belief;
        char mesg[MESG_LEN_ns];
        int res;

        printf ("\nWelcome to Netica API!\n");
        printf ("This demo project is from the first 2 examples of the Reference Manual.\n");
        printf ("If it compiles, links and runs successfully (i.e. without generating\n");
        printf ("errors), then your installation is probably good.\n");
        printf ("Now you can replace the Demo.c file with your own code.\n");
        printf ("--------------------------------------------------------------------\n\n");

        env = NewNeticaEnviron_ns (NULL, NULL, NULL);
        res = InitNetica2_bn (env, mesg);

        printf ("%s\n", mesg);
        if (res < 0)  return -1;

        net = NewNet_bn("BotCasual", env);
		        CHKERR

        Estado_Actual = NewNode_bn("St",6,net);
	SetNodeStateNames_bn (Estado_Actual, "Atacar","Recoger_Armas","Recoger_Energia","Explorar","Huir","Detectar_Peligro");
	CHKERR

	Health = NewNode_bn("H",2,net);
	SetNodeStateNames_bn (Health,"Alta","Baja");
	CHKERR

	Weapons = NewNode_bn("W",2,net);
	SetNodeStateNames_bn(Weapons,"Armado","Desarmado");
	CHKERR

	OpponentWeapons = NewNode_bn("OW",2,net);
	SetNodeStateNames_bn(OpponentWeapons,"Armado","Desarmado");
	CHKERR

	HearSound = NewNode_bn("HN",2,net);
	SetNodeStateNames_bn(HearSound,"Si","No");
	CHKERR

	NumberEnemies = NewNode_bn("NE",2,net);
	SetNodeStateNames_bn (NumberEnemies,"Si","No");
	CHKERR

	ProximateWeapons = NewNode_bn("PW",2,net);
	SetNodeStateNames_bn (ProximateWeaposn,"Si","No");
	CHKERR

	ProximateHealing = NewNode_bn("PH",2,net);
	SetNodeStateNames_bn (ProximateHealing,"Si","No");
        CHKERR

	Estado_Futuro = NewNode_bn("St1",6,net);
        SetNodeStateNames_bn (Estado_Futuro, "Atacar","Recoger_Armas","Recoger_Energia","Explorar","Huir","Detectar_Peligro");
        CHKERR


        /* SetNodeTitle_bn (TbOrCa, "Tuberculosis or Cancer");
        SetNodeTitle_bn (Cancer, "Lung Cancer");
        CHKERR*/
        *Estado_Actual, *Health, *Weapons, *OpponentWeapons, *HearSound, *NumberEnemies, *ProximateWeapons, *ProximateHealing, *Estado_Futuro

        //AddLink_bn (VisitAsia, Tuberculosis);
	AddLink_bn(Estado_Actual, Estado_Futuro);
	AddLink_bn(Health, Estado_Futuro)
        AddLink_bn(Weapons, Estado_Futuro);
        AddLink_bn(OpponentWeapons, Estado_Futuro);
        AddLink_bn(HearSound, Estado_Futuro);
        AddLink_bn(NumberEnemies, Estado_Futuro);
        AddLink_bn(ProximateWeapons, Estado_Futuro);
        AddLink_bn(ProximateHealing, Estado_Futuro);
        CHKERR
	//Hasta aqui
        SetNodeProbs(Estado_Actual, "Atacar", 19.31 );
        SetNodeProbs(Estado_Actual, "Recoger_Armas", 21.045 );
        SetNodeProbs(Estado_Actual, "Recoger_Energia", 8.826  );
        SetNodeProbs(Estado_Actual, "Explorar", 7.318  );
        SetNodeProbs(Estado_Actual, "Huir", 22.632  );
        SetNodeProbs(Estado_Actual, "Detectar_Peligro", 20.869  );

        SetNodeProbs(Health, "Alta", 37.969);
        SetNodeProbs(Health, "Baja", 62.031);

        SetNodeProbs(Weapons, "Armado", 35.966);
        SetNodeProbs(Weapons, "Desarmado", 64.034);

        SetNodeProbs(OpponentWeapons, "Armado", );
        SetNodeProbs(OpponentWeapons, "Desarmado", );

        //                   Tuberculosis Cancer
        SetNodeProbs(HearSound, "Si", );
        SetNodeProbs(HearSound, "No",  );

        SetNodeProbs(NumberEnemies, "Si",  );
        SetNodeProbs(NumberEnemies, "No",  );

        SetNodeProbs(ProximateWeapons, "Si",  );
        SetNodeProbs(ProximateWeapons, "No",  );

        SetNodeProbs(ProximateHealing, "Si",  );
        SetNodeProbs(ProximateHealing, "No",  );

       

        
        //                  TbOrCa  Abnormal Normal
        SetNodeProbs (Estado_Futuro, "Atacar","Recoger_Armas","Recoger_Energia","Explorar","Huir","Detectar_Peligro",   );
        
       CompileNet_bn (net);
        CHKERR

        belief = GetNodeBelief ("Tuberculosis", "present", net);
        CHKERR

        printf ("The probability of tuberculosis is %g\n\n", belief);

        EnterFinding ("XRay", "abnormal", net);
        belief = GetNodeBelief ("Tuberculosis", "present", net);
        CHKERR

        printf ("Given an abnormal X-ray, \n\
         the probability of tuberculosis is %g\n\n", belief);

        EnterFinding ("VisitAsia", "visit", net);
        belief = GetNodeBelief ("Tuberculosis", "present", net);
        CHKERR

        printf ("Given an abnormal X-ray and a visit to Asia, \n\
             the probability of tuberculosis is %g\n\n", belief);
end:
        DeleteNet_bn (net);
        res = CloseNetica_bn (env, mesg);
        printf ("%s\n", mesg);
        printf ("Press <enter> key to quit ");
        getchar();
        return (res < 0) ? -1 : 0;

error:
        fprintf (stderr, "NeticaDemo: Error in %s\n", 
                 ErrorMessage_ns (GetError_ns (env, ERROR_ERR, NULL)));
        goto end;
}

