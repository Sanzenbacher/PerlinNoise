//
//  PerlinNoiseGenerator.cpp
//  PerlinNoise
//
//  Created by Sascha Sanzenbacher on 12.07.15.
//  Copyright (c) 2015 Sascha Sanzenbacher. All rights reserved.
//

#include "PerlinNoiseGenerator.h"
#include <math.h>
#include <algorithm>

float Gradient[Gradientsize_X][Gradientsize_Y][2];

void gradient_ausgeben()
{
    for(int x=0;x<Gradientsize_X;x++)
    {
        for(int y=0;y<Gradientsize_Y;y++)
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
    
    for(int x=0;x<Gradientsize_X;x++)
    {
        for(int y=0;y<Gradientsize_Y;y++)
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

float gradient_berechnen(float x, float y, unsigned hoehe, unsigned breite)
{
    unsigned x1, x2, y1, y2;
    float xgrad, ygrad;
    xgrad= x / ((float)breite / (float)Gradientsize_X);
    ygrad= y / ((float)hoehe / (float)Gradientsize_Y );
    
    x1 = floor(xgrad);
    x2 = ceil(xgrad);
    y1 = floor(ygrad);
    y2 = ceil(ygrad);
    
    float v1x, v2x, v3x, v4x, v1y, v2y, v3y, v4y;

	if ((x > 100) && (y > 100)) {
		v1x = 1; }
    v1x = xgrad - x1;
    v1y = ygrad - y1;
    
    v2x = xgrad - x2;
    v2y = ygrad - y1;
    
    v3x = xgrad - x1;
    v3y = ygrad - y2;
    
    v4x = xgrad - x2;
    v4y = ygrad - y2;
    
    
    float s1, s2, s3, s4;
    
    s1 = v1x * Gradient[x1][y1][0]+ v1y * Gradient[x1][y1][1];
    s2 = v2x * Gradient[x2][y1][0]+ v2y * Gradient[x2][y1][1];
    s3 = v3x * Gradient[x1][y2][0]+ v3y * Gradient[x1][y2][1];
    s4 = v4x * Gradient[x2][y2][0]+ v4y * Gradient[x2][y2][1];
    
    float d1, d2;
    
    d1 = xgrad - x1;
    d2 = ygrad - y1;
    
    float si, si2;
    
    si  = d1*s1 + (1-d1)*s2;
    si2 = d1*s4 + (1-d1)*s3;
    
    return d2*si + (1-d2)*si2;
    
}

char* gradient_bild(unsigned hoehe, unsigned breite)
{
    char* bild = new char[hoehe*breite*4]; //RGB    32 bpp, 8 bpc, kCGImageAlphaNoneSkipFirst
    for(int x=0;x<breite;x++)
    {
        for(int y=0;y<hoehe;y++)
        {
            bild[(x+breite*y)*4]=0;
            bild[(x+breite*y)*4+1]=0;//1.0/ std::max<float>(gradient_berechnen(x, y, hoehe, breite),0.00001)*32;
            bild[(x+breite*y)*4+2]=gradient_berechnen(x, y, hoehe, breite)*255;
            bild[(x+breite*y)*4+3]=0;
        }
    }
    return bild;
}