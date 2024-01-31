#include "MainScreen.h"
#include "AppManager.h"

MainScreen::MainScreen()
{
	consulterBut = new Texture("Consulter", "ARCADE.TTF", 72, { 0,0,0 });
	consulterBut->Pos(Vector2(400, 100));
	ajouterBut = new Texture("Ajouter heure", "ARCADE.TTF", 72, { 0,0,0 });
	ajouterBut->Pos(Vector2(400, 225));
	rappelBut = new Texture("Creer rappel", "ARCADE.TTF", 72, { 0,0,0 });
	rappelBut->Pos(Vector2(400, 350));
	listeBut = new Texture("Liste course", "ARCADE.TTF", 72, { 0,0,0 });
	listeBut->Pos(Vector2(400, 475));

	mInputMgr = InputManager::Instance();
}

MainScreen::~MainScreen()
{
	delete consulterBut;
	consulterBut = NULL;
	delete ajouterBut;
	ajouterBut = NULL;
	delete rappelBut;
	rappelBut = NULL;
	delete listeBut;
	listeBut = NULL;
}

void MainScreen::Render() const
{
	consulterBut->Render();
	ajouterBut->Render();
	rappelBut->Render();
	listeBut->Render();
}

void MainScreen::update()
{
	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
		if (ajouterBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(2);
		}

		if (consulterBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(1);
		}

		if (listeBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(3);
		}

		if (rappelBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(4);
		}
	}
}
