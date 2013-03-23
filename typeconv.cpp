//Type Convertion
#include "typeconv.h"

//Functions
LPCWSTR IntToWSTR(int integer) 
{
	LPWSTR message = new wchar_t[16];
	wsprintf(message, L"%d", integer);
	return message;
}

LPCWSTR JoinWSTR(LPCWSTR str1, LPCWSTR str2)
{
	LPWSTR message = new wchar_t[wcslen(str1)+wcslen(str2)];
	wsprintf(message, L"%s %s", str1, str2);
	return message;
}