//Input Class header (100% coverage)
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


//Input Class
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();
	
	void SetMouseClicks();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void MKeyDown(unsigned int);
	void MKeyUp(unsigned int);
	void MCoord(unsigned int, unsigned int);

	bool IsKeyDown(unsigned int);
	bool IsMKeyDown(unsigned int);
	bool IsMKeyDownHold(unsigned int);
	bool IsMKeyClick(unsigned int);
	int KeysDown();
	int MGetX();
	int MGetY();

public:
	void MKeyClick(unsigned int, bool);

	int pressed_keys;
	bool mouse_click[3];
	bool mouse_keys[3];
	int mouseX, mouseY;
	bool main_keys[256];
};
//End Input Class

#endif
