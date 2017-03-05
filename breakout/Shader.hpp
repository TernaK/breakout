//
//  Shader.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:
  /* members */
  GLuint program;
  
  /* constructor */
  Shader() {};

  /* methods */
  Shader& use();
  void compile(std::string vertexSource, std::string fragmentSource, std::string geometrySource = ""); // Note: geometry source code is optional
  void setFloat(std::string name, GLfloat value, GLboolean useShader = false);
  void setInteger(std::string name, GLint value, GLboolean useShader = false);
  void setVector2f(std::string name, const glm::vec2& value, GLboolean useShader = false);
  void setVector3f(std::string name, const glm::vec3 &value, GLboolean useShader = false);
  void setVector4f(std::string name, const glm::vec4 &value, GLboolean useShader = false);
  void setMatrix4(std::string name, const glm::mat4 &matrix, GLboolean useShader = false);
  
private:
  void checkCompileErrors(GLuint object, std::string type);
};


#endif /* Shader_hpp */
