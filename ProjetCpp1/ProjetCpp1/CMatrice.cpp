#include "CMatrice.h"
#include <stdio.h>

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNE_BASE 2

CMatrice<class Type>::CMatrice<Type>() {
	//TODO
	// 1 - initialiser le nombres de lignes et de colonnes à NBRE_LIGNES_BASE et NBRE_COLONNE_BASE
	// 2 - initialiser MATTableau
}

CMatrice<Type>::CMatrice<Type>(CMatrice<Type> *MATarg) {

}

CMatrice<Type>::~CMatrice<Type>() {

}

//Fonction pour obtenir la transposé d'une matrice quelconque
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
void CMatrice<Type>::MATAfficher() {
	unsigned int iBoucle, jBoucle;
	for (iBoucle = 0; iBoucle < uiMATNbreColonnes; iBoucle++) {
		for (jBoucle = 0; jBoucle < uiMATNbreLignes; jBoucle++) {
			printf("%d ", MATLireVal(iBoucle, jBoucle));
		}
		printf("\n");
	}
}