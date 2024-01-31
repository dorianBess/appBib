#include "ConsulterScreen.h"
#include "AppManager.h"

ConsulterScreen::ConsulterScreen()
{
	mainScreenBut = new Texture("Main screen", "ARCADE.TTF", 72, { 0,0,0 });
	mainScreenBut->Pos(Vector2(200, 50));

	mInputMgr = InputManager::Instance();

	infos = infoList::Instance();
	infos->Pos(Vector2(300, 200));

	nextPage = new Texture(">", "ARCADE.TTF", 72, { 0,0,0 });
	prevPage = new Texture("<", "ARCADE.TTF", 72, { 0,0,0 });

	nextPage->Pos(Vector2(700, 400));
	prevPage->Pos(Vector2(600, 400));
}

ConsulterScreen::~ConsulterScreen()
{
	delete mainScreenBut;
	mainScreenBut = NULL;

	delete nextPage;
	nextPage = NULL;

	delete prevPage;
	prevPage = NULL;
}

void ConsulterScreen::Render() const
{
	infos->Render();
	mainScreenBut->Render();

	if(infoList::Instance()->needToRenderNextArrow())
	nextPage->Render();
	if (infoList::Instance()->needToRenderPrevArrow())
	prevPage->Render();
}

void ConsulterScreen::update()
{
	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
		if (mainScreenBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(0);
		}

		for (auto info : infos->Instance()->listeInfo)
		{
			if (info->resetQBut->isClicked(MousePos.x, MousePos.y))
			{
				infoList::Instance()->resetInfo(info->mId);
				AudioManager::Instance()->PlaySFX("right.mp3");
			}
		}

		if (nextPage->isClicked(MousePos.x, MousePos.y))
		{
			infoList::Instance()->setStartIndexNextPage();
		}

		if (prevPage->isClicked(MousePos.x, MousePos.y))
		{
			infoList::Instance()->setStartIndexPrevPage();
		}
	}
}
