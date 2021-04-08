#include "CMatriceOperation.h"

template<class Type>
CMatriceOperation<Type>::CMatriceOperation()
{
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator+(CMatriceOperation<Type> MAOArg)
{
	return CMatriceOperation<Type>();
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator-(CMatriceOperation<Type> MAOArg)
{
	return CMatriceOperation<Type>();
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(CMatriceOperation<Type> MAOArg)
{
	return CMatriceOperation<Type>();
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(Type varArg)
{
	CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = MATLireNbreLignes();
	unsigned int uiNbColonnes = MATLireNbreColonnes();
	MAOresult.MATModifierNbreColonnes(uiNbColonnes);
	MAOresult.MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonnes; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(MATLireVal(jBoucleColonne, iBoucleLigne)*varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator/(Type varArg)
{
	CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = MATLireNbreLignes();
	unsigned int uiNbColonnes = MATLireNbreColonnes();
	MAOresult.MATModifierNbreColonne(uiNbColonnes);
	MAOresult.MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonnes; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(MATLireVal(jBoucleColonne, iBoucleLigne)/varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

