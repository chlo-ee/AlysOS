#include "MiniSched.h"

Alys::MiniSched::MiniSched() {}

Alys::MiniTask *Alys::MiniSched::schedule(MiniTask *task) {
    if (nextTask == NULL) {
        // Using a fresh queue
        #ifdef MINISCHED_DEBUG
        Serial.print("Scheduling ");
        Serial.print(task->name);
        Serial.println(" onto an empty queue.");
        #endif
        nextTask = task;
        task->previousTask = NULL;
        task->nextTask = NULL;
    } else {
        bool scheduled = false;
        MiniTask *taskIterator = nextTask;
        MiniTask *lastValidTask = NULL;
        while (taskIterator != NULL) {
            lastValidTask = taskIterator;
            if (taskIterator->plannedExecution > (task->plannedExecution)) {
                // Squeeze task in before another task
                #ifdef MINISCHED_DEBUG
                Serial.print("Scheduling ");
                Serial.print(task->name);
                Serial.print(" before ");
                Serial.print(taskIterator->name);
                #endif
                task->previousTask = taskIterator->previousTask;
                task->nextTask = taskIterator;
                if (taskIterator->previousTask != NULL) {
                    taskIterator->previousTask->nextTask = task;
                    #ifdef MINISCHED_DEBUG
                    Serial.print(" and after ");
                    Serial.println(taskIterator->previousTask->name);
                    #endif
                } else {
                    nextTask = task;
                    #ifdef MINISCHED_DEBUG
                    Serial.println("");
                    #endif
                }
                taskIterator->previousTask = task;
                scheduled = true;
                break;
            }
            taskIterator = taskIterator->nextTask;
        }

        // We are last
        if (!scheduled) {
            #ifdef MINISCHED_DEBUG
            Serial.print("Scheduling ");
            Serial.print(task->name);
            Serial.println(" last.");
            #endif
            task->previousTask = lastValidTask;
            task->nextTask = NULL;
            lastValidTask->nextTask = task;
        }
    }
    return task;
}

Alys::MiniTask *Alys::MiniSched::schedule(MiniTask::vTaskCallback callback, MiniTask::ScheduleMode mode, unsigned long delay) {
    return schedule(callback, mode, delay, "");
}

Alys::MiniTask *Alys::MiniSched::schedule(MiniTask::vTaskCallback callback, MiniTask::ScheduleMode mode, unsigned long delay, String name) {
    MiniTask *taskPointer;
    taskPointer = new MiniTask();
    taskPointer->callback = callback;
    taskPointer->mode = mode;
    taskPointer->plannedExecution = millis() + delay;
    taskPointer->active = true;
    taskPointer->interval = delay;
    taskPointer->name = name;
    taskPointer->ready=true;
    
    schedule(taskPointer);

    return taskPointer;
}

unsigned long Alys::MiniSched::execute() {
    unsigned long c_millis = millis();
    if (nextTask == NULL) return MINISCHED_MAX_IDLE_TIME;
    if (c_millis < nextTask->plannedExecution) return min(nextTask->plannedExecution - c_millis, (unsigned long)MINISCHED_MAX_IDLE_TIME);
    unsigned long currentCycle = c_millis / MINISCHED_STAT_CYCLE_MS;
    
    if (currentCycle != cycleCounter) {
        cycleCounter = currentCycle;
        loadInLastCycle = loadInCurrentCycle;
        loadInCurrentCycle = 0;
    }

    runTask(c_millis);
    unsigned long c_millis_n = millis();
    loadInCurrentCycle += c_millis_n - c_millis;
    if (nextTask->plannedExecution > c_millis_n) {
        return min(nextTask->plannedExecution - c_millis_n, (unsigned long)MINISCHED_MAX_IDLE_TIME);
    }
    return 0;
}

void Alys::MiniSched::runTask(unsigned long startTime) {
    if (nextTask == NULL) return;
    if (!nextTask->ready) return;

    if (nextTask->active) {
        #ifdef MINISCHED_DEBUG
        Serial.print("Running task: ");
        Serial.println(nextTask->name);
        #endif
        nextTask->execute();
    }

    MiniTask *executedTask = nextTask;
    nextTask = executedTask->nextTask;
    if (nextTask != NULL) {
        nextTask->previousTask = NULL;
    }
    if (executedTask->mode == MiniTask::ScheduleMode::ONCE || !executedTask->active) {
        delete executedTask;
    } else {
        executedTask->plannedExecution = startTime + executedTask->interval;
        schedule(executedTask);
    }
}

u8 Alys::MiniSched::getLastLoad() {
    return (u8)min(loadInLastCycle / 10, (unsigned long) 100);
}

unsigned long Alys::MiniSched::getCycleCounter() {
    return cycleCounter;
}

void Alys::MiniSched::addTimeToStatistics(unsigned long time) {
    unsigned long currentCycle = millis() / MINISCHED_STAT_CYCLE_MS;
    
    if (currentCycle != cycleCounter) {
        cycleCounter = currentCycle;
        loadInLastCycle = loadInCurrentCycle;
        loadInCurrentCycle = 0;
    }
    
    loadInCurrentCycle += time;
}