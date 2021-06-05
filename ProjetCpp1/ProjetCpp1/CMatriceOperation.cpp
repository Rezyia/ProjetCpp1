#include "CMatriceOperation.h"
#include "CMatrice.h"
#include "CException.h"

#define ERROR_TAILLE_MATRICE_DIFF "Les matrices ne sont pas de même dimensions"
#define ERROR_TAILLE_MATRICE_IMCOMPATIBLE "Les matrices ne peuvent pas être multipliées entre elles"

#define ERROR_NON_TRIDIAGONALE "La matrice n'est pas tridiagonale"


/**********************************************************************************

							Constructeur Par défaut

Entrée :	Rien
Nécessite :	Rien
Sortie :	Une matrice de type Type de dimensions NBRE_LIGNES_BASE * NBRE_COLONNES_BASE
			(voir CMatrice.cpp ou CMatrice.h) avec des valeurs non-initialisées
**********************************************************************************/
template<class Type>
CMatriceOperation<Type>::CMatriceOperation()
{
}


/**********************************************************************************

							Constructeur de recopie

Entrée :	Adresse d'une autre CMatriceOperation
Nécessite :	Rien
Sortie :	Une matrice de type Type de même dimensions que celle passée en
			paramètre et de même valeurs de matrice.
**********************************************************************************/
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(CMatriceOperation& MATarg)
{
	// Affectation des dimensions :
	CMatrice<Type>::uiMATNbreColonnes = MATarg.MATLireNbreColonnes();
	CMatrice<Type>::uiMATNbreLignes = MATarg.MATLireNbreLignes();

	// Allocation de la matrice :
	CMatrice<Type>::MATTableau = (Type**)malloc(CMatrice<Type>::uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < CMatrice<Type>::uiMATNbreLignes; uiBoucleAlloc++) {
		CMatrice<Type>::MATTableau[uiBoucleAlloc] = (Type*)malloc(CMatrice<Type>::uiMATNbreColonnes * sizeof(Type));
	}

	// Recopie des valeurs :
	for (unsigned int iBoucleRecopie = 0; iBoucleRecopie < CMatrice<Type>::uiMATNbreLignes; iBoucleRecopie++) {
		for (unsigned int jBoucleRecopie = 0; jBoucleRecopie < CMatrice<Type>::uiMATNbreColonnes; jBoucleRecopie++) {
			CMatrice<Type>::MATTableau[iBoucleRecopie][jBoucleRecopie] = MATarg.MATLireVal(iBoucleRecopie, jBoucleRecopie);
		}
	}
}


/**********************************************************************************

					Constructeur avec nombre de lignes et colonnes :

Entrée :	Nombre de lignes (uiNbRow) et nombre de colonnes (uiNbCol)
Nécessite :	Rien
Sortie :	Une matrice de type Type de dimensions uiNbRow * uiNbCol.
**********************************************************************************/
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(unsigned int uiNbRow, unsigned int uiNbCol)
{
	CMatrice<Type>::uiMATNbreColonnes = uiNbCol;
	CMatrice<Type>::uiMATNbreLignes = uiNbRow;
	CMatrice<Type>::MATTableau = (Type**)malloc(uiNbRow * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiNbRow; uiBoucleAlloc++) {
		CMatrice<Type>::MATTableau[uiBoucleAlloc] = (Type*)malloc(uiNbCol * sizeof(Type));
	}
}



/**********************************************************************************

							Constructeur par fichier :

Entrée :	Pointeur vers une chaîne de charactères
Nécessite :	Rien
Sortie :	Une matrice de type double avec les dimensions et valeurs inscrites
			dans le fichier.
**********************************************************************************/
template<class Type>
CMatriceOperation<Type>::CMatriceOperation(char* pcNomFichier)
{
	// Ouverture du fichier :
	std::ifstream ifsFichier(pcNomFichier);
	
	if (!ifsFichier.is_open()) {
		std::cout << "Le fichier n'a pas pu être ouvert\n";
	}
	// Si fichier ouvert correctement :
	else {
		int iNumChamps = 0;
		char cLigne[NBRE_MAX_LIGNES_FICHIER];

		// Récupère la première ligne du fichier :
		ifsFichier >> cLigne;
		

		int indiceCourrant = 0;
		int indiceValeurCourrante = 0;
		char valeurCourrante[NBRE_MAX_LIGNES_FICHIER - NBRE_MAX_CHAMPS_FICHIER];


		/* Prototype d'analyse des champs (abandonné car ordre des champs supposé comme celui des exemples :
				TypeMatrice, NBLignes, NBColonnes, Matrice)
		// Analyse du champ : caracteres jusqu'au '=' ou si il rencontre un '\0' ou un '\n'
		char* champsCourrant[NBRE_MAX_CHAMPS_FICHIER];
		int indiceChampsCourrant = 0;
		while (cLigne[indiceCourrant] != '=' && cLigne[indiceCourrant] != '\0' && cLigne[indiceCourrant] != '\n' && indiceChampsCourrant < NBRE_MAX_CHAMPS_FICHIER) {
			champsCourrant[indiceChampsCourrant] = cLigne[indiceCourrant];

			indiceChampsCourrant++;
			indiceCourrant++;
		}
		champsCourrant[indiceChampsCourrant] = '\0'; // "Fermer" champsCourrant en tant que chaîne de caractères
		indiceCourrant++; // On passe le '='
		*/


		// On suppose que le format est respecté :

		// Tant que tous les champs n'ont pas été complétés :
		while (iNumChamps < 4 && ifsFichier.good()) {
			//Pour chaque ligne du fichier :
			indiceCourrant = 0;
			indiceValeurCourrante = 0;

			// On passe jusqu'aux '=' :
			while (cLigne[indiceCourrant] != '=' && indiceCourrant < NBRE_MAX_LIGNES_FICHIER) {
				if (cLigne[indiceCourrant] == '\0' || cLigne[indiceCourrant] == '\n') // 
					std::cout << "Erreur : fin de ligne imprévue\n";
				indiceCourrant++;
			}
			indiceCourrant++; // Pour passer le '='

			// Analyse de la valeur :
			while (cLigne[indiceCourrant] != '\0' && cLigne[indiceCourrant] != '\n' && indiceCourrant < NBRE_MAX_LIGNES_FICHIER) {
				valeurCourrante[indiceValeurCourrante] = cLigne[indiceCourrant];

				indiceValeurCourrante++;
				indiceCourrant++;
			}
			valeurCourrante[indiceValeurCourrante] = '\0';


			// Affectation des attributs :
			switch (iNumChamps) {
				// TypeMatrice :
			case 0:
				//std::cout << "switch case 0" << std::endl;
				// Ce projet gère UNIQUEMENT le cas où TypeMatrice vaut double, donc :

				if (strcmp((const char*)valeurCourrante, "double") == 0) {
					//this = new CMatriceOperation<double>();
					//std::cout << "type correcte : " << valeurCourrante << std::endl;
				}
				else {
					//std::cout << "Le type de matrice n'a pas été accepté (seul le type double est accepté)\n";
				}
				break;


				// NBLignes :
			case 1:
				//std::cout << "switch case 1" << std::endl;
				CMatrice<double>::uiMATNbreLignes = atoi((const char*)valeurCourrante);
				//std::cout << "Nb Lignes = " << valeurCourrante << std::endl;
				break;


				// NBColonnes :
			case 2:
				//std::cout << "switch case 2" << std::endl;
				CMatrice<double>::uiMATNbreColonnes = atoi((const char*)valeurCourrante);
				//std::cout << "Nb Colonnes = " << valeurCourrante << std::endl;
				break;


				// Matrice :
			case 3:
			{
				//std::cout << "switch case 3" << std::endl;
				
				// Initialisation tableau matrice : 
				CMatrice<double>::MATTableau = (double**)malloc(CMatrice<double>::uiMATNbreLignes * sizeof(double*));
				for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < CMatrice<double>::uiMATNbreLignes; uiBoucleAlloc++) {
					CMatrice<double>::MATTableau[uiBoucleAlloc] = (double*)malloc(CMatrice<double>::uiMATNbreColonnes * sizeof(double));
				}
				unsigned int lBoucleInitMat = 0;
				unsigned int cBoucleInitMat = 0;

				// Retour à la ligne (début des valeurs) :
				ifsFichier >> cLigne;

				//std::cout << "Affectation des valeurs :" << std::endl;

				//std::cout << "max : [" << CMatrice<double>::MATLireNbreLignes()-1 << ";" << CMatrice<double>::MATLireNbreColonnes()-1 << "]\n";

				while (lBoucleInitMat < CMatrice<double>::MATLireNbreLignes()) {
					cBoucleInitMat = 0;
					while (cBoucleInitMat < CMatrice<double>::MATLireNbreColonnes()) {
						CMatrice<double>::MATModifierVal(atof(cLigne), lBoucleInitMat, cBoucleInitMat);
						
						//std::cout << "[" << lBoucleInitMat << ";" << cBoucleInitMat << "] = ";
						//std::cout << cLigne << std::endl;

						// Passage à la valeur suivante :
						ifsFichier >> cLigne;
						cBoucleInitMat++;
					}

					lBoucleInitMat++;
				}
				break;
			}

			default:
				std::cout << "switch défaut, erreur rencontrée" << std::endl;
				break;
			}



			// Passage au champs suivant :
			iNumChamps++;
			ifsFichier >> cLigne;
		}
	}
	//std::cout << "Fin constructeur par fichier. \n";
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
CMatriceOperation<Type>& CMatriceOperation<Type>::operator+(CMatriceOperation<Type> MAOArg)
{
	// Initialisation matrice retour :
	//std::cout << "Initialisation matrice retour :\n";
	unsigned int uiNbCol = CMatrice<Type>::MATLireNbreColonnes(), uiNbRow = CMatrice<Type>::MATLireNbreLignes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbRow, uiNbCol);

	try {
		if (CMatrice<Type>::MATLireNbreColonnes() != MAOArg.MATLireNbreColonnes() || CMatrice<Type>::MATLireNbreLignes() != MAOArg.MATLireNbreLignes()) {
			CException *EXCerreur = new CException((char*)ERROR_TAILLE_MATRICE_DIFF);
			//EXCerreur->EXCModifierErreur((char*)ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}

		//std::cout << "Calcul :\n";
		for (unsigned int uiBoucleRow = 0; uiBoucleRow < uiNbRow; uiBoucleRow++) {
			for (unsigned int uiBoucleCol = 0; uiBoucleCol < uiNbCol; uiBoucleCol++) {
				//std::cout << "[" << uiBoucleRow << ";" << uiBoucleCol << "] = " << CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) + MAOArg.CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) << std::endl;
				MAOresult->CMatrice<Type>::MATModifierVal(CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) + MAOArg.CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol), uiBoucleRow, uiBoucleCol);
			}
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}


	//std::cout << "Retour matrice :\n";
	return *MAOresult;
}

/**
Operation - entre 2 matrices

Entrée : Matrice de type Type
Nécessite : Les deux matrices doivent être de même taille
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale à la différences des cases[i][j] des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type>& CMatriceOperation<Type>::operator-(CMatriceOperation<Type> MAOArg)
{
	// Initialisation matrice retour :
	//std::cout << "Initialisation matrice retour :\n";
	unsigned int uiNbCol = CMatrice<Type>::MATLireNbreColonnes(), uiNbRow = CMatrice<Type>::MATLireNbreLignes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbRow, uiNbCol);

	try {
		if (CMatrice<Type>::MATLireNbreColonnes() != MAOArg.MATLireNbreColonnes() || CMatrice<Type>::MATLireNbreLignes() != MAOArg.MATLireNbreLignes()) {
			CException *EXCerreur = new CException((char*)ERROR_TAILLE_MATRICE_DIFF);
			//EXCerreur->EXCModifierErreur((char*)ERROR_TAILLE_MATRICE_DIFF);
			throw(*EXCerreur);
		}

		//std::cout << "Calcul :\n";
		for (unsigned int uiBoucleRow = 0; uiBoucleRow < uiNbRow; uiBoucleRow++) {
			for (unsigned int uiBoucleCol = 0; uiBoucleCol < uiNbCol; uiBoucleCol++) {
				//std::cout << "[" << uiBoucleRow << ";" << uiBoucleCol << "] = " << CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) + MAOArg.CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) << std::endl;
				MAOresult->CMatrice<Type>::MATModifierVal(CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol) - MAOArg.CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucleCol), uiBoucleRow, uiBoucleCol);
			}
		}
	}
	catch (CException EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}


	//std::cout << "Retour matrice :\n";
	return *MAOresult;
}

/**
Operation * entre 2 matrices

Entrée : Matrice de type Type
Nécessite : La hauteur de la matrice appelante doit être égale à la longueur del'autre
Sortie : une matrice de type Type qui est le produit des 2 autres matrices
**/
template<class Type>
CMatriceOperation<Type>& CMatriceOperation<Type>::operator*(CMatriceOperation<Type> MAOArg)
{
	// Initialisation matrice retour :
	//std::cout << "Initialisation matrice retour :\n";
	unsigned int uiNbCol = MAOArg.CMatrice<Type>::MATLireNbreColonnes(), uiNbRow = CMatrice<Type>::MATLireNbreLignes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbRow, uiNbCol);


	try {
		if (CMatrice<Type>::MATLireNbreColonnes() != MAOArg.CMatrice<Type>::MATLireNbreLignes()) {
			throw(CException((char*)ERROR_TAILLE_MATRICE_DIFF));
		}
		Type tResultatCase;
		for (unsigned int uiBoucleRow = 0; uiBoucleRow < uiNbRow; uiBoucleRow++) {
			for (unsigned int uiBoucleCol = 0; uiBoucleCol < uiNbCol; uiBoucleCol++) {
				for (unsigned int uiBoucle = 0; uiBoucle < CMatrice<Type>::MATLireNbreColonnes(); uiBoucle++) {
					if (uiBoucle == 0) {
						tResultatCase = CMatrice<Type>::MATLireVal(uiBoucleRow, 0) * MAOArg.CMatrice<Type>::MATLireVal(0, uiBoucleCol);
					}
					else {
						tResultatCase += CMatrice<Type>::MATLireVal(uiBoucleRow, uiBoucle) * MAOArg.CMatrice<Type>::MATLireVal(uiBoucle, uiBoucleCol);
					}
				}
				MAOresult->MATModifierVal(tResultatCase, uiBoucleRow, uiBoucleCol);
			}
		}
	}
	catch (CException& EXClevee) {
		std::cout << "Erreur : " << EXClevee.EXCLireErreur() << ".\n";
	}

	return *MAOresult;
}

/**
Operation * entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au produit de varArg et de la cases[i][j] de la matrices
**/
template <class Type>
CMatriceOperation<Type>& CMatriceOperation<Type>::operator*(Type varArg)
{
	unsigned int uiNbLignes = CMatrice<Type>::MATLireNbreLignes();
	unsigned int uiNbColonnes = CMatrice<Type>::MATLireNbreColonnes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbLignes, uiNbColonnes);

	unsigned int uiBoucleLigne;
	unsigned int uiBoucleColonne;

	for (uiBoucleLigne = 0; uiBoucleLigne < uiNbLignes; uiBoucleLigne++) {
		for (uiBoucleColonne = 0; uiBoucleColonne < uiNbColonnes; uiBoucleColonne++) {
			MAOresult->MATModifierVal(CMatrice<Type>::MATLireVal(uiBoucleLigne, uiBoucleColonne)*varArg, uiBoucleLigne, uiBoucleColonne);
		}
	}
	return *MAOresult;
}

/**
Operation / entre 1 matrices et un objet Type

Entrée : un objet varArg de classe Type
Nécessite : La matrice est de type Type
Sortie : une matrice de type Type de même taille et dont chaque case[i][j] est égale au quotient de varArg et de la cases[i][j] de la matrices
**/
template <class Type>
CMatriceOperation<Type>& CMatriceOperation<Type>::operator/(Type varArg)
{
	unsigned int uiNbLignes = CMatrice<Type>::MATLireNbreLignes();
	unsigned int uiNbColonnes = CMatrice<Type>::MATLireNbreColonnes();
	CMatriceOperation<Type>* MAOresult = new CMatriceOperation<Type>(uiNbLignes, uiNbColonnes);

	unsigned int uiBoucleLigne;
	unsigned int uiBoucleColonne;

	for (uiBoucleLigne = 0; uiBoucleLigne < uiNbLignes; uiBoucleLigne++) {
		for (uiBoucleColonne = 0; uiBoucleColonne < uiNbColonnes; uiBoucleColonne++) {
			MAOresult->MATModifierVal(CMatrice<Type>::MATLireVal(uiBoucleLigne, uiBoucleColonne)/varArg, uiBoucleLigne, uiBoucleColonne);
		}
	}
	return *MAOresult;
}


template <class Type>
CMatriceOperation<Type>& CMatriceOperation<Type>::MATGetSousMatrice(unsigned int uiNewNbCol, unsigned int uiNewNbRow) {
	/*if (uiNewNbCol >= uiMATNbreColonnes || uiNewNbRow >= uiMATNbreLignes) {
		throw(CException((char*)ERROR_PARAMETRES_INCORRECTS));
	}*/
	CMatriceOperation<Type>* MAONewMatrice = new CMatriceOperation(uiNewNbCol, uiNewNbRow);

	for (unsigned int uiInitRow = 0; uiInitRow < uiNewNbRow; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiNewNbCol; uiInitCol++) {
			Type currentVal = CMatrice<Type>::MATLireVal(uiInitRow, uiInitCol);
			MAONewMatrice->MATModifierVal(currentVal, uiInitRow, uiInitCol);
		}
	}
	return *MAONewMatrice;
}



template <class Type>
bool CMatriceOperation<Type>::MAOIsMatriceTridiagonale()
{
	bool bResult = CMatrice<Type>::MATIsMatriceCarre();
	
	unsigned int uiBoucleLigne = 0;
	unsigned int uiBoucleColonne = 0;

	while (uiBoucleLigne < CMatrice<Type>::uiMATNbreLignes && bResult) {
		while (uiBoucleColonne < CMatrice<Type>::uiMATNbreColonnes && bResult) {
			int iDiffColLigne = uiBoucleLigne - uiBoucleColonne;
			if (iDiffColLigne < 0) {
				iDiffColLigne *= -1;
			}
			if (iDiffColLigne > 1 && CMatrice<Type>::MATLireVal(uiBoucleLigne, uiBoucleColonne) != 0) {
				bResult = false;
			}
			uiBoucleColonne++;
		}
		uiBoucleLigne++;
	}

	return bResult;
}


template <class Type>
Type CMatriceOperation<Type>::MAODeterminantTridiagonale() {
	Type det = 0;
	try {
		if (!MAOIsMatriceTridiagonale()) {
			throw(CException((char*)ERROR_NON_TRIDIAGONALE));
		}
		if (CMatrice<Type>::uiMATNbreLignes == 2 /*&& CMatrice<Type>::uiMATNbreColonnes == 2*/) {
			det += CMatrice<Type>::MATLireVal(0, 0)*CMatrice<Type>::MATLireVal(1, 1) - CMatrice<Type>::MATLireVal(0, 1)*CMatrice<Type>::MATLireVal(1, 0);
		}
		else if (CMatrice<Type>::uiMATNbreLignes == 1 /*&& CMatrice<Type>::uiMATNbreColonnes == 1*/) {
			det += CMatrice<Type>::MATLireVal(0, 0);
		}
		else if (CMatrice<Type>::uiMATNbreLignes < 1 /*&& CMatrice<Type>::uiMATNbreColonnes == 0*/) {
			det += 0;
		}
		else {
			CMatriceOperation<Type> MAOMoinsUn = CMatriceOperation<Type>::MATGetSousMatrice(CMatrice<Type>::uiMATNbreColonnes - 1, CMatrice<Type>::uiMATNbreLignes- 1);
			CMatriceOperation<Type> MAOMoinsDeux = CMatriceOperation::MATGetSousMatrice(CMatrice<Type>::uiMATNbreColonnes - 2, CMatrice<Type>::uiMATNbreLignes - 2);
			det += CMatrice<Type>::MATLireVal(CMatrice<Type>::uiMATNbreLignes - 1, CMatrice<Type>::uiMATNbreColonnes - 1)*MAOMoinsUn.MAODeterminantTridiagonale() - CMatrice<Type>::MATLireVal(CMatrice<Type>::uiMATNbreLignes - 2, CMatrice<Type>::uiMATNbreColonnes - 1)*CMatrice<Type>::MATLireVal(CMatrice<Type>::uiMATNbreLignes - 1, CMatrice<Type>::uiMATNbreColonnes - 2)*MAOMoinsDeux.MAODeterminantTridiagonale();
		}
	}
	catch (CException &EXCLevee) {
		std::cout << EXCLevee.EXCLireErreur() << "\n";
	}
	return det;
}

