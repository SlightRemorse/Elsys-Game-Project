//Input Class header
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

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	void MouseCoord(unsigned int, unsigned int);

	bool IsKeyDown(unsigned int);
	int KeysDown();
	int MouseGetX();
	int MouseGetY();

private:
	int pressed_keys;
	int mouseX, mouseY;
	bool main_keys[256];
};
//End Input Class

#endif
