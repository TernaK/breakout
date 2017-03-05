//
//  Game.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Game.hpp"

SpriteRenderer *gameRenderer;

Game::Game(GLint width, GLint height)
{
  this->state = GAME_MENU;
  this->width = width;
  this->height = height;
}

Game::~Game()
{
  delete gameRenderer;
}

void Game::init()
{
//  
//  // Load shaders
  ResourceManager::loadShader("resources/shaders/sprite_vshader.glsl", "resources/shaders/sprite_fshader.glsl", "", "sprite");
//  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
                                    static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("sprite").use().setInteger("image", 0);
  ResourceManager::getShader("sprite").setMatrix4("projection", projection);
//  // Set render-specific controls
//  gameRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
//  // Load textures
//  ResourceManager::loadTexture("resources/textures/awesomeface.png", GL_TRUE, "face");
  
  
  // Load textures
  ResourceManager::loadTexture("resources/textures/background.jpg", GL_FALSE, "background");
  ResourceManager::loadTexture("resources/textures/face.png", GL_TRUE, "face");
  ResourceManager::loadTexture("resources/textures/block.png", GL_FALSE, "block");
  ResourceManager::loadTexture("resources/textures/block_solid.png", GL_FALSE, "block_solid");
  // Load levels
  GameLevel one; one.load("resources/levels/level0", this->width, this->height * 0.5);
  GameLevel two; two.load("resources/levels/level1", this->width, this->height * 0.5);
  GameLevel three; three.load("resources/levels/level2", this->width, this->height * 0.5);
  GameLevel four; four.load("resources/levels/level3", this->width, this->height * 0.5);
  this->levels.push_back(one);
  this->levels.push_back(two);
  this->levels.push_back(three);
  this->levels.push_back(four);
  this->level = 1;
  
  gameRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::render()
{
  if(this->state == GAME_ACTIVE)
  {
    // Draw background
    gameRenderer->draw(ResourceManager::getTexture("background"),
                       glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
    // Draw level
    this->levels[this->level].draw(*gameRenderer);
  }
//  this->levels[level].draw(SpriteRenderer &renderer)
//  Renderer->draw(ResourceManager::getTexture("face"),
//                 glm::vec2(200, 200),
//                 glm::vec2(300, 400),
//                 45.0f,
//                 glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::processInput(GLfloat dt)
{
  
}

void Game::update(GLfloat dt)
{
  
}
