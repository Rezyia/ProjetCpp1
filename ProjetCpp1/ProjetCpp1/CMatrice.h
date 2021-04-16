#pragma once
template <class Type> class CMatrice
{
private:
	unsigned int uiMATNbreLignes;
	unsigned int uiMATNbreColonnes;
	Type* MATTableau;
public:
	CMatrice<Type>();
	CMatrice<Type>(CMatrice<Type>* MATarg);
	CMatrice<Type>(unsigned int nbCol, unsigned int nbRow);
	CMatrice<Type>(char* pcNomFichier);
	~CMatrice<Type>();
	CMatrice<Type> MATTransposer();
	void MATAfficher();


	void MATModifierNbreLignes(unsigned int uiArg);
	void MATModifierNbreColonnes(unsigned int uiArg);

	unsigned int MATLireNbreColonnes() {
		return uiMATNbreColonnes;
	}

	unsigned int MATLireNbreLignes() {
		return uiMATNbreLignes;
	}

	void MATModifierVal(Type valArg, unsigned int uiNumCol, unsigned int uiNumLig){
		MATTableau[uiNumLig][uiNumCol] = valArg;
	}

	Type MATLireVal(unsigned int uiNumCol, unsigned int uiNumLig) {
		return MATTableau[uiNumLig][uiNumCol];
	}

};
