#ifndef Debugger_h
#define Debugger_h

#include "config.h"
#include "DebugHook.h"

namespace Alys {
    class Debugger {
        public:
            static Debugger& getInstance() {
                static Debugger instance;
                return instance;
            };

            void addHook(DebugHook *hook);
            void removeHook(DebugHook *hook);
            void println(String msg);

        private:
            DebugHook *firstHook = NULL;
    };
};

#endif