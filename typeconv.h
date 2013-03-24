//Type Convertion header
#ifndef _TYPECONV_H_
#define _TYPECONV_H_

//Includes
#include <Windows.h>

//Functions
LPWSTR IntToWSTR(int);

LPWSTR JoinWSTR(bool, LPCWSTR, LPCWSTR);
LPWSTR JoinWSTR(bool, LPCWSTR, LPCWSTR, LPCWSTR);
LPWSTR JoinWSTR(bool, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);
LPWSTR JoinWSTR(bool, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR);

LPWSTR SafeWSTR(LPCWSTR);


#endif