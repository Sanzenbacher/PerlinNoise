//
//  PerlinNoiseGenerator.cpp
//  PerlinNoise
//
//  Created by Sascha Sanzenbacher on 12.07.15.
//  Copyright (c) 2015 Sascha Sanzenbacher. All rights reserved.
//

#include "PerlinNoiseGenerator.h"

float Gradient[X][Y][2];

void gradient_ausgeben()
{
    for(int x=0;x<X;x++)
    {
        for(int y=0;y<Y;y++)
        {
            printf("(%f,%f)",Gradient[x][y][0], Gradient[x][y][1]);
            //printf("%f ", sqrt(pow(Gradient[x][y][0], 2) + pow(Gradient[x][y][1], 2)));
        }
        printf("\n");
        
    }
}

void vector_im_einheitszkreis()
{
    srand((unsigned)time(NULL));
    
    float zufallszahl1 ,zufallszahl2, laenge;
    
    for(int x=0;x<X;x++)
    {
        for(int y=0;y<Y;y++)
        {
            zufallszahl1 = (float)rand();
            zufallszahl2 = (float)rand();
            laenge = sqrt(pow(zufallszahl1, 2) + pow(zufallszahl2, 2));
            Gradient[x][y][0]=zufallszahl1/laenge;
            Gradient[x][y][1]=zufallszahl2/laenge;
        }
    }
    
    //gradient_ausgeben();
}

char* gradient_bild(unsigned hoehe, unsigned breite)
{
    char* bild = new char[hoehe*breite*4]; //RGB    32 bpp, 8 bpc, kCGImageAlphaNoneSkipFirst
    for(int x=0;x<X;x++)
    {
        for(int y=0;y<Y;y++)
        {
            bild[(x+breite*y)*4]=255;
            bild[(x+breite*y)*4+1]=(char)(Gradient[x][y][0]*255.0);
            bild[(x+breite*y)*4+2]=0;
            bild[(x+breite*y)*4+3]=0;
        }
    }
    return bild;
}