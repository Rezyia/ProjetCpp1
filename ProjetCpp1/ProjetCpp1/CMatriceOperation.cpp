#include "CMatriceOperation.h"
#include "CMatrice.h"

#define ERROR_TAILLE_MATRICE_DIFF "Les matrices ne sont pas de même dimensions"
#define ERROR_TAILLE_MATRICE_IMCOMPATIBLE "Les matrices ne peuvent pas être multipliées entre elles"

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
	try {
		
		if (this->MATLireNbreColonnes() != MAOArg->MATLireNbreColonnes() || this->MATLireNbreLignes() != MAOArg->MATLireNbreLignes()) {
			CException *EXCerreur;// = new CException(ERROR_TAILLE_MATRICE_DIFF);
			EXCerreur->ModifierErreur(ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}
		else {
			unsigned int uiNbCol = this->MATLireNbreColonnes(), uiNbRow = this->MATLireNbreLignes();
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);

			for (int iBoucleRow = 0; i < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; j < uiNbCol; iBoucleCol++) {
					MAOresult->MATModifierVal(this->MATLireVal(iBoucleRow, iBoucleCol) + MAOArg->MATLireVal(iBoucleRow, iBoucleCol), iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator-(CMatriceOperation<Type> MAOArg)
{
	try {
		if (this->MATLireNbreColonnes() != MAOArg->MATLireNbreColonnes() || this->MATLireNbreLignes() != MAOArg->MATLireNbreLignes()) {
			CException *EXCerreur;// = new CException(ERROR_TAILLE_MATRICE_DIFF);
			EXCerreur->EXCModifierErreur(ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}
		else {
			unsigned int uiNbCol = this->MATLireNbreColonnes(), uiNbRow = this->MATLireNbreLignes();
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);

			for (int iBoucleRow = 0; i < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; j < uiNbCol; iBoucleCol++) {
					MAOresult->MATModifierVal(this->MATLireVal(iBoucleRow, iBoucleCol) - MAOArg->MATLireVal(iBoucleRow, iBoucleCol), iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n"
	}
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator*(CMatriceOperation<Type> MAOArg)
{
	try {
		if (MAOArg->MATLireNbreLignes() != this->MATLireNbreColonnes()) {
			CException *EXCerreur;// = new CException(ERROR_TAILLE_MATRICE_IMCOMPATIBLE);
			EXCerreur->EXCModifierErreur(ERROR_TAILLE_MATRICE_IMCOMPATIBLE);
			throw(*EXCerreur);
		}
		else {
			unsigned int nbRow = this->MATLireNbreLignes(), nbCol = MAOArg->MATLireNbreColonnes(); // hauteur MatA et longueur MatB de MatA*MatB
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);
			Type tResultatCase;

			for (int iBoucleRow = 0; iBoucleRow < nbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < nbCol; iBoucleCol++) {
					for (int iBoucle = 0; iBoucle < this->MATLireNbreColonnes(); iBoucle++) {
						if (k == 0) {
							tResultatCase = this->MATLireVal(iBoucleRow, 0) * MAOArg->MATLireVal(0, iBoucleCol);
						}
						else {
							tResultatCase += this->MATLireVal(iBoucleRow, iBoucle) * MAOArg->MATLireVal(iBoucle, iBoucleCol);
						}	
					}
					MAOresult->MATModifierVal(tResultatCase, iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n"
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
	int iBoucleColonne;
	for (iBoucleColonne = 0; iBoucleColonne < uiNbColonnes; iBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult.MATModifierVal(this->MATLireVal(iBoucleColonne, iBoucleLigne)*varArg, iBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator/(Type varArg)
{
	CMatriceOperation<Type> *MAOresult = new CMatriceOperation<Type>();
	unsigned int uiNbLignes = this->MATLireNbreLignes();
	unsigned int uiNbColonnes = this->MATLireNbreColonnes();
	MAOresult->MATModifierNbreColonnes(uiNbColonnes);
	MAOresult->MATModifierNbreLignes(uiNbLignes);

	int iBoucleLigne;
	int iBoucleColonne;
	for (iBoucleColonne = 0; iBoucleColonne < uiNbColonnes; iBoucleColonne++) {
		for (iBoucleLigne = 0; iBoucleLigne < uiNbLignes; iBoucleLigne++) {
			MAOresult->MATModifierVal(this->MATLireVal(iBoucleColonne, iBoucleLigne)/varArg, iBoucleColonne, iBoucleLigne);
		}
	}
	return MAOresult;
}

