#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iomanip>
#include "CMatrice.h"

#define NBRE_LIGNES_BASE 2
#define NBRE_COLONNES_BASE 2

#define NBRE_MAX_CHAMPS_FICHIER 32
#define NBRE_MAX_LIGNES_FICHIER 255


/**********************************************************************************

							Constructeur Par défaut

Entrée :	Rien
Nécessite :	Rien
Sortie :	Une matrice de type Type de dimensions NBRE_LIGNES_BASE * NBRE_COLONNES_BASE
			(voir CMatrice.cpp ou CMatrice.h) avec des valeurs non initialisées
**********************************************************************************/
template <class Type>
CMatrice<Type>::CMatrice() { 
	//std::cout << "Constructeur par défaut :\n";
	uiMATNbreColonnes = NBRE_COLONNES_BASE;
	uiMATNbreLignes = NBRE_LIGNES_BASE;

	MATTableau = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}
}

/**********************************************************************************

							Constructeur de recopie

Entrée :	Adresse d'une autre CMatriceOperation
Nécessite :	Rien
Sortie :	Une matrice de type Type de même dimensions que celle passée en paramètre
			et de même valeurs de matrice.
**********************************************************************************/
template <class Type>
CMatrice<Type>::CMatrice(CMatrice<Type>& MATarg) {
	//std::cout << "Constructeur de recopie :\n";

	// Affectation des dimensions :
	uiMATNbreColonnes = MATarg.MATLireNbreColonnes();
	uiMATNbreLignes = MATarg.MATLireNbreLignes();

	// Allocation de la matrice :
	MATTableau = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc< uiMATNbreLignes; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}

	// Recopie des valeurs :
	for (unsigned int iBoucleRecopie = 0; iBoucleRecopie < uiMATNbreLignes; iBoucleRecopie++) {
		for (unsigned int jBoucleRecopie = 0; jBoucleRecopie < uiMATNbreColonnes; jBoucleRecopie++) {
			MATTableau[iBoucleRecopie][jBoucleRecopie] = MATarg.MATLireVal(iBoucleRecopie, jBoucleRecopie);
		}
	}
}

/**********************************************************************************

				Constructeur avec nombre de lignes et colonnes :

Entrée :	Nombre de lignes (uiNbRow) et nombre de colonnes (uiNbCol)
Nécessite :	Rien
Sortie :	Une matrice de type Type de dimensions uiNbRow * uiNbCol 
			avec des valeurs non-initialisées.
**********************************************************************************/
template <class Type>
CMatrice<Type>::CMatrice(unsigned int uiNbCol, unsigned int uiNbRow) { // test constructeur custom sizes
	uiMATNbreColonnes = uiNbCol;
	uiMATNbreLignes = uiNbRow;
	MATTableau = (Type**)malloc(uiNbCol * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiNbCol; uiBoucleAlloc++) {
		MATTableau[uiBoucleAlloc] = (Type*)malloc(uiNbRow * sizeof(Type));
	}
}

/**********************************************************************************

							Constructeur par fichier :

Entrée :	Pointeur vers une chaîne de charactères
Nécessite :	Rien
Sortie :	Une matrice de type double avec les dimensions et valeurs inscrites
			dans le fichier
**********************************************************************************/
template<class Type>
CMatrice<Type>::CMatrice(char* pcNomFichier)
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
				uiMATNbreLignes = atoi((const char*)valeurCourrante);
				//std::cout << "Nb Lignes = " << valeurCourrante << std::endl;
				break;


				// NBColonnes :
			case 2:
				//std::cout << "switch case 2" << std::endl;
				uiMATNbreColonnes = atoi((const char*)valeurCourrante);
				//std::cout << "Nb Colonnes = " << valeurCourrante << std::endl;
				break;


				// Matrice :
			case 3:
			{
				//std::cout << "switch case 3" << std::endl;
				
				// Initialisation tableau matrice : 
				MATTableau = (double**)malloc(uiMATNbreLignes * sizeof(double*));
				for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
					MATTableau[uiBoucleAlloc] = (double*)malloc(uiMATNbreColonnes * sizeof(double));
				}
				unsigned int lBoucleInitMat = 0;
				unsigned int cBoucleInitMat = 0;

				// Retour à la ligne (début des valeurs) :
				ifsFichier >> cLigne;

				//std::cout << "Affectation des valeurs :" << std::endl;

				//std::cout << "max : [" << CMatrice<double>::MATLireNbreLignes()-1 << ";" << CMatrice<double>::MATLireNbreColonnes()-1 << "]\n";

				while (lBoucleInitMat < MATLireNbreLignes()) {
					cBoucleInitMat = 0;
					while (cBoucleInitMat < MATLireNbreColonnes()) {
						MATModifierVal(atof(cLigne), lBoucleInitMat, cBoucleInitMat);
						
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


// Destructeur
template <class Type>
CMatrice<Type>::~CMatrice() {
	free(MATTableau);
}



//Fonction pour obtenir la transpos� d'une matrice quelconque
template <class Type>
CMatrice<Type>& CMatrice<Type>::MATTransposer() {
	CMatrice<Type> *MATtmp = new CMatrice<Type>(MATLireNbreColonnes(), MATLireNbreLignes());
	//MATtmp->MATModifierNbreColonnes(MATLireNbreLignes());
	//MATtmp->MATModifierNbreLignes(MATLireNbreColonnes());

	unsigned int uiBoucleCol, uiBoucleRow;

	for (uiBoucleRow = 0; uiBoucleRow < uiMATNbreLignes; uiBoucleRow++) {
		for (uiBoucleCol = 0; uiBoucleCol < uiMATNbreColonnes; uiBoucleCol++) {
			MATtmp->MATModifierVal(MATLireVal(uiBoucleRow, uiBoucleCol), uiBoucleRow, uiBoucleCol);
		}
	}
	return *MATtmp;
}

//Fonction pour afficher une matrice
template <class Type>
void CMatrice<Type>::MATAfficher() 
{
	unsigned int uiBoucleCol, uiBoucleRow;
	for (uiBoucleRow = 0; uiBoucleRow < uiMATNbreLignes; uiBoucleRow++) {
		for (uiBoucleCol = 0; uiBoucleCol < uiMATNbreColonnes; uiBoucleCol++) {
			std::cout << MATLireVal(uiBoucleRow, uiBoucleCol) << "\t";
		}
		std::cout << "\n";
	}
}


/**********************************************************************************

					Modificateur du nombre de lignes d'une matrice :

Entrée :			Nombre de lignes à changer
Nécessite :			Rien
Sortie :			Rien
Post-condition :	Nouvelle MATMatrice de type Type de dimensions uiArg * uiMATNbreColonnes
					remplie par des 0 puis avec les valeurs de la MATMatrice originale
**********************************************************************************/
template <class Type>
void CMatrice<Type>::MATModifierNbreLignes(unsigned int uiArg) {
	//Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg);
	
	// Allocation nouvelle matrice
	Type** newMat = (Type**)malloc(uiArg * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiArg; uiBoucleAlloc++) {
		newMat[uiBoucleAlloc] = (Type*)malloc(uiMATNbreColonnes * sizeof(Type));
	}

	// Initialisation nouvelle matrice par des 0 :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = MATTableau[uiInitRow][uiInitCol];
		}
	}

	uiMATNbreLignes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}


/**********************************************************************************

					Modificateur du nombre de colonnes d'une matrice :

Entrée :			Nombre de colonnes à changer
Nécessite :			Rien
Sortie :			Rien
Post-condition :	Nouvelle MATMatrice de type Type de dimensions uiMATNbreLignes * uiArg
					remplie par des 0 puis avec les valeurs de la MATMatrice originale
**********************************************************************************/
template <class Type>
void CMatrice<Type>::MATModifierNbreColonnes(unsigned int uiArg) {
	//Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg);
	
	// Allocation nouvelle matrice
	Type** newMat = (Type**)malloc(uiMATNbreLignes * sizeof(Type*));
	for (unsigned int uiBoucleAlloc = 0; uiBoucleAlloc < uiMATNbreLignes; uiBoucleAlloc++) {
		newMat[uiBoucleAlloc] = (Type*)malloc(uiArg * sizeof(Type));
	}

	// Initialisation nouvelle matrice par des 0 :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = 0;
		}
	}

	// Copie de MATTableau dans newMat :
	for (unsigned int uiInitRow = 0; uiInitRow < uiArg; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiMATNbreColonnes; uiInitCol++) {
			newMat[uiInitRow][uiInitCol] = MATTableau[uiInitRow][uiInitCol];
		}
	}

	uiMATNbreColonnes = uiArg;

	free(MATTableau);
	MATTableau = newMat;
}


template <class Type>
CMatrice<Type>& CMatrice<Type>::MATGetSousMatrice(unsigned int uiNewNbCol, unsigned int uiNewNbRow) {
	CMatrice<Type>* MATNewMatrice = new CMatrice(uiNewNbCol, uiNewNbRow);

	for (unsigned int uiInitRow = 0; uiInitRow < uiNewNbRow; uiInitRow++) {
		for (unsigned int uiInitCol = 0; uiInitCol < uiNewNbCol; uiInitCol++) {
			Type currentVal = MATLireVal(uiInitRow, uiInitCol);
			MATNewMatrice.MATModifierVal(currentVal, uiInitRow, uiInitCol);
		}
	}
	return *MATNewMatrice;
}

