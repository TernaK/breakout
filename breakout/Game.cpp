//
//  Game.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "Game.hpp"
#include "BallObject.hpp"

SpriteRenderer *GameRenderer;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject      *Player;

ParticleGenerator   *Particles;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;
BallObject     *Ball;

Game::Game(GLint width, GLint height)
{
  this->state = GAME_MENU;
  this->width = width;
  this->height = height;
}

Game::~Game()
{
  delete GameRenderer;
  delete Ball;
  delete Player;
  delete Particles;
}

void Game::init()
{
  // Load shaders
  ResourceManager::loadShader("resources/shaders/sprite_vshader.glsl",
                              "resources/shaders/sprite_fshader.glsl",
                              "", "sprite");
  ResourceManager::loadShader("resources/shaders/particle_vshader.glsl",
                              "resources/shaders/particle_fshader.glsl",
                              "", "particle");
  
  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f,
                                    static_cast<GLfloat>(this->width),
                                    static_cast<GLfloat>(this->height),
                                    0.0f, -1.0f, 1.0f);
  ResourceManager::getShader("sprite").use().setInteger("image", 0);
  ResourceManager::getShader("sprite").use().setMatrix4("projection", projection);
  ResourceManager::getShader("particle").use().setMatrix4("projection", projection);
  
  // Load textures
  ResourceManager::loadTexture("resources/textures/background.jpg", GL_FALSE, "background");
  ResourceManager::loadTexture("resources/textures/face.png", GL_TRUE, "face");
  ResourceManager::loadTexture("resources/textures/block.png", GL_FALSE, "block");
  ResourceManager::loadTexture("resources/textures/block_solid.png", GL_FALSE, "block_solid");
  ResourceManager::loadTexture("resources/textures/paddle.png", GL_TRUE, "paddle");
  ResourceManager::loadTexture("resources/textures/particle.png", GL_TRUE, "particle");
  
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
  
  /* ball */
  glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
  Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                        ResourceManager::getTexture("face"));
  
  /* particles */
  Particles = new ParticleGenerator(ResourceManager::getShader("particle"),
                                    ResourceManager::getTexture("particle"),
                                    500);
  
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
    
    //draw particles
    Particles->Draw();
    
    //draw ball
    Ball->draw(*GameRenderer);
  }
}

void Game::processInput(GLfloat dt)
{
  if (this->state == GAME_ACTIVE)
  {
    GLfloat distanceCovered = PLAYER_VELOCITY * dt;
    // Move playerboard
    if (this->keys[GLFW_KEY_A])
    {
      if (Player->position.x >= 0)
      {
        Player->position.x -= distanceCovered;
        if (Ball->stuck)
          Ball->position.x -= distanceCovered;
      }
    }
    if (this->keys[GLFW_KEY_D])
    {
      if (Player->position.x <= this->width - Player->size.x)
      {
        Player->position.x += distanceCovered;
        if (Ball->stuck)
          Ball->position.x += distanceCovered;
      }
    }
    if (this->keys[GLFW_KEY_SPACE])
      Ball->stuck = false;
  }
}

void Game::update(GLfloat dt)
{
  // Update objects
  Ball->move(dt, this->width);
  
  // Check for collisions
  this->doCollisions();
  
  Particles->Update(dt, *Ball, 2, glm::vec2(Ball->radius / 2));
  
  // Check loss condition
  if (Ball->position.y >= this->height) // Did ball reach bottom edge?
  {
    this->resetLevel();
    this->resetPlayer();
  }
}

float clamp(float value, float min, float max) {
  return std::max(min, std::min(max, value));
}
void Game::doCollisions()
{
  for (GameObject &box : this->levels[this->level].bricks)
  {
    if (!box.destroyed)
    {
      Collision collision = checkCollision(*Ball, box);
      if (std::get<0>(collision)) // If collision is true
      {
        // Destroy block if not solid
        if (!box.isSolid)
          box.destroyed = GL_TRUE;
        // Collision resolution
        Direction dir = std::get<1>(collision);
        glm::vec2 diff_vector = std::get<2>(collision);
        if (dir == LEFT || dir == RIGHT) // Horizontal collision
        {
          Ball->velocity.x = -Ball->velocity.x; // Reverse horizontal velocity
          // Relocate
          GLfloat penetration = Ball->radius - std::abs(diff_vector.x);
          if (dir == LEFT)
            Ball->position.x += penetration; // Move ball to right
          else
            Ball->position.x -= penetration; // Move ball to left;
        }
        else // Vertical collision
        {
          Ball->velocity.y = -Ball->velocity.y; // Reverse vertical velocity
          // Relocate
          GLfloat penetration = Ball->radius - std::abs(diff_vector.y);
          if (dir == UP)
            Ball->position.y -= penetration; // Move ball bback up
          else
            Ball->position.y += penetration; // Move ball back down
        }
      }
    }
  }
  // Also check collisions for player pad (unless stuck)
  Collision result = checkCollision(*Ball, *Player);
  if (!Ball->stuck && std::get<0>(result))
  {
    // Check where it hit the board, and change velocity based on where it hit the board
    GLfloat centerBoard = Player->position.x + Player->size.x / 2;
    GLfloat distance = (Ball->position.x + Ball->radius) - centerBoard;
    GLfloat percentage = distance / (Player->size.x / 2);
    // Then move accordingly
    GLfloat strength = 2.0f;
    glm::vec2 oldVelocity = Ball->velocity;
    Ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
    //Ball->Velocity.y = -Ball->Velocity.y;
    Ball->velocity = glm::normalize(Ball->velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
    // Fix sticky paddle
    Ball->velocity.y = -1 * std::abs(Ball->velocity.y);
  }
}

GLboolean Game::checkCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
  // Collision x-axis?
  bool collisionX = one.position.x + one.size.x >= two.position.x &&
  two.position.x + two.size.x >= one.position.x;
  // Collision y-axis?
  bool collisionY = one.position.y + one.size.y >= two.position.y &&
  two.position.y + two.size.y >= one.position.y;
  // Collision only if on both axes
  return collisionX && collisionY;
}

Collision Game::checkCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
  // Get center point circle first
  glm::vec2 center(one.position + one.radius);
  // Calculate AABB info (center, half-extents)
  glm::vec2 aabb_half_extents(two.size.x / 2, two.size.y / 2);
  glm::vec2 aabb_center(two.position.x + aabb_half_extents.x, two.position.y + aabb_half_extents.y);
  // Get difference vector between both centers
  glm::vec2 difference = center - aabb_center;
  glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
  // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
  glm::vec2 closest = aabb_center + clamped;
  // Now retrieve vector between center circle and closest point AABB and check if length < radius
  difference = closest - center;
  
  if (glm::length(difference) < one.radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
    return std::make_tuple(GL_TRUE, vectorDirection(difference), difference);
  else
    return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

// Calculates which direction a vector is facing (N,E,S or W)
Direction Game::vectorDirection(glm::vec2 target)
{
  glm::vec2 compass[] = {
    glm::vec2(0.0f, 1.0f),	// up
    glm::vec2(1.0f, 0.0f),	// right
    glm::vec2(0.0f, -1.0f),	// down
    glm::vec2(-1.0f, 0.0f)	// left
  };
  GLfloat max = 0.0f;
  GLuint best_match = -1;
  for (GLuint i = 0; i < 4; i++)
  {
    GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
    if (dot_product > max)
    {
      max = dot_product;
      best_match = i;
    }
  }
  return (Direction)best_match;
}

void Game::resetLevel()
{
  if (this->level == 0)
    this->levels[0].load("resources/levels/level1", this->width, this->height * 0.5f);
  else if (this->level == 1)
    this->levels[1].load("resources/levels/level2", this->width, this->height * 0.5f);
  else if (this->level == 2)
    this->levels[2].load("resources/levels/level3", this->width, this->height * 0.5f);
  else if (this->level == 3)
    this->levels[3].load("resources/levels/level4", this->width, this->height * 0.5f);
}

void Game::resetPlayer()
{
  // Reset player/ball stats
  Player->size = PLAYER_SIZE;
  Player->position = glm::vec2(this->width / 2 - PLAYER_SIZE.x / 2, this->height - PLAYER_SIZE.y);
  Ball->reset(Player->position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}
