//DirectX Fonts header
#ifndef _DIRECT_FONT_H_
#define _DIRECT_FONT_H_

//Includes
#include <d3dx9.h>

#pragma comment (lib, "d3dx9.lib")

//DirectX Fonts Class
class DXFonts
{
public:
	DXFonts(IDirect3DDevice9*);
	DXFonts(const DXFonts&);
	~DXFonts();
	
	void getDevice(IDirect3DDevice9*);
	bool Initialize();
	void Shutdown();

	bool SetFont(LPCWSTR, int, int=0, unsigned int=FW_NORMAL, int=1, bool=false, DWORD=ANTIALIASED_QUALITY);

	ID3DXFont* pD3DX_font;

private:
	IDirect3DDevice9* pDevice;
};
//End DirectX Fonts Class

//Globals

#endif

