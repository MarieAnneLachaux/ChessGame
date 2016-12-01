//
//  Texture.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 30/01/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Texture_h
#define Texture_h


#endif /* Texture_h */



// Include

#define GLEW_STATIC 1
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Opengl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>


// Classe Texture

class Texture
{
public:
    
    Texture(std::string fichierImage);
    ~Texture();
    void charger();
    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);
    
    
private:
    
    GLuint m_id;
    std::string m_fichierImage;
};


