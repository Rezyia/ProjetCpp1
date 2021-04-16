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
	CMatriceOperation<Type>(CMatriceOperation *MAOcopie);
	~CMatriceOperation<Type>();

	// Autres méthodes :
	CMatriceOperation<Type> operator+(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator-(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator*(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator*(Type varArg);
	CMatriceOperation<Type> operator/(Type varArg);
};