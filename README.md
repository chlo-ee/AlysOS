
# AlysOS

This is the Alys Operating System intended for use with ESP8266 microcontrollers.
The aim of this project is making complex projects more manageable by offloading the ressource management.
To accomplish this there are a few components that work hand in hand. Some of them can be enabled or disabled in the config.h file of libAlysOS.

## Debugger

Probably the most important part of programming is debugging code. Usually this is done by sending debug messages via Serial.println().
The thing is that sometimes the serial console is not an option. Also debug messages look pretty cool on projects with displays. So the AlysOS debugger actually uses debug hooks that can be defined before booting. Each time a debug message is emmited using Alys::alys_debug(string) all the hooks will be passed the given string.

## Scheduler

Virtually all bigger projects will have different parts of your code running simultaniously. Usually this is a tedious task but AlysOS has some features that make this insanely simple.

Powering AlysOS is MiniSched - a small cooperative scheduler that takes care of repeatedly calling functions at defined points in time. In order for MiniShed to run, your "loop'-function should not be changed.

## Services

The simplest way to have different parts of your code running simultaneously is using the Sevice-class. An example is provided in Services/EchoService. Every service has some parameters like the name and the interval in which the onTick function should be called. The onTick function defines what the service will do everytime it is called by the scheduler and the onBoot function is executed once on boot.

Think of the onBoot() function as your setup() and the onTick() function as your loop() function.

To install a service, instanciate it and call the inherited enroll() function. It will then be launched with the boot() function of AlysOS.

## FSManager

The FSManager uses LittleFS to read files or work with configurations. Currently there isn´t much you can do with it BUT it's really useful if you want to save different config parameters on the ESP.

Be aware that it WILL format the ESP's data partition whenever it is initiated and can´t find a LittleFS filesystem. This makes using it really easy but might lead to lost data if you still need data from your ESP.