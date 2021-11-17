#ifndef Init_h
#define Init_h

#include "BootHook.h"

namespace Alys {
    class Init {
        public:
            static Init& getInstance() {
                static Init instance;
                return instance;
            };
            boolean addHook(BootHook *hook);
            void boot();

        private:
            BootHook *firstHook = NULL;
    };
};

#endif