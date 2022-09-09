#include "EchoService.h"

static void onBoot() {
    Alys::Debugger::getInstance().println("EchoService boot hook");
};

static void onTick() {
    Alys::Debugger::getInstance().println("EchoService tick");
};

EchoService::EchoService() : Alys::Service() {
    this->name = "EchoService";
    this->interval = 10000;
    this->onBootCallback = &onBoot;
    this->onTickCallback = &onTick;
}