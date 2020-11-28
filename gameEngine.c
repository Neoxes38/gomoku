#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameEngine.h"
#include "ordinateur.h"
#include "joueur.h"



bool resteCasesLibres(int *plateau, int nbCol, int nbLignes)
{
    int i, j;
    for(i=0; i<nbLignes; i++)
    {
        for(j=0; j<nbCol; j++)
        {
            if (plateau[i*nbCol+j]==0)
            {
                return true;
            }
        }
    }
    return false;
}



bool isPartieNonTerminee(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int nbTours, int *gagnant, int joueur, int ordinateur)
{
    int i, j, compteurJoueur, compteurOrdinateur, ligneAParcourir, colonneAParcourir;
    
    // Personne ne peut avoir aligné 5 pions
    if (nbTours<5)
    {   
        return true;
    }


    ///// Parcours vertical (haut vers le bas)
    for (j=0; j<nbCol; j++)
    {
        compteurJoueur = 0;
        compteurOrdinateur = 0;
        for (i=0; i<nbLignes; i++)
        {
            if(plateau[i*nbCol+j] == ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur = 0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            }
            else if (plateau[i*nbCol+j]==joueur)
            {
                compteurJoueur++;
                compteurOrdinateur = 0;
                if(compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[i*nbCol+j]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
        }
    }



    ///// Parcours Horizontal (gauche vers la droite)
    for (i=0; i<nbLignes; i++)
    {
        compteurJoueur=0;
        compteurOrdinateur=0;
        for (j=0; j<nbCol; j++)
        {
            if(plateau[i*nbCol+j]==ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur=0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            }
            else if (plateau[i*nbCol+j]==joueur)
            {
                compteurJoueur++;
                compteurOrdinateur=0;
                if(compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[i*nbCol+j]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
        }
    }



    ///// Parcours Diagonal1 (haut gauche vers bas droit)
    
    /// Moitié basse
    j=0;
    for (i=(nbLignes-nbPionsAAligner); i>=0; i--)
    {
        ligneAParcourir = i;
        colonneAParcourir = j;
        compteurJoueur = 0;
        compteurOrdinateur = 0;

        while(ligneAParcourir != nbLignes)
        {
            if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur = 0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            } 
            else if(plateau[ligneAParcourir*nbCol+colonneAParcourir]==joueur)
            {
                compteurOrdinateur = 0;
                compteurJoueur++;
                if (compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
            ligneAParcourir++;
            colonneAParcourir++;
        }
    }

    /// Moitié haute
    i=0;
    for(j=0; j<(nbCol-nbPionsAAligner); j++)
    {
        ligneAParcourir=i;
        colonneAParcourir=j;
        compteurJoueur=0;
        compteurOrdinateur=0;

        while(colonneAParcourir != nbCol)
        {
            if(plateau[ligneAParcourir*nbCol+colonneAParcourir]==ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur=0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==joueur)
            {
                compteurJoueur++;
                compteurOrdinateur=0;
                if(compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
            ligneAParcourir++;
            colonneAParcourir++;
        }
    }


    ////// Parcours Diagonale 2 (bas gauche vers le haut droit)
    
    /// Moitié haute
    j=0;
    for(i=nbPionsAAligner-1; i<nbLignes-1; i++)
    {
        ligneAParcourir = i;
        colonneAParcourir = j;
        compteurJoueur=0;
        compteurOrdinateur=0;
        while (ligneAParcourir>=0)
        {
            if(plateau[ligneAParcourir*nbCol+colonneAParcourir]==ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur=0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==joueur)
            {
                compteurJoueur++;
                compteurOrdinateur=0;
                if(compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
            ligneAParcourir--;
            colonneAParcourir++;
        }
    }

    /// Moitié basse
    i=nbLignes-1;
    for(j=0; j<=(nbCol-nbPionsAAligner); j++)
    {
        ligneAParcourir=i; 
        colonneAParcourir=j;
        compteurJoueur=0;
        compteurOrdinateur=0;
        while(colonneAParcourir != nbCol)
        {
            if(plateau[ligneAParcourir*nbCol+colonneAParcourir]==ordinateur)
            {
                compteurOrdinateur++;
                compteurJoueur=0;
                if(compteurOrdinateur==nbPionsAAligner)
                {
                    *gagnant = ordinateur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==joueur)
            {
                compteurJoueur++;
                compteurOrdinateur=0;
                if(compteurJoueur==nbPionsAAligner)
                {
                    *gagnant = joueur;
                    return false;
                }
            }
            else if (plateau[ligneAParcourir*nbCol+colonneAParcourir]==0)
            {
                compteurJoueur=0;
                compteurOrdinateur=0;
            }
            ligneAParcourir--;
            colonneAParcourir++;
        }
    }

    // Si y a plus de cases jouables sur le plateau
    if(!resteCasesLibres(plateau, nbCol, nbLignes))
    {
        *gagnant = 0;
        return false;
    }

    // Si on est dans aucun des cas précédents, alors la partie continue
    return true;
}

void afficherEcranDeFin(int gagnant)
{
    printf("\n\t -----------------------------------------------\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    if(gagnant==1)
    {
        printf("\t|    Bien joué ! (GG comme on dit chez nous)\t|\n");
    }
    else if (gagnant==2)
    {
        printf("\t|     Perdu... Vous êtes mauvais ma parole !\t|\n");
    }
    else 
    {
        printf("\t|\t    Eh c'est un match nuuuul !    \t|\n");
    }
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t -----------------------------------------------\n");
}


int lancerLaPartie(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int joueurDepart, int joueur, int ordinateur)
{
    int *positionAJouer ;
    int joueurCourant, gagnant, nbTours;
    int coupJoueurLigne, coupJoueurCol;
    bool isCoupValide ;
    positionAJouer = calloc(2, sizeof(int));

    nbTours = 0;
    joueurCourant = joueurDepart;

    while (isPartieNonTerminee(plateau, nbCol, nbLignes, nbPionsAAligner, nbTours, &gagnant, joueur, ordinateur))
    {
        if (joueurCourant==joueur)
        {
            isCoupValide = false;

            while(!isCoupValide)
            {
                saisieDesCoordonnees(&coupJoueurLigne, &coupJoueurCol);
                isCoupValide = verificationValiditeCoordonnees(coupJoueurLigne, coupJoueurCol, plateau, nbLignes, nbCol);
            }

            positionAJouer[0] = coupJoueurLigne;
            positionAJouer[1] = coupJoueurCol;                
        }
        else 
        {
            determinerCoupOrdinateur(plateau, nbCol, nbLignes, nbPionsAAligner, positionAJouer);
        }

        jouerUnCoup(plateau, joueurCourant, positionAJouer, nbCol); 
        affPlateau(plateau, nbCol, nbLignes);

        nbTours+=1; 
        joueurCourant = 3 - joueurCourant; 
    }

    free(positionAJouer);
    return gagnant;

}


void affPlateau(int *plateau, int nbCol, int nbLignes)
{
    int i, j;

    printf("\n\n\tOrdinateur = X ; Vous = O \n");
    printf("\n\n     col\t");
    for (j=0; j<nbCol; j++)
    {
        printf("%d\t\t", j);
    }
    printf("\nlign\n\t");
    for (j=0; j<nbCol; j++)
    {
        printf("  -------------\t");
    }
    printf("\n");     
    printf("\t|\t");
    for (j=0; j<nbCol; j++)
    {
        printf("\t|\t");
    }
    printf("\n");    
    for (i=0; i<nbLignes; i++)
    {
        printf("%d\t|\t", i);
        for (j=0; j<nbCol; j++)
        {
            if (plateau[i*nbCol+j]==1)
            {    
                printf("O\t|\t");
            }
            else if(plateau[i*nbCol+j]==2)
            {
                printf("X\t|\t");
            }
            else 
            {
                printf(" \t|\t");
            }
        }
        printf("\n");
        printf("\t|\t");
        for (j=0; j<nbCol; j++)
        {
            printf("\t|\t");
        }
        printf("\n\t");    
        if (i!=nbLignes-1)
        {
            for (j=0; j<nbCol; j++)
            {
                printf("| -------------\t");
            }
            printf("|\n");   
            printf("\t|\t");
            for (j=0; j<nbCol; j++)
            {
                printf("\t|\t");
            }
            printf("\n");    
        } 
    }
    for (j=0; j<nbCol; j++)
    {
        printf("  -------------\t");
    }
    printf("\n");   
}


void jouerUnCoup(int *plateau, int joueurCourant, int *positionAJouer, int nbCol)
{
    plateau[positionAJouer[0]*nbCol+ positionAJouer[1]] = joueurCourant;
}


void initialiserLeJeu(int *scoreFinalJoueur, int *scoreFinalOrdinateur)
{
    int *plateau ;
    int nbCol, nbLignes, nbPionsAAligner, joueur, ordinateur, joueurDepart, gagnant;
    char reponse[3] = {0};

    printf("Vous devez indiquer qui commence à jouer : 1 pour vous ou 2 pour l'ordinateur\n");
    printf("joueur : ");
    scanf("%d", &joueurDepart);

    while(joueurDepart!=1 && joueurDepart!=2)
    {
        printf("Le joueur que vous avez indiqué n'est pas valide\n");
        printf("Vous devez indiquer qui commence à jouer : 1 pour vous ou 2 pour l'ordinateur\n");
        printf("joueur : ");
        scanf("%d", &joueurDepart);
    }

    nbCol = 8 ;
    nbLignes = 8 ;
    plateau = calloc(nbCol*nbLignes, sizeof(int)); // Crée zone mémoire et initialise à 0
    nbPionsAAligner = 5 ;
    joueur = 1 ;
    ordinateur = 2 ;
    
    // Affiche le plateau initialisé avant le début de la partie
    affPlateau(plateau, nbCol, nbLignes);

    // 0 pour match nul, 1 pour le joueur, 2 pour l'ordinateur
    gagnant = lancerLaPartie(plateau, nbCol, nbLignes, nbPionsAAligner, joueurDepart, joueur, ordinateur);

    // Affichage de l'écran de fin de partie
    afficherEcranDeFin(gagnant);
    free(plateau);

    if(gagnant==1)
    {
        *scoreFinalJoueur+=1;
    }
    else if (gagnant == 2)
    {
        *scoreFinalOrdinateur+=1;
    }
    
    printf("\n\nSouhaitez vous recommencer une partie ? 'Oui' ou 'Non'  :  \n");
    scanf("%s", reponse);

    while(strcmp(reponse,"Oui")!=0 && strcmp(reponse,"Non")!=0)
    {
        printf("\n\nVotre réponse est invalide...\n");
        printf("Souhaitez vous recommencer une partie ? 'Oui' ou 'Non'  :  \n");
        scanf("%s", reponse);
    }

    if(strcmp(reponse,"Oui")==0)
    {
        printf("\n\n");
        initialiserLeJeu(scoreFinalJoueur, scoreFinalOrdinateur);
    }
}


void ecranDesPartiesGagnees(int scoreFinalJoueur, int scoreFinalOrdinateur)
{
    printf("\n\t -----------------------------------------------\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t  Vous avez gagné %d partie(s)\t\t|\n", scoreFinalJoueur);
    printf("\t|\tL'ordinateur a gagné %d partie(s)\t|\n", scoreFinalOrdinateur);
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t -----------------------------------------------\n");

    if (scoreFinalJoueur>=scoreFinalOrdinateur)
    {
        printf("\n\t -----------------------------------------------\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t Ouais, vous vous débrouillez...\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t -----------------------------------------------\n");
    }
    else 
    {
        printf("\n\t -----------------------------------------------\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|   Vous voyez, vous êtes mauvais ! Mouhahaha\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t -----------------------------------------------\n");
    }

}