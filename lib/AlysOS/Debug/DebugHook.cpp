#include "DebugHook.h"

Alys::DebugHook::DebugHook(String name, vDebugCallback callback) {
    this->name = name;
    this->callback = callback;
}

void Alys::DebugHook::execute(String msg) {
    if (callback != NULL) {
        callback(msg);
    }
}