#include "CMatriceOperation.h"
#include "CMatrice.h"
#include "CException.h"

#define ERROR_TAILLE_MATRICE_DIFF "Les matrices ne sont pas de même dimensions"
#define ERROR_TAILLE_MATRICE_IMCOMPATIBLE "Les matrices ne peuvent pas être multipliées entre elles"

// Constructeur par défaut :
template<class Type>
CMatriceOperation<Type>::CMatriceOperation()
{
}


// Constructeur de recopie :
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(CMatriceOperation& MATarg)
{
	// Affectation des dimensions :
	CMatrice<Type>::uiMATNbreColonnes = MATarg.MATLireNbreColonnes();
	CMatrice<Type>::uiMATNbreLignes = MATarg.MATLireNbreLignes();

	// Allocation de la matrice :
	CMatrice<Type>::MATTableau = (Type**)malloc(CMatrice<Type>::uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < CMatrice<Type>::uiMATNbreLignes; uiBoucleAlloc++) {
		CMatrice<Type>::MATTableau[uiBoucleAlloc] = (Type*)malloc(CMatrice<Type>::uiMATNbreColonnes * sizeof(Type));
	}

	// Recopie des valeurs :
	for (unsigned int iBoucleRecopie = 0; iBoucleRecopie < CMatrice<Type>::uiMATNbreLignes; iBoucleRecopie++) {
		for (unsigned int jBoucleRecopie = 0; jBoucleRecopie < CMatrice<Type>::uiMATNbreColonnes; jBoucleRecopie++) {
			CMatrice<Type>::MATTableau[iBoucleRecopie][jBoucleRecopie] = MATarg.MATLireVal(iBoucleRecopie, jBoucleRecopie);
		}
	}
}


// Constructeur avec paramètres lignes et colonnes :
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(unsigned int uiNbRow, unsigned int uiNbCol)
{
	CMatrice<Type>::uiMATNbreColonnes = uiNbCol;
	CMatrice<Type>::uiMATNbreLignes = uiNbRow;
	CMatrice<Type>::MATTableau = (Type**)malloc(uiNbRow * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiNbRow; uiBoucleAlloc++) {
		CMatrice<Type>::MATTableau[uiBoucleAlloc] = (Type*)malloc(uiNbCol * sizeof(Type));
	}
}


// Constructeur par fichier :
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(char* pcNomFichier)
{
	// Ouverture du fichier :
	std::ifstream ifsFichier(pcNomFichier);
	
	if (!ifsFichier.is_open()) {
		std::cout << "Le fichier n'a pas pu être ouvert\n";
	}
	// Si fichier ouvert correctement :
	else {
		int iNumChamps = 0;
		char cLigne[NBRE_MAX_LIGNES_FICHIER];

		// Récupère la première ligne du fichier :
		ifsFichier >> cLigne;
		

		int indiceCourrant = 0;
		int indiceValeurCourrante = 0;
		char valeurCourrante[NBRE_MAX_LIGNES_FICHIER - NBRE_MAX_CHAMPS_FICHIER];


		/* Prototype d'analyse des champs (abandonné car ordre des champs supposé comme celui des exemples :
				TypeMatrice, NBLignes, NBColonnes, Matrice)
		// Analyse du champ : caracteres jusqu'au '=' ou si il rencontre un '\0' ou un '\n'
		char* champsCourrant[NBRE_MAX_CHAMPS_FICHIER];
		int indiceChampsCourrant = 0;
		while (cLigne[indiceCourrant] != '=' && cLigne[indiceCourrant] != '\0' && cLigne[indiceCourrant] != '\n' && indiceChampsCourrant < NBRE_MAX_CHAMPS_FICHIER) {
			champsCourrant[indiceChampsCourrant] = cLigne[indiceCourrant];

			indiceChampsCourrant++;
			indiceCourrant++;
		}
		champsCourrant[indiceChampsCourrant] = '\0'; // "Fermer" champsCourrant en tant que chaîne de caractères
		indiceCourrant++; // On passe le '='
		*/


		// On suppose que le format est respecté :

		// Tant que tous les champs n'ont pas été complétés :
		while (iNumChamps < 4 && ifsFichier.good()) {
			//Pour chaque ligne du fichier :
			indiceCourrant = 0;
			indiceValeurCourrante = 0;

			// On passe jusqu'aux '=' :
			while (cLigne[indiceCourrant] != '=' && indiceCourrant < NBRE_MAX_LIGNES_FICHIER) {
				if (cLigne[indiceCourrant] == '\0' || cLigne[indiceCourrant] == '\n') // 
					std::cout << "Erreur : fin de ligne imprévue\n";
				indiceCourrant++;
			}
			indiceCourrant++; // Pour passer le '='

			// Analyse de la valeur :
			while (cLigne[indiceCourrant] != '\0' && cLigne[indiceCourrant] != '\n' && indiceCourrant < NBRE_MAX_LIGNES_FICHIER) {
				valeurCourrante[indiceValeurCourrante] = cLigne[indiceCourrant];

				indiceValeurCourrante++;
				indiceCourrant++;
			}
			valeurCourrante[indiceValeurCourrante] = '\0';


			// Affectation des attributs :
			switch (iNumChamps) {
				// TypeMatrice :
			case 0:
				//std::cout << "switch case 0" << std::endl;
				// Ce projet gère UNIQUEMENT le cas où TypeMatrice vaut double, donc :

				if (strcmp((const char*)valeurCourrante, "double") == 0) {
					//this = new CMatriceOperation<double>();
					std::cout << "type correcte : " << valeurCourrante << std::endl;
				}
				else {
					std::cout << "Le type de matrice n'a pas été accepté (seul le type double est accepté)\n";
				}
				break;


				// NBLignes :
			case 1:
				//std::cout << "switch case 1" << std::endl;
				CMatrice<double>::uiMATNbreLignes = atoi((const char*)valeurCourrante);
				std::cout << "Nb Lignes = " << valeurCourrante << std::endl;
				break;


				// NBColonnes :
			case 2:
				//std::cout << "switch case 2" << std::endl;
				CMatrice<double>::uiMATNbreColonnes = atoi((const char*)valeurCourrante);
				std::cout << "Nb Colonnes = " << valeurCourrante << std::endl;
				break;


				// Matrice :
			case 3:
			{
				//std::cout << "switch case 3" << std::endl;
				
				// Initialisation tableau matrice : 
				CMatrice<double>::MATTableau = (double**)malloc(CMatrice<double>::uiMATNbreLignes * sizeof(double*));
				for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < CMatrice<double>::uiMATNbreLignes; uiBoucleAlloc++) {
					CMatrice<double>::MATTableau[uiBoucleAlloc] = (double*)malloc(CMatrice<double>::uiMATNbreColonnes * sizeof(double));
				}
				unsigned int lBoucleInitMat = 0;
				unsigned int cBoucleInitMat = 0;

				// Retour à la ligne (début des valeurs) :
				ifsFichier >> cLigne;

				std::cout << "Affectation des valeurs :" << std::endl;

				//std::cout << "max : [" << CMatrice<double>::MATLireNbreLignes()-1 << ";" << CMatrice<double>::MATLireNbreColonnes()-1 << "]\n";

				while (lBoucleInitMat < CMatrice<double>::MATLireNbreLignes()) {
					cBoucleInitMat = 0;
					while (cBoucleInitMat < CMatrice<double>::MATLireNbreColonnes()) {
						CMatrice<double>::MATModifierVal(atof(cLigne), lBoucleInitMat, cBoucleInitMat);
						
						std::cout << "[" << lBoucleInitMat << ";" << cBoucleInitMat << "] = ";
						std::cout << cLigne << std::endl;

						// Passage à la valeur suivante :
						ifsFichier >> cLigne;
						cBoucleInitMat++;
					}

					lBoucleInitMat++;
				}
				break;
			}

			default:
				std::cout << "switch défaut, erreur rencontrée" << std::endl;
				break;
			}



			// Passage au champs suivant :
			iNumChamps++;
			ifsFichier >> cLigne;
		}
	}
	std::cout << "Fin constructeur par fichier. \n";
}

template<class Type>
CMatriceOperation<Type>::~CMatriceOperation()
{
}

/**
Operation + entre 2 matrices

Entrée : Matrice de type Type
Nécessite : Les deux matrices doivent être de même taille
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale à la somme des cases[i][j] des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator+(CMatriceOperation<Type> MAOArg)
{
	try {
		
		if (CMatrice<Type>::MATLireNbreColonnes() != MAOArg.MATLireNbreColonnes() || CMatrice<Type>::MATLireNbreLignes() != MAOArg.MATLireNbreLignes()) {
			CException *EXCerreur = new CException((char*)ERROR_TAILLE_MATRICE_DIFF);
			//EXCerreur->EXCModifierErreur((char*)ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}
		/*else {
			
		}*/
		
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}

	unsigned int uiNbCol = CMatrice<Type>::MATLireNbreColonnes(), uiNbRow = CMatrice<Type>::MATLireNbreLignes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);

	for (unsigned int uiBoucleRow = 0; uiBoucleRow < uiNbRow; uiBoucleRow++) {
		for (unsigned int uiBoucleCol = 0; uiBoucleCol < uiNbCol; uiBoucleCol++) {
			MAOresult->CMatrice<Type>::MATModifierVal(CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) + MAOArg.CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol), uiBoucleRow, uiBoucleCol);
		}
	}
	return *MAOresult;
}

/**
Operation - entre 2 matrices

Entrée : Matrice de type Type
Nécessite : Les deux matrices doivent être de même taille
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale à la différences des cases[i][j] des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator-(CMatriceOperation<Type> MAOArg)
{
	try {
		if (this->MATLireNbreColonnes() != MAOArg->MATLireNbreColonnes() || this->MATLireNbreLignes() != MAOArg->MATLireNbreLignes()) {
			CException *EXCerreur;// = new CException(ERROR_TAILLE_MATRICE_DIFF);
			EXCerreur->EXCModifierErreur(ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}
		else {
			unsigned int uiNbCol = this->MATLireNbreColonnes();
			unsigned int uiNbRow = this->MATLireNbreLignes();
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);

			for (int iBoucleRow = 0; iBoucleRow < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < uiNbCol; iBoucleCol++) {
					MAOresult->MATModifierVal(this->MATLireVal(iBoucleRow, iBoucleCol) - MAOArg->MATLireVal(iBoucleRow, iBoucleCol), iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}
}

/**
Operation * entre 2 matrices

Entrée : Matrice de type Type
Nécessite : La hauteur de la matrice appelante doit être égale à la longueur del'autre
Sortie : une matrice de type Type qui est le produit des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(CMatriceOperation<Type> MAOArg)
{
	try {
		if (MAOArg->MATLireNbreLignes() != this->MATLireNbreColonnes()) {
			CException *EXCerreur;// = new CException(ERROR_TAILLE_MATRICE_IMCOMPATIBLE);
			EXCerreur->EXCModifierErreur(ERROR_TAILLE_MATRICE_IMCOMPATIBLE);
			throw(*EXCerreur);
		}
		else {
			unsigned int uiNbRow = this->MATLireNbreLignes();
			unsigned int uiNbCol = MAOArg->MATLireNbreColonnes(); // hauteur MatA et longueur MatB de MatA*MatB
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);
			Type tResultatCase;

			for (int iBoucleRow = 0; iBoucleRow < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < uiNbCol; iBoucleCol++) {
					for (int iBoucle = 0; iBoucle < this->MATLireNbreColonnes(); iBoucle++) {
						if (iBoucle == 0) {
							tResultatCase = this->MATLireVal(iBoucleRow, 0) * MAOArg->MATLireVal(0, iBoucleCol);
						}
						else {
							tResultatCase += this->MATLireVal(iBoucleRow, iBoucle) * MAOArg->MATLireVal(iBoucle, iBoucleCol);
						}	
					}
					MAOresult->MATModifierVal(tResultatCase, iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}
}

/**
Operation * entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au produit de varArg et de la cases[i][j] de la matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(Type varArg)
{
	CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = this->MATLireNbreLignes();
	unsigned int uiNbColonnes = this->MATLireNbreColonnes();
	MAOresult.MATModifierNbreColonnes(uiNbColonnes);
	MAOresult.MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int iBoucleColonne;
	for (iBoucleColonne = 0; iBoucleColonne < uiNbColonnes; iBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(this->MATLireVal(iBoucleColonne, iBoucleLigne)*varArg, iBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

/**
Operation / entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au quotient de varArg et de la cases[i][j] de la matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator/(Type varArg)
{
	CMatriceOperation<Type> *MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = this->MATLireNbreLignes();
	unsigned int uiNbColonnes = this->MATLireNbreColonnes();
	MAOresult->MATModifierNbreColonnes(uiNbColonnes);
	MAOresult->MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int iBoucleColonne;
	for (iBoucleColonne = 0; iBoucleColonne < uiNbColonnes; iBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult->MATModifierVal(this->MATLireVal(iBoucleColonne, iBoucleLigne)/varArg, iBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

