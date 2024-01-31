#ifndef _INFOLIST_H
#define _INFOLIST_H

#include <list>
#include <fstream>
#include <filesystem>
#include "Info.h"
#include <nlohmann/json.hpp>

class infoList : public AppEntity
{

private:
	static infoList* sInstance;
	nlohmann::json data_;	
	int lastId;
	int startIndexRender = 0;
public:
	std::string filename;
	std::list<Info*> listeInfo;	
public: 
	static infoList* Instance();
	static void Release();

	void addInfo(Info* info,int setInJson = 1);
	void Render();

	bool needToRenderNextArrow();
	bool needToRenderPrevArrow();
	void setStartIndexNextPage();
	void setStartIndexPrevPage();

	void recupererInfos();
	void resetInfo(int id);

private:
	infoList();
	~infoList();
	
};

#endif

