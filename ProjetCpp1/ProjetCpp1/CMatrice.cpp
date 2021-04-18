#include <fstream>
#include <cstring>
#include <stdio.h>
#include "CMatrice.h"

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNES_BASE 2

#define NBRE_MAX_CHAMPS_FICHIER 32
#define NBRE_MAX_LIGNES_FICHIER 255


/**
Constructeur par défaut :

Entrée : Rien
Nécessite : Rien
Sortie : une matrice de type Type de dimensions 2x2 avec des valeur non-initialisées :
**/
template <class Type>
CMatrice<Type>::CMatrice() { 
	//std::cout << "Constructeur par défaut :\n";
	uiMATNbreColonnes = NBRE_COLONNES_BASE;
	uiMATNbreLignes = NBRE_LIGNES_BASE;

	MATTableau = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}
}

// Constructeur de recopie
template <class Type>
CMatrice<Type>::CMatrice(CMatrice<Type>& MATarg) {
	//std::cout << "Constructeur de recopie :\n";

	// Affectation des dimensions :
	uiMATNbreColonnes = MATarg.MATLireNbreColonnes();
	uiMATNbreLignes = MATarg.MATLireNbreLignes();

	// Allocation de la matrice :
	MATTableau = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc< uiMATNbreLignes; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}

	// Recopie des valeurs :
	for (unsigned int iBoucleRecopie = 0; iBoucleRecopie < uiMATNbreLignes; iBoucleRecopie++) {
		for (unsigned int jBoucleRecopie = 0; jBoucleRecopie < uiMATNbreColonnes; jBoucleRecopie++) {
			MATTableau[iBoucleRecopie][jBoucleRecopie] = MATarg.MATLireVal(iBoucleRecopie, jBoucleRecopie);
		}
	}
}

// Constructeur avec dimensions
template <class Type>
CMatrice<Type>::CMatrice(unsigned int uiNbCol, unsigned int uiNbRow) { // test constructeur custom sizes
	uiMATNbreColonnes = uiNbCol;
	uiMATNbreLignes = uiNbRow;
	MATTableau = (Type**)malloc(uiNbCol * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiNbCol; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiNbRow * sizeof(Type));
	}
}

// Constructeur depuis un fichier
template<class Type>
CMatrice<Type>::CMatrice(char* pcNomFichier)
{
	// Ouverture du fichier :
	std::ifstream ifsFichier(pcNomFichier);
	if (ifsFichier == NULL) {
		std::cout << "Le fichier n'a pas pu être ouvert\n";
	}
	// Si fichier ouvert correctement :
	else {
		int iNumChamps = 0;
		char cLigne[255];
		ifsFichier >> cLigne;

		int indiceCourrant = 0;
		int indiceValeurCourrante = 0;
		char* valeurCourrante[NBRE_MAX_LIGNES_FICHIER - NBRE_MAX_CHAMPS_FICHIER];


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


		// On suppose que le format est respecté
		while (iNumChamps < 4) {
			//Pour chaque ligne du fichier :
			indiceCourrant = 0;
			indiceValeurCourrante = 0;

			// On passe jusqu'aux '=' :
			while (cLigne[indiceCourrant] != '=' && indiceCourrant < NBRE_MAX_CHAMPS_FICHIER) {
				if (cLigne[indiceCourrant] != '\0' && cLigne[indiceCourrant] != '\n') // 
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

			switch (iNumChamps) {
			// TypeMatrice :
			case 0:
				// Ce projet gère UNIQUEMENT le cas où TypeMatrice vaut double, donc :
				if (strcmp(valeurCourrante[0], "double") == 0) {
					this = new CMatrice<double>();
				}
				else {
					std::cout << "Le type de matrice n'a pas été accepté (seul le type double est accepté)\n";
				}
				break;

			// NBLignes :
			case 1:
				uiMATNbreLignes = atoi(valeurCourrante[0]);
				break;

			// NBColonnes :
			case 2:
				uiMATNbreColonnes = atoi(valeurCourrante[0]);
				break;

			// Matrice :
			case 3:
				MATTableau = (double**)malloc(uiMATNbreLignes * sizeof(double*));
				for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
					MATTableau[uiBoucleAlloc] = (double*)malloc(uiMATNbreColonnes * sizeof(double));
				}
				int lBoucleInitMat = 0;
				int cBoucleInitMat = 0;

				// Retour à la ligne (début des valeurs) :
				ifsFichier >> cLigne;

				while (lBoucleInitMat < uiMATNbreLignes) {
					while (cBoucleInitMat < uiMATNbreColonnes) {
						MATModifierVal(atoi(cLigne), cBoucleInitMat, lBoucleInitMat);
						// Passage à la valeur suivante :
						ifsFichier >> cLigne;
						if (strcmp(cLigne, "]") == 0) {
							std::cout << "Erreur: Fin de matrice rencontrée trop tot";
						}
						lBoucleInitMat++;
						cBoucleInitMat++;
					}
				}
				break;
			}

			// Passage au champs suivant :
			iNumChamps++;
			ifsFichier >> cLigne;
		}
	}
}


// Destructeur
template <class Type>
CMatrice<Type>::~CMatrice() {
	free(MATTableau);
}



//Fonction pour obtenir la transpos� d'une matrice quelconque
template <class Type>
CMatrice<Type> CMatrice<Type>::MATTransposer() {
	CMatrice<Type> *MATtmp = new CMatrice<Type>(MATLireNbreColonnes(), MATLireNbreLignes());
	//MATtmp->MATModifierNbreColonnes(MATLireNbreLignes());
	//MATtmp->MATModifierNbreLignes(MATLireNbreColonnes());

	unsigned int uiBoucleCol, uiBoucleRow;

	for (uiBoucleRow = 0; uiBoucleRow < uiMATNbreLignes; uiBoucleRow++) {
		for (uiBoucleCol = 0; uiBoucleCol < uiMATNbreColonnes; uiBoucleCol++) {
			MATtmp->MATModifierVal(MATLireVal(uiBoucleRow, uiBoucleCol), uiBoucleRow, uiBoucleCol);
		}
	}
	return *MATtmp;
}

//Fonction pour afficher une matrice
template <class Type>
void CMatrice<Type>::MATAfficher() 
{
	unsigned int uiBoucleCol, uiBoucleRow;
	for (uiBoucleRow = 0; uiBoucleRow < uiMATNbreLignes; uiBoucleRow++) {
		for (uiBoucleCol = 0; uiBoucleCol < uiMATNbreColonnes; uiBoucleCol++) {
			std::cout << MATLireVal(uiBoucleRow, uiBoucleCol) << "\t";
		}
		std::cout << "\n";
	}
}


// Fonction pour modifier le nombre de lignes de la matrice
template <class Type>
void CMatrice<Type>::MATModifierNbreLignes(unsigned int uiArg) {
	//Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg);
	
	// Allocation nouvelle matrice
	Type** newMat = (Type**)malloc(uiArg * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiArg; uiBoucleAlloc++) {
		newMat[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}

	// Initialisation nouvelle matrice par des 0 :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = MATTableau[uiInitRow][uiInitCol];
		}
	}

	uiMATNbreLignes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}


// Fonction pour modifier le nombre de colonnes de la matrice
template <class Type>
void CMatrice<Type>::MATModifierNbreColonnes(unsigned int uiArg) {
	//Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg);
	
	// Allocation nouvelle matrice
	Type** newMat = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
		newMat[uiBoucleAlloc] = (Type*)malloc(uiArg * sizeof(Type));
	}

	// Initialisation nouvelle matrice par des 0 :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = MATTableau[uiInitRow][uiInitCol];
		}
	}

	uiMATNbreColonnes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}
