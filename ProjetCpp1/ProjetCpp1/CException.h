#pragma once
class CException
{
private:
	char* pcErreur;
public:
	CException(char* pcErr);
	CException(CException *EXCcopy);
	~CException();
	char* EXCLireErreur();
};