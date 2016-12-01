// ----------------------------------------------
// Informatique Graphique 3D & Réalité Virtuelle.
// Travaux Pratiques
// Shaders
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
// ----------------------------------------------

attribute vec3 ks;
attribute vec3 kd;// attribut car doit d'abord passer à travers le vertexShader
attribute vec2 vt;
attribute float o1;
attribute float o2;

varying vec4 P;
varying vec3 N;
varying vec3 vKD; //ce qui va devenir un attribut dans le fragment shader
varying vec3 vKS;
varying vec2 vVT;
varying float vO1;
varying float vO2;

void main(void) {
    P = gl_Vertex;
    N = gl_Normal;
    
    vKD = kd; //on fait directement passer les attributs dans le fragment shader grace a ca
    vKS = ks;
    vVT=vt;
    vO1=o1;
    vO2=o2;
    
    gl_Position = ftransform ();
}
