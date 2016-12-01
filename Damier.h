//
//  Damier.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 05/02/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Damier_h
#define Damier_h


#endif /* Damier_h */

#ifndef Case_h
#define Case_h


#endif /* Case_h */



#include <cmath>
#include <vector>
#include "Vec3.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include "Vec2.h"
#include "Mesh.h"


class Case{
public:
    
    inline Case () {
        centre = Vec3f (0.0,0.0,0.0);
        couleur =-1;
        piece='e';
        indiceM=-1;}
    
    inline Case (Vec3f centre, int couleur, char piece,int indiceM) : centre (centre), couleur(couleur), piece(piece),indiceM(indiceM)  {}

    
    inline virtual ~Case() {}
    
    
    Vec3f centre;
    int couleur;
    char piece;
    int indiceM;
};

class Damier {
    
public:
    Case cases[8][8];
    Mesh mesh;
    
    Damier();
    
    void deplacement(int i, int j, std::vector<Vec2i>  & d) ;
    
    
    
};


