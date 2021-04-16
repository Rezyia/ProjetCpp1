#include "CMatriceOperation.h"
#include "CMatrice.h"
#include "CException.h"

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

/**
Operation + entre 2 matrices

Entrée : Matrice de type Type
Nécessite : Les deux matrices doivent être de même taille
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale à la somme des cases[i][j] des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type> CMatriceOperation<Type>::operator+(CMatriceOperation<Type> MAOArg)
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

			for (int iBoucleRow = 0; iBoucleRow < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < uiNbCol; iBoucleCol++) {
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

/**
Operation - entre 2 matrices

Entrée : Matrice de type Type
Nécessite : Les deux matrices doivent être de même taille
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale à la différences des cases[i][j] des 2 autres matrices
**/
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
			unsigned int uiNbCol = this->MATLireNbreColonnes();
			unsigned int uiNbRow = this->MATLireNbreLignes();
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);

			for (int iBoucleRow = 0; iBoucleRow < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < uiNbCol; iBoucleCol++) {
					MAOresult->MATModifierVal(this->MATLireVal(iBoucleRow, iBoucleCol) - MAOArg->MATLireVal(iBoucleRow, iBoucleCol), iBoucleRow, iBoucleCol);
				}
			}
			return MAOresult;
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}
}

/**
Operation * entre 2 matrices

Entrée : Matrice de type Type
Nécessite : La hauteur de la matrice appelante doit être égale à la longueur del'autre
Sortie : une matrice de type Type qui est le produit des 2 autres matrices
**/
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
			unsigned int uiNbRow = this->MATLireNbreLignes();
			unsigned int uiNbCol = MAOArg->MATLireNbreColonnes(); // hauteur MatA et longueur MatB de MatA*MatB
			CMatriceOperation<Type> MAOresult = new CMatriceOperation<Type>(uiNbCol, uiNbRow);
			Type tResultatCase;

			for (int iBoucleRow = 0; iBoucleRow < uiNbRow; iBoucleRow++) {
				for (int iBoucleCol = 0; iBoucleCol < uiNbCol; iBoucleCol++) {
					for (int iBoucle = 0; iBoucle < this->MATLireNbreColonnes(); iBoucle++) {
						if (iBoucle == 0) {
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
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}
}

/**
Operation * entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au produit de varArg et de la cases[i][j] de la matrices
**/
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

/**
Operation / entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au quotient de varArg et de la cases[i][j] de la matrices
**/
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

