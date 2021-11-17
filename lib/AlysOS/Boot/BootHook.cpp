#include "BootHook.h"

Alys::BootHook::BootHook(String name, vBootCallback callback) {
    this->name = name;
    this->callback = callback;
}

void Alys::BootHook::execute() {
    if (callback != NULL) {
        #ifdef ALYS_FEATURE_DEBUG
        Debugger::getInstance().println("[BOOT] Reached hook: " + name);
        #endif
        callback();
    }
}