#include "Init.h"

boolean Alys::Init::addHook(BootHook *hook) {
    BootHook *previousHook = NULL;

    if (this->firstHook == NULL) {
        this->firstHook = hook;
    } else {
        previousHook = firstHook;
        while (previousHook->next != NULL) {
            previousHook = previousHook->next;
        }
        previousHook->next = hook;
    }
    return true;
}

void Alys::Init::boot() {
    BootHook *hook = firstHook;
    while (hook != NULL) {
        hook->execute();
        hook = hook->next;
    }
}