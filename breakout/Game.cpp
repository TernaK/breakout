//
//  Game.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Game.hpp"

SpriteRenderer *GameRenderer;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject      *Player;

Game::Game(GLint width, GLint height)
{
  this->state = GAME_MENU;
  this->width = width;
  this->height = height;
}

Game::~Game()
{
  delete GameRenderer;
}

void Game::init()
{
  // Load shaders
  ResourceManager::loadShader("resources/shaders/sprite_vshader.glsl", "resources/shaders/sprite_fshader.glsl", "", "sprite");
  
  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f,
                                    static_cast<GLfloat>(this->width),
                                    static_cast<GLfloat>(this->height),
                                    0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("sprite").use().setInteger("image", 0);
  ResourceManager::getShader("sprite").setMatrix4("projection", projection);
  
  // Load textures
  ResourceManager::loadTexture("resources/textures/background.jpg", GL_FALSE, "background");
  ResourceManager::loadTexture("resources/textures/face.png", GL_TRUE, "face");
  ResourceManager::loadTexture("resources/textures/block.png", GL_FALSE, "block");
  ResourceManager::loadTexture("resources/textures/block_solid.png", GL_FALSE, "block_solid");
  ResourceManager::loadTexture("resources/textures/paddle.png", GL_TRUE, "paddle");
  
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
  
  /* player */
  glm::vec2 playerPos = glm::vec2(this->width / 2 - PLAYER_SIZE.x / 2,
                                  this->height - PLAYER_SIZE.y);
  Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
  
  GameRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::render()
{
  if(this->state == GAME_ACTIVE)
  {
    // Draw background
    GameRenderer->draw(ResourceManager::getTexture("background"),
                       glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
    // Draw level
    this->levels[this->level].draw(*GameRenderer);
    
    //draw player
    Player->draw(*GameRenderer);
  }
}

void Game::processInput(GLfloat dt)
{
  if (this->state == GAME_ACTIVE)
  {
    GLfloat velocity = PLAYER_VELOCITY * dt;
    // Move playerboard
    if (this->keys[GLFW_KEY_A])
    {
      if (Player->position.x >= 0)
        Player->position.x -= velocity;
    }
    if (this->keys[GLFW_KEY_D])
    {
      if (Player->position.x <= this->width - Player->size.x)
        Player->position.x += velocity;
    }
  }
}

void Game::update(GLfloat dt)
{
  
}
