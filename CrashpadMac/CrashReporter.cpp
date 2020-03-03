//
//  CrashReporter.cpp
//  CrashpadMac
//
//  Created by Anton Katekov on 2020/03/03.
//  Copyright © 2020 Anton Katekov. All rights reserved.
//

#include "CrashReporter.hpp"

#include <errno.h>
#include <mach/mach.h>
#include <pthread.h>
#include <stdint.h>
#include <memory>
#include <utility>

#include "client/crashpad_client.h"
#include "base/logging.h"
#include "base/mac/mach_logging.h"
#include "base/strings/stringprintf.h"
#include "util/mac/mac_util.h"
#include "util/mach/child_port_handshake.h"
#include "util/mach/exception_ports.h"
#include "util/mach/mach_extensions.h"
#include "util/mach/mach_message.h"
#include "util/mach/notify_server.h"
#include "util/misc/clock.h"
#include "util/misc/implicit_cast.h"
#include "util/posix/double_fork_and_exec.h"


CrashReporter::CrashReporter()
{
}



