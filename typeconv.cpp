//Type Convertion
#include "typeconv.h"

//Functions
LPWSTR IntToWSTR(int integer) //Converting an integer to LPWSTR
{
	LPWSTR message = new WCHAR[10];
	wsprintf(message, L"%d", integer);

	return message;
}

LPWSTR JoinWSTR(LPCWSTR str1, LPCWSTR str2, bool clear, bool space) // Joining 2 LPWSTR
{
	LPWSTR message;
	if(space)
	{
		message = new WCHAR[wcslen(str1)+wcslen(str2)+2];
		wsprintf(message, L"%s %s", str1, str2);
	}
	else
	{
		message = new WCHAR[wcslen(str1)+wcslen(str2)+1];
		wsprintf(message, L"%s%s", str1, str2);
	}
	if(clear)
	{
		delete str1;
		delete str2;
	}
	return message;
}

LPWSTR SafeWSTR(LPCWSTR input) // Creates a safe WSTR that can be easily deleted from the memory.
{
	LPWSTR output = new WCHAR[wcslen(input)+1];
	wsprintf(output, input);

	return output;
}