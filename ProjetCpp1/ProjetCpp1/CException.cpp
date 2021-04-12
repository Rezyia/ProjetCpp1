#include "CException.h"
#include <cstring>

CException::CException(char * pcErr)
{
	//strcpy(pcErreur, pcErr);
}

CException::CException(CException * EXCcopy)
{
	//strcpy(pcErreur, EXCcopy->EXCLireErreur());
}

CException::~CException()
{
}

char* CException::EXCLireErreur()
{
	return pcErreur;
}
