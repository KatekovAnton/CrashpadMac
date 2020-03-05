//
//  FileManager.m
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/04.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#import "FileManager.h"

NSString *applicationDataDirectory()
{
    NSFileManager* fileManager = [[NSFileManager alloc] init];
    NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
    NSArray* urlPaths = [fileManager URLsForDirectory:NSApplicationSupportDirectory
                                            inDomains:NSUserDomainMask];
    
    NSURL* appDirectory = [[urlPaths objectAtIndex:0] URLByAppendingPathComponent:bundleID isDirectory:YES];
    
    //TODO: handle the error
    if (![fileManager fileExistsAtPath:[appDirectory path]]) {
        [fileManager createDirectoryAtURL:appDirectory withIntermediateDirectories:NO attributes:nil error:nil];
    }
    return [appDirectory path];
}

@implementation FileManager

+ (NSString *)fileSavePathWithFileName:(NSString *)fileName
{
    NSString *basePath = applicationDataDirectory();
    NSString* fullFilePath = [basePath stringByAppendingPathComponent:fileName];
    return fullFilePath;
}

+ (NSString *)fileBundlePathWithFileName:(NSString *)fileName
{
    NSString *filePath = [[NSBundle mainBundle] pathForAuxiliaryExecutable:fileName];
    return filePath;
}

@end
