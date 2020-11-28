#include <stdbool.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "ordinateur.h"



typedef struct MeilleurCoup MeilleurCoup;
struct MeilleurCoup
{
    int positionLigne;
    int positionColonne;
    int score;
};


void determinerCoupOrdinateur(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int *positionAJouer)
{   
    double *tabCoefCases;
    int i, j, scoreJouerOrdinateur, scoreBloquerAdversaire;
    MeilleurCoup coupPourOrdinateur, coupBlocageAdversaire;
    
    coupPourOrdinateur.positionLigne = 0;
    coupPourOrdinateur.positionColonne = 0;
    coupPourOrdinateur.score = 0;

    coupBlocageAdversaire.positionLigne = -1;
    coupBlocageAdversaire.positionColonne = -1;
    coupBlocageAdversaire.score = (nbPionsAAligner-1)*195;

    tabCoefCases = malloc(nbLignes*nbCol*sizeof(double));
    setCoefCases(tabCoefCases, nbCol, nbLignes);

    // boucle sur toutes les cases libres de plateau
    for (i=0; i<nbLignes; i++)
    {
        for (j=0; j<nbCol ; j++)
        {
            if(plateau[i*nbCol+j] == 0) // Certifie qu'on ira pas sur des cases déjà prises
            {   
                scoreJouerOrdinateur = evalPosition(tabCoefCases, plateau, nbCol, nbLignes, nbPionsAAligner, i, j, 2);
                scoreBloquerAdversaire = evalPosition(tabCoefCases, plateau, nbCol, nbLignes, nbPionsAAligner, i, j, 1);
                if(scoreBloquerAdversaire>coupBlocageAdversaire.score)
                {
                    coupBlocageAdversaire.positionLigne = i;
                    coupBlocageAdversaire.positionColonne = j;
                    coupBlocageAdversaire.score = scoreBloquerAdversaire;
                }
                if(scoreJouerOrdinateur>coupPourOrdinateur.score)
                {
                    coupPourOrdinateur.positionLigne = i;
                    coupPourOrdinateur.positionColonne = j;
                    coupPourOrdinateur.score = scoreJouerOrdinateur;
                }
            }
        }
    }

    if (coupBlocageAdversaire.score>(nbPionsAAligner-1)*195   &&    coupPourOrdinateur.score<nbPionsAAligner*195)
    {
        positionAJouer[0] = coupBlocageAdversaire.positionLigne;
        positionAJouer[1] = coupBlocageAdversaire.positionColonne;
    }
    else 
    {
        positionAJouer[0] = coupPourOrdinateur.positionLigne;
        positionAJouer[1] = coupPourOrdinateur.positionColonne;
    }
    
    free(tabCoefCases);
    
}


double parcoursVertical(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe)
{
    int *copiePlateau;
    int joueurEnCours, joueurAdverse, i, ligneDebut, ligneFin;
    double maxCompteurVertical, compteurVertical, potentielAlignement;

    copiePlateau = malloc(nbLignes*nbCol*sizeof(int));
    memcpy(copiePlateau, plateau, nbLignes*nbCol*sizeof(int));

    joueurEnCours = ptDeVueDe;
    joueurAdverse = 3 - joueurEnCours;
    copiePlateau[positionLigne*nbCol+positionColonne] = joueurEnCours;

    maxCompteurVertical = 0;
    compteurVertical = 0;
    if ( !( (positionLigne==0  &&  copiePlateau[(positionLigne+1)*nbCol+positionColonne]==joueurAdverse)
            || (positionLigne==nbLignes-1  &&  copiePlateau[(positionLigne-1)*nbCol+positionColonne]==joueurAdverse)
            || ((positionLigne!=0 && positionLigne!=nbLignes-1)  
                    &&  (   copiePlateau[(positionLigne+1)*nbCol+positionColonne]==joueurAdverse
                            || copiePlateau[(positionLigne-1)*nbCol+positionColonne]==joueurAdverse
                        )
               )
          ))
    {
        ligneDebut = positionLigne - (nbPionsAAligner-1) ;
        ligneFin = positionLigne + (nbPionsAAligner-1) ;
        if(ligneDebut<0)        ligneDebut = 0 ;
        if(ligneFin>nbLignes-1) ligneFin = nbLignes-1 ;

        for (i=ligneDebut; i<ligneFin; i++)
        {
            if (copiePlateau[i*nbCol+positionColonne]==joueurEnCours)
            {
                compteurVertical++;
                if (compteurVertical>maxCompteurVertical)
                {
                    maxCompteurVertical=compteurVertical;
                }
            }
            else if (copiePlateau[i*nbCol+positionColonne]==joueurAdverse)
            {
                maxCompteurVertical-=1;
                compteurVertical = 0;
            }
            else 
            {
                potentielAlignement = parcoursVertical(copiePlateau, nbCol, nbLignes, nbPionsAAligner, i, positionColonne, joueurEnCours);
                if(potentielAlignement>=nbPionsAAligner || potentielAlignement-floor(potentielAlignement)>0) // Faudra voir ce que ça change si on enlève la deuxième condition
                {
                    compteurVertical+=0.09;
                    if (compteurVertical>maxCompteurVertical)
                    {
                        maxCompteurVertical=compteurVertical;
                    }
                }
                else // On peut pas espérer pouvoir aligner 5 pions sur cet alignement
                {
                    maxCompteurVertical = 0;
                    break; // Donc on abandonne cet alignement
                }
            }
        }

    }
    free(copiePlateau);
    return maxCompteurVertical;
}


double parcoursHorizontal(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe)
{
    int *copiePlateau;
    int joueurEnCours, joueurAdverse, j, colonneDebut, colonneFin;
    double maxCompteurHorizontal, compteurHorizontal, potentielAlignement;

    copiePlateau = malloc(nbLignes*nbCol*sizeof(int));
    memcpy(copiePlateau, plateau, nbLignes*nbCol*sizeof(int));

    joueurEnCours = ptDeVueDe;
    joueurAdverse = 3 - joueurEnCours;
    copiePlateau[positionLigne*nbCol+positionColonne] = joueurEnCours;

    maxCompteurHorizontal = 0;
    compteurHorizontal = 0;
    if ( !( (positionColonne==0  &&  copiePlateau[positionLigne*nbCol+(positionColonne+1)]==joueurAdverse)
            || (positionColonne==nbCol-1  &&  copiePlateau[positionLigne*nbCol+(positionColonne-1)]==joueurAdverse)
            || ((positionColonne!=0 && positionColonne!=nbCol-1)  
                    &&  (   copiePlateau[positionLigne*nbCol+(positionColonne+1)]==joueurAdverse
                            || copiePlateau[positionLigne*nbCol+(positionColonne-1)]==joueurAdverse
                        )
               )
          ))
    {
        colonneDebut = positionColonne - (nbPionsAAligner-1) ;
        colonneFin = positionColonne + (nbPionsAAligner-1) ;
        if(colonneDebut<0)        colonneDebut = 0 ;
        if(colonneFin>nbCol-1)    colonneFin = nbCol-1 ;

        for (j=colonneDebut; j<colonneFin; j++)
        {
            if (copiePlateau[positionLigne*nbCol+j]==joueurEnCours)
            {
                compteurHorizontal++;
                if (compteurHorizontal>maxCompteurHorizontal)
                {
                    maxCompteurHorizontal=compteurHorizontal;
                }
            }
            else if (copiePlateau[positionLigne*nbCol+j]==joueurAdverse)
            {
                maxCompteurHorizontal-=1;
                compteurHorizontal = 0;
            }
            else 
            {
                potentielAlignement = parcoursHorizontal(copiePlateau, nbCol, nbLignes, nbPionsAAligner, positionLigne, j, joueurEnCours);
                if(potentielAlignement>=nbPionsAAligner || potentielAlignement-floor(potentielAlignement)>0) // Faudra voir ce que ça change si on enlève la deuxième condition
                {
                    compteurHorizontal+=0.09;
                    if (compteurHorizontal>maxCompteurHorizontal)
                    {
                        maxCompteurHorizontal=compteurHorizontal;
                    }
                }
                else // On peut pas espérer pouvoir aligner 5 pions sur cet alignement
                {
                    maxCompteurHorizontal = 0;
                    break; // Donc on abandonne cet alignement
                }
            }
        }

    }
    free(copiePlateau);
    return maxCompteurHorizontal;

}


double parcoursDiag1(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe)
{
    int *copiePlateau;
    int joueurEnCours, joueurAdverse, i, j, ligneDebut, ligneFin, colonneDebut, colonneFin;
    double maxCompteurDiag1, compteurDiag1, potentielAlignement;

    copiePlateau = malloc(nbLignes*nbCol*sizeof(int));
    memcpy(copiePlateau, plateau, nbLignes*nbCol*sizeof(int));

    joueurEnCours = ptDeVueDe;
    joueurAdverse = 3 - joueurEnCours;
    copiePlateau[positionLigne*nbCol+positionColonne] = joueurEnCours;

    compteurDiag1 = 0;
    maxCompteurDiag1 = 0;
    // pas dans les coins et pas d'adversaire en contact direct... Ca me semble étrange
    if (  !( (positionLigne==0 && positionColonne==nbCol-1)
             || (positionColonne==0 && positionLigne==nbLignes-1)
             || (positionLigne==nbLignes-1 && positionColonne==nbCol-1)
             || ((positionLigne==0 || positionColonne==0) && copiePlateau[(positionLigne+1)*nbCol+(positionColonne+1)]==joueurAdverse)
             || ((positionLigne==nbLignes-1 || positionColonne==nbCol-1) && copiePlateau[(positionLigne-1)*nbCol+(positionColonne-1)]==joueurAdverse)
             || ((positionLigne!=0 && positionLigne!=nbLignes-1 && positionColonne!=0 && positionColonne!=nbCol-1)
                    && ( copiePlateau[(positionLigne+1)*nbCol+(positionColonne+1)]==joueurAdverse
                          ||  copiePlateau[(positionLigne-1)*nbCol+(positionColonne-1)]==joueurAdverse
                       )
                )
           )
       )
    {
        ligneDebut = positionLigne - (nbPionsAAligner-1);
        ligneFin = positionLigne + (nbPionsAAligner-1);
        colonneDebut = positionColonne - (nbPionsAAligner-1);
        colonneFin = positionColonne + (nbPionsAAligner-1);

        while (ligneDebut<0 || colonneDebut<0)
        {
            ligneDebut++;
            colonneDebut++;
        }
        while (ligneFin>nbLignes-1 || colonneFin>nbCol-1)
        {
            ligneFin--;
            colonneFin--;
        }

        if ( !( (ligneDebut>(nbLignes-1)-(nbPionsAAligner-1)  &&  (colonneDebut<(nbCol-1)-(nbPionsAAligner-1)))
                ||  (ligneDebut<(nbLignes-1)-(nbPionsAAligner-1)  &&  (colonneDebut>(nbCol-1)-(nbPionsAAligner-1)))
           )) // si on est pas sur les bords où on pourra jamais avoir un alignement de 5
        {
            i = ligneDebut;
            j = colonneDebut;
            while(i<=ligneFin && j<=colonneFin)
            {
                if (copiePlateau[i*nbCol+j]==joueurEnCours)
                {
                    compteurDiag1++;
                    if(compteurDiag1>maxCompteurDiag1)
                    {
                        maxCompteurDiag1=compteurDiag1;
                    }
                }
                else if (copiePlateau[i*nbCol+j]==joueurAdverse)
                {
                    maxCompteurDiag1-=1;
                    compteurDiag1 = 0;
                }
                else
                {
                    potentielAlignement = parcoursDiag1(copiePlateau, nbCol, nbLignes, nbPionsAAligner, i, j, joueurEnCours);
                    if(potentielAlignement>=nbPionsAAligner || potentielAlignement-floor(potentielAlignement)>0) // Faudra voir ce que ça change si on enlève la deuxième condition
                    {
                        compteurDiag1+=0.09;
                        if (compteurDiag1>maxCompteurDiag1)
                        {
                            maxCompteurDiag1=compteurDiag1;
                        }
                    }
                    else // On peut pas espérer pouvoir aligner 5 pions sur cet alignement
                    {
                        maxCompteurDiag1 = 0;
                        break; // Donc on abandonne cet alignement
                    }
                }
                i++;
                j++;                
            }
        }
    }
    free(copiePlateau);
    return maxCompteurDiag1;
}


double parcoursDiag2(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe)
{
    int *copiePlateau;
    int joueurEnCours, joueurAdverse, i, j, ligneDebut, ligneFin, colonneDebut, colonneFin;
    double maxCompteurDiag2, compteurDiag2, potentielAlignement;

    copiePlateau = malloc(nbLignes*nbCol*sizeof(int));
    memcpy(copiePlateau, plateau, nbLignes*nbCol*sizeof(int));

    joueurEnCours = ptDeVueDe;
    joueurAdverse = 3 - joueurEnCours;
    copiePlateau[positionLigne*nbCol+positionColonne] = joueurEnCours;

    compteurDiag2 = 0;
    maxCompteurDiag2 = 0;
    // pas dans les coins et pas d'adversaire en contact direct... Ca me semble étrange
    if (  !( (positionLigne==0 && positionColonne==0)
             || (positionColonne==0 && positionLigne==nbLignes-1)
             || (positionLigne==nbLignes-1 && positionColonne==nbCol-1)
             || ((positionLigne==nbLignes-1 || positionColonne==0) && copiePlateau[(positionLigne-1)*nbCol+(positionColonne+1)]==joueurAdverse)
             || ((positionLigne==0 || positionColonne==nbCol-1) && copiePlateau[(positionLigne+1)*nbCol+(positionColonne-1)]==joueurAdverse)
             || ((positionLigne!=0 && positionLigne!=nbLignes-1 && positionColonne!=0 && positionColonne!=nbCol-1)
                    && ( copiePlateau[(positionLigne+1)*nbCol+(positionColonne-1)]==joueurAdverse
                          ||  copiePlateau[(positionLigne-1)*nbCol+(positionColonne+1)]==joueurAdverse
                       )
                )
           )
       )
    {
        ligneDebut = positionLigne + (nbPionsAAligner-1);
        ligneFin = positionLigne - (nbPionsAAligner-1);
        colonneDebut = positionColonne - (nbPionsAAligner-1);
        colonneFin = positionColonne + (nbPionsAAligner-1);

        while (ligneDebut>nbLignes-1 || colonneDebut<0)
        {
            ligneDebut--;
            colonneDebut++;
        }
        while (ligneFin<0 || colonneFin>nbCol-1)
        {
            ligneFin++;
            colonneFin--;
        }

        if ( !( (ligneDebut<(nbLignes-1)-(nbPionsAAligner-1)  &&  (colonneDebut<(nbCol-1)-(nbPionsAAligner-1)))
                ||  (ligneDebut>(nbLignes-1)-(nbPionsAAligner-1)  &&  (colonneDebut>(nbCol-1)-(nbPionsAAligner-1)))
           )) // si on est pas sur les bords où on pourra jamais avoir un alignement de 5
        {
            i = ligneDebut;
            j = colonneDebut;
            while(i>=ligneFin && j<=colonneFin)
            {
                if (copiePlateau[i*nbCol+j]==joueurEnCours)
                {
                    compteurDiag2++;
                    if(compteurDiag2>maxCompteurDiag2)
                    {
                        maxCompteurDiag2=compteurDiag2;
                    }
                }
                else if (copiePlateau[i*nbCol+j]==joueurAdverse)
                {
                    maxCompteurDiag2-=1;
                    compteurDiag2 = 0;
                }
                else
                {
                    potentielAlignement = parcoursDiag2(copiePlateau, nbCol, nbLignes, nbPionsAAligner, i, j, joueurEnCours);
                    if(potentielAlignement>=nbPionsAAligner || potentielAlignement-floor(potentielAlignement)>0) // Faudra voir ce que ça change si on enlève la deuxième condition
                    {
                        compteurDiag2+=0.09;
                        if (compteurDiag2>maxCompteurDiag2)
                        {
                            maxCompteurDiag2=compteurDiag2;
                        }
                    }
                    else // On peut pas espérer pouvoir aligner 5 pions sur cet alignement
                    {
                        maxCompteurDiag2 = 0;
                        break; // Donc on abandonne cet alignement
                    }
                }
                i--;
                j++;                
            }
        }
    }
    free(copiePlateau);
    return maxCompteurDiag2;

}

// Coefficients d'importance des cases de la grille
void setCoefCases(double *tabCoefCases, int nbCol, int nbLignes)
{
    int i, j, borneFinI, borneFinJ;
    double ecartCoef = (double) 1/nbCol;
    borneFinI = (int) nbLignes/2;
    borneFinJ = (int) nbCol/2 ;
    
    // Remplis à partir des coins vers le centre
    for (i=0; i<borneFinI; i++)
    {
        for (j=0; j<borneFinJ; j++)
        {
            tabCoefCases[i*nbCol+j] = (i+j)*ecartCoef;
            tabCoefCases[i*nbCol+(nbCol-1-j)] = (i+j)*ecartCoef;
            tabCoefCases[(nbLignes-1-i)*nbCol+j] = (i+j)*ecartCoef;
            tabCoefCases[(nbLignes-1-i)*nbCol+(nbCol-1-j)] = (i+j)*ecartCoef;
        }
    }
    
    // Mais si nbLignes et nbCol impair, il reste une colonne et une ligne au centre
    if (nbCol%2 != 0)
    {
        for (i=0 ; i<borneFinI; i++)
        {
            tabCoefCases[i*nbCol + borneFinJ] = (i+(nbCol/2))*ecartCoef ;
            tabCoefCases[(nbLignes-1-i)*nbCol + borneFinJ] = (i+(nbCol/2))*ecartCoef ;
        }
        for (j=0 ; j<borneFinJ ; j++)
        {
            tabCoefCases[borneFinI*nbCol + j] = ((nbLignes/2)+j)*ecartCoef ;
            tabCoefCases[borneFinI*nbCol + (nbCol-1-j)] = ((nbLignes/2)+j)*ecartCoef ;
        }
        tabCoefCases[borneFinI*nbCol+borneFinJ] = ((nbLignes/2)+(nbCol/2))*ecartCoef ;
    }
}


// Evalue le coup du point de vue de ptDeVueDe
int evalPosition(double *tabCoefCases, int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe)
{
    double maxCompteurVertical, maxCompteurHorizontal, maxCompteurDiag1, maxCompteurDiag2, maxCompteurs, scoreCompteurs;
    int nombreFavorable ;

    maxCompteurVertical = parcoursVertical(plateau, nbCol, nbLignes, nbPionsAAligner, positionLigne, positionColonne, ptDeVueDe);
    maxCompteurHorizontal = parcoursHorizontal(plateau, nbCol, nbLignes, nbPionsAAligner, positionLigne, positionColonne, ptDeVueDe);
    maxCompteurDiag1 = parcoursDiag1(plateau, nbCol, nbLignes, nbPionsAAligner, positionLigne, positionColonne, ptDeVueDe);
    maxCompteurDiag2 = parcoursDiag2(plateau, nbCol, nbLignes, nbPionsAAligner, positionLigne, positionColonne, ptDeVueDe);

    if(ptDeVueDe == 1)
    {
        if(maxCompteurVertical<nbPionsAAligner-1)   maxCompteurVertical = 0;
        if(maxCompteurHorizontal<nbPionsAAligner-1) maxCompteurHorizontal = 0;
        if(maxCompteurDiag1<nbPionsAAligner-1)      maxCompteurDiag1 = 0;
        if(maxCompteurDiag2<nbPionsAAligner-1)      maxCompteurDiag2 = 0;
    }

    nombreFavorable = 0 ;
    if (maxCompteurVertical>nbPionsAAligner-3)   nombreFavorable++ ;
	if (maxCompteurHorizontal>nbPionsAAligner-3) nombreFavorable++ ;
	if (maxCompteurDiag1>nbPionsAAligner-3)      nombreFavorable++ ;
	if (maxCompteurDiag2>nbPionsAAligner-3)      nombreFavorable++ ;

    maxCompteurs = maxCompteurVertical ;
	if (maxCompteurs < maxCompteurHorizontal) maxCompteurs = maxCompteurHorizontal ;
	if (maxCompteurs < maxCompteurDiag1)      maxCompteurs = maxCompteurDiag1 ;
	if (maxCompteurs < maxCompteurDiag2)      maxCompteurs = maxCompteurDiag2 ;

    scoreCompteurs = maxCompteurs*195 + 5*tabCoefCases[positionLigne*nbCol+positionColonne] + 20*nombreFavorable/4 ;
    return round(scoreCompteurs);
} 
