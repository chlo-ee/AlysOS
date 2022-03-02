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
            Alys::Debugger::getInstance().println("[FS Config] Returning: " + result);
            break;
        }
    } while (file.position() < file.size());
    file.close();
    return result;
}

String Alys::FsManager::readFile(String fileName) { 
    File file = LittleFS.open(fileName, "r");
    return file.readString();
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
    File writeFile = LittleFS.open(SPI_SETTINGS_MANAGER_FILENAME_TMP, "w");

    boolean exists = LittleFS.exists(SPI_SETTINGS_MANAGER_FILENAME);
    if (exists) {
        File readFile = LittleFS.open(SPI_SETTINGS_MANAGER_FILENAME, "r");
        
        do {
            String content = readFile.readStringUntil('\n');
            String pair[] = {"", ""};
            splitString(content, '=', pair);
            if (pair[0] != property) {
                writeFile.print(content);
                writeFile.print('\n');
            }
        } while (readFile.position() < readFile.size());
        readFile.close();
    }
    Alys::Debugger::getInstance().println("[FS Config] Writing: " + property + "=" + value);
    writeFile.print(property);
    writeFile.print("=");
    writeFile.print(value);
    writeFile.print('\n');
    writeFile.close();

    LittleFS.remove(SPI_SETTINGS_MANAGER_FILENAME);
    LittleFS.rename(SPI_SETTINGS_MANAGER_FILENAME_TMP, SPI_SETTINGS_MANAGER_FILENAME);
}
