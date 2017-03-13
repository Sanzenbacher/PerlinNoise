//
//  PerlinNoiseGenerator.h
//  PerlinNoise
//
//  Created by Sascha Sanzenbacher on 12.07.15.
//  Copyright (c) 2015 Sascha Sanzenbacher. All rights reserved.
//

#ifndef __PerlinNoise__PerlinNoiseGenerator__
#define __PerlinNoise__PerlinNoiseGenerator__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define Gradientsize_X 32
#define Gradientsize_Y 32

extern float Gradient[Gradientsize_X][Gradientsize_Y][2];

void gradient_ausgeben();

void vector_im_einheitszkreis();

void gradient_bild(unsigned char* bild, unsigned hoehe, unsigned breite);

#endif /* defined(__PerlinNoise__PerlinNoiseGenerator__) */
