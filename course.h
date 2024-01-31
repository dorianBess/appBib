#ifndef _COURSE_H
#define _COURSE_H

#include "Texture.h"

class Course : public AppEntity
{
public:
	Texture* mainTex;
	Texture* deleteTex;
	int mId;
	std::string mNom;
public:
	Course(std::string nom, int id = -1);
	~Course();
	void Render();
};

#endif

