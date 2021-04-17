// ProjetCpp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CMatriceOperation.h"
#include "CMatriceOperation.cpp"


int main()
{
	std::cout << "Programme compilé, exécution :\n";
	

	std::cout << "\nTest 1 : création mat:\n";
	CMatriceOperation<int>* mat = new CMatriceOperation<int>();

	mat->MATModifierVal(1, 0, 0);
	mat->MATModifierVal(2, 0, 1);
	mat->MATModifierVal(3, 1, 0);
	mat->MATModifierVal(4, 1, 1);

	mat->MATAfficher();


	std::cout << "\nTest 2 : création mat2:\n";
	CMatriceOperation<int>* mat2 = new CMatriceOperation<int>(*mat);

	mat2->MATAfficher();

	
	std::cout << "\nTest 3 : création mat3:\n";
	CMatriceOperation<double>* mat3 = new CMatriceOperation<double>(3,2);

	mat3->MATModifierVal(1.1, 0, 0);
	mat3->MATModifierVal(2.2, 0, 1);
	mat3->MATModifierVal(3.0, 1, 0);
	mat3->MATModifierVal(4.5, 1, 1);
	mat3->MATModifierVal(5.0, 2, 0);
	mat3->MATModifierVal(6  , 2, 1);

	mat3->MATAfficher();


	std::cout << "\nTest 4 : création mat4:\n";
	CMatriceOperation<double>* mat4 = new CMatriceOperation<double>((char*)"matInit.txt");

	mat4->MATAfficher();


	/*
	std::cout << "\nTest 5 : opérations :\n";

	CMatriceOperation<int> mat4;
	mat4 = *mat + *mat2;

	mat4.MATAfficher();
	*/


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
