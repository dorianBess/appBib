#ifndef _CONSULTERSCREEN_H
#define _CONSULTERSCREEN_H

#include "Screen.h"
#include <list>
#include <string>
#include "InputManager.h"
#include "infoList.h"


class ConsulterScreen : public Screen
{

private:
	infoList* infos;

	Texture* mainScreenBut;

	InputManager* mInputMgr;
public:
	Texture* nextPage;
	Texture* prevPage;

	void Render() const override;
	void update() override;
public:

	ConsulterScreen();
	~ConsulterScreen();
	
};

#endif

