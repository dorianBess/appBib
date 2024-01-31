#ifndef _APPMANAGER_H
#define _APPMANAGER_H


#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Screen.h"
#include "MainScreen.h"
#include <list>
#include "AjouterScreen.h"
#include "ConsulterScreen.h"
#include "CourseScreen.h"
#include "courseList.h"
#include "RappelScreen.h"
#include <ctime>


class AppManager
{
private: 

	static AppManager* sInstance;

	const int FRAME_RATE = 120;

	bool mQuit;
	Graphics* mGraphics;
	AssetManager* mAssetMgr;
	InputManager* mInputMgr;
	AudioManager* mAudioMgr;
	infoList* mInfoList;
	courseList* mCourseList;

	std::map<int,Screen*> mScreens;

	MainScreen* mMainScreen;
	AjouterScreen* mAjouterScreen;
	ConsulterScreen* mConsulterScreen;
	CourseScreen* mCourseScreen;
	RappelScreen* mRappelScreen;

	bool showRappel;
	bool rappelThrow;

	Timer* mTimer;


public:
	static int typeScreen;
	SDL_Event mEvents;
	std::string jsonFilename;
	std::string heureRappel;
public :

	static AppManager* Instance();
	static void Release();
	static void changeTypeScreen(int type);

	void Run();

private:

	AppManager();
	~AppManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();
};

#endif // !_APPMANAGER_H

