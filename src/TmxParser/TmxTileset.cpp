//-----------------------------------------------------------------------------
// TmxTileset.cpp
//
// Copyright (c) 2010-2012, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#include "../tinyxml/tinyxml.h"

#include "TmxMap.h"
#include "TmxTileset.h"
#include "TmxImage.h"
#include "TmxTile.h"

using std::vector;
using std::string;

namespace Tmx 
{
	Tileset::Tileset() 
		: first_gid(0)
		, name()
		, tile_width(0)
		, tile_height(0)
		, margin(0)
		, spacing(0)
		, image(NULL)
		, tiles()
		, has_error(false)
		, error_code(0)
		, error_text()
	{
	}

	Tileset::~Tileset() 
	{
		// Delete the image from memory if allocated.
		if (image) 
		{
			delete image;
			image = NULL;
		}
		
		// Iterate through all of the tiles in the set and delete each of them.
		vector< Tile* >::iterator tIter;
		for (tIter = tiles.begin(); tIter != tiles.end(); ++tIter) 
		{
			Tile *tile = (*tIter);
			
			if (tile) 
			{
				delete tile;
				tile = NULL;
			}
		}
	}

	void Tileset::Parse(const TiXmlNode *tilesetNode, const std::string &filePath) 
	{
		const TiXmlElement *tilesetElem = tilesetNode->ToElement();
		tilesetElem->Attribute("firstgid", &first_gid);
 		if (tilesetElem->Attribute("source"))
        {
			ParseTsxFile(filePath + tilesetElem->Attribute("source"));
        }
        else
        {
			ParseElement(tilesetElem);
        }
    }

	void Tileset::ParseElement(const TiXmlElement *tilesetElem)
	{
		// Read all the attributes into local variables.
		tilesetElem->Attribute("tilewidth", &tile_width);
		tilesetElem->Attribute("tileheight", &tile_height);
		tilesetElem->Attribute("margin", &margin);
		tilesetElem->Attribute("spacing", &spacing);

        char const *rawName = tilesetElem->Attribute("name");
		name = (rawName == NULL) ? "" : rawName;

		// Parse the image.
		const TiXmlNode *imageNode = tilesetElem->FirstChild("image");
		
		if (imageNode) 
		{
			image = new Image();
			image->Parse(imageNode);
		}

		// Iterate through all of the tile elements and parse each.
		const TiXmlNode *tileNode = tilesetElem->FirstChild("tile");
		while (tileNode)
		{
			// Allocate a new tile and parse it.
			Tile *tile = new Tile();
			tile->Parse(tileNode);

			// Add the tile to the collection.
			tiles.push_back(tile);

			tileNode = tilesetElem->IterateChildren("tile", tileNode);
		}
	}

	void Tileset::ParseTsxFile(const std::string &fileName) 
	{
        // Most of this is copy-pasted from Map::ParseFile()
		char* fileText;
		int fileSize;

		// Open the file for reading.
		FILE *file = fopen(fileName.c_str(), "rb");

		// Check if the file could not be opened.
		if (!file) 
		{
			has_error = true;
			error_code = TMX_COULDNT_OPEN;
			error_text = "Could not open the file " + fileName;
			return;
		}
		
		// Find out the file size.
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		// Allocate memory for the file and read it into the memory.
		fileText = new char[fileSize];
		fread(fileText, 1, fileSize, file);

		fclose(file);

		// Copy the contents into a C++ string and delete it from memory.
		std::string text(fileText, fileText+fileSize);
		delete [] fileText;

		// Create a tiny xml document and use it to parse the text.
		TiXmlDocument doc;
		doc.Parse(text.c_str());
        if (doc.Error())
        {
			has_error = true;
			error_code = TMX_PARSING_ERROR;
			error_text = doc.ErrorDesc();
			return;
        }
        else
        {
            ParseElement(doc.FirstChild("tileset")->ToElement());
        }
	}
    
	const Tile *Tileset::GetTile(int index) const 
	{
		for (unsigned int i = 0; i < tiles.size(); ++i) 
		{
			if (tiles.at(i)->GetId() == index) 
			{
				return tiles.at(i);
			}
		}

		return NULL;
	}
};
