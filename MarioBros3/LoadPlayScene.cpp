#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"

#include "rapidjson/document.h"

using namespace rapidjson;

void CPlayScene::CreatGrid(string filePath, string fileName)
{
	string fullPath = filePath + "/" + fileName;
	TiXmlDocument doc(fullPath.c_str());



	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* node = root->FirstChildElement("properties");
		string name;
		int CellHeight, CellWidth, TotalColumn, TotalRow;
		for (TiXmlElement* TMX = node->FirstChildElement("property"); TMX != NULL; TMX = TMX->NextSiblingElement("property"))
		{
			name = TMX->Attribute("name");
			if (name == "CellHeight") TMX->QueryIntAttribute("value", &CellHeight);
			if (name == "CellWidth") TMX->QueryIntAttribute("value", &CellWidth);
			if (name == "TotalColumn") TMX->QueryIntAttribute("value", &TotalColumn);
			if (name == "TotalRow") TMX->QueryIntAttribute("value", &TotalRow);
		}
		this->grid = new Grid(TotalColumn, TotalRow, CellWidth, CellHeight);
	}
}

void CPlayScene::newObject(LPGAMEOBJECT object, string stringGrid)
{
	if(stringGrid== "")
		addobjects.push_back(object);
	else
	{
		DebugOut(L"[ADD Cell] %s \n", ToLPCWSTR(stringGrid));
		Document document;
		document.Parse(stringGrid.c_str());
		for (auto& v : document.GetArray())
		{

			auto cr = v.GetObject();
			int x = cr["x"].GetInt();
			int y = cr["y"].GetInt();

			grid->AddObject(object, x, y);
		}
		document.Clear();
	}
}