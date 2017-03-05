////
////  Shader.cpp
////  breakout
////
////  Created by Terna Kpamber on 3/3/17.
////  Copyright © 2017 Terna Kpamber. All rights reserved.
////
//
#include "Shader.hpp"
using namespace std;
using namespace glm;

Shader& Shader::use()
{
  glUseProgram(this->program);
  return *this;
}

void Shader::setFloat(std::string name, GLfloat value, GLboolean useShader)
{
  if(useShader) this->use();
  glUniform1f(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::setInteger(std::string name, GLint value, GLboolean useShader)
{
  if(useShader) this->use();
  glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::setVector2f(std::string name, const glm::vec2 &value, GLboolean useShader)
{
  if(useShader) this->use();
  glUniform2fv(glGetUniformLocation(this->program, name.c_str()), 1, value_ptr(value));
}

void Shader::setVector3f(std::string name, const glm::vec3 &value, GLboolean useShader)
{
  if(useShader) this->use();
  glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, value_ptr(value));
}

void Shader::setVector4f(std::string name, const glm::vec4 &value, GLboolean useShader)
{
  if(useShader) this->use();
  glUniform4fv(glGetUniformLocation(this->program, name.c_str()), 1, value_ptr(value));
}

void Shader::setMatrix4(std::string name, const glm::mat4 &matrix, GLboolean useShader)
{
  if(useShader) this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
}

void Shader::compile(std::string vertexSource, std::string fragmentSource, std::string geometrySource)
{
  GLuint sVertex, sFragment, gShader = 0;
  /* vertex shader */
  const GLchar* v_string = vertexSource.c_str();
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &v_string, NULL);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");
  
  /* fragment shader */
  const GLchar* f_string = fragmentSource.c_str();
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &f_string, NULL);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");
  
  /* geometry shader */
  if (!geometrySource.empty())
  {
    gShader = glCreateShader(GL_GEOMETRY_SHADER);
    const GLchar* g_string = geometrySource.c_str();
    glShaderSource(gShader, 1, &g_string, NULL);
    glCompileShader(gShader);
    checkCompileErrors(gShader, "GEOMETRY");
  }
  
  /* shader programs */
  this->program = glCreateProgram();
  glAttachShader(this->program, sVertex);
  glAttachShader(this->program, sFragment);
  if(!geometrySource.empty()) glAttachShader(this->program, gShader);
  glLinkProgram(this->program);
  checkCompileErrors(this->program, "PROGRAM");
  
  /* delete shaders */
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
  if(!geometrySource.empty())
    glDeleteShader(gShader);
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
      << infoLog << "\n -- --------------------------------------------------- -- "
      << std::endl;
    }
  }
  else
  {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
      << infoLog << "\n -- --------------------------------------------------- -- "
      << std::endl;
    }
  }
}
