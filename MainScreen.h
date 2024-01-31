#ifndef _MAINSCREEN_H
#define _MAINSCREEN_H

#include "Screen.h"
#include <list>
#include "Texture.h"
#include "InputManager.h"


class MainScreen : public Screen
{
private:
	std::list<Texture*> allTextures;

	Texture* consulterBut;
	Texture* ajouterBut;
	Texture* rappelBut;
	Texture* listeBut;

	InputManager* mInputMgr;

public:
	void Render() const override;
	void update() override;
public:

	MainScreen();
	~MainScreen();
};

#endif

