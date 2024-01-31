#ifndef _COURSELIST_H
#define _COURSELIST_H

#include <list>
#include <fstream>
#include <filesystem>
#include "Course.h"
#include <nlohmann/json.hpp>

class courseList : public AppEntity
{

private:
	static courseList* sInstance;
	nlohmann::json data_;
	int lastId = 0;
	int startIndexRender = 0;
public:
	std::string filename;
	std::list<Course*> listeCourse;
public:
	static courseList* Instance();
	static void Release();

	void addCourse(Course* nom, int setInJson = 1);
	void Render();

	bool needToRenderNextArrow();
	bool needToRenderPrevArrow();
	void setStartIndexNextPage();
	void setStartIndexPrevPage();

	void recupererInfos();
	void deleteCourse(int id);

	courseList();
	~courseList();
};

#endif

