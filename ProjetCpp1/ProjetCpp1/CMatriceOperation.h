#pragma once
#include "CMatrice.h"
#include "CMatrice.cpp"

template <class Type>

class CMatriceOperation :
	public CMatrice<Type>
{
public:
	// Constructeur:
	CMatriceOperation<Type>();
	CMatriceOperation<Type>(CMatriceOperation& MATarg);
	CMatriceOperation<Type>(unsigned int uiNbRow, unsigned int uiNbCol);
	CMatriceOperation<Type>(char* pcNomFichier);
	~CMatriceOperation<Type>();

	// Autres méthodes :
	CMatriceOperation<Type>& operator+(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator-(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator*(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator*(Type varArg);
	CMatriceOperation<Type>& operator/(Type varArg);

	bool MAOIsMatriceTridiagonale();
	Type MAODeterminantTridiagonale();


	CMatriceOperation<Type>& MATGetSousMatrice(unsigned int uiNewNbCol, unsigned int uiNewNbRow);

};