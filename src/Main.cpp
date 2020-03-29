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
        const nodelist_bn* orig_nodes;
	int numnodes;
        double belief;
	stream_ns* casefile;
	char mesg[MESG_LEN_ns];
	int i, res;
	report_ns* err;

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

        //Cargas la red

        net = ReadNet_bn ( NewFileStream_ns ("BotCasual.neta", env, NULL), NO_VISUAL_INFO);
	orig_nodes = GetNetNodes_bn (net);
        int saved = SetNetAutoUpdate_bn (net, 0); 
	CHKERR
        
        numnodes = LengthNodeList_bn (orig_nodes);

        CompileNet_bn (net);
        CHKERR

        /*for (i = 0;  i < numnodes;  ++i)
                printf ("%s", GetNodeName_bn (NthNode_bn (orig_nodes, i)));
	CHKERR*/

        /////  ************* EJEMPLOS ********************* ///////
        printf("*********************TEST*********************\n\n");

        printf("-----------------PRIMER EJEMPLO-----------------\n\n");

        EnterFinding ("St", "Atacar", net);
        CHKERR

        EnterFinding ("OW", "Armado", net);
        belief = GetNodeBelief ("St1", "Atacar", net);
        CHKERR

        printf ("P(St1 = Atacar | St = Atacar , H,W, Ow = Armado, HN,NE,PW,PH) =  %g\n\n", belief);

        SetNetAutoUpdate_bn (net, saved); 

        RetractNodeFindings_bn(NthNode_bn(orig_nodes, 0));
        RetractNodeFindings_bn(NthNode_bn(orig_nodes, 3));

        printf("-----------------SEGUNDO EJEMPLO-----------------\n\n");

        EnterFinding ("W", "Desarmado", net);
        EnterFinding ("H", "Alto", net);
        CHKERR

        EnterFinding ("PW", "No", net);
        belief = GetNodeBelief ("St1", "Explorar", net);
        CHKERR

        printf ("P(St1 = Explorar| St, H = Alto,W= Desarmado, Ow , HN,NE,PW = No,PH) = %g\n\n", belief);

        RetractNodeFindings_bn(NthNode_bn(orig_nodes, 2));
        RetractNodeFindings_bn(NthNode_bn(orig_nodes, 1));
        RetractNodeFindings_bn(NthNode_bn(orig_nodes, 6));

        printf("-----------------TERCER EJEMPLO-----------------\n\n");

        EnterFinding ("HN", "Si", net);
        CHKERR

        EnterFinding ("PH", "Si", net);
        belief = GetNodeBelief ("St1", "Huir", net);
        CHKERR

        printf ("P(St1 = Huir | St, H, W, OW, HN = Si, NE, PW, PH = Si ) = %g\n\n", belief);

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

