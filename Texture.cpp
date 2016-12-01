//
//  Texture.cpp
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 30/01/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include <stdio.h>
#include "Texture.h"


using namespace std;

Texture::Texture(string fichierImage) : m_id(0), m_fichierImage(fichierImage)
{

    
}


// Destructeur

Texture::~Texture()
{
glDeleteTextures(1, &m_id);
}


// Méthodes




void Texture::charger()
{
        // Chargement de l'image dans une surface SDL
        
        SDL_Surface *imageSDL = IMG_Load(m_fichierImage.c_str());
        
        if(imageSDL == 0)
        {
            std::cout << "Erreur : " << SDL_GetError() << std::endl;
        }
        
        
        // Génération de l'ID
        
        glGenTextures(1, &m_id);
        
        
        // Verrouillage
        
        glBindTexture(GL_TEXTURE_2D, m_id);
        
        
        // Format de l'image
        
        GLenum formatInterne(0);
        GLenum format(0);
        
        
        // Détermination du format et du format interne pour les images à 3 composantes
        
        if(imageSDL->format->BytesPerPixel == 3)
        {
            // Format interne
            
            formatInterne = GL_RGB;
            
            
            // Format
            
            if(imageSDL->format->Rmask == 0xff)
                format = GL_RGB;
            
            else
                format = GL_BGR;
        }
        
        
        // Détermination du format et du format interne pour les images à 4 composantes
        
        else if(imageSDL->format->BytesPerPixel == 4)
        {
            // Format interne
            
            formatInterne = GL_RGBA;
            
            
            // Format
            
            if(imageSDL->format->Rmask == 0xff)
                format = GL_RGBA;
            
            else
                format = GL_BGRA;
        }
        
        
        // Dans les autres cas, on arrête le chargement
        
        else
        {
            std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
            SDL_FreeSurface(imageSDL);
        }
        
        
        // Copie des pixels
        
        glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageSDL->w, imageSDL->h, 0, format, GL_UNSIGNED_BYTE, imageSDL->pixels);
        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Déverrouillage
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }



GLuint Texture::getID() const
{
    return m_id;
}


void Texture::setFichierImage(const std::string &fichierImage)
{
    m_fichierImage = fichierImage;
}
