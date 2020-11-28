#include <stdbool.h> 
#include <stdio.h>
#include "joueur.h"

void saisieDesCoordonnees(int *coupJoueurLigne, int *coupJoueurCol)
{
    printf("\nVeuillez entrer les coordonnées de votre coup à jouer :\n");
    printf("ligne : ");
    scanf("%d", coupJoueurLigne);
    printf("colonne : ");
    scanf("%d", coupJoueurCol);
    printf("\n");
}

bool verificationValiditeCoordonnees(int coupJoueurLigne, int coupJoueurCol, int *plateau, int nbLignes, int nbCol)
{
    if (coupJoueurLigne<0 || coupJoueurLigne > nbLignes-1 || coupJoueurCol<0 || coupJoueurCol > nbCol-1)
    {
        printf("Les coordonnées saisies sont invalides.\nElles doivent être comprises entre 0 et %d.\n", nbCol-1);
        return false;
    }
    if (plateau[coupJoueurLigne*nbCol+coupJoueurCol]!=0)
    {
        printf("La case indiquée est déjà occupée. Veuillez saisir de nouvelles coordonnées\n");
        return false;
    }
    return true;
}