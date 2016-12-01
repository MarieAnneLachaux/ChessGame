//
//  Ray.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 06/02/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Ray_h
#define Ray_h


#include "Mesh.h"

class Ray {
    
public:
    inline Ray () {}
    inline Ray (const Vec3f & o, const Vec3f & w) : origin(o), direction(normalize(w)) {} //attention a bien normaliser la direction
    inline virtual ~Ray () {}
    Vec3f origin;
    Vec3f direction;
    inline bool intersectionRayonTriangle(Vertex p0, Vertex p1, Vertex p2){
        Vec3f e0 = p1.p-p0.p;
        Vec3f e1 = p2.p - p0.p;
        Vec3f n = cross(e0, e1) / cross(e0, e1).length() ; //normale au triangle renormalisée
        Vec3f q= cross(direction, e1);
        float a= dot(e0, q);
        
        if (dot(n,direction)>0 || fabs(a)<0.005f) {
        return false;
        } //condition pour savoir si on est pas dans la "sortie" du triangle considérée comme un volume
        
        Vec3f s= (origin - p0.p)/a;
        Vec3f r=cross(s,e0);
        float b0 = dot(s,q);
        float b1 = dot (r,direction);
        float b2 = 1 - b0 - b1;
        
        if (b0<0 || b1 <0 || b2 <0) {
            return false;
        }
        
        float t = dot (e1,r);
        if (t>=0) {return true;}
        
        return false;
    }
    
};


#endif /* Ray_h */
