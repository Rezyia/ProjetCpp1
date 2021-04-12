#include "CException.h"
#include <cstring>

CException::CException(char * pcErr)
{
	strcpy_s(pcErreur, sizeof(pcErr), pcErr);
}

CException::CException(CException * EXCcopy)
{
	strcpy_s(pcErreur, sizeof(EXCcopy->EXCLireErreur()), EXCcopy->EXCLireErreur());
}

CException::~CException()
{
}

char* CException::EXCLireErreur()
{
	return pcErreur;
}

void CException::EXCModifierErreur(char* pcErr) {
	strcpy_s(pcErreur, sizeof(pcErr), pcErr);
}
