//
//  ViewController.m
//  PerlinNoise
//
//  Created by Sascha Sanzenbacher on 12.07.15.
//  Copyright (c) 2015 Sascha Sanzenbacher. All rights reserved.
//

#import "ViewController.h"

#import "PerlinNoiseGenerator.h"

#import <CoreGraphics/CGColorSpace.h>

@interface ViewController ()

- (void)updateImageView;

@end

@implementation ViewController

- (void)updateImageView
{
    char* data = gradient_bild(1024, 1024);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate((void*)data, 1024, 1024,
                                                 8,
                                                 1024*4, colorSpace,
                                                 kCGImageAlphaNoneSkipFirst);
    CGImageRef imageWithData = CGBitmapContextCreateImage(context);
    [self.image setImage:[UIImage imageWithCGImage:imageWithData]];
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(context);
    CGImageRelease(imageWithData);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    vector_im_einheitszkreis();
    [self updateImageView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
