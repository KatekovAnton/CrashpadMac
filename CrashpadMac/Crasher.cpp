//
//  Crasher.cpp
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/03.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#include "Crasher.hpp"
#include <vector>



void Crasher::simulateCrash() {
    std::vector<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }

    a.insert(a.begin() + 1000000, 100);

}
