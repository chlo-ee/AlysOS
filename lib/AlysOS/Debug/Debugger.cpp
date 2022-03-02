#include "Debugger.h"

void Alys::Debugger::addHook(DebugHook *hook) {
    DebugHook *previousHook = NULL;

    if (this->firstHook == NULL) {
        this->firstHook = hook;
    } else {
        previousHook = firstHook;
        while (previousHook->next != NULL) {
            previousHook = previousHook->next;
        }
        previousHook->next = hook;
    }
    hook->previous = previousHook;
}

void Alys::Debugger::removeHook(DebugHook *hook) {
    if (this->firstHook == NULL) return;

    DebugHook *previousHook = firstHook;
    while (previousHook->next != hook) {
        if (previousHook->next == NULL) return;
        previousHook = previousHook->next;
    }
    previousHook->next = hook->next;

    if(hook->next != NULL) {
        hook->next->previous = previousHook;
    }
}

void Alys::Debugger::println(String msg) {
    DebugHook *hook = firstHook;
    while (hook != NULL) {
        hook->execute(msg);
        hook = hook->next;
    }
}
