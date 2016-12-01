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

#pragma once
#include <cmath>
#include <vector>
#include "Vec3.h"

/// A simple vertex class storing position and normal
class Vertex {
public:
    inline Vertex () {}
    inline Vertex (const Vec3f & p, const Vec3f & n) : p (p), n (n) {}
    inline virtual ~Vertex () {}
    Vec3f p;
    Vec3f n;
    Vec3f vt;
    
};


/// A Triangle class expressed as a triplet of indices (over an external vertex list)
class Triangle {
public:
    inline Triangle () {
        ve[0] = ve[1] = ve[2] = 0;
    }
    inline Triangle (const Triangle & t) {
        ve[0] = t.ve[0];
        ve[1] = t.ve[1];
        ve[2] = t.ve[2];
    }
    inline Triangle (unsigned int v0, unsigned int v1, unsigned int v2) {
        ve[0] = v0;
        ve[1] = v1;
        ve[2] = v2;
    }
    inline virtual ~Triangle () {}
    inline Triangle & operator= (const Triangle & t) {
        ve[0] = t.ve[0];
        ve[1] = t.ve[1];
        ve[2] = t.ve[2];
        return (*this);
    }
    unsigned int ve[3];
};

class Square {
public:
    inline Square () {
        v[0] = v[1] = v[2] = v[3]= 0;
    }
    inline Square (const Square & s) {
        v[0] = s.v[0];
        v[1] = s.v[1];
        v[2] = s.v[2];
        v[3] = s.v[3];
    }
    inline Square (unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
        v[3] = v3;
    }
    
    inline virtual ~Square () {}
    
    inline Square & operator= (const Square & s) {
        v[0] = s.v[0];
        v[1] = s.v[1];
        v[2] = s.v[2];
        v[3] = s.v[3];
        return (*this);
    }
    unsigned int v[4];
};




/// A Mesh class, storing a list of vertices and a list of triangles indexed over it.
class Mesh {
public:
	std::vector<Vertex> V;
	std::vector<Triangle> T;
    std::vector<Square> S;
    

    /// Loads the mesh from a <file>.off
	//void loadOFF (const std::string & filename);
    
    /// Compute smooth per-vertex normals
    void recomputeNormals ();

    /// scale to the unit cube and center at original
    void centerAndScaleToUnit ();
    
   void deplacer(Vec3f pocition1, Vec3f position2);
    
};
