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
	unsigned int uiNbLignes = this->MATLireNbreLignes();
	unsigned int uiNbColonnes = this->MATLireNbreColonnes();
	MAOresult.MATModifierNbreColonnes(uiNbColonnes);
	MAOresult.MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonnes; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(this->MATLireVal(jBoucleColonne, iBoucleLigne)*varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator/(Type varArg)
{
	CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = this->MATLireNbreLignes();
	unsigned int uiNbColonnes = this->MATLireNbreColonnes();
	MAOresult.MATModifierNbreColonnes(uiNbColonnes);
	MAOresult.MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonnes; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(this->MATLireVal(jBoucleColonne, iBoucleLigne)/varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

