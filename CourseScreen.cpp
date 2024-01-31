#include "CourseScreen.h"
#include "AppManager.h"

CourseScreen::CourseScreen()
{
	itemInput = new Texture("Entrez ici", "ARCADE.TTF", 72, { 0,0,0 });
	itemInput->Pos(Vector2(200, 500));

	validerItem = new Texture("Valider", "ARCADE.TTF", 72, { 0,0,0 });
	validerItem->Pos(Vector2(600, 500));

	mainScreenBut = new Texture("Main screen", "ARCADE.TTF", 72, { 0,0,0 });
	mainScreenBut->Pos(Vector2(200, 50));

	mInputMgr = InputManager::Instance();

	course = courseList::Instance();
	course->Pos(Vector2(300, 200));

	nextPage = new Texture(">", "ARCADE.TTF", 72, { 0,0,0 });
	prevPage = new Texture("<", "ARCADE.TTF", 72, { 0,0,0 });

	nextPage->Pos(Vector2(700, 400));
	prevPage->Pos(Vector2(600, 400));

}

CourseScreen::~CourseScreen()
{
	delete itemInput;
	itemInput = NULL;

	delete validerItem;
	validerItem = NULL;

	delete mainScreenBut;
	mainScreenBut = NULL;

	delete nextPage;
	nextPage = NULL;

	delete prevPage;
	prevPage = NULL;
}

void CourseScreen::Render() const
{
	itemInput->Render();
	validerItem->Render();
	mainScreenBut->Render();
	course->Render();
	if (course->needToRenderNextArrow())
		nextPage->Render();
	if (course->needToRenderPrevArrow())
		prevPage->Render();
}

void CourseScreen::update()
{
	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
		if (itemInput->isClicked(MousePos.x, MousePos.y))
		{
			itemInput->redrawText(" ", "ARCADE.TTF", 72, { 0,0,0 });
			SDL_StartTextInput();
		}
		else
		{
			SDL_StopTextInput();
		}

		if (validerItem->isClicked(MousePos.x, MousePos.y))
		{
			course->addCourse(new Course(text));
			itemInput->redrawText("Entrez ici", "ARCADE.TTF", 72, { 0,0,0 });
			AudioManager::Instance()->PlaySFX("right.mp3");
		}

		if (mainScreenBut->isClicked(MousePos.x, MousePos.y))
		{
			AppManager::Instance()->changeTypeScreen(0);
		}

		if (nextPage->isClicked(MousePos.x, MousePos.y))
		{
			course->setStartIndexNextPage();
		}

		if (prevPage->isClicked(MousePos.x, MousePos.y))
		{
			course->setStartIndexPrevPage();
		}

		for (auto info : course->listeCourse)
		{
			if (info->deleteTex->isClicked(MousePos.x, MousePos.y))
			{
				courseList::Instance()->deleteCourse(info->mId);
				AudioManager::Instance()->PlaySFX("right.mp3");
				return;
			}
		}
	}
}

void CourseScreen::checkInput()
{
	text = itemInput->texte;
	text += AppManager::Instance()->mEvents.text.text;	
	text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());
	itemInput->redrawText(text.c_str(), "ARCADE.TTF", 72, { 0,0,0 });
}
