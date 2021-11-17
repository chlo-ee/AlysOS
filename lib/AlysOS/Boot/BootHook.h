#ifndef BootHook_h
#define BootHook_h

#include "config.h"
#include <Arduino.h>

#ifdef ALYS_FEATURE_DEBUG
#include "Debug/Debugger.h"
#endif

namespace Alys {
    class BootHook {
        public:
            typedef void (* vBootCallback)();

            BootHook(String name, vBootCallback callback);
            void execute();
            BootHook* next = NULL;

        private:
            vBootCallback callback = NULL;
            String name;
};
};

#endif