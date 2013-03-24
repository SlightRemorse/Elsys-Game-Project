//Type Convertion header
#ifndef _TYPECONV_H_
#define _TYPECONV_H_

//Includes
#include <Windows.h>

//Functions
LPWSTR IntToWSTR(int);
LPWSTR JoinWSTR(LPCWSTR, LPCWSTR, bool=false, bool=false);
LPWSTR SafeWSTR(LPCWSTR);


#endif