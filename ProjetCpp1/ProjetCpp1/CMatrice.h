#pragma once
template <class Type> class CMatrice
{
private:
	unsigned int uiMATNbreLignes;
	unsigned int uiMATNbreColonnes;
	Type MATTableau[][];
public:
	CMatrice<Type>();
	CMatrice<Type>(CMatrice<Type>* MATarg);
	~CMatrice<Type>();
	CMatrice<Type> MATTransposer();
	void MATAfficher();

	void MATModifierNbreLignes(unsigned int uiArg) {
		uiMATNbreLignes = uiArg;
		//TODO - r�allou� MATTableau
	}

	unsigned int MATLireNbreLignes() {
		return uiMATNbreLignes;
	}

	void MATModifierNbreColonne(unsigned int uiArg) {
		uiMATNbreColonnes = uiArg;
		//TODO - r�allou� MATTableau
	}

	unsigned int MATLireNbreColonne() {
		return uiMATNbreColonnes;
	}

	void MATModifierVal(Type valArg, unsigned int uiNumCol, unsigned int uiNumLig){
		MATTableau[uiNumCol][uiNumLig] = valArg;
	}

	Type MATLireVal(unsigned int uiNumCol, unsigned int uiNumLig) {
		return MATTableau[uiNumCol][uiNumLig];
	}
};
