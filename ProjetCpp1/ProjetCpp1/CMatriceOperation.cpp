#include "CMatriceOperation.h"
#include "CMatrice.h"

template<class Type>
CMatriceOperation<Type>::CMatriceOperation()
{
}

template<class Type>
CMatriceOperation<Type>::CMatriceOperation(CMatriceOperation * MAOcopie)
{
}

template<class Type>
CMatriceOperation<Type>::~CMatriceOperation()
{
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator+(CMatriceOperation<Type> MAOArg)
{
	if (this->MATLireNbreColonnes() != MAOArg->MATLireNbreColonnes() || this->MATLireNbreLignes() != MAOArg->MATLireNbreLignes()) {
		std::cout << "Erreur : Les matrices ne sont pas de même dimensions.\n";
	}
	else {
		unsigned int nbCol = this->MATLireNbreColonnes(), nbRow = this->MATLireNbreLignes();
		CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(nbCol, nbRow);

		for (int i = 0; i < nbRow; i++) {
			for (int j = 0; j < nbCol; j++) {
				MAOresult->MATModifierVal(this->MATLireVal(i,j) + MAOArg->MATLireVal(i,j), i, j);
			}
		}
		return MAOresult;
	}
	/* Avec Exceptions :
	try {
		
		CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(this->MATLireNbreColonnes(), this->MATLireNbreLignes());
	}
	catch () {

	}
	*/
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator-(CMatriceOperation<Type> MAOArg)
{
	if (this->MATLireNbreColonnes() != MAOArg->MATLireNbreColonnes() || this->MATLireNbreLignes() != MAOArg->MATLireNbreLignes()) {
		std::cout << "Erreur : Les matrices ne sont pas de même dimensions.\n";
	}
	else {
		unsigned int nbCol = this->MATLireNbreColonnes(), nbRow = this->MATLireNbreLignes();
		CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(nbCol, nbRow);

		for (int i = 0; i < nbRow; i++) {
			for (int j = 0; j < nbCol; j++) {
				MAOresult->MATModifierVal(this->MATLireVal(i, j) - MAOArg->MATLireVal(i, j), i, j);
			}
		}
		return MAOresult;
	}
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(CMatriceOperation<Type> MAOArg)
{
	if (this->MATLireNbreLignes() != MAOArg->MATLireNbreColonnes()) {
		std::cout << "Erreur : Les matrices ne peuvent pas être multipliées entre elles.\n";
	}
	else {
		unsigned int nbCol = MAOarg->MATLireNbreColonnes(), nbRow = this->MATLireNbreLignes(); // hauteur MatA et longueur MatB de MatA*MatB
		CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(nbCol, nbRow);
		Type calcul;

		for (int i = 0; i < nbRow; i++) {
			for (int j = 0; j < nbCol; j++) {
				calcul = 0;
				for (int k=0; k<this->MATLireNbreLignes())
				MAOresult->MATModifierVal(this->MATLireVal(i, j) + MAOArg->MATLireVal(i, j), i, j);
			}
		}
		return MAOresult;
	}
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

