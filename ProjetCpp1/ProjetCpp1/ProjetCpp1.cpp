// ProjetCpp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CMatriceOperation.h"
#include "CMatriceOperation.cpp"


int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "Erreur : veuillez mettre au moins un fichier en paramètre.\n";
		exit(EXIT_FAILURE);
	}

	CMatriceOperation<double>** tCMatrices = (CMatriceOperation<double>**)malloc((argc-2) * sizeof(CMatriceOperation<double>*));


	// •	Pour chaque nom de fichier passé en paramètre, lire le fichier et créer la matrice associée,
	for (int iBoucleInitFichier = 1; iBoucleInitFichier < argc; iBoucleInitFichier++) {
		tCMatrices[iBoucleInitFichier-1] = new CMatriceOperation<double>(argv[iBoucleInitFichier]);
	}

	double c;
	CMatriceOperation<double>* CMatTemp = new CMatriceOperation<double>();

	// •	Demander à l’utilisateur de saisir une valeur c,
	std::cout << "Entrez une valeur c : ";
	std::cin >> c;

	// •	Afficher le résultat de la multiplication de chacune des matrices par la valeur c, 
	for (int iBoucleCalculs = 0; iBoucleCalculs < argc-1; iBoucleCalculs++) {
		std::cout << "\nMatrice n°" << iBoucleCalculs + 1 << " :\n";

		*CMatTemp = *tCMatrices[iBoucleCalculs] * c;
		CMatTemp->MATAfficher();
	}

	// •	Afficher le résultat de la division de chacune des matrices par la valeur c, 
	for (int iBoucleCalculs = 0; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		std::cout << "\nMatrice n°" << iBoucleCalculs + 1 << " :\n";

		*CMatTemp = *tCMatrices[iBoucleCalculs] / c;
		CMatTemp->MATAfficher();
	}

	// •	Afficher le résultat de l’addition de toutes les matrices entre elles : M1+M2+M3+….,
	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc-1; iBoucleCalculs++) {
		*CMatTemp = *CMatTemp + *tCMatrices[iBoucleCalculs];
	}

	std::cout << "\nSomme des matrices :\n";
	CMatTemp->MATAfficher();

	// •	Afficher le résultat de l’opération suivante : M1 - M2 + M3 - M4 + M5 - M6 + ….
	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		if (iBoucleCalculs % 2 == 0) {
			*CMatTemp = *CMatTemp + *tCMatrices[iBoucleCalculs];
		}
		else {
			*CMatTemp = *CMatTemp - *tCMatrices[iBoucleCalculs];
		}
	}

	std::cout << "\nAlternance - et + des matrices :\n";
	CMatTemp->MATAfficher();

	// •	Afficher le résultat du produit des matrices.
	CMatTemp = new CMatriceOperation<double>(*tCMatrices[0]);
	for (int iBoucleCalculs = 1; iBoucleCalculs < argc - 1; iBoucleCalculs++) {
		*CMatTemp = *CMatTemp * *tCMatrices[iBoucleCalculs];

	}

	std::cout << "\nProduit des matrices : \n";
	CMatTemp->MATAfficher();

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
