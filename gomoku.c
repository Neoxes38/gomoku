#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <math.h>
#include <string.h>

#include "gameEngine.h"

// Ligne de compilation :  gcc gomoku.c joueur.c gameEngine.c ordinateur.c -o gomoku -lm
// Ligne d'exécution :     ./gomoku 

int main(int argc, char *argv[]) 
{
    int scoreFinalJoueur, scoreFinalOrdinateur;
    scoreFinalJoueur=0;
    scoreFinalOrdinateur=0;
    initialiserLeJeu(&scoreFinalJoueur, &scoreFinalOrdinateur);
    ecranDesPartiesGagnees(scoreFinalJoueur, scoreFinalOrdinateur);
    return 0;
}