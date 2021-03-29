#pragma once
template <class Type> class CMatrice
{
private:
	unsigned int uiMATNbreLignes;
	unsigned int uiMATNbreColonnes;
	Type MATTableau[][];
public:
	CMatrice();
	CMatrice(CMatrice MATarg);
	~CMatrice();
	CMatrice MATTransposer();
	void MATAfficher();
};
