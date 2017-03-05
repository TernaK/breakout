//
//  Game.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <GL/glew.h>
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "GameLevel.hpp"
#include <GLFW/glfw3.h>

enum GameState {
  GAME_ACTIVE, GAME_MENU, GAME_END
};

class Game
{
public:
  /* constructors, destructor */
  Game(GLint width = 1280, GLint height = 720);
  ~Game();
  
  /* methods */
  void init();
  void render();
  void processInput(GLfloat dt);
  void update(GLfloat dt);
  
  /* members */
  
  GameState  state;
  GLboolean  keys[1024];
  GLuint	   width, height;
  
  std::vector<GameLevel> levels;
  GLuint                 level;
};

#endif /* Game_hpp */
