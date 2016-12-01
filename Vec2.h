//
//  Vec2.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 07/02/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Vec2_h
#define Vec2_h


#endif /* Vec2_h */


#pragma once

#include <cmath>
#include <iostream>

/// Vector in 2 dimensions, with basics operators overloaded.
template <class T>


class Vec2 {
    
public:
    inline Vec2 (void)	{ p[0] = p[1] = 0.0; }
    
    inline Vec2 (T p0, T p1) {
        p[0] = p0;
        p[1] = p1;
    };
    
   
    ~Vec2() {}
    
    inline Vec2 (const Vec2 & v) {
        init (v[0], v[1]);
    }
    
    inline Vec2 (T* pp) {
        p[0] = pp[0];
        p[1] = pp[1];
    };
    
    inline Vec2 & init (T x, T y) {
        p[0] = x;
        p[1] = y;
        return (*this);
    };
    
    
    //Operator
    
    inline T& operator[] (int Index) {
        return (p[Index]);
    };
    
    inline const T& operator[] (int Index) const {
        return (p[Index]);
    };
    
    inline Vec2& operator= (const Vec2 & P) {
        p[0] = P[0];
        p[1] = P[1];
        return (*this);
    };
    
    inline bool operator == (const Vec2 & a) const {
        return(p[0] == a[0] && p[1] == a[1]);
    };
   
    
protected:
    T p[2];

};

template <class T>
std::ostream & operator<< (std::ostream & output, const Vec2<T> & v) {
    output << v[0] << " " << v[1];
    return output;
}

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int> Vec2i;


