#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include "AppManager.h"

int main(int argc, char** argv)
{
    AppManager* app = AppManager::Instance(); 

    app->Run();

    AppManager::Release();
    app = NULL;

    return 0;
}