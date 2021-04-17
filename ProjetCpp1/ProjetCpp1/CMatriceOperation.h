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
	CMatriceOperation<Type>(unsigned int uiiNbCol, unsigned int uiNbRow);
	CMatriceOperation<Type>(char* pcNomFichier);
	~CMatriceOperation<Type>();

	// Autres méthodes :
	CMatriceOperation<Type>& operator+(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator-(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator*(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type>& operator*(Type varArg);
	CMatriceOperation<Type>& operator/(Type varArg);
};