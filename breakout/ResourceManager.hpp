//
//  ResourceManager.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <map>
#include <GL/glew.h>
#include "Shader.hpp"
#include "Texture.hpp"

class ResourceManager
{
public:
  /* members */
  // Resource storage
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  
  /* methods */
  // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
  static Shader loadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name);
  // Retrieves a stored sader
  static Shader getShader(std::string name);
  // Loads (and generates) a texture from file
  static Texture2D loadTexture(std::string file, GLboolean alpha, std::string name);
  // Retrieves a stored texture
  static Texture2D getTexture(std::string name);
  // Properly de-allocates all loaded resources
  static void clear();
  
private:
  /* constructor */
  // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
  ResourceManager() { };
  
  /* methods */
  // Loads and generates a shader from file
  static Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile = "");
  // Loads a single texture from file
  static Texture2D loadTextureFromFile(std::string file, GLboolean alpha);
};


#endif /* ResourceManager_hpp */
