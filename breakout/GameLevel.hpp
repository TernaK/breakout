//
//  GameLevel.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef GameLevel_hpp
#define GameLevel_hpp

#include <vector>
#include "GameObject.hpp"
#include "ResourceManager.hpp"

class GameLevel
{
public:
  std::vector<GameObject> bricks;
  
  GameLevel() { }
  // Loads level from file
  void load(std::string levelFile, GLuint levelWidth, GLuint levelHeight);
  // Render level
  void draw(SpriteRenderer &renderer);
  // Check if the level is completed (all non-solid tiles are destroyed)
  GLboolean isCompleted();
private:
  // Initialize level from tile data
  void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif /* GameLevel_hpp */
