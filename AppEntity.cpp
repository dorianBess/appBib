#include "AppEntity.h"

AppEntity::AppEntity(float x, float y) {

	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;

	mActive = true;

	mParent = NULL;

	mScale = VEC2_ONE;
}

AppEntity::~AppEntity() {

	mParent = NULL;
}

void AppEntity::Pos(Vector2 pos) {

	mPos = pos;
}

Vector2 AppEntity::Pos(SPACE space) {

	if (space == local || mParent == NULL) {
		return mPos;
	}

	Vector2 parentScale = mParent->Scale(world);
	Vector2 rotPos = RotateVector(Vector2(mPos.x * parentScale.x,mPos.y * parentScale.y), mParent->Rotation(local));

	return mParent->Pos(world) + rotPos;
}

void AppEntity::Rotation(float r) {

	mRotation = r;

	if (mRotation > 360.0f) {
		mRotation -= 360.0f;
	}

	if (mRotation < 0) {
		mRotation += 360.0f;
	}
}

void AppEntity::Scale(Vector2 scale)
{
	mScale = scale;
}

Vector2 AppEntity::Scale(SPACE space) 
{
	if (space == local || mParent == NULL)
		return mScale;

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

float AppEntity::Rotation(SPACE space) {

	if (space == local || mParent == NULL) {
		return mRotation;
	}
	return mParent->Rotation(world) + mRotation;
}

void AppEntity::Active(bool active) {

	mActive = active;
}

bool AppEntity::Active() {

	return mActive;
}

void AppEntity::Parent(AppEntity* parent) {

	if (parent == NULL)
	{
		mPos = Pos(world);
		mRotation = Rotation(world);
		mScale = Scale(world);
	} 
	else
	{
		if (mParent != NULL) Parent(NULL);
		Vector2 parentScale = parent->Scale(world);
		mPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		mRotation -= parent->Rotation(world);

		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

AppEntity* AppEntity::Parent() {

	return mParent;
}

void AppEntity::Translate(Vector2 vec)
{
	mPos += vec;
}

void AppEntity::Rotate(float amount)
{
	mRotation += amount;
}

void AppEntity::Update() {

}

void AppEntity::Render() {

}

