//
//  ParticleGenerator.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/5/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef ParticleGenerator_hpp
#define ParticleGenerator_hpp

#include "Shader.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"


// Represents a single particle and its state
struct Particle {
  glm::vec2 position, velocity;
  glm::vec4 color;
  GLfloat life;
  
  Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};


// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
class ParticleGenerator
{
public:
  // Constructor
  ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
  // Update all particles
  void update(GLfloat dt, GameObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
  // Render all particles
  void draw();
  
private:
  // Sstate
  std::vector<Particle> particles;
  GLuint amount;
  // Render state
  Shader shader;
  Texture2D texture;
  GLuint VAO;
  // Initializes buffer and vertex attributes
  void init();
  // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
  GLuint firstUnusedParticle();
  // Respawns particle
  void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif /* ParticleGenerator_hpp */
