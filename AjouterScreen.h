#ifndef _AJOUTERSCREEN_H
#define _AJOUTERSCREEN_H

#include "Screen.h"
#include <list>
#include "Texture.h"
#include "InputManager.h"
#include "infoList.h"


class AjouterScreen : public Screen
{
private:
	std::list<Texture*> allTextures;

	Texture* titre;
	Texture* affichHeure;
	Texture* affich2p;
	Texture* affichMinute;
	Texture* affichQuantite;
	Texture* buttonValider;

	int selectedEntriesID;

	std::string text;
	int maxTextSize;

	Texture* validerBut;
	Texture* mainScreenBut;

	InputManager* mInputMgr;
	infoList* mInfoList;

public:
	void Render() const override;
	void update() override;
public:

	AjouterScreen();
	~AjouterScreen();
	void checkInput();
};

#endif

