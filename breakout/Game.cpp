//
//  Game.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Game.hpp"

SpriteRenderer *Renderer;

Game::Game(GLint width, GLint height)
{
  this->state = GAME_MENU;
  this->width = width;
  this->height = height;
}

Game::~Game()
{
  
}

void Game::init()
{
  
  // Load shaders
  ResourceManager::loadShader("resources/shaders/sprite_vshader.glsl", "resources/shaders/sprite_fshader.glsl", "", "sprite");
  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
                                    static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("sprite").use().setInteger("image", 0);
  ResourceManager::getShader("sprite").setMatrix4("projection", projection);
  // Set render-specific controls
  Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
  // Load textures
  ResourceManager::loadTexture("resources/textures/awesomeface.png", GL_TRUE, "face");
}

void Game::render()
{
  Renderer->draw(ResourceManager::getTexture("face"),
                 glm::vec2(200, 200),
                 glm::vec2(300, 400),
                 45.0f,
                 glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::processInput(GLfloat dt)
{
  
}

void Game::update(GLfloat dt)
{
  
}
