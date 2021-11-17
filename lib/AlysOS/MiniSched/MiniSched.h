#ifndef MiniSched_h
#define MiniSched_h
#include <Arduino.h>
#include "MiniTask.h"

#define MINISCHED_STAT_CYCLE_MS 1000
#define MINISCHED_MAX_IDLE_TIME 100

//#define MINISCHED_DEBUG

namespace Alys
{
    class MiniSched {
    public:
        static MiniSched& getInstance()
        {
            static MiniSched instance;
            return instance;
        }

        MiniTask *schedule(MiniTask::vTaskCallback, MiniTask::ScheduleMode mode, unsigned long delay);
        MiniTask *schedule(MiniTask::vTaskCallback, MiniTask::ScheduleMode mode, unsigned long delay, String name);
        MiniTask *schedule(MiniTask *task);
        unsigned long execute();
        u8 getLastLoad();
        unsigned long getCycleCounter();
        void addTimeToStatistics(unsigned long time);

    private:
        MiniSched();
        MiniTask *nextTask = NULL;
        void runTask(unsigned long startTime);
        void insertTask(MiniTask *task, MiniTask *previous, MiniTask *next);
        unsigned long loadInLastCycle = 0;
        unsigned long loadInCurrentCycle = 0;
        unsigned long cycleCounter = 0;
    };
};

#endif