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
#include "client/crash_report_database.h"
#include "client/settings.h"
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







static crashpad::CrashpadClient *_client = nullptr;
bool CrashReporter::StartCrashReporter(const std::string &pathToCrashReport, const std::string &pathToCrashHandler)
{
#define CRASHED_DBNAME "EMAIL"
#define CRASHED_APPNAME "APP_MAC"
#define CRASHED_APPVERSION "0.0.1"
    std::string url;
    url = "https://";
    url += CRASHED_DBNAME;
    url += "deadbrains.com/crashserver";
    
    std::map<std::string, std::string> annotations;
    annotations["format"] = "minidump";        // Crashpad setting to save crash as a minidump
    annotations["prod"].assign(CRASHED_APPNAME);            // appName
    annotations["ver"].assign(CRASHED_APPVERSION);    // appVersion
    annotations["key"] = "Sample key";            // Optional key field
    annotations["email"] = "smapleemail@gmail.com";    // Optional user email
    annotations["comments"] = "Sample comment";    // Optional crash description
    
    base::FilePath filePathToCrashReport(pathToCrashReport);
    base::FilePath filePathToCrashHandler(pathToCrashHandler);
    
    // Tutorial
    // https://help.backtrace.io/en/articles/2337714-crashpad-integration-guide
    
    std::vector<std::string> arguments;
#if defined DEBUG
    /*
     * REMOVE THIS FOR ACTUAL BUILD.
     *
     * To disable crashpad’s default limitation of
     * 1 upload per hour, pass the --no-rate-limit
     * argument to the handler
     *
     */
    arguments.push_back("--no-rate-limit");
#endif
    

    std::unique_ptr<crashpad::CrashReportDatabase> database =
        crashpad::CrashReportDatabase::Initialize(filePathToCrashReport);
    
    if (database == nullptr || database->GetSettings() == NULL) {
        return false;
    }

    /* Enable automated uploads. */
    bool ok = database->GetSettings()->SetUploadsEnabled(true);
//    if (!ok) { // always ok
//        return false;
//    }
    
    // error
    // maybe this https://stackoverflow.com/questions/48438404/cant-call-ioutil-readdir-on-dev-fd-on-macos
    _client = new crashpad::CrashpadClient();
    bool started = _client->StartHandler(filePathToCrashHandler, filePathToCrashReport, filePathToCrashReport, url, annotations, arguments, false, false);
    if (!started) {
        return false;
    }
    
    return true;
    
}
