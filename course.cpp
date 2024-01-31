#include "course.h"

Course::Course(std::string nom, int id)
{
	if (id != -1)
	{
		mId = id;
	}
	mNom = nom;
	mainTex = new Texture(nom, "ARCADE.TTF", 40, { 0,0,0 });
	mainTex->Parent(this);
	deleteTex = new Texture("X", "ARCADE.TTF", 40, { 0,0,0 });
	deleteTex->Parent(mainTex);
	deleteTex->Pos(Vector2(400, 0));
}

Course::~Course()
{
	delete mainTex;
	mainTex = NULL;
	delete deleteTex;
	deleteTex = NULL;
}

void Course::Render()
{
	mainTex->Render();
	deleteTex->Render();
}