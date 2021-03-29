#include "CMatrice.h"
#include <stdio.h>

CMatrice<class Type>::CMatrice<Type>() {

}

CMatrice<Type>::CMatrice<Type>(CMatrice<Type> *MATarg) {

}

CMatrice<Type>::~CMatrice<Type>() {

}

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

void CMatrice<Type>::MATAfficher() {
	unsigned int iBoucle, jBoucle;
	for (iBoucle = 0; iBoucle < uiMATNbreColonnes; iBoucle++) {
		for (jBoucle = 0; jBoucle < uiMATNbreLignes; jBoucle++) {
			printf("%d ", MATTableau[iBoucle][jBoucle]);
		}
		printf("\n");
	}
}