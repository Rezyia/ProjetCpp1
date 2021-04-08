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
	unsigned int uiNbLigne = MATLireNbreLignes();
	unsigned int uiNbColonne = MATLireNbreColonne();
	MAOresult.MATModifierNbreColonne(uiNbColonne);
	MAOresult.MATModifierNbreLignes(uiNbLigne);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonne; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLigne; iBoucleLigne++) {
			MAOresult.MATModifierVal(MATLireVal(jBoucleColonne, iBoucleLigne)*varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator/(Type varArg)
{
	CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLigne = MATLireNbreLignes();
	unsigned int uiNbColonne = MATLireNbreColonne();
	MAOresult.MATModifierNbreColonne(uiNbColonne);
	MAOresult.MATModifierNbreLignes(uiNbLigne);

	int iBoucleLigne;
	int jBoucleColonne;
	for (jBoucleColonne = 0; jBoucleColonne < uiNbColonne; jBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLigne; iBoucleLigne++) {
			MAOresult.MATModifierVal(MATLireVal(jBoucleColonne, iBoucleLigne)/varArg, jBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

