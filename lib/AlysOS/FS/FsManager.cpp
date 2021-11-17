#include "FsManager.h"

boolean Alys::FsManager::init() {
    bool initok = LittleFS.begin();
    if (!(initok))
    {
        alys_debug("Formatting LittleFS...");
        LittleFS.format();
        initok = LittleFS.begin();
    }
    if (!(initok)) {
        alys_debug("Failed. Retrying...");
        LittleFS.format();
        initok = LittleFS.begin();
    }
    initialized = initok;
    return initok;
}

String Alys::FsManager::readProperty(String property) {
    if (!initialized) {
        alys_panic("[PANIC] Reading " + property + " from uninitialized SpiSettingsManager is not allowed!", false);
    }

    if (!LittleFS.exists(SPI_SETTINGS_MANAGER_FILENAME)) {
        return "";
    }

    String result = "";
    File file = LittleFS.open(SPI_SETTINGS_MANAGER_FILENAME, "r");
    do {
        String content = file.readStringUntil('\n');
        String pair[] = {"", ""};
        splitString(content, '=', pair);
        if (pair[0] == property) {
            result = pair[1];
            break;
        }
    } while (file.position() < file.size());
    file.close();
    return result;
}

void Alys::FsManager::splitString(String input, char separator, String *result)
{
    int writeIdx = 0;
    int maxIndex = input.length() - 1;

    for (int i = 0; i <= maxIndex; i++) {
        if (writeIdx == 0 && input.charAt(i) == separator) {
            writeIdx = 1;
        } else {
            result[writeIdx] = result[writeIdx] + input.charAt(i);
        }
    }
}

void Alys::FsManager::writeProperty(String property, String value) {
    String resultingFile = "";

    boolean exists = LittleFS.exists(SPI_SETTINGS_MANAGER_FILENAME);
    if (exists) {
        File readFile = LittleFS.open(SPI_SETTINGS_MANAGER_FILENAME, "r");
        
        do {
            String content = readFile.readStringUntil('\n');
            String pair[] = {"", ""};
            splitString(content, '=', pair);
            if (pair[0] != property) {
                resultingFile += pair[0] + "=" + pair[1];
            }
            content = readFile.readStringUntil('\n');
        } while (readFile.position() < readFile.size());
        readFile.close();
    }

    File writeFile = LittleFS.open(SPI_SETTINGS_MANAGER_FILENAME, "w");

    if (exists) {
        writeFile.print(resultingFile);
        writeFile.print('\n');
    }

    writeFile.print(property);
    writeFile.print("=");
    writeFile.print(value);
    writeFile.print('\n');
    writeFile.close();
}