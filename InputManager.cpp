#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance()
{
    if (sInstance == NULL) {
        sInstance = new InputManager();
    }
    return sInstance;
}

void InputManager::Release()
{
    delete sInstance;
    sInstance = NULL;
}

InputManager::~InputManager()
{
    delete[] mPreviousKeyboardState;
    mPreviousKeyboardState = NULL;
}

InputManager::InputManager()
{
    mKeyboardState = SDL_GetKeyboardState(&mKeyLenght);
    mPreviousKeyboardState = new Uint8[mKeyLenght];
    memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLenght);
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
    return mKeyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
    return !mPreviousKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
    return mPreviousKeyboardState[scanCode] && !mKeyboardState[scanCode];
}

Vector2 InputManager::MousePos()
{
    return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left :
		mask = SDL_BUTTON_LMASK;
        break;

    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case foraward:
        mask = SDL_BUTTON_X2MASK;
        break;
    }

    return (mMouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;

    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case foraward:
        mask = SDL_BUTTON_X2MASK;
        break;
    }

    return !(mPreviousMouseState & mask) && (mMouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case left:
        mask = SDL_BUTTON_LMASK;
        break;

    case right:
        mask = SDL_BUTTON_RMASK;
        break;
    case middle:
        mask = SDL_BUTTON_MMASK;
        break;
    case back:
        mask = SDL_BUTTON_X1MASK;
        break;
    case foraward:
        mask = SDL_BUTTON_X2MASK;
        break;
    }

    return (mPreviousMouseState & mask) && !(mMouseState & mask);
}

void InputManager::Update()
{
    mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePrevInput()
{
    memcpy(mPreviousKeyboardState, mKeyboardState, mKeyLenght);
    mPreviousMouseState = mMouseState;
}
