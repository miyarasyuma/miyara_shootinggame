#pragma once

class KeyManager
{
private:
	static char oldKey[256];
	static char nowKey[256];

	static int  oldMouse;
	static int  nowMouse;
 
private:
	KeyManager() = default;

public://構造体を作らないため
	static void Update();
	static bool OnKeyClick(int key);   //押した瞬間
	static bool OnKeyReleased(int key);//離した瞬間
	static bool OnKeyPressed(int key); //押されている間

	static bool OnMouseClick(int key);   //押した瞬間
	static bool OnMouseReleased(int key);//離した瞬間
	static bool OnMousePressed(int key); //押されている間
};

