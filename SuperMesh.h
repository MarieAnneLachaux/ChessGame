//
//  SuperMesh.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 26/01/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef SuperMesh_h
#define SuperMesh_h

#endif /* SuperMesh_h */

#include "Mesh.h"

class SuperMesh {
public:
    void loadOFF (const std::string & filename);
    void centerAndScaleToUnit ();

    std::vector<Mesh> meshes;
};