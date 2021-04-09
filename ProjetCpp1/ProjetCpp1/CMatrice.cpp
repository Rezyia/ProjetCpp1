#include "CMatrice.h"
#include <stdio.h>

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNES_BASE 2

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
CMatrice<Type>::CMatrice(char * pcNomFichier)
{
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
