//
//  SpriteRenderer.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/4/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "SpriteRenderer.hpp"
using namespace std;

SpriteRenderer::SpriteRenderer(const Shader& shader)
{
  this->shader = shader;
  this->init();
}

SpriteRenderer::~SpriteRenderer()
{
  glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::init()
{
  GLuint VBO;
  vector<GLfloat> quadData =
  {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  
  glGenVertexArrays(1, &this->VAO);
  glBindVertexArray(this->VAO);
  {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*quadData.size(), quadData.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
}

void SpriteRenderer::draw(const Texture2D& texture,
          glm::vec2 position,
          glm::vec2 size,
          GLfloat rotate,
          glm::vec3 color)
{
  
  // Prepare transformations
  this->shader.use();
  
  /* model */
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(position, 0.0f));//fifth translate to positon
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));//fourth translate back to original position
  model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));//third rotate
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));//second translate to origin
  model = glm::scale(model, glm::vec3(size, 1.0f));//first scale
  
  this->shader.setMatrix4("model", model);
  
  /* color */
  this->shader.setVector3f("spriteColor", color);
  
  /* texture */
  glActiveTexture(GL_TEXTURE0);
  texture.bind();
  
  /* draw */
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
