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

#define X 1024
#define Y 1024

extern float Gradient[X][Y][2];

void gradient_ausgeben();

void vector_im_einheitszkreis();

char* gradient_bild(unsigned hoehe, unsigned breite);

#endif /* defined(__PerlinNoise__PerlinNoiseGenerator__) */
