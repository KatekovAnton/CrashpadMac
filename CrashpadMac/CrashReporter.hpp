//
//  CrashReporter.hpp
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/03.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#ifndef CrashReporter_hpp
#define CrashReporter_hpp

#include <stdio.h>
#include <string>



class CrashReporter {
    
public:
    static bool StartCrashReporter(const std::string &pathToCrashReport, const std::string &pathToCrashHandler);
    
};

#endif /* CrashReporter_hpp */
