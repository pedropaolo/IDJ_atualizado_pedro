
#include "TileMap.h"

#include <fstream>
TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)
    : Component(associated) {
  Load(move(file));
    SetTileSet(tileSet);



}
void TileMap::Load(std::string file) {

  std::ifstream fileContent(file, std::ifstream::in);
  if (!fileContent.is_open()) {
    exit(EXIT_FAILURE); // TODO exits, but how does it explain it?
  }

  std::string lineString;

  int indexValue = 0;
  int nextNum = 0;
  /* Getting the first line, which will always be the sizes of the map. */
  getline(fileContent, lineString);
  for (unsigned int i = 0; i < lineString.size(); i++) {
    if (lineString.at(i) == ',') {
      switch (nextNum) {
        case 0:
          TileMap::mapWidth = indexValue;
          break;
        case 1:
          TileMap::mapHeight = indexValue;
          break;
        case 2:
          TileMap::mapDepth = indexValue;
          break;
      }
      indexValue = 0;
      nextNum++;
    } else {
      indexValue *= 10;
      indexValue += lineString.at(i) - '0';
    }
  }

  /* Getting the rest of the file, where the actual map really is. */
  int tileValue = 0;
  while (getline(fileContent, lineString)) {
    for (unsigned int i = 0; i < lineString.size(); i++) {
      if (lineString.at(i) >= '0' && lineString.at(i) <= '9') {
        tileValue *= 10;
        tileValue += lineString.at(i) - '0';
      } else if (lineString.at(i) == ',') {
        /* Storing it in the vector minus one. */
        TileMap::tileMatrix.push_back(tileValue - 1);
        tileValue = 0;
      } else {
        tileValue = 0;
      }
    }
  }

  fileContent.close();

	std::ifstream fileReader("map/tileMap.txt", std::ios::in);
	if(fileReader.good()) {
		int x;
		char s;
		fileReader >> mapWidth >> s >> mapHeight >> s >> mapDepth >> s;
		for(int k = 0; k < mapDepth; k++) {
			for(int j = 0; j < mapHeight; j++) {
				for(int i = 0; i < mapWidth; i++) {
					fileReader >> x >> s;
					tileMatrix.emplace_back(x-1);
				}
			}
		}
	}else{
		printf("Unable to read %s", file.c_str());
	}
	fileReader.close();



 
}
void TileMap::SetTileSet(TileSet* tileSet) {
   this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {

  /* Calculating the coordinates into the vector. */
  return TileMap::tileMatrix.at(x +
                                (y * TileMap::mapWidth) +
                                (z * TileMap::mapWidth * TileMap::mapHeight));
}

void TileMap::Render() {

  for (unsigned int i = 0; i < TileMap::mapDepth; i++) {
  /* Rendering each layer of the map. */
  for (int i = TileMap::mapDepth - 1; i >= 0; i--) {
    TileMap::RenderLayer(i,
                         TileMap::tileSet->GetTileWidth(),
                         TileMap::tileSet->GetTileHeight());
  }
}}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

  /* Rendering each tile of the layer. */
  for (int j = 0; j < TileMap::mapHeight; j++) {
    for (int i = 0; i < TileMap::mapWidth; i++) {
      TileMap::tileSet->RenderTile(TileMap::At(i, j, layer),
                                   i * TileMap::tileSet->GetTileWidth(),
                                   j * TileMap::tileSet->GetTileHeight());
    }
  }
}
int TileMap::GetWidth() {
  return TileMap::mapWidth;
}
int TileMap::GetHeight() {
  return TileMap::mapHeight;
}
int TileMap::GetDepth() {
  return TileMap::mapDepth;
}
void TileMap::Update(float dt) {
}
bool TileMap::Is(std::string type) {
  if (type.compare("TileMap") == 0) {
    return true;
  }
  return false;
}