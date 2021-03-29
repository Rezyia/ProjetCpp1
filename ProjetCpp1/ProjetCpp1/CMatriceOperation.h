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
	CMatriceOperation operator+(CMatriceOperation MAOArg);
	CMatriceOperation operator-(CMatriceOperation MAOArg);
	CMatriceOperation operator*(CMatriceOperation MAOArg);
	CMatriceOperation operator*(Type varArg);
	CMatriceOperation operator/(Type varArg);
};
