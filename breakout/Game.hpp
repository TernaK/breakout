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
#include "BallObject.hpp"
#include "ParticleGenerator.hpp"
#include <GLFW/glfw3.h>

enum GameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_END
};

enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

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
  
  void resetLevel();
  void resetPlayer();
  
  /* members */
  
  GameState  state;
  GLboolean  keys[1024];
  GLuint	   width, height;
  
  std::vector<GameLevel> levels;
  GLuint                 level;
  
private:
  GLboolean checkCollision(GameObject &one, GameObject &two);
  Collision checkCollision(BallObject &one, GameObject &two);
  Direction vectorDirection(glm::vec2 target);
  void doCollisions();
};

#endif /* Game_hpp */
