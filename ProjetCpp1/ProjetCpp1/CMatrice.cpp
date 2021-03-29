#include "CMatrice.h"
#include <stdio.h>

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNE_BASE 2

template <class Type>
CMatrice<Type>::CMatrice() {
	//TODO
	// 1 - initialiser le nombres de lignes et de colonnes � NBRE_LIGNES_BASE et NBRE_COLONNE_BASE
	// 2 - initialiser MATTableau
}

template <class Type>
CMatrice<Type>::CMatrice(CMatrice<Type> *MATarg) {

}

template <class Type>
CMatrice<Type>::~CMatrice() {

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