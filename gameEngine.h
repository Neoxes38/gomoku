// Header

void affPlateau(int *plateau, int nbCol, int nbLignes);
int lancerLaPartie(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int joueurDepart, int joueur, int ordinateur);
void jouerUnCoup(int *plateau, int joueurCourant, int *positionAJouer, int nbCol);
bool isPartieNonTerminee(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int nbTours, int *gagnant, int joueur, int ordinateur);
void afficherEcranDeFin(int gagnant);
bool resteCasesLibres(int *plateau, int nbCol, int nbLignes);
void initialiserLeJeu(int *scoreFinalJoueur, int *scoreFinalOrdinateur);
void ecranDesPartiesGagnees(int scoreFinalJoueur, int scoreFinalOrdinateur);
