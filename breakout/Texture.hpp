//
//  Texture.hpp
//  breakout
//
//  Created by Terna Kpamber on 3/3/17.
//  Copyright © 2017 Terna Kpamber. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class Texture2D
{
public:
  /* constructor */
  Texture2D();
  
  /* methods */
  // Generates texture from image data
  void generate(GLuint width, GLuint height, unsigned char* data);
  // Binds the texture as the current active GL_TEXTURE_2D texture object
  void bind() const;
  
  /* members */
  // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
  GLuint textureId;
  // Texture image dimensions
  GLuint width, height; // Width and height of loaded image in pixels
  // Texture Format
  GLuint internalFormat; // Format of texture object
  GLuint imageFormat; // Format of loaded image
  // Texture configuration
  GLuint wrapS; // Wrapping mode on S axis
  GLuint wrapT; // Wrapping mode on T axis
  GLuint filterMin; // Filtering mode if texture pixels < screen pixels
  GLuint filterMax; // Filtering mode if texture pixels > screen pixels
};

#endif /* Texture_hpp */
