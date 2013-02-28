//Type Convertion
#include "typeconv.h"

//Functions
LPCWSTR IntToWSTR(int integer) 
{
	LPWSTR message = new wchar_t[sizeof(int)];
	wsprintf(message, L"%d", integer);
	return message;
}