#include "courseList.h"
#pragma warning(disable : 4996)
courseList* courseList::sInstance = NULL;

courseList* courseList::Instance()
{
	if (sInstance == NULL) {
		sInstance = new courseList();
	}
	return sInstance;
}

void courseList::Release()
{
	delete sInstance;
	sInstance = NULL;
}

courseList::courseList()
{

}

courseList::~courseList()
{
	for (auto info : listeCourse)
	{
		delete info;
		info = NULL;
	}
	listeCourse.clear();
	data_.clear();
}

void courseList::addCourse(Course* course, int setInJson)
{
	if (setInJson)
	{
		course->mId = ++lastId;
		nlohmann::json newRecord =
		{
			{"nom",course->mNom},
			{"id",course->mId}
		};

		data_["course"].push_back(newRecord);
		std::ofstream file_out(filename);
		if (file_out.is_open()) {
			file_out << std::setw(4) << data_ << std::endl;
			file_out.close();
		}
	}
	listeCourse.push_back(course);
	course->Parent(this);
}

void courseList::Render()
{
	int nbAff = 0;
	int index = 0;
	for (auto info : listeCourse)
	{
		if (index >= startIndexRender)
		{
			info->Pos(Vector2(0, (float)50 * nbAff));
			nbAff++;
			info->Render();
		}
		index++;
		if (index - startIndexRender == 4)
		{
			return;
		}
	}
}

bool courseList::needToRenderNextArrow()
{
	return listeCourse.size() - startIndexRender > 4;
}

bool courseList::needToRenderPrevArrow()
{
	return startIndexRender >= 4;
}

void courseList::setStartIndexNextPage()
{
	if (!needToRenderNextArrow()) return;
	startIndexRender += 4;
	if (startIndexRender > listeCourse.size())
	{
		startIndexRender = listeCourse.size() - 4;
	}
}

void courseList::setStartIndexPrevPage()
{
	if (!needToRenderPrevArrow()) return;
	startIndexRender -= 4;
	if (startIndexRender < 0)
	{
		startIndexRender = 0;
	}
}

void courseList::recupererInfos()
{
	std::ifstream file(filename);
	if (file.is_open()) {
		file >> data_;
		file.close();
	}
	else
	{
		return;
	}

	for (const auto& record : data_["course"])
	{
		addCourse(new Course(record["nom"],record["id"]), 0);
		if (record["id"] > lastId)
		{
			lastId = record["id"];
		}
	}
}

void courseList::deleteCourse(int id)
{
	for (auto info : listeCourse)
	{
		if (info->mId == id)
		{
			delete info;
			listeCourse.remove(info);
			break;
		}
	}

	auto it = data_["course"].begin();
	for (; it != data_["course"].end(); ++it) 
	{
		if (it->at("id") == id)break;
	}
	if (it != data_["course"].end()) data_["course"].erase(it);

	std::ofstream file_out(filename);
	if (file_out.is_open()) {
		file_out << std::setw(4) << data_ << std::endl;
		file_out.close();
	}

	/*for (auto& record : data_["course"])
	{
		if (record["id"] == id)
		{
			data_.erase(record);
			std::ofstream file_out(filename);
			if (file_out.is_open()) {
				file_out << std::setw(4) << data_ << std::endl;
				file_out.close();
			}
			return;
		}
	}*/
}