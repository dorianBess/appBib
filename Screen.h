#ifndef _SCREEN_H
#define _SCREEN_H

class Screen
{

private: 
	static Screen* sInstance;

public :
	virtual void Render() const = 0;
	virtual void update() = 0;
	virtual ~Screen() = default;
};

#endif

