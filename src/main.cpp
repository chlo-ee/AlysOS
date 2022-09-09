#include <Arduino.h>
#include "alys.h"
#include <Services/EchoService.h>

EchoService echoSvc = EchoService();

void test() {
    String teststr = Alys::FsManager::getInstance().readProperty("TESTSTR");
    if (teststr.length() == 0) {
        Alys::alys_debug("Writing...");
        Alys::FsManager::getInstance().writeProperty("TESTSTR", "Hello World!");
    } else {
        Alys::alys_debug(teststr);
    }
}

//########################################## HOOKS ##########################################
//=== Debug Serial
void debug_serial(String msg) {
    Serial.println(msg);
}
Alys::DebugHook debugSerialHook = Alys::DebugHook("Serial", debug_serial);

//=== Boot Serial
void boot_serial() {
    Serial.begin(9600);
    Serial.println();
}
Alys::BootHook bootSerialHook = Alys::BootHook("Serial Monitor", boot_serial);

//=== Boot System Info
void boot_systemInfo() {
    Alys::alys_debug("+-----------------------------------------+");
    Alys::alys_debug("|              AlysOS v0.1                |");
    Alys::alys_debug("|           \"We'll be fine!\"              |");
    Alys::alys_debug("+-----------------------------------------+");
    Alys::alys_debug("| Boot sequence is already in progress... |");
    Alys::alys_debug("+-----------------------------------------+");
}
Alys::BootHook bootSystemInfo = Alys::BootHook("Display System Info", boot_systemInfo);

//=== Boot Schedule Test
void boot_scheduleTest() {
    Alys::MiniSched::getInstance().schedule(test, Alys::MiniTask::ScheduleMode::REPEAT, 1000);
}
Alys::BootHook bootScheduleTestHook = Alys::BootHook("Schedule Test", boot_scheduleTest);
//########################################## HOOKS ##########################################

void setup() {
    // Serial monitor setup
    Alys::Debugger::getInstance().addHook(&debugSerialHook);
    Alys::Init::getInstance().addHook(&bootSerialHook);

    // System Info
    Alys::Init::getInstance().addHook(&bootSystemInfo);

    // Test
    Alys::Init::getInstance().addHook(&bootScheduleTestHook);

    // Echo Service
    echoSvc.enrol();

    // Boot
    Alys::Init::getInstance().boot();
}

void loop() {
    delay(Alys::MiniSched::getInstance().execute());
}