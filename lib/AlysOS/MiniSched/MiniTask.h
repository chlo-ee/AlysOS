#include <Arduino.h>
#ifndef MiniTask_h
#define MiniTask_h

namespace Alys {
    class MiniTask {
    public:
        typedef void (* vTaskCallback)();
        enum ScheduleMode {
            ONCE,
            REPEAT
        };

        vTaskCallback callback;
        MiniTask::ScheduleMode mode;
        unsigned long plannedExecution;
        unsigned long interval;
        bool active;
        void execute();
        bool ready = false;
        String name = "";

        MiniTask *previousTask = NULL;
        MiniTask *nextTask = NULL;
    };
};

#endif