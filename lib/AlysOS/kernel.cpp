#include "kernel.h"

void Alys::alys_panic(String message, boolean hard) {
    if (hard) {
        ESP.reset();
    }
    alys_debug(message);
    ESP.restart();
}

void Alys::alys_debug(String message) {
    #ifdef ALYS_FEATURE_DEBUG
    Alys::Debugger::getInstance().println(message);
    #endif
}