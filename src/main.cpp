#include <Arduino.h>
#include "alys.h"
#include <Services/EchoService.h>

//########################################### MISC ###########################################
void fsTest() {
    String teststr = Alys::FsManager::getInstance().readProperty("TESTSTR");
    if (teststr.length() == 0) {
        Alys::alys_debug("Writing...");
        Alys::FsManager::getInstance().writeProperty("TESTSTR", "Hello World!");
    } else {
        Alys::alys_debug(teststr);
    }
}

//######################################### SERVICES ########################################
EchoService echoSvc = EchoService();

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
    Alys::alys_debug("|              AlysOS v0.2                |");
    Alys::alys_debug("|           \"We'll be fine!\"              |");
    Alys::alys_debug("+-----------------------------------------+");
    Alys::alys_debug("| Boot sequence is already in progress... |");
    Alys::alys_debug("+-----------------------------------------+");
}
Alys::BootHook bootSystemInfo = Alys::BootHook("Display System Info", boot_systemInfo);
Alys::BootHook bootTestHook = Alys::BootHook("FS Test", fsTest);


//######################################### BOOTING #########################################
void setup() {
    // Serial monitor setup
    Alys::Debugger::getInstance().addHook(&debugSerialHook);
    Alys::Init::getInstance().addHook(&bootSerialHook);

    // System Info
    Alys::Init::getInstance().addHook(&bootSystemInfo);

    // Test
    Alys::Init::getInstance().addHook(&bootTestHook);

    // Echo Service
    echoSvc.enrol();

    // Boot
    Alys::Init::getInstance().boot();
}

void loop() {
    delay(Alys::MiniSched::getInstance().execute());
}