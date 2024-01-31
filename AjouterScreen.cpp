#include "AjouterScreen.h"
#include <regex>
#include "AppManager.h"

AjouterScreen::~AjouterScreen()
{
	delete titre;
	titre = NULL;
	delete affichHeure;
	affichHeure = NULL;
	delete affich2p;
	affich2p = NULL;
	delete affichMinute;
	affichMinute = NULL;
	delete affichQuantite;
	affichQuantite = NULL;
	delete buttonValider;
	buttonValider = NULL;

	delete mainScreenBut;
	mainScreenBut = NULL;
}

AjouterScreen::AjouterScreen()
{
	titre = new Texture("Heure / Quantite", "ARCADE.TTF", 72, { 0,0,0 });
	titre->Pos(Vector2(400, 100));
	affichHeure = new Texture("00", "ARCADE.TTF", 72, { 0,0,0 });
	affichHeure->Pos(Vector2(200, 300));
	affich2p = new Texture(" : ", "ARCADE.TTF", 72, { 0,0,0 });
	affich2p->Pos(Vector2(250, 300));
	affichMinute = new Texture("00", "ARCADE.TTF", 72, { 0,0,0 });
	affichMinute->Pos(Vector2(300, 300));
	affichQuantite = new Texture("0", "ARCADE.TTF", 72, { 0,0,0 });
	affichQuantite->Pos(Vector2(500, 300));

	validerBut = new Texture("Valider", "ARCADE.TTF", 72, { 0,0,0 });
	validerBut->Pos(Vector2(400, 500));

	mainScreenBut = new Texture("Main screen", "ARCADE.TTF", 72, { 0,0,0 });
	mainScreenBut->Pos(Vector2(200, 50));

	mInputMgr = InputManager::Instance();
	mInfoList = infoList::Instance();
}

void AjouterScreen::Render() const
{
	titre->Render();
	affichHeure->Render();
	affich2p->Render();
	affichMinute->Render();
	affichQuantite->Render();
	validerBut->Render();
	mainScreenBut->Render();
}

void AjouterScreen::update()
{
	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
		if (affichHeure->isClicked(MousePos.x, MousePos.y))
		{
			maxTextSize = 2;
			selectedEntriesID = 1;
			affichHeure->redrawText(" ", "ARCADE.TTF", 72, { 0,0,0 });
			SDL_StartTextInput();
		}
		else if (affichMinute->isClicked(MousePos.x, MousePos.y))
		{
			maxTextSize = 2;
			selectedEntriesID = 2;
			affichMinute->redrawText(" ", "ARCADE.TTF", 72, { 0,0,0 });
			SDL_StartTextInput();
		}
		else if (affichQuantite->isClicked(MousePos.x, MousePos.y))
		{
			maxTextSize = 3;
			selectedEntriesID = 3;
			affichQuantite->redrawText(" ", "ARCADE.TTF", 72, { 0,0,0 });
			SDL_StartTextInput();
		}
		else
		{
			if (selectedEntriesID == 1)
			{
				std::regex regexNombres("(0?[0-9]|1?[0-9]|2[0-4])");
				if (!std::regex_match(affichHeure->texte, regexNombres))
				{
					affichHeure->redrawText("00", "ARCADE.TTF", 72, { 0,0,0 });
					AudioManager::Instance()->PlaySFX("wrong.mp3");
				}
			}
			if (selectedEntriesID == 2)
			{
				std::regex regexNombres("([0-5]?[0-9])");
				if (!std::regex_match(affichMinute->texte, regexNombres))
				{
					affichMinute->redrawText("00", "ARCADE.TTF", 72, { 0,0,0 });
					AudioManager::Instance()->PlaySFX("wrong.mp3");
				}
			}
			if (selectedEntriesID == 3)
			{
				std::regex regexNombres("[0-9]{1,3}");
				if (!std::regex_match(affichQuantite->texte, regexNombres))
				{
					affichQuantite->redrawText("0", "ARCADE.TTF", 72, { 0,0,0 });
					AudioManager::Instance()->PlaySFX("wrong.mp3");
				}
			}
			SDL_StopTextInput();
		}

		if (validerBut->isClicked(MousePos.x, MousePos.y))
		{
			mInfoList->addInfo(new Info(affichHeure->texte + "H" + affichMinute->texte,affichQuantite->texte));
			AudioManager::Instance()->PlaySFX("right.mp3");
		}

		if (mainScreenBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(0);
		}
	}
}

void AjouterScreen::checkInput()
{
	if (selectedEntriesID == 1)
	{
		text = affichHeure->texte;
		text += AppManager::Instance()->mEvents.text.text;
		text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
		if (text.size() <= maxTextSize)
		{
			affichHeure->redrawText(text.c_str(), "ARCADE.TTF", 72, { 0,0,0 });
		}
	}
	else if (selectedEntriesID == 2)
	{
		text = affichMinute->texte;
		text += AppManager::Instance()->mEvents.text.text;
		text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
		if (text.size() <= maxTextSize)
		{
			affichMinute->redrawText(text.c_str(), "ARCADE.TTF", 72, { 0,0,0 });
		}
	}
	else if (selectedEntriesID == 3)
	{
		text = affichQuantite->texte;
		text += AppManager::Instance()->mEvents.text.text;
		text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
		if (text.size() <= maxTextSize)
		{
			affichQuantite->redrawText(text.c_str(), "ARCADE.TTF", 72, { 0,0,0 });
		}
	}
}
