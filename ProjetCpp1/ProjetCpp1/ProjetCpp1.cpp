// ProjetCpp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CMatriceOperation.h"
#include "CMatriceOperation.cpp"


int main(int argc, char* argv[]) {

	/**********************************************************************************

					Partie déclarations et initialisations du programme :

	**********************************************************************************/

	// Vérification : au moins 1 argument
	if (argc < 2) {
		std::cout << "Erreur : veuillez mettre au moins un fichier en paramètre.\n";
		exit(EXIT_FAILURE);
	}

	// Allocation de l'array des matrices CMatriceOperation :
	CMatriceOperation<double>** tCMatrices = (CMatriceOperation<double>**)malloc((argc-2) * sizeof(CMatriceOperation<double>*));


	// •	Pour chaque nom de fichier passé en paramètre, lire le fichier et créer la matrice associée,
	for (int iBoucleInitFichier = 1; iBoucleInitFichier < argc; iBoucleInitFichier++) {
		tCMatrices[iBoucleInitFichier-1] = new CMatriceOperation<double>(argv[iBoucleInitFichier]);
	}

	// Déclaration et Initialisation des variables :
	double c;
	CMatriceOperation<double>* CMatTemp = new CMatriceOperation<double>();


	/**********************************************************************************

							Partie principale du programme :

	**********************************************************************************/


	// •	Demander à l’utilisateur de saisir une valeur c,
	std::cout << "Entrez une valeur c : ";
	std::cin >> c;


	// •	Afficher le résultat de la multiplication de chacune des matrices par la valeur c, 
	std::cout << "\n ### Multiplication des matrices par " << c << ": ###\n";

	for (int iBoucleCalculs = 0; iBoucleCalculs < argc-1; iBoucleCalculs++) {
		std::cout << "\nMatrice n°" << iBoucleCalculs + 1 << " :\n";

		*CMatTemp = *tCMatrices[iBoucleCalculs] * c;
		CMatTemp->MATAfficher();
	}


	// •	Afficher le résultat de la division de chacune des matrices par la valeur c,
	std::cout << "\n ### Divisions des matrices par " << c << ": ###\n";

	for (int iBoucleCalculs = 0; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		std::cout << "\nMatrice n°" << iBoucleCalculs + 1 << " :\n";

		*CMatTemp = *tCMatrices[iBoucleCalculs] / c;
		CMatTemp->MATAfficher();
	}


	// •	Afficher le résultat de l’addition de toutes les matrices entre elles : M1+M2+M3+….,
	std::cout << "\n ### Somme des matrices : ###\n";

	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc-1; iBoucleCalculs++) {
		*CMatTemp = *CMatTemp + *tCMatrices[iBoucleCalculs];
	}
	CMatTemp->MATAfficher();


	// •	Afficher le résultat de l’opération suivante : M1 - M2 + M3 - M4 + M5 - M6 + ….
	std::cout << "\n ### Alternance - et + des matrices : ###\n";

	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		if (iBoucleCalculs % 2 == 0) {
			*CMatTemp = *CMatTemp + *tCMatrices[iBoucleCalculs];
		}
		else {
			*CMatTemp = *CMatTemp - *tCMatrices[iBoucleCalculs];
		}
	}
	CMatTemp->MATAfficher();


	// •	Afficher le résultat du produit des matrices.
	std::cout << "\nProduit des matrices : \n";

	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		*CMatTemp = *CMatTemp * *tCMatrices[iBoucleCalculs];

	}
	CMatTemp->MATAfficher();

	/**********************************************************************************

									Fin du programme :

	**********************************************************************************/

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
