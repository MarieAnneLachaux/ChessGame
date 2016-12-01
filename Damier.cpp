//
//  Damier.cpp
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 07/02/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//


#include"Damier.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

Damier::Damier() {
    
    //Creation du damier
    // remplissage centre
    for (int j=0;j<8;j++){
        for (int i=0;i<8;i++) {
            cases[i][j].centre = Vec3f(-0.678604+0.086210375+j*0.17242075,0.678604+0.086408-i*0.172816,0.0);
            
        }
    }
    
    for (int i=2;i<6;i++) {                 // remplissage couleur
        for (int j=0;j<8;j++) {
            cases[i][j].couleur=-1;
        }
    }
    for (int i=0;i<2;i++) {
        for (int j=0;j<8;j++) {
            cases[i][j].couleur=0;
        }
    }
    
    for (int i=6;i<8;i++) {
        for (int j=0;j<8;j++) {
            cases[i][j].couleur=1;
        }
    }
    
    for (int i=0;i<2;i++) {
        for (int j=0;j<8;j++) {
            cases[i][j].piece='e';
        }
    }
    
    for(int j=0;j<8;j++){                   // remplissage piece
        cases[1][j].piece='p';
        cases[6][j].piece='o';
    }
    cases[0][0].piece='t';
    cases[0][7].piece='t';
    cases[7][0].piece='t';
    cases[7][7].piece='t';
    cases[0][1].piece='h';
    cases[0][6].piece='h';
    cases[7][1].piece='h';
    cases[7][6].piece='h';
    cases[0][2].piece='b';
    cases[0][5].piece='b';
    cases[7][2].piece='b';
    cases[7][5].piece='b';
    cases[0][3].piece='q';
    cases[7][3].piece='q';
    cases[0][4].piece='k';
    cases[7][4].piece='k';
    
    cases[7][0].indiceM=1; 
    cases[7][1].indiceM=2;
    cases[7][2].indiceM=4;
    cases[7][3].indiceM=3;
    cases[7][4].indiceM=24;
    cases[7][5].indiceM=5;
    cases[7][6].indiceM=6;
    cases[7][7].indiceM=7;
    
    cases[6][0].indiceM=16;
    cases[6][1].indiceM=17;
    cases[6][2].indiceM=18;
    cases[6][3].indiceM=19;
    cases[6][4].indiceM=20;
    cases[6][5].indiceM=21;
    cases[6][6].indiceM=22;
    cases[6][7].indiceM=23;
    
    cases[0][0].indiceM=15;
    cases[0][1].indiceM=11;
    cases[0][2].indiceM=9;
    cases[0][3].indiceM=12;
    cases[0][4].indiceM=13;
    cases[0][5].indiceM=8;
    cases[0][6].indiceM=10;
    cases[0][7].indiceM=14;
    
    
    cases[1][0].indiceM=32;
    cases[1][1].indiceM=31;
    cases[1][2].indiceM=30;
    cases[1][3].indiceM=29;
    cases[1][4].indiceM=28;
    cases[1][5].indiceM=27;
    cases[1][6].indiceM=26;
    cases[1][7].indiceM=25;
    
}

void Damier::deplacement(int k, int l, vector<Vec2i> & d) {
    int i, j;
    int indice ;
    
    switch (cases[k][l].piece) {
    
    case 't':
            indice=0;
            d.resize(14,Vec2i(-1,-1));
            
            j=l;
            i=k+1;
            if (i<8) { d[indice]=Vec2i(i,l);
                indice ++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                if (i>7) break;
                d[indice]=Vec2i(i,l);
                indice++;
            }
            i=k-1;
            if (i>=0) {d[indice]=Vec2i(i,l);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                if (i<0) break;
                d[indice]=Vec2i(i,l);
                indice++;
            }
            i=k;
            j=l+1;
            if (j<8) {d[indice]=Vec2i(k,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                j+=1;
                if (j>7) break;
                d[indice]=Vec2i(k,j);
                indice++;
            }
            j=l-1;
            if (j>=0){ d[indice]=Vec2i(k,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                j-=1;
                if (j<0) break;
                d[indice]=Vec2i(k,j);
                indice++;
            }

               break;
            
    case 'b':
            indice=0;
            d.resize(14,Vec2i(-1,-1));

            j=l+1;
            i=k+1;
            if (i<8 || j<8){
                d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                j+=1;
                if (i>7 || j>7) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l-1;
            i=k-1;
            if (i>=0 || j>=0) {d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                j-=1;
                if (i<0 || j<0) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l+1;
            i=k-1;
            if (i>=0 || j<8) { d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                j+=1;
                if (i<0 || j>7) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l-1;
            i=k+1;
            if (i<8 || j>=0) { d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                j-=1;
                if (i>7 || j<0) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
           
            break;
            
    case 'q':
            indice=0;
            d.resize(21,Vec2i(-1,-1));

            j=l;
            i=k+1;
            if (i<8) { d[indice]=Vec2i(i,l);
                indice++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                if (i>7) break;
                d[indice]=Vec2i(i,l);
                indice++;
            }
            i=k-1;
            if (i>=0){ d[indice]=Vec2i(i,l);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                if (i<0) break;
                d[indice]=Vec2i(i,l);
                indice++;
            }
            i=k;
            j=l+1;
            if (j<8) {d[indice]=Vec2i(k,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                j+=1;
                if (j>7) break;
                d[indice]=Vec2i(k,j);
                indice++;
            }
            j=l-1;
            if (j>=0) {d[indice]=Vec2i(k,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                j-=1;
                if (j<0) break;
                d[indice]=Vec2i(k,j);
                indice++;
            }
            j=l+1;
            i=k+1;
            if (i<8 || j<8) { d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                j+=1;
                if (i>7 || j>7) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l-1;
            i=k-1;
            if (i>=0 || j>=0) {d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                j-=1;
                if (i<0 || j<0) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l+1;
            i=k-1;
            if (i>=0 || j<8) { d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i-=1;
                j+=1;
                if (i<0 || j>7) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
            j=l-1;
            i=k+1;
            if (i<8 || j>=0) {d[indice]=Vec2i(i,j);
                indice++;}
            while (cases[i][j].piece=='e'){
                i+=1;
                j-=1;
                if (i>7 || j<0) break;
                d[indice]=Vec2i(i,j);
                indice++;
            }
            
          
            break;
           
            
    case 'k':
            indice=0;
            d.resize(8,Vec2i(-1,-1));
            i=k;
            j=l;
            
            if (j+1<8)
                {d[indice]=Vec2i(i,j+1);
                indice++;}
            if (i+1<8){
                d[indice]=Vec2i(i+1,j);
                indice++;}
            if (0<=j-1){
                d[indice]=Vec2i(i,j-1);
                indice++;}
            if (0<=i-1){
                d[indice]=Vec2i(i-1,j);
                indice++;}
            if (j+1<8 && i+1<8){
                d[indice]=Vec2i(i+1,j+1);
                indice++;}
            if (0<=j-1 && 0<=i-1){
                d[indice]=Vec2i(i-1,j-1);
                indice++;}
            if (0<=i-1 && j+1<8){
                d[indice]=Vec2i(i-1,j+1);
                indice++;}
            if (0<=j-1 && i+1<8){
                d[indice]=Vec2i(i+1,j-1);
                indice++;}
            break;
            
        case 'h' :
            indice=0;
            d.resize(8,Vec2i(-1,-1));
            i=k;
            j=l;
            if ((0<=i-2)&&(j+1<8)){
                d[indice]=Vec2i(i-2,j+1);
                indice++;}
            if ((0<=i-1)&&(j+2<8)){
                d[indice]=Vec2i(i-1,j+2);
                indice++;}
            if ((i+1<8)&&(j+2<8)){
               d[indice]=Vec2i(i+1,j+2);
                indice++;}
            if ((i+2<8)&&(j+1<8)){
                d[indice]=Vec2i(i+2,j+1);
                indice++;}
            if (i+2<8 && 0<=j-1){
                d[indice]=Vec2i(i+2,j-1);
                indice++;}
            if (0<=j-2 && i+1<8){
                d[indice]=Vec2i(i+1,j-2);
                indice++;}
            if (0<=i-1 && 0<=j-2){
                d[indice]=Vec2i(i-1,j-2);
                indice++;}
            if (0<=i-2 && 0<=j-1){
                d[indice]=Vec2i(i-2,j-1);
                indice++;}
            break;
        
        case 'o' :
            indice=0;
            d.resize(4,Vec2i(-1,-1));
            i=k;
            j=l;
            if ( cases[i-1][j].piece=='e'){ d[indice]=Vec2i(i-1,j); indice++;}
            if ( cases[i-1][j].piece=='e' && cases[i-2][j].piece=='e') {d[indice]=Vec2i(i-2,j);
                indice++;}
            if (0<=j-1){
                if ( !(cases[i-1][j-1].piece=='e')) {d[indice]=Vec2i(i-1,j-1);indice++;}}
            if (j+1<8) {
                if ( !(cases[i-1][j+1].piece=='e')) {d[indice]=Vec2i(i-1,j+1);indice++;}}
        break;
        
        case 'p' :
            indice=0;
            d.resize(4,Vec2i(-1,-1));
            i=k;
            j=l;
                if ( cases[i+1][j].piece=='e') {d[indice]=Vec2i(i+1,j); indice++;}
                if ( cases[i+1][j].piece=='e' && cases[i+2][j].piece=='e') {d[indice]=Vec2i(i+2,j); indice++;}
            
            if (0<=j-1){
                if ( !(cases[i+1][j-1].piece=='e')){ d[indice]=Vec2i(i+1,j-1);indice++;}}
            if (j+1<8) {
                if ( !(cases[i+1][j+1].piece=='e')){ d[indice]=Vec2i(i+1,j+1);indice++;}}
        break;
            
        case 'w' :
            indice=0;
            d.resize(3,Vec2i(-1,-1));
            i=k;
            j=l;
            
            if(0<=i-1) {
                if ( cases[i-1][j].piece=='e'){ d[indice]=Vec2i(i-1,j); indice++;}
            if (0<=j-1){
                if ( !(cases[i-1][j-1].piece=='e')) {d[indice]=Vec2i(i-1,j-1);indice++;}}
            if (j+1<8) {
                if ( !(cases[i-1][j+1].piece=='e')){ d[indice]=Vec2i(i-1,j+1);indice++;}}}
        break;
            
        case 'n' :
            indice=0;
            d.resize(3,Vec2i(-1,-1));
            i=k;
            j=l;
            
            if(i+1<8) {
                if ( cases[i+1][j].piece=='e') {d[indice]=Vec2i(i+1,j); indice++;}
                if (0<=j-1){
                    if ( !(cases[i+1][j-1].piece=='e')) {d[indice]=Vec2i(i+1,j-1); indice++;}}
                if (j+1<8) {
                    if ( !(cases[i+1][j+1].piece=='e')){ d[indice]=Vec2i(i+1,j+1); indice++;}}}
        break;
            
        default:
            
        break;
            
    }
    
    }
    
    
    
    







