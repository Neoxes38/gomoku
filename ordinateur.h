// Header

void determinerCoupOrdinateur(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int *positionAJouer);
void setCoefCases(double *tabCoefCases, int nbCol, int nbLignes);
int evalPosition(double *tabCoefCases, int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe);
double parcoursVertical(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe);
double parcoursHorizontal(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe);
double parcoursDiag1(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe);
double parcoursDiag2(int *plateau, int nbCol, int nbLignes, int nbPionsAAligner, int positionLigne, int positionColonne, int ptDeVueDe);