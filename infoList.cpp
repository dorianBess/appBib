#include "infoList.h"
#pragma warning(disable : 4996)
infoList* infoList::sInstance = NULL;

infoList* infoList::Instance()
{
	if (sInstance == NULL) {
		sInstance = new infoList();
	}
	return sInstance;
}

void infoList::Release()
{
	delete sInstance;
	sInstance = NULL;
}

infoList::infoList()
{
	//filename = SDL_GetBasePath();
	//filename.append("test.json");
	//if (!std::filesystem::exists(filename))
	//{
	//	std::ofstream create_file(filename);
	//	if (!create_file.is_open()) {
	//		printf("Erreur lors de la création du fichier JSON.");
	//	}
	//	else
	//	{

	//		// Initialiser le fichier avec un objet JSON vide
	//		std::string start = R"({"enregistrements":[],"course":[]})";
	//		create_file << start;
	//		create_file.close();
	//		std::ifstream file(filename);
	//		data_ = nlohmann::json::parse(file);
	//		data_.parse(start);


	//	}
	//}
	//recupererInfos();
}

infoList::~infoList()
{
	for (auto info : listeInfo)
	{
		delete info;
		info = NULL;
	}
	listeInfo.clear();
	data_.clear();
}

void infoList::addInfo(Info* info, int setInJson)
{
	if (setInJson)
	{
		info->mId = ++lastId;
		nlohmann::json newRecord =
		{
			{"date",info->mDate},
			{"heure",info->mHeure},
			{"chiffre", info->mQuantite},
			{"id",info->mId}
		};

		data_["enregistrements"].push_back(newRecord);
		std::ofstream file_out(filename);
		if (file_out.is_open()) {
			file_out << std::setw(4) << data_ << std::endl;
			file_out.close();
		}
	}
	listeInfo.push_back(info);
	info->Parent(this);
}

void infoList::Render()
{
	int nbAff = 0;
	int index = 0;
	for (auto info : listeInfo)
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

bool infoList::needToRenderNextArrow()
{
	return listeInfo.size() - startIndexRender > 4;
}

bool infoList::needToRenderPrevArrow()
{
	return startIndexRender >= 4;
}

void infoList::setStartIndexNextPage()
{
	if (!needToRenderNextArrow()) return;
	startIndexRender += 4;
	if (startIndexRender > listeInfo.size())
	{
		startIndexRender = listeInfo.size() - 4;
	}
}

void infoList::setStartIndexPrevPage()
{
	if (!needToRenderPrevArrow()) return;
	startIndexRender -= 4;
	if (startIndexRender < 0)
	{
		startIndexRender = 0;
	}
}

void infoList::recupererInfos()
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

	for (const auto& record : data_["enregistrements"])
	{
		addInfo(new Info(record["heure"], record["chiffre"],record["date"],record["id"]), 0);
		if (record["id"] > lastId)
		{
			lastId = record["id"];
		}
	}
}

void infoList::resetInfo(int id)
{
	for (auto info : listeInfo)
	{
		if (info->mId == id)
		{
			info->Reset();
			break;
		}
	}
	for (auto& record : data_["enregistrements"])
	{
		if (record["id"] == id)
		{			
			record["chiffre"] = "0";
			std::ofstream file_out(filename);
			if (file_out.is_open()) {
				file_out << std::setw(4) << data_ << std::endl;
				file_out.close();
			}
			return;
		}
	}
}


