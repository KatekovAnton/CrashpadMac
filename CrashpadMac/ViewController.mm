//
//  ViewController.m
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/03.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#import "ViewController.h"
#include "Crasher.hpp"


@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)onSimulateCrash:(id)sender {
    Crasher::simulateCrash();
}


@end
