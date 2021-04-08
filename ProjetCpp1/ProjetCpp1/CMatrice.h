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
	CMatrice<Type>(unsigned int length, unsigned int height);
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
		MATTableau[uiNumCol][uiNumLig] = valArg;
	}

	Type MATLireVal(unsigned int uiNumCol, unsigned int uiNumLig) {
		return MATTableau[uiNumCol][uiNumLig];
	}

};
