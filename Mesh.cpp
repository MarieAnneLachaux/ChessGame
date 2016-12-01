// --------------------------------------------------------------------------
// Copyright(C) 2009-2015
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
// --------------------------------------------------------------------------

#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "Vec3.h"

using namespace std;

/*void Mesh::loadOFF (const std::string & filename) {
    FILE * file = fopen(filename.c_str (), "r");
     if( file == NULL ){
        printf("Impossible to open the file !\n");
        }
    vector<Vec3f> N;
    
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    int gcurrent =0;

    
    
    while( 1 ){
        
      char lineHeader[128];
      // read the first word of the line
      int res = fscanf(file, "%s", lineHeader);
       if (res == EOF)
                  break; // EOF = End Of File. Quit the loop.
        
            // else : parse lineHeader

        if ( strcmp( lineHeader, "n" ) == 0 ){
            int VSize,NSize,TSize,SSize;
            fscanf(file, "%d %d %d %d\n",&VSize, &NSize, &TSize, &SSize);
            V.resize(VSize);
            N.resize(NSize);
            T.resize(TSize);
            S.resize(SSize);
            
        }
        
        else if (strcmp( lineHeader, "g" ) == 0 ){
        
        fscanf(file, "%d\n", &gcurrent );

        }
        
        else if ( strcmp( lineHeader, "v" ) == 0 ){
            Vertex vertex;
            fscanf(file, "%f %f %f\n", &vertex.p[0], &vertex.p[1], &vertex.p[2] );
            V[i]=vertex;
            V[i].g=gcurrent;
            i++;
        }
        
    
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            Vec3f normale;
            fscanf(file, "%f %f %f\n", &normale[0], &normale[1], &normale[2]);
            N[j]=normale;
            j++;
        }
        
       
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            
            unsigned int vertexIndex[4], normalIndex[4], uvIndex[4];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0],&normalIndex[0], &vertexIndex[1],&uvIndex[1], &normalIndex[1], &vertexIndex[2],&uvIndex[2], &normalIndex[2],&vertexIndex[3],&uvIndex[3], &normalIndex[3]);

            if (matches == 9){
                
                V[vertexIndex[0]-1].n=N[normalIndex[0]-1];  // Attribution des normales aux sommets
                V[vertexIndex[1]-1].n=N[normalIndex[1]-1];
                V[vertexIndex[2]-1].n=N[normalIndex[2]-1];
                
                T[k].ve[0] = vertexIndex[0]-1;  // On remplit la liste des triangles avec l'indice des vertex
                T[k].ve[1] = vertexIndex[1]-1;
                T[k].ve[2] = vertexIndex[2]-1;
                k++;
                
            }
            else if (matches == 12){
                V[vertexIndex[0]-1].n=N[normalIndex[0]-1];
                V[vertexIndex[1]-1].n=N[normalIndex[1]-1];
                V[vertexIndex[2]-1].n=N[normalIndex[2]-1];
                V[vertexIndex[3]-1].n=N[normalIndex[3]-1];
                
                S[l].v[0] = vertexIndex[0]-1; // on remplit la liste des carrés avec l'indice de sommets
                S[l].v[1] = vertexIndex[1]-1;
                S[l].v[2] = vertexIndex[2]-1;
                S[l].v[3] = vertexIndex[3]-1;
                l++;
            }
            
            
            
            else {printf("File can't be read by our simple parser :  Try exporting with other options\n");}
    }

}
    
    centerAndScaleToUnit();
    //recomputeNormals();
   
}*/

void Mesh::recomputeNormals () {
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n = Vec3f (0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < T.size (); i++) {
        Vec3f e01 = V[T[i].ve[1]].p -  V[T[i].ve[0]].p;
        Vec3f e02 = V[T[i].ve[2]].p -  V[T[i].ve[0]].p;
        Vec3f n = cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 3; j++)
            V[T[i].ve[j]].n += n;
    }
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n.normalize ();
    
    for (unsigned int i = 0; i < S.size (); i++) {
        Vec3f e01 = V[S[i].v[1]].p -  V[S[i].v[0]].p;
        Vec3f e02 = V[S[i].v[2]].p -  V[S[i].v[0]].p;
        Vec3f n = cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 4; j++)
            V[S[i].v[j]].n += n;
    }
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n.normalize ();
}


void Mesh::centerAndScaleToUnit () {
    Vec3f c;
    for  (unsigned int i = 0; i < V.size (); i++)
        c += V[i].p;
    c /= V.size ();
    float maxD = dist (V[0].p, c);
    for (unsigned int i = 0; i < V.size (); i++){
        float m = dist (V[i].p, c);
        if (m > maxD)
            maxD = m;
    }
    for  (unsigned int i = 0; i < V.size (); i++)
        V[i].p = (V[i].p - c) / maxD;
}

void Mesh::deplacer(Vec3f position1, Vec3f position2) {

    
    int n = V.size();
    Vec3f deplacement = position2 - position1;
    
    for(int i=0;i<n;i++){
        V[i].p+=deplacement;
    }
    
    
}
    
    
