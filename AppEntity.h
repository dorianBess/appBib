#ifndef _APPENTITY_H
#define _APPENTITY_H
#include "MathHelper.h"

class AppEntity
{
	
public:
	enum SPACE{local = 0, world = 1};

private:
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	bool mActive;
	AppEntity* mParent;

public:

	AppEntity(float x = 0.0f, float y = 0.0f);
	~AppEntity();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = world);

	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(AppEntity* parent);
	AppEntity* Parent();

	void Translate(Vector2 vec);
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();
};

#endif

