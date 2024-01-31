#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "AppEntity.h"
#include "AssetManager.h"
#include <functional>

class Texture : public AppEntity
{
protected :

	SDL_Texture* mTex;

	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

	std::function<void()> onClickAction;
public:
	std::string texte;

public :
	Texture(std::string filename);
	Texture(std::string filename,int x,int y,int w,int h);
	Texture(std::string text,std::string fontpath,int size, SDL_Color color);
	~Texture();

	bool isClicked(float x, float y) const;
	void setOnClick(std::function<void()> onClick);
	void onClick();

	void redrawText(std::string text,std::string fontpath, int size, SDL_Color color);

	SDL_Texture* getSDLTexture();

	virtual void Render();
};


#endif

