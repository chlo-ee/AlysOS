#ifndef alys_h
#include <Arduino.h>
#include "config.h"
#include "kernel.h"

#include <Boot/Init.h>
#include <MiniSched/MiniSched.h>

#ifdef ALYS_FEATURE_DEBUG
#include <Debug/Debugger.h>
#endif

#ifdef ALYS_FEATURE_FS
#include <FS/FsManager.h>
#endif

namespace Alys {
    #ifdef ALYS_FEATURE_FS

    //=== Init File System
    void boot_initFilesystem() {
        if (FsManager::getInstance().init()) {
            alys_debug("Filesystem OK!");
        } else {
            alys_panic("[PANIC] Filesystem could not be initialized!", false);
        }
    }
    BootHook bootInitFilesystem = BootHook("Initialize Filesystem", boot_initFilesystem);
    boolean boot_initFilesystem_active = Init::getInstance().addHook(&bootInitFilesystem);

    #endif
}

#endif