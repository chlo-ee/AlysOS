#ifndef DebugHook_h
#define DebugHook_h

#include <Arduino.h>

namespace Alys {
    class DebugHook {
        public:
            typedef void (* vDebugCallback)(String msg);

            DebugHook(String name, vDebugCallback callback);
            void execute(String msg);
            DebugHook* previous = NULL;
            DebugHook* next = NULL;

        private:
            vDebugCallback callback = NULL;
            String name;
    };
}

#endif