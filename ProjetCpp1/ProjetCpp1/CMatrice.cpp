#include "CMatrice.h"
#include <stdio.h>

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNE_BASE 2

template <class Type>
CMatrice<Type>::CMatrice() {
	uiMATNbreColonnes = 2;
	uiMATNbreLignes = 2;
	MATTableau = (Type*)malloc(sizeof(Type) * 2 * 2);
}

template <class Type>
CMatrice<Type>::CMatrice(CMatrice<Type> *MATarg) {
	
}

template <class Type>
CMatrice<Type>::CMatrice(unsigned int nbCol, unsigned int nbRow) { // test constructeur custom sizes
	uiMATNbreColonnes = nbCol;
	uiMATNbreLignes = nbRow;
	MATTableau = (Type*)malloc(sizeof(Type) * nbCol * nbRow);
}

template <class Type>
CMatrice<Type>::~CMatrice() {
	free(MATTableau);
}

//Fonction pour obtenir la transpos� d'une matrice quelconque
template <class Type>
CMatrice<Type> CMatrice<Type>::MATTransposer() {
	CMatrice<Type> *MATtmp = new CMatrice<Type>();
	MATtmp->MATModifierNbreColonne(MATLireNbreLignes());
	MATtmp->MATModifierNbreLignes(MATLireNbreColonne());
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
void CMatrice<Type>::MATAfficher() {
	unsigned int iBoucle, jBoucle;
	for (iBoucle = 0; iBoucle < uiMATNbreColonnes; iBoucle++) {
		for (jBoucle = 0; jBoucle < uiMATNbreLignes; jBoucle++) {
			std::cout << MATLireVal(iBoucle, jBoucle) << " ";
		}
		std::cout << "\n";
	}
}