
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
