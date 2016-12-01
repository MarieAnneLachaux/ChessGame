// ----------------------------------------------
// Informatique Graphique 3D & Réalité Virtuelle.
// Travaux Pratiques
// Shaders
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
// ----------------------------------------------

// Add here all the value you need to describe the light or the material. 
// At first used const values. 
// Then, use uniform variables and set them from the CPU program.


uniform sampler2D textureKD; //texture --- uniform because all the vertices of the triangle will have the same texture (image) -- sampler2D indique que la variable contient une texture2D

uniform vec3 lightPos1;
uniform vec3 lightPos2;

varying vec4 P; // fragment-wise position
varying vec3 N; // fragment-wise normal

varying vec3 vKD;//on recupere vKD dans le fragment Shader
varying vec3 vKS;
varying vec2 vVT; //texture coordinees --- varying pcq chaque sommet du triangle a une valeur differente
varying float vO1; //ombre portees source 1 et 2
varying float vO2;

void main (void) {
    
    
    vec3 p = vec3 (gl_ModelViewMatrix * P);
    vec3 n = normalize (gl_NormalMatrix * N);
    
    vec3 l1 = normalize (lightPos1 - p);
    vec3 r1 = reflect (l1, n);
    
    vec3 l2 = normalize (lightPos2 - p);
    vec3 r2 = reflect (l2, n);
    
    vec3 w0 = normalize (-p);
    
    
    //Diffus:
    
    vec3 kd = vKD* texture2D(textureKD, vVT).xyz; //la fonction texture(texture2D,texCoord) renvoie la couleur correspondant à la position texCoord sur la texture2D.
    vec3 fd = 3.0*kd / 3.14;
    
    
    //BLIN-PHONG:
    
    vec3 ks = vKS;
    float s= 10.0;
    
    vec3 fs1=ks*pow(dot(r1,w0),s);
    vec3 fs2=ks*pow(dot(r2,w0),s);
    
    vec3 L1 = vec3(1.0,1.0,1.0);
    vec3 L2 = vec3(1.0,1.0,1.0);
    
    
    vec3 color1 = vO1*L1*(fd+fs1)*(max(dot(n,l1),0.0)) ;
    vec3 color2 = vO2*L2*(fd+fs2)*(max(dot(n,l2),0.0)) ;
    
    vec3 color = (color1 + color2);
    
   if (vKS==vec3(0.0,0.0,0.0)) {
        color = kd;
    }
    
    gl_FragColor = vec4(color,1.0);
    
}

