#include "Info.h"

Info::Info(std::string heure, std::string quantite,std::string date,int id)
{
	if (date == "")
	{
		//auto now = std::chrono::system_clock::now();
		//std::string s = std::format("{:%d/%m}", now);
		// Récupérer le temps actuel
		std::time_t currentTime;
		time(&currentTime);

		// Convertir le temps en une structure tm (temps local) en utilisant localtime_s
		std::tm localTime;
		if (localtime_s(&localTime, &currentTime) == 0) {
			char timeString[6];
			std::string s = "";
			snprintf(timeString, sizeof(timeString), "%02d/%02d", localTime.tm_mday, localTime.tm_mon +1);
			s = timeString;
			mDate = s;
		}	
	}
	else
	{
		mDate = date;
	}
	
	mHeure = heure;
	mQuantite = quantite;
	if (id != -1)
	{
		mId = id;
	}
	mainBut = new Texture(mDate + " | " + heure + " | " + quantite + "G", "ARCADE.TTF", 40, {0,0,0});
	//mainBut->Pos(Vector2(300, 200));
	mainBut->Parent(this);
	resetQBut = new Texture("Reset", "ARCADE.TTF", 40, { 0,0,0 });
	resetQBut->Parent(mainBut);
	resetQBut->Pos(Vector2(400, 0));
}

Info::~Info()
{
	delete mainBut;
	mainBut = NULL;
	delete resetQBut;
	resetQBut = NULL;
}

void Info::Render()
{
	mainBut->Render();
	resetQBut->Render();
}

void Info::Reset() 
{
	mQuantite = "0";
	mainBut->redrawText(mDate + " | " + mHeure + " | " + mQuantite + "G", "ARCADE.TTF", 40, { 0,0,0 });
}
