//
//  ViewController.m
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/03.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#import "ViewController.h"
#import "FileManager.h"

#include "Crasher.hpp"
#include "CrashReporter.hpp"



@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    
    NSString *crashReportFilePath = [FileManager fileSavePathWithFileName:@"crashReport.anton"];
    std::string crashReportFilePathStr = std::string([crashReportFilePath UTF8String]);
    NSString *crashhandlerFilePath = [FileManager fileBundlePathWithFileName:@"crashpad_handler"];
    std::string crashhandlerFilePathStr = std::string([crashhandlerFilePath UTF8String]);
    
    bool success = CrashReporter::StartCrashReporter(crashReportFilePathStr, crashhandlerFilePathStr);
    
    _textCrashReport.stringValue = crashReportFilePath;
    _textCrashHandler.stringValue = crashhandlerFilePath;
    if (success) {
        _textStartSuccess.stringValue = @"Start: success";
    }
    else {
        _textStartSuccess.stringValue = @"Start: failed";
    }
    
    
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)onSimulateCrash:(id)sender {
    Crasher::simulateCrash();
}


@end
