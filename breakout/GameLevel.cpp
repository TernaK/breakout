//
//  GameLevel.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "GameLevel.hpp"
using namespace std;

// Loads level from file
void GameLevel::load(std::string levelFile, GLuint levelWidth, GLuint levelHeight)
{
  // Clear old data
  this->bricks.clear();
  // Load from file
  GLuint tileCode;
  GameLevel level;
  std::string line;
  std::ifstream fstream(levelFile);
  std::vector<std::vector<GLuint>> tileData;
  if (fstream)
  {
    while (std::getline(fstream, line)) // Read each line from level file
    {
      std::istringstream sstream(line);
      std::vector<GLuint> row;
      while (sstream >> tileCode) // Read each word seperated by spaces
        row.push_back(tileCode);
      tileData.push_back(row);
    }
    if (tileData.size() > 0)
      this->init(tileData, levelWidth, levelHeight);
  }
}

// Render level
void GameLevel::draw(SpriteRenderer &renderer)
{
  for(auto brick: bricks){
    if(!brick.destroyed)
      brick.draw(renderer);
  }
}
// Check if the level is completed (all non-solid tiles are destroyed)
GLboolean GameLevel::isCompleted()
{
  for(auto brick: this->bricks)
    if(!brick.isSolid && !brick.destroyed)
      return GL_FALSE;
    
  return GL_TRUE;
}

// Initialize level from tile data
void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
  // Calculate dimensions
  GLuint height = (GLuint)tileData.size();
  GLuint width = (GLuint)tileData[0].size();
  GLfloat unit_width = levelWidth / static_cast<GLfloat>(width);
  GLfloat unit_height = levelHeight / height;
  // Initialize level tiles based on tileData
  for (GLuint y = 0; y < height; ++y)
  {
    for (GLuint x = 0; x < width; ++x)
    {
      // Check block type from level data (2D level array)
      if (tileData[y][x] == 1) // Solid
      {
        glm::vec2 pos(unit_width * x, unit_height * y);
        glm::vec2 size(unit_width, unit_height);
        GameObject obj(pos, size,
                       ResourceManager::getTexture("block_solid"),
                       glm::vec3(0.8f, 0.8f, 0.7f)
                       );
        obj.isSolid = GL_TRUE;
        this->bricks.push_back(obj);
      }
      else if (tileData[y][x] > 1)
      {
        glm::vec3 color = glm::vec3(1.0f); // original: white
        if (tileData[y][x] == 2)
          color = glm::vec3(0.2f, 0.6f, 1.0f);
        else if (tileData[y][x] == 3)
          color = glm::vec3(0.0f, 0.7f, 0.0f);
        else if (tileData[y][x] == 4)
          color = glm::vec3(0.8f, 0.8f, 0.4f);
        else if (tileData[y][x] == 5)
          color = glm::vec3(1.0f, 0.5f, 0.0f);
        
        glm::vec2 pos(unit_width * x, unit_height * y);
        glm::vec2 size(unit_width, unit_height);
        this->bricks.push_back( GameObject(pos, size, ResourceManager::getTexture("block"), color) );
      }
    }
  }
}
