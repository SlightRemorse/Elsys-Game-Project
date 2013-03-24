//Type Convertion
#include "typeconv.h"

//Functions
LPWSTR IntToWSTR(int integer) //Converting an integer to LPWSTR
{
	LPWSTR message = new WCHAR[10];
	wsprintf(message, L"%d", integer);

	return message;
}

//JoinWSTR functions

LPWSTR JoinWSTR(bool clear, LPCWSTR str1, LPCWSTR str2) // Joining 2 LPWSTR
{

	LPWSTR message = new WCHAR[wcslen(str1)+wcslen(str2)+2];
	wsprintf(message, L"%s%s", str1, str2);
	
	if(clear)
	{
		delete str1;
		delete str2;
	}
	return message;
}

LPWSTR JoinWSTR(bool clear, LPCWSTR str1, LPCWSTR str2, LPCWSTR str3) // Joining 3 LPWSTR
{

	LPWSTR message = new WCHAR[wcslen(str1)+wcslen(str2)+wcslen(str3)+2];
	wsprintf(message, L"%s%s%s", str1, str2, str3);
	
	if(clear)
	{
		delete str1;
		delete str2;
		delete str3;
	}
	return message;
}

LPWSTR JoinWSTR(bool clear, LPCWSTR str1, LPCWSTR str2, LPCWSTR str3, LPCWSTR str4) // Joining 4 LPWSTR
{

	LPWSTR message = new WCHAR[wcslen(str1)+wcslen(str2)+wcslen(str3)+wcslen(str4)+2];
	wsprintf(message, L"%s%s%s%s", str1, str2, str3, str4);
	
	if(clear)
	{
		delete str1;
		delete str2;
		delete str3;
		delete str4;
	}
	return message;
}

LPWSTR JoinWSTR(bool clear, LPCWSTR str1, LPCWSTR str2, LPCWSTR str3, LPCWSTR str4, LPCWSTR str5) // Joining 5 LPWSTR
{

	LPWSTR message = new WCHAR[wcslen(str1)+wcslen(str2)+wcslen(str3)+wcslen(str4)+wcslen(str5)+2];
	wsprintf(message, L"%s%s%s%s%s", str1, str2, str3, str4, str5);
	
	if(clear)
	{
		delete str1;
		delete str2;
		delete str3;
		delete str4;
		delete str5;
	}
	return message;
}

//End JoinWSTR functions

LPWSTR SafeWSTR(LPCWSTR input) // Creates a safe WSTR that can be easily deleted from the memory.
{
	LPWSTR output = new WCHAR[wcslen(input)+1];
	wsprintf(output, input);

	return output;
}