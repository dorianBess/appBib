#ifndef _COURSESCREEN_H
#define _COURSESCREEN_H

#include "Screen.h"
#include <list>
#include "Texture.h"
#include "InputManager.h"
#include "courseList.h"

class CourseScreen : public Screen
{
private:
	
	Texture* itemInput;
	Texture* validerItem;
	Texture* mainScreenBut;

	Texture* nextPage;
	Texture* prevPage;

	InputManager* mInputMgr;

	std::string text;
public:
	courseList* course;

	void Render() const override;
	void update() override;
	void checkInput();
public:

	CourseScreen();
	~CourseScreen();
};

#endif


