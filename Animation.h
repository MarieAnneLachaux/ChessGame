//
//  Animation.h
//  
//
//  Created by Marie-Anne Lachaux on 06/02/2016.
//
//

#ifndef Animation_h
#define Animation_h



#endif /* Animation_h */
#include "Vec2.h"

class Animation {
    
    public :
    
    Vec2i depart;
    Vec2i arrivee;
    int etatJeux;
    int joueur;
    
    inline Animation () {
        joueur=1;
        etatJeux=0;
    }
    
    
};