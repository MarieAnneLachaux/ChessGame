// ----------------------------------------------
// Informatique Graphique 3D & RÈalitÈ Virtuelle.
// Travaux Pratiques
// Shaders
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
#define GLEW_STATIC 1
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>


#include "Vec3.h"
#include "Camera.h"
#include "Mesh.h"
#include "GLProgram.h"
#include "SuperMesh.h"
#include "Texture.h"
#include "Damier.h"
#include "Ray.h"
#include "Animation.h"

using namespace std;

static const unsigned int DEFAULT_SCREENWIDTH = 1024;
static const unsigned int DEFAULT_SCREENHEIGHT = 768;
//static const string DEFAULT_MESH_FILE ("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/modele2.rtf");
static const string DEFAULT_MESH_FILE ("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Modeles/chessMinimal.rtf");



static string appTitle ("Informatique Graphique & Realite Virtuelle - Travaux Pratiques - Shaders");
static GLint window;
static unsigned int FPS = 0;
static bool fullScreen = false;

static Camera camera;
static SuperMesh superMesh;
static SuperMesh superMesh2;
static Mesh cubeBk;
static Mesh cubeFt;
static Mesh cubeLf;
static Mesh cubeRt;
static Mesh cubeUp;
static Mesh cubeDn;

Program * glProgram;

const Vec3f lightPos1;
const Vec3f lightPos2;


Texture texture2 ("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/echiquier2.jpg");
Texture texture0 ("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/verre3.jpg" );
Texture texture1 ("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/verre6.jpg");

Texture up("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_up.tga");
Texture dn("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_dn.tga");
Texture bk("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_ft.tga");
Texture ft("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_bk.tga");
Texture rt("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_lf.tga");
Texture lf("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/Textures/stratosphere_rt.tga");



GLint kdLocation;
GLint ksLocation;
GLint vtLocation;
GLint texLocation;
GLint ombre1Location;
GLint ombre2Location;


Damier damier;


static vector<float> intersect;
static vector<float> intersect2;

Animation animation;
float step = (0.70827*2)/8;

void printUsage () {
  std::cerr << std::endl 
	    << appTitle << std::endl
	    << "Author: Tamy Boubekeur" << std::endl << std::endl
	    << "Usage: ./main [<file.off>]" << std::endl
	    << "Commands:" << std::endl 
	    << "------------------" << std::endl
	    << " ?: Print help" << std::endl
	    << " w: Toggle wireframe mode" << std::endl
	    << " <drag>+<left button>: rotate model" << std::endl 
	    << " <drag>+<right button>: move model" << std::endl
	    << " <drag>+<middle button>: zoom" << std::endl
	    << " q, <esc>: Quit" << std::endl << std::endl; 
}


void printGlError(string prefix) {
    GLenum error= glGetError();
    if(error!=GL_NO_ERROR) {
        cout<<prefix<<"glGeterror: "<<error<<" : "<<gluErrorString(error)<<endl;
    }
    
}


void dessinerCube() {
    Vertex vertex1,vertex2,vertex3,vertex4,vertex5,vertex6,vertex7,vertex8;
    vertex1.p=Vec3f(-20.0,-20.0,-20.0);
    vertex2.p=Vec3f(20.0,-20.0,-20.0);
    vertex3.p=Vec3f(20.0,20.0,-20.0);
    vertex4.p=Vec3f(-20.0,20.0,-20.0);
    vertex5.p=Vec3f(-20.0,20.0,20.0);
    vertex6.p=Vec3f(20.0,20.0,20.0);
    vertex7.p=Vec3f(20.0,-20.0,20.0);
    vertex8.p=Vec3f(-20.0,-20.0,20.0);
    
    Square square(0,1,2,3);
  
    
    
    
    cubeBk.V.resize(4);
    cubeBk.V[0]=vertex2;
    cubeBk.V[1]=vertex1;
    cubeBk.V[2]=vertex8;
    cubeBk.V[3]=vertex7;
    cubeBk.V[0].vt=Vec3f(1.0,1.0,0.0);
    cubeBk.V[1].vt=Vec3f(0.0,1.0,0.0);
    cubeBk.V[2].vt=Vec3f(0.0,0.0,0.0);
    cubeBk.V[3].vt=Vec3f(1.0,0.0,0.0);
    cubeBk.S.resize(1,square);
    cubeBk.T.resize(0);
    
    cubeFt.V.resize(4);
    cubeFt.V[0]=vertex3;
    cubeFt.V[1]=vertex6;
    cubeFt.V[2]=vertex5;
    cubeFt.V[3]=vertex4;
    cubeFt.V[0].vt=Vec3f(0.0,1.0,0.0);
    cubeFt.V[1].vt=Vec3f(0.0,0.0,0.0);
    cubeFt.V[2].vt=Vec3f(1.0,0.0,0.0);
    cubeFt.V[3].vt=Vec3f(1.0,1.0,0.0);
    cubeFt.S.resize(1,square);
    cubeFt.T.resize(0);
    
    
    cubeUp.V.resize(4);
    cubeUp.V[0]=vertex5;
    cubeUp.V[1]=vertex6;
    cubeUp.V[2]=vertex7;
    cubeUp.V[3]=vertex8;
    cubeUp.V[0].vt=Vec3f(0.0,1.0,0.0);
    cubeUp.V[1].vt=Vec3f(0.0,0.0,0.0);
    cubeUp.V[2].vt=Vec3f(1.0,0.0,0.0);
    cubeUp.V[3].vt=Vec3f(1.0,1.0,0.0);
    cubeUp.S.resize(1,square);
    cubeUp.T.resize(0);

    
    cubeDn.V.resize(4);
    cubeDn.V[0]=vertex1;
    cubeDn.V[1]=vertex2;
    cubeDn.V[2]=vertex3;
    cubeDn.V[3]=vertex4;
    cubeDn.V[0].vt=Vec3f(1.0,0.0,0.0);
    cubeDn.V[1].vt=Vec3f(1.0,1.0,0.0);
    cubeDn.V[2].vt=Vec3f(0.0,1.0,0.0);
    cubeDn.V[3].vt=Vec3f(0.0,0.0,0.0);
    cubeDn.S.resize(1,square);
    cubeDn.T.resize(0);

    
    
    cubeLf.V.resize(4);
    cubeLf.V[0]=vertex1;
    cubeLf.V[1]=vertex4;
    cubeLf.V[2]=vertex5;
    cubeLf.V[3]=vertex8;
    cubeLf.V[0].vt=Vec3f(1.0,1.0,0.0);
    cubeLf.V[1].vt=Vec3f(0.0,1.0,0.0);
    cubeLf.V[2].vt=Vec3f(0.0,0.0,0.0);
    cubeLf.V[3].vt=Vec3f(1.0,0.0,0.0);
    cubeLf.S.resize(1,square);
    cubeLf.T.resize(0);

    
    cubeRt.V.resize(4);
    cubeRt.V[0]=vertex3;
    cubeRt.V[1]=vertex2;
    cubeRt.V[2]=vertex7;
    cubeRt.V[3]=vertex6;
    cubeRt.V[0].vt=Vec3f(1.0,1.0,0.0);
    cubeRt.V[1].vt=Vec3f(0.0,1.0,0.0);
    cubeRt.V[2].vt=Vec3f(0.0,0.0,0.0);
    cubeRt.V[3].vt=Vec3f(1.0,0.0,0.0);
    cubeRt.S.resize(1,square);
    cubeRt.T.resize(0);
    
    cubeBk.recomputeNormals();
    cubeDn.recomputeNormals();
    cubeLf.recomputeNormals();
    cubeRt.recomputeNormals();
    cubeUp.recomputeNormals();
    cubeFt.recomputeNormals();
   
}


/*void dessinerDamier(){
    // construction du damier
    Vertex vertex1,vertex2,vertex3,vertex4,vertex5,vertex6,vertex7,vertex8;
    vertex1.p=Vec3f(-7.0827,-7.0827,0.4);
    vertex2.p=Vec3f(-7.0827,7.0827,0.4);
    vertex3.p=Vec3f(7.0827,7.0827,0.4);
    vertex4.p=Vec3f(7.0827,-7.0827,0.4);
    
    vertex1.vt=Vec3f(0.0,0.0,0.0);
    vertex2.vt=Vec3f(1.0,0.0,0.0);
    vertex3.vt=Vec3f(1.0,1.0,0.0);
    vertex4.vt=Vec3f(0.0,1.0,0.0);
    
    
    Square square1(0,3,2,1);
    Square square2(0,1,2,3);
    
    superMesh.meshes[superMesh.meshes.size()-1].V.resize(4);
    superMesh.meshes[superMesh.meshes.size()-1].S.resize(1);
    superMesh.meshes[superMesh.meshes.size()-1].T.resize(0);
    superMesh.meshes[superMesh.meshes.size()-1].V[0]=vertex1;
    superMesh.meshes[superMesh.meshes.size()-1].V[1]=vertex2;
    superMesh.meshes[superMesh.meshes.size()-1].V[2]=vertex3;
    superMesh.meshes[superMesh.meshes.size()-1].V[3]=vertex4;
    superMesh.meshes[superMesh.meshes.size()-1].S[0]=square1;
    
    superMesh.meshes[superMesh.meshes.size()-2].V.resize(4);
    superMesh.meshes[superMesh.meshes.size()-2].S.resize(1);
    superMesh.meshes[superMesh.meshes.size()-2].T.resize(0);
    superMesh.meshes[superMesh.meshes.size()-2].V[0]=vertex1;
    superMesh.meshes[superMesh.meshes.size()-2].V[1]=vertex2;
    superMesh.meshes[superMesh.meshes.size()-2].V[2]=vertex3;
    superMesh.meshes[superMesh.meshes.size()-2].V[3]=vertex4;
    superMesh.meshes[superMesh.meshes.size()-2].S[0]=square2;
    
    superMesh.centerAndScaleToUnit();
    superMesh.meshes[superMesh.meshes.size()-1].recomputeNormals();
    superMesh.meshes[superMesh.meshes.size()-2].recomputeNormals();
};*/



void dessinerDamier(int resolution){
 // construction du damier
    vector<vector<Vertex>> vertices;
    vertices.resize(resolution+1);
    for (int l=0;l<resolution+1; l++) {
        vertices[l].resize(resolution+1);
    }
    
    vector<vector<Square>> squares;
    squares.resize(resolution);
    for (int l=0;l<resolution; l++) {
        squares[l].resize(resolution);
    }
    
    for( int j =0;j<=resolution;j++) {
        for (int i=0; i<=resolution; i++) {
            Vertex v;
            v.p=Vec3f(-7.0827+i* 14.1654/float(resolution),-7.0827+j* 14.1654/float(resolution),0.4);
            v.vt=Vec3f(i/float(resolution),j/float(resolution),0.0);
            vertices[i][j]=v;
            
        }
    }
    
    for( int j =0;j<=resolution-1;j++) {
        for (int i=0; i<=resolution-1; i++) {
            Square s (i+j*(resolution+1),(i+1)+j*(resolution+1),(i+1)+(j+1)*(resolution+1),i+(j+1)*(resolution+1));
            squares[i][j]=s;
        }
    }
 
 
 

 
 superMesh.meshes[superMesh.meshes.size()-1].V.resize((resolution+1)*(resolution+1));
 superMesh.meshes[superMesh.meshes.size()-1].S.resize(resolution*resolution);
 superMesh.meshes[superMesh.meshes.size()-1].T.resize(0);
    
    for( int j =0;j<=resolution;j++) {
        for (int i=0; i<=resolution; i++) {
            int k = i+j*(resolution+1);
            superMesh.meshes[superMesh.meshes.size()-1].V[k]=vertices[i][j];
        }
    }
    
    for( int j =0;j<=resolution-1;j++) {
        for (int i=0; i<=resolution-1; i++) {
            int k = i+j*resolution;
            superMesh.meshes[superMesh.meshes.size()-1].S[k]=squares[i][j];
        }
    }
    
/* on fair le dessous
    
    Vertex vertex0,vertex1,vertex2,vertex3;
    vertex0.p=vertices[0][0].p;
    vertex1.p=vertices[0][resolution].p;
    vertex2.p=vertices[resolution][resolution].p;
    vertex3.p=vertices[resolution][0].p;
    

    
 Square squareDessous(0,(resolution+1)*resolution,(resolution+1)*(resolution+1),resolution);
  
 superMesh.meshes[superMesh.meshes.size()-2].V.resize(4);
 superMesh.meshes[superMesh.meshes.size()-2].S.resize(1);
 superMesh.meshes[superMesh.meshes.size()-2].T.resize(0);
    superMesh.meshes[superMesh.meshes.size()-2].V[0]=vertex0;
 superMesh.meshes[superMesh.meshes.size()-2].V[1]=vertex1;
 superMesh.meshes[superMesh.meshes.size()-2].V[2]=vertex2;
 superMesh.meshes[superMesh.meshes.size()-2].V[3]=vertex3;
 superMesh.meshes[superMesh.meshes.size()-2].S[0]=squareDessous;
 */
    
    
    Vertex vertex1,vertex2,vertex3,vertex4;
    vertex1.p=Vec3f(-7.0827,-7.0827,0.4);
    vertex2.p=Vec3f(7.0827,-7.0827,0.4);
    vertex3.p=Vec3f(7.0827,7.0827,0.4);
    vertex4.p=Vec3f(-7.0827,7.0827,0.4);
    
    vertex1.vt=Vec3f(0.0,0.0,0.0);
    vertex2.vt=Vec3f(1.0,0.0,0.0);
    vertex3.vt=Vec3f(1.0,1.0,0.0);
    vertex4.vt=Vec3f(0.0,1.0,0.0);
    
    Square square2(0,3,2,1);
    
    
    superMesh.meshes[superMesh.meshes.size()-2].V.resize(4);
    superMesh.meshes[superMesh.meshes.size()-2].S.resize(1);
    superMesh.meshes[superMesh.meshes.size()-2].T.resize(0);
    superMesh.meshes[superMesh.meshes.size()-2].V[0]=vertex1;
    superMesh.meshes[superMesh.meshes.size()-2].V[1]=vertex2;
    superMesh.meshes[superMesh.meshes.size()-2].V[2]=vertex3;
    superMesh.meshes[superMesh.meshes.size()-2].V[3]=vertex4;
    superMesh.meshes[superMesh.meshes.size()-2].S[0]=square2;
    
 superMesh.centerAndScaleToUnit();
 superMesh.meshes[superMesh.meshes.size()-1].recomputeNormals();
 superMesh.meshes[superMesh.meshes.size()-2].recomputeNormals();
    
   
 };


void hasIntersection1() {
    intersect.resize(superMesh.meshes[34].V.size(),1.0);
    
    float epsilon = 0.0001;
    for (unsigned int i = 0; i < superMesh.meshes[34].V.size (); i++) {
        const Vertex & v = superMesh.meshes[34].V[i];
        Vec3f wi = lightPos1 - v.p;
        Ray r(v.p+epsilon*v.n, wi); //epsilon dans la direction de la normale pour s'assurer qu'on ne prend pas en compte le point de depart
        
        for (int m=0; m<superMesh.meshes.size()-2; m++) {
            
            for (unsigned int k = 0; k < superMesh.meshes[m].T.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[2]])) {
                    intersect[i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            
            for (unsigned int k = 0; k < superMesh.meshes[m].S.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ||
                    
                    r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[3]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ){
                    
                    intersect[i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            if (intersect[i]==0.0) break;
            
        }
    }

    /*intersect.resize(superMesh.meshes.size());
    
    for (int g=0; g<superMesh.meshes.size(); g++) {
        intersect[g].resize(superMesh.meshes[g].V.size(),1.0);
   
    
        float epsilon = 0.00001;
        for (unsigned int i = 0; i < superMesh.meshes[g].V.size (); i++) {
            const Vertex & v = superMesh.meshes[g].V[i];
            Vec3f wi = lightPos1 - v.p;
            Ray r(v.p+epsilon*v.n, wi); //epsilon dans la direction de la normale pour s'assurer qu'on ne prend pas en compte le point de depart
            
        for (int m=0; m<superMesh.meshes.size(); m++) {
            
            for (unsigned int k = 0; k < superMesh.meshes[m].T.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[2]])) {
                    intersect[g][i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            
            for (unsigned int k = 0; k < superMesh.meshes[m].S.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ||
                    
                    r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[3]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ){
                    
                    intersect[g][i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            if (intersect[g][i]==0.0) break;
            
        }
    }}*/
    
    }



void hasIntersection2() {
    intersect2.resize(superMesh.meshes[34].V.size(),1.0);
    
    float epsilon = 0.0001;
    for (unsigned int i = 0; i < superMesh.meshes[34].V.size (); i++) {
        const Vertex & v = superMesh.meshes[34].V[i];
        Vec3f wi = lightPos2 - v.p;
        Ray r(v.p+epsilon*v.n, wi); //epsilon dans la direction de la normale pour s'assurer qu'on ne prend pas en compte le point de depart
        
        for (int m=0; m<superMesh.meshes.size()-2; m++) {
            
            for (unsigned int k = 0; k < superMesh.meshes[m].T.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[2]])) {
                    intersect2[i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            
            for (unsigned int k = 0; k < superMesh.meshes[m].S.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ||
                    
                    r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[3]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ){
                    
                    intersect2[i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            if (intersect2[i]==0.0) break;
            
        }
    }
    
    /*
    intersect2.resize(superMesh.meshes.size());
    
    for (int g=0; g<superMesh.meshes.size(); g++) {
        intersect2[g].resize(superMesh.meshes[g].V.size(),1.0);

        float epsilon = 0.00001;
        for (unsigned int i = 0; i < superMesh.meshes[g].V.size (); i++) {
            const Vertex & v = superMesh.meshes[g].V[i];
            Vec3f wi = lightPos2 - v.p;
            Ray r(v.p+epsilon*v.n, wi); //epsilon dans la direction de la normale pour s'assurer qu'on ne prend pas en compte le point de depart
        
            for (int m=0; m<superMesh.meshes.size(); m++) {
        
                for (unsigned int k = 0; k < superMesh.meshes[m].T.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].T[k].ve[2]])) {
                    intersect2[g][i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
            
            
            
            for (unsigned int k = 0; k < superMesh.meshes[m].S.size (); k++) {
                if (r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[1]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ||
                    
                    r.intersectionRayonTriangle(
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[3]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[0]],
                                                superMesh.meshes[m].V[superMesh.meshes[m].S[k].v[2]])
                    
                    ){
                    
                    intersect2[g][i] = 0.0;
                    break; // on arrete des qu'on a trouve un triangle
                    
                }
            }
                if (intersect2[g][i]==0.0) break;
            
        }
    }
    }*/
}




void init (const char * modelFilename) {
#ifndef __APPLE__
    glewInit();
#endif  
    glCullFace (GL_BACK);
    
    // Specifies the faces to cull (here the ones pointing away from the camera)
  glEnable (GL_CULL_FACE); // Enables face culling (based on the orientation defined by the CW/CCW enumeration).
  glDepthFunc (GL_LESS); // Specify the depth test for the z-buffer
  glEnable (GL_DEPTH_TEST); // Enable the z-buffer in the rasterization
  glLineWidth (2.0); // Set the width of edges in GL_LINE polygon mode
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f); // Background color
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	
  camera.resize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT); // Setup the camera
  superMesh.loadOFF(modelFilename); // Load a mesh file
    
    dessinerDamier(100);
    dessinerCube();
    
    try {
    glProgram = Program::genVFProgram ("Simple GL Program", "/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/shader.vert", "/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/PROJET_IGR202/PROJET_IGR202/shader.frag"); // Load and compile pair of shaders
    glProgram->use (); // Activate the shader program
  } catch (Exception & e) {
    cerr << e.msg () << endl;
  }
    {
        GLenum error= glGetError();
        if(error!=GL_NO_ERROR) {
            cout<<error;
        }
    }
    
    //Chargement des lumieres
    glProgram-> setUniform3f("lightPos1",0.0, -10.0, 20.0) ;
    glProgram-> setUniform3f("lightPos2",0.0, +10.0, 20.0) ;
    
    
    //Chargement des textures
    
    texture0.charger();
    texture1.charger();
    texture2.charger();
    up.charger();
    dn.charger();
    bk.charger();
    rt.charger();
    lf.charger();
    ft.charger();
    
    {
        GLenum error= glGetError();
        if(error!=GL_NO_ERROR) {
            cout<<error;
        }
    }
    
    
    // Ombres portees
    //hasIntersection1();
    //hasIntersection2();
    
    
    //Attribution des locations pour nos shaders
    
    
    vtLocation = glProgram ->getAttribLocation("vt");
    printGlError("vtLocation");
    
    
    kdLocation = glProgram->getAttribLocation("kd");
    printGlError("kdLocation");
    ksLocation = glProgram->getAttribLocation("ks");
    printGlError("ksLocation");
    
    
    texLocation = glProgram -> getUniformLocation("textureKD");
    printGlError("texLocation");
    
    ombre1Location =glProgram->getAttribLocation("o1");
    printGlError("o1Location");
    
    ombre2Location =glProgram->getAttribLocation("o2");
    printGlError("o2Location");

    
}



void drawScene () {
    
    
    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_2D, bk.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    
    glBegin (GL_QUADS);
        for (unsigned int j = 0; j < 4; j++) {
            const Vertex & v = cubeBk.V[j];
            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
            glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
            glProgram->setAttrib1f(ombre1Location,1.0);
            glProgram->setAttrib1f(ombre2Location,1.0);
            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
        }
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture(GL_TEXTURE_2D, ft.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    glBegin (GL_QUADS);
    for (unsigned int j = 0; j < 4; j++) {
        const Vertex & v = cubeFt.V[j];
        glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
        glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
        glProgram->setAttrib1f(ombre1Location,1.0);
        glProgram->setAttrib1f(ombre2Location,1.0);
        glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
        glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
        glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture(GL_TEXTURE_2D, dn.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    glBegin (GL_QUADS);
    for (unsigned int j = 0; j < 4; j++) {
        const Vertex & v = cubeDn.V[j];
        glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
        glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
        glProgram->setAttrib1f(ombre1Location,1.0);
        glProgram->setAttrib1f(ombre2Location,1.0);
        glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
        glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
        glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
        
        
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindTexture(GL_TEXTURE_2D, up.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    
    glBegin (GL_QUADS);
    for (unsigned int j = 0; j < 4; j++) {
        const Vertex & v = cubeUp.V[j];
        glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
        glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
        glProgram->setAttrib1f(ombre1Location,1.0);
        glProgram->setAttrib1f(ombre2Location,1.0);
        glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
        glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
        glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
        
        
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    glBindTexture(GL_TEXTURE_2D, lf.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    
    glBegin (GL_QUADS);
    for (unsigned int j = 0; j < 4; j++) {
        const Vertex & v = cubeLf.V[j];
        glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
        glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
        glProgram->setAttrib1f(ombre1Location,1.0);
        glProgram->setAttrib1f(ombre2Location,1.0);
        glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
        glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
        glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
        
        
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    glBindTexture(GL_TEXTURE_2D, rt.getID());
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    glBegin (GL_QUADS);
    for (unsigned int j = 0; j < 4; j++) {
        const Vertex & v = cubeRt.V[j];
        glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
        glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
        glProgram->setAttrib1f(ombre1Location,1.0);
        glProgram->setAttrib1f(ombre2Location,1.0);
        glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
        glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
        glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
        
        
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    glDepthMask(GL_TRUE);
   glBindTexture(GL_TEXTURE_2D, texture2.getID()); //on bind notre texture à la texture active courante
    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
    

    
    glBegin (GL_QUADS);
    for (unsigned int i = 0; i < superMesh.meshes[34].S.size(); i++) {
        for (unsigned int j = 0; j < 4; j++) {
            const Vertex & v = superMesh.meshes[34].V[superMesh.meshes[34].S[i].v[j]];
            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
            glProgram->setAttrib3f(ksLocation, 1.0,1.0,1.0);
            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
            glProgram->setAttrib1f(ombre1Location,1.0/*intersect[superMesh.meshes[34].S[i].v[j]]*/);
            glProgram->setAttrib1f(ombre2Location,1.0/*intersect[superMesh.meshes[34].S[i].v[j]]*/);
            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
            
            
        }
    }
    glEnd ();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    glBegin (GL_QUADS);
    
    for (unsigned int i = 0; i < superMesh.meshes[33].S.size(); i++) {
        for (unsigned int j = 0; j < 4; j++) {
            const Vertex & v = superMesh.meshes[33].V[superMesh.meshes[33].S[i].v[j]];
            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
            glProgram->setAttrib3f(ksLocation, 0.0,0.0,0.0);
            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
            glProgram->setAttrib1f(ombre1Location,1.0);
            glProgram->setAttrib1f(ombre2Location,1.0);
            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
            
            
        }
    }
    glEnd ();
    
    
    
    
    for ( int i =0; i<8; i++) {
        for ( int j =0; j<8; j++) {
            
            if ( damier.cases[i][j].piece !='e') {
                if( damier.cases[i][j].couleur==0)
                {   glBindTexture(GL_TEXTURE_2D, texture0.getID()); //on bind notre texture à la texture active
                
                    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
                    
                    int g = damier.cases[i][j].indiceM;
                    glBegin (GL_TRIANGLES);
                    for (unsigned int i = 0; i < superMesh.meshes[g].T.size(); i++) {
                        for (unsigned int j = 0; j < 3; j++) {
                            const Vertex & v = superMesh.meshes[g].V[superMesh.meshes[g].T[i].ve[j]];
                            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib3f(ksLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
                            glProgram->setAttrib1f(ombre1Location,1.0);
                            glProgram->setAttrib1f(ombre2Location,1.0);
                            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
                            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
                            
                            
                        }
                    }
                    glEnd ();
                    
                    glBegin (GL_QUADS);
                    for (unsigned int i = 0; i < superMesh.meshes[g].S.size(); i++) {
                        for (unsigned int j = 0; j < 4; j++) {
                            const Vertex & v = superMesh.meshes[g].V[superMesh.meshes[g].S[i].v[j]];
                            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib3f(ksLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
                            glProgram->setAttrib1f(ombre1Location,1.0);
                            glProgram->setAttrib1f(ombre2Location,1.0);
                            
                            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
                            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
                        }
                    }
                    glEnd ();
                    glBindTexture(GL_TEXTURE_2D, 0);
                
                }
                
                else {  glBindTexture(GL_TEXTURE_2D, texture1.getID());
                    glProgram->setUniform1u(texLocation, 0); //set to 0 because the texture is bound to GL_TEXTURE0 -- call the glUniform1i
                    
                    int g = damier.cases[i][j].indiceM;
                    glBegin (GL_TRIANGLES);
                    for (unsigned int i = 0; i < superMesh.meshes[g].T.size(); i++) {
                        for (unsigned int j = 0; j < 3; j++) {
                            const Vertex & v = superMesh.meshes[g].V[superMesh.meshes[g].T[i].ve[j]];
                            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib3f(ksLocation, 0.7,0.7,1.0);
                            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
                            glProgram->setAttrib1f(ombre1Location,1.0);
                            glProgram->setAttrib1f(ombre2Location,1.0);
                            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
                            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
                            
                            
                        }
                    }
                    glEnd ();
                    
                    glBegin (GL_QUADS);
                    for (unsigned int i = 0; i < superMesh.meshes[g].S.size(); i++) {
                        for (unsigned int j = 0; j < 4; j++) {
                            const Vertex & v = superMesh.meshes[g].V[superMesh.meshes[g].S[i].v[j]];
                            glProgram->setAttrib3f(kdLocation, 1.0,1.0,1.0);
                            glProgram->setAttrib3f(ksLocation, 0.7,0.7,1.0);
                            glProgram->setAttrib2f(vtLocation,v.vt[0],v.vt[1]);
                            glProgram->setAttrib1f(ombre1Location,1.0);
                            glProgram->setAttrib1f(ombre2Location,1.0);
                            
                            glNormal3f (v.n[0], v.n[1], v.n[2]); // Specifies current normal vertex
                            glVertex3f (v.p[0], v.p[1], v.p[2]); // Emit a vertex (one triangle is emitted each time 3 vertices are emitted)
                        }
                    }
                    glEnd ();
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
    
            }}}}
    

void reshape(int w, int h) {
  camera.resize (w, h);
}

void display () {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  camera.apply (); 
  drawScene ();
  glFlush ();
  glutSwapBuffers (); 
}

void key (unsigned char keyPressed, int x, int y) {
  switch (keyPressed) {
  case 'f':
    if (fullScreen) {
      glutReshapeWindow (camera.getScreenWidth (), camera.getScreenHeight ());
      fullScreen = false;
    } else {
      glutFullScreen ();
      fullScreen = true;
    }      
    break;
  case 'q':
  case 27:
    exit (0);
    break;
  case 'w':
    GLint mode[2];
    glGetIntegerv (GL_POLYGON_MODE, mode);
    glPolygonMode (GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
    break;
    break;
  default:
    printUsage ();
    break;
  }
}



void mouse (int button, int state, int x, int y) {
    
    
    
    camera.handleMouseClickEvent (button, state, x, y);
    
    
    int i , j;
    float xr,yr;
    Vec3f deplacement;
    
    GLfloat Ax,Ay,Az;
    GLdouble Bx,By,Bz,t;
    camera.getPos(Ax, Ay, Az);
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
    glGetIntegerv(GL_VIEWPORT,viewport);
    gluUnProject(GLdouble (x), GLdouble (viewport[3]-y), GLdouble (0), mvmatrix, projmatrix, viewport, &Bx, &By, &Bz);
    
    //Remplacer SOURI.X par x et SOURI.Y par y si besoin
    
    t   =  -Az/(Bz-Az);
    xr = t*(Bx-Ax)+Ax;
    yr = (t *(By-Ay)+Ay);
    
    //Mx et My sont les coordonnées sur le damier
    //BUG POSSIBLE : Il utilise Gldouble, peut peut etre bugger. Voir avec float ou double si ça marche dans ce cas.
    //
    

    if(button==GLUT_LEFT_BUTTON) {
        
        if (state==GLUT_UP) {

            i=floor((-yr + 0.70827)/step);
            j=floor((xr+0.70827)/step);
            
            
            if ( ( -1<i && i<8 && -1<j && j<8) ) {
                
                switch ( animation.etatJeux) {
                        
                    case 0 :
                        if((damier.cases[i][j].piece=='e') || animation.joueur!=damier.cases[i][j].couleur ){
                            animation.etatJeux=0;
                            cout<<"casevide"<<endl;}
                        else { animation.etatJeux=1;
                            animation.depart=Vec2i(i,j);
                            cout<<"departlance"<<endl;
                    break;
                        
                    case 1:
                        if(damier.cases[i][j].couleur==animation.joueur) animation.etatJeux=0;
                        
                        else if (damier.cases[i][j].piece=='e') {
                            cout<<"arrivee vide"<<endl;
                            animation.arrivee=Vec2i(i,j);
                            vector<Vec2i> deplacements;
                            damier.deplacement(animation.depart[0],animation.depart[1],deplacements);
            

                            if (std::find(deplacements.begin(), deplacements.end(), animation.arrivee) != (deplacements.end())) {
                                cout<<"deplacement autorise"<<endl;
                                
                                int couleur=damier.cases[animation.depart[0]][animation.depart[1]].couleur;
                                char piece =damier.cases[animation.depart[0]][animation.depart[1]].piece;
                                int indiceM=damier.cases[animation.depart[0]][animation.depart[1]].indiceM;
                                
                                damier.cases[animation.depart[0]][animation.depart[1]].couleur=damier.cases[i][j].couleur;
                                damier.cases[animation.depart[0]][animation.depart[1]].piece=damier.cases[i][j].piece;
                                damier.cases[animation.depart[0]][animation.depart[1]].indiceM=damier.cases[i][j].indiceM;
                                damier.cases[i][j].couleur=couleur;
                                damier.cases[i][j].piece=piece;
                                damier.cases[i][j].indiceM=indiceM;
                                superMesh.meshes[indiceM].deplacer(damier.cases[animation.depart[0]][animation.depart[1]].centre,damier.cases[i][j].centre);
                                if(damier.cases[i][j].piece=='o') damier.cases[i][j].piece='w';
                                if(damier.cases[i][j].piece=='p') damier.cases[i][j].piece='n';
                                animation.etatJeux=0;
                                animation.joueur=abs(1-animation.joueur);}
                            else animation.etatJeux=0;
                        }
                                
                        else if ((damier.cases[i][j].couleur)!=animation.joueur) {
                            char piece = damier.cases[animation.depart[0]][animation.depart[1]].piece;
                            vector<Vec2i> deplacements;
                            damier.deplacement(animation.depart[0],animation.depart[1],deplacements);
                            
                            if (std::find(deplacements.begin(), deplacements.end(), animation.arrivee) != (deplacements.end())) {
                            
                            if (piece=='p'||piece=='o'||piece=='w'||piece=='n') {
                                if ((Vec2i(i,j)==Vec2i(animation.depart[0]+1,animation.depart[1]))||(Vec2i(i,j)==Vec2i(animation.depart[0]+2,animation.depart[1]))||(Vec2i(i,j)==Vec2i(animation.depart[0]-1,animation.depart[1]))||(Vec2i(i,j)==Vec2i(animation.depart[0]-2,animation.depart[1]))) {
                                    animation.etatJeux=0;
                                    break;
                                }
                            }
                            
                            int indiceM=damier.cases[animation.depart[0]][animation.depart[1]].indiceM;
                            damier.cases[i][j].couleur=damier.cases[animation.depart[0]][animation.depart[1]].couleur;
                            damier.cases[i][j].piece=damier.cases[animation.depart[0]][animation.depart[1]].piece;
                            damier.cases[i][j].indiceM=indiceM;
                            damier.cases[animation.depart[0]][animation.depart[1]].couleur=-1;
                            damier.cases[animation.depart[0]][animation.depart[1]].piece='e';
                            damier.cases[animation.depart[0]][animation.depart[1]].indiceM=-1;
                            superMesh.meshes[indiceM].deplacer(damier.cases[animation.depart[0]][animation.depart[1]].centre,damier.cases[i][j].centre);
                            if(damier.cases[i][j].piece=='o') damier.cases[i][j].piece='w';
                            if(damier.cases[i][j].piece=='p') damier.cases[i][j].piece='n';
                            animation.etatJeux=0;
                            animation.joueur=abs(1-animation.joueur);
                        }
                        }

                        break;
                        
                    default:
                        break;
            
                }
                }}
            else { animation.etatJeux=0;}
            
        
    }
}
}


void motion (int x, int y) {
  camera.handleMouseMoveEvent (x, y);
}

void idle () {
  static float lastTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
  static unsigned int counter = 0;
  counter++;
  float currentTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
  if (currentTime - lastTime >= 1000.0f) {
    FPS = counter;
    counter = 0;
    static char winTitle [128];
      
    unsigned int numOfTriangles = superMesh.meshes[0].T.size ();
    unsigned int numOfSquares = superMesh.meshes[0].S.size ();

    sprintf (winTitle, "Number Of Triangles: %d & Number Of Squares: %d", numOfTriangles, numOfSquares);
    glutSetWindowTitle (winTitle);
    lastTime = currentTime;
  }
  glutPostRedisplay (); 
}


int main (int argc, char ** argv) {
  if (argc > 2) {
    printUsage ();
    exit (1);
  }
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize (DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT);
  window = glutCreateWindow (appTitle.c_str ());
  init (argc == 2 ? argv[1] : DEFAULT_MESH_FILE.c_str ());
  glutIdleFunc (idle);
  glutReshapeFunc (reshape);
  glutDisplayFunc (display);
  glutKeyboardFunc (key);
  glutMotionFunc (motion);
  glutMouseFunc (mouse);
  printUsage ();  
  glutMainLoop ();
  return 0;
}

