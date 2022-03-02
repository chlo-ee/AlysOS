#ifndef FsManager_h
#define FsManager_h

#include "config.h"
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "kernel.h"

#define SPI_SETTINGS_MANAGER_FILENAME "/settings"
#define SPI_SETTINGS_MANAGER_FILENAME_TMP "/settings_tmp"
#define SPI_SETTINGS_MANAGER_PROPERTY_MODE "MODE"

namespace Alys {
    class FsManager {
        public:
            static FsManager& getInstance() {
                static FsManager instance;
                return instance;
            }

            boolean init();
            String readProperty(String property);
            String readFile(String fileName);
            void writeProperty(String property, String value);

        private:
            boolean initialized = false;
            void splitString(String input, char seperator, String *result);
    };
};

#endif
