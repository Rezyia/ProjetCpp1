#include <fstream>
#include <cstring>
#include <stdio.h>
#include "CMatrice.h"

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNES_BASE 2

#define NBRE_MAX_CHAMPS_FICHIER 32
#define NBRE_MAX_LIGNES_FICHIER 255

// Constructeur par defaut
template <class Type>
CMatrice<Type>::CMatrice() { 
	uiMATNbreColonnes = NBRE_COLONNES_BASE;
	uiMATNbreLignes = NBRE_LIGNES_BASE;
	MATTableau = (Type*)malloc(sizeof(Type) * NBRE_COLONNES_BASE * NBRE_LIGNES_BASE);
}

// Constructeur de recopie
template <class Type>
CMatrice<Type>::CMatrice(CMatrice<Type> *MATarg) {
	// WIP / To change :
	uiMATNbreColonnes = NBRE_COLONNES_BASE;
	uiMATNbreLignes = NBRE_LIGNES_BASE;
	MATTableau = (Type*)malloc(sizeof(Type) * NBRE_COLONNES_BASE * NBRE_LIGNES_BASE);
}

// Constructeur avec dimensions
template <class Type>
CMatrice<Type>::CMatrice(unsigned int nbCol, unsigned int nbRow) { // test constructeur custom sizes
	uiMATNbreColonnes = nbCol;
	uiMATNbreLignes = nbRow;
	MATTableau = (Type*)malloc(sizeof(Type) * nbCol * nbRow);
}

// Constructeur depuis un fichier
template<class Type>
CMatrice<Type>::CMatrice(char* pcNomFichier)
{
	// Ouverture du fichier :
	ifstream ifsFichier(pcNomFichier);
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
				if (strcmp(valeurCourrante, "double") == 0) {
					this = new CMatrice<double>();
				}
				else {
					std::cout << "Le type de matrice n'a pas été accepté (seul le type double est accepté)\n";
				}
				break;

			// NBLignes :
			case 1:
				uiMATNbreLignes = atoi(valeurCourrante);
				break;

			// NBColonnes :
			case 2:
				uiMATNbreColonnes = atoi(valeurCourrante);
				break;

			// Matrice :
			case 3:
				MATTableau = malloc(sizeof(double) * uiMATNbreColonnes * uiMATNbreLignes);
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
	CMatrice<Type> *MATtmp = new CMatrice<Type>();
	MATtmp->MATModifierNbreColonnes(MATLireNbreLignes());
	MATtmp->MATModifierNbreLignes(MATLireNbreColonnes());
	unsigned int iBoucle, jBoucle;
	for (iBoucle = 0; iBoucle < uiMATNbreColonnes; iBoucle++) {
		for (jBoucle = 0; jBoucle < uiMATNbreLignes; jBoucle++) {
			//MATtmp->MATTableau[jBoucle][iBoucle] = MATTableau[iBoucle][jBoucle];
			MATtmp->MATModifierVal(MATLireVal(iBoucle, jBoucle), jBoucle, iBoucle);
		}
	}
	return *MATtmp;
}

//Fonction pour afficher une matrice
template <class Type>
void CMatrice<Type>::MATAfficher() 
{
	unsigned int iBoucle, jBoucle;
	for (iBoucle = 0; iBoucle < uiMATNbreColonnes; iBoucle++) {
		for (jBoucle = 0; jBoucle < uiMATNbreLignes; jBoucle++) {
			std::cout << MATLireVal(iBoucle, jBoucle) << " ";
		}
		std::cout << "\n";
	}
}


// Fonction pour modifier le nombre de lignes de la matrice
template <class Type>
void CMatrice<Type>::MATModifierNbreLignes(unsigned int uiArg) {
	Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg); // Allocation nouvelle matrice

	// Initialisation nouvelle matrice par des 0 :
	for (int i = 0; i < uiArg; i++) {
		for (int j = 0; j < uiMATNbreColonnes; j++) {
			newMat[i][j] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (int i = 0; i < std::min(uiArg, uiMATNbreLignes); i++) {
		for (int j = 0; j < uiMATNbreColonnes; j++) {
			newMat[i][j] = MATTableau[i][j];
		}
	}

	uiMATNbreLignes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}

// Fonction pour modifier le nombre de colonnes de la matrice
template <class Type>
void CMatrice<Type>::MATModifierNbreColonnes(unsigned int uiArg) {
	Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg); // Allocation nouvelle matrice

	// Initialisation nouvelle matrice par des 0 :
	for (int i = 0; i < uiArg; i++) {
		for (int j = 0; j < uiMATNbreColonnes; j++) {
			newMat[i][j] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (int i = 0; i < uiMATNbreLignes; i++) {
		for (int j = 0; j < std::min(uiArg, uiMATNbreColonnes); j++) {
			newMat[i][j] = MATTableau[i][j];
		}
	}

	uiMATNbreColonnes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}
