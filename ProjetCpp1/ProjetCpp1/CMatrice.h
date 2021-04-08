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

	void MATModifierNbreLignes(unsigned int uiArg) {
		Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg); // Allocation nouvelle matrice

		// Initialisation nouvelle matrice par des 0 :
		for (int i=0; i < uiArg; i++) {
			for (int j=0; j < uiMATNbreColonnes; j++) {
				newMat[i][j] = 0;
			}
		}

		// Copie de MATTableau dans newMat :
		for (int i = 0; i < std::min(uiArg, uiMATNbreLignes); i++) {
			for (int j = 0; j < uiMATNbreColonnes; j++) {
				newMat[i][j] = MATTableau[i][j];
			}
		}

		uiMATNbreLignes = uiArg;

		free(MATTableau);
		MATTableau = newMat;
	}

	unsigned int MATLireNbreLignes() {
		return uiMATNbreLignes;
	}

	void MATModifierNbreColonne(unsigned int uiArg) {
		Type* newMat = malloc(typeof(Type) * uiMATNbreColonnes* uiArg); // Allocation nouvelle matrice

		// Initialisation nouvelle matrice par des 0 :
		for (int i = 0; i < uiArg; i++) {
			for (int j = 0; j < uiMATNbreColonnes; j++) {
				newMat[i][j] = 0;
			}
		}

		// Copie de MATTableau dans newMat :
		for (int i = 0; i < uiMATNbreLignes; i++) {
			for (int j = 0; j < std::min(uiArg, uiMATNbreColonnes); j++) {
				newMat[i][j] = MATTableau[i][j];
			}
		}

		uiMATNbreColonnes = uiArg;

		free(MATTableau);
		MATTableau = newMat;
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
