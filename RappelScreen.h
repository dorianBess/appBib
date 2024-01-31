#ifndef _RAPPELSCREEN_H
#define _RAPPELSCREEN_H

#include "Screen.h"
#include <list>
#include "Texture.h"
#include "InputManager.h"
#include "nlohmann/json.hpp"

class RappelScreen : public Screen
{
private:
	Texture* titre;
	Texture* affichHeure;
	Texture* affich2p;
	Texture* affichMinute;
	Texture* buttonValider;

	Texture* validerBut;

	int selectedEntriesID;
	std::string text;
	int maxTextSize;

	nlohmann::json data_;

	Texture* mainScreenBut;
	InputManager* mInputMgr;

public:
	std::string heureRappel;
	std::string filename;
	void Render() const override;
	void update() override;
public:

	RappelScreen();
	~RappelScreen();
	void checkInput();
};

#endif

