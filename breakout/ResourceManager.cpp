//
//  ResourceManager.cpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#include "ResourceManager.hpp"
#include <SOIL/SOIL.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader ResourceManager::loadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name)
{
  Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
  return Shaders[name];
}

Shader ResourceManager::getShader(std::string name)
{
  return Shaders[name];
}

Texture2D ResourceManager::loadTexture(std::string file, GLboolean alpha, std::string name)
{
  Textures[name] = loadTextureFromFile(file, alpha);
  return Textures[name];
}

Texture2D ResourceManager::getTexture(std::string name)
{
  return Textures[name];
}

void ResourceManager::clear()
{
  // (Properly) delete all shaders
  for (auto iter : Shaders)
    glDeleteProgram(iter.second.program);
  // (Properly) delete all textures
  for (auto iter : Textures)
    glDeleteTextures(1, &iter.second.textureId);
}

Shader ResourceManager::loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile)
{
  // 1. Retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try
  {
    // Open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::stringstream vShaderStream, fShaderStream;
    // Read file's buffer contents into streams
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    // If geometry shader path is present, also load a geometry shader
    if (!gShaderFile.empty())
    {
      std::ifstream geometryShaderFile(gShaderFile);
      std::stringstream gShaderStream;
      gShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryCode = gShaderStream.str();
    }
  }
  catch (std::exception e)
  {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }
//  const GLchar *vShaderCode = vertexCode.c_str();
//  const GLchar *fShaderCode = fragmentCode.c_str();
//  const GLchar *gShaderCode = geometryCode.c_str();
  // 2. Now create shader object from source code
  Shader shader;
  shader.compile(vertexCode, fragmentCode, !gShaderFile.empty() ? geometryCode : "");
  return shader;
}

Texture2D ResourceManager::loadTextureFromFile(std::string file, GLboolean alpha)
{
  // Create Texture object
  Texture2D texture;
  if (alpha)
  {
    texture.internalFormat = GL_RGBA;
    texture.imageFormat = GL_RGBA;
  }
  // Load image
  int width, height;
  unsigned char* image = SOIL_load_image(file.c_str(), &width, &height, 0, texture.imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  // Now generate texture
  texture.generate(width, height, image);
  // And finally free image data
  SOIL_free_image_data(image);
  return texture;
}
