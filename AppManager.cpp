#include "AppManager.h"
#include "InputManager.h"
#include "MainScreen.h"
#include <regex>

AppManager* AppManager::sInstance = NULL;
int AppManager::typeScreen = 0;

AppManager* AppManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new AppManager();
	}
	return sInstance;
}

void AppManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

AppManager::AppManager() {

	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized()) {
		mQuit = true;
	}

	mAssetMgr = AssetManager::Instance();

	mInputMgr = InputManager::Instance();

	mAudioMgr = AudioManager::Instance();

	mInfoList = infoList::Instance();

	mCourseList = courseList::Instance();

	mMainScreen = new MainScreen();
	mScreens[0] = mMainScreen;

	mConsulterScreen = new ConsulterScreen();
	mScreens[1] = mConsulterScreen;

	mAjouterScreen = new AjouterScreen();
	mScreens[2] = mAjouterScreen;

	mCourseScreen = new CourseScreen();
	mScreens[3] = mCourseScreen;

	mRappelScreen = new RappelScreen();
	mScreens[4] = mRappelScreen;

	typeScreen = 0;
	showRappel = false;

	mTimer = Timer::Instance();

	jsonFilename = SDL_GetBasePath();
	jsonFilename.append("info.json");
	if (!std::filesystem::exists(jsonFilename))
	{
		std::ofstream create_file(jsonFilename);
		if (!create_file.is_open()) {
			printf("Erreur lors de la création du fichier JSON.");
		}
		else
		{
			// Initialiser le fichier avec un objet JSON vide
			std::string start = R"({"enregistrements":[],"course":[]})";
			create_file << start;
			create_file.close();
		}
	}
	mInfoList->filename = jsonFilename;
	mInfoList->recupererInfos();
	mCourseList->filename = jsonFilename;
	mCourseList->recupererInfos();
	mRappelScreen->filename = jsonFilename;
}

AppManager::~AppManager() {

	AudioManager::Release();
	mAudioMgr = NULL;

	AssetManager::Release();
	mAssetMgr = NULL;

	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputMgr = NULL;

	infoList::Release();
	mInfoList = NULL;

	courseList::Release();
	mCourseList = NULL;

	Timer::Release();
	mTimer = NULL;

	for (auto screen : mScreens)
	{
		delete screen.second;
		screen.second = NULL;
	}

	mScreens.clear();
}

void AppManager::EarlyUpdate()
{
	mTimer->Reset();
	mInputMgr->Update();
}

void AppManager::Update()
{
	// Récupérer le temps actuel
	std::time_t currentTime;
	time(&currentTime);
	std::string s = "";
	// Convertir le temps en une structure tm (temps local) en utilisant localtime_s
	std::tm localTime;
	if (localtime_s(&localTime, &currentTime) == 0) {
		char timeString[6];		
		snprintf(timeString, sizeof(timeString), "%02d/%02d", localTime.tm_hour, localTime.tm_min);
		s = timeString;
	}

	
	if (heureRappel != "" && s == heureRappel)
	{
		if(!rappelThrow)
		showRappel = true;
	}
	else 
	{
		showRappel = false;
		rappelThrow = false;
	}
	if (showRappel)
	{
		mAudioMgr->PlaySFX("harp.mp3");
		showRappel = false;
		rappelThrow = true;
	}

	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
	}

	mScreens[typeScreen]->update();
	
	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		Vector2 MousePos = InputManager::Instance()->MousePos();
	}
}

void AppManager::Render()
{
	mGraphics->ClearBackBuffer();
	mScreens[typeScreen]->Render();
	mGraphics->Render();
}

void AppManager::changeTypeScreen(int type)
{
	typeScreen = type;
}

void AppManager::LateUpdate()
{
	mInputMgr->UpdatePrevInput();
}

void AppManager::Run() {

	while (!mQuit) {

		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {

			if (mEvents.type == SDL_QUIT) {
				mQuit = true;
			}

			if (mEvents.type == SDL_TEXTINPUT)
			{
				if (typeScreen == 2) 
				{
					mAjouterScreen->checkInput();
				}
				if (typeScreen == 3)
				{
					mCourseScreen->checkInput();
				}
				if (typeScreen == 4)
				{
					mRappelScreen->checkInput();
				}
			}
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}


	}
}
