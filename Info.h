#ifndef _INFO_H
#define _INFO_H

#include "Texture.h"
#include <chrono>

class Info : public AppEntity
{
public:
	Texture* mainBut;
	Texture* resetQBut;
	std::string mHeure;
	std::string mQuantite;
	std::string mDate;
	int mId;
public:
	Info(std::string heure, std::string quantite,std::string date = "",int id = -1);
	~Info();
	void Render();
	void Reset();
};

#endif

