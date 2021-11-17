#ifndef kernel_h
#include <Arduino.h>
#include "config.h"

#include <Boot/Init.h>
#include <Boot/BootHook.h>

#ifdef ALYS_FEATURE_DEBUG
#include <Debug/Debugger.h>
#endif

namespace Alys {
    void alys_panic(String message, boolean hard);
    void alys_debug(String message);
}

#endif