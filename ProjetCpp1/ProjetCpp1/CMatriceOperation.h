#pragma once
#include "CMatrice.h"

template <class Type>

class CMatriceOperation :
	public CMatrice<Type>
{
public:
	// Constructeur:
	CMatriceOperation<Type>();


	// Autres méthodes :
	CMatriceOperation<Type> operator+(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator-(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator*(CMatriceOperation<Type> MAOArg);
	CMatriceOperation<Type> operator*(Type varArg);
	CMatriceOperation<Type> operator/(Type varArg);
};