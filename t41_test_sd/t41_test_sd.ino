#include "SPI.h"
#include "SD.h"
#define FILE_LENGTH 512
int chipSelect = BUILTIN_SDCARD;
void rwFile(char* path);
void delFile(char* path);

void setup() {  
    Serial.begin(115200);
    while (!Serial);
    while (!SD.begin(chipSelect)) delay(2000);
    rwFile("/hoge.txt");
    delFile("/hoge.txt");
}

void loop() {
}

void rwFile(char* path) {
    static uint8_t buf[FILE_LENGTH];
    File file;

    file = SD.open(path, FILE_WRITE);
    if (!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    for (size_t i = 0; i < 2048; i++) file.write(buf, FILE_LENGTH);

    Serial.printf("%u bytes written\n", 2048 * FILE_LENGTH);
    file.close();
    
    file = SD.open(path);
    if (!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    size_t len = file.size();
    size_t dlen = len;
    while (dlen){
        size_t readlen = dlen;
        if (readlen > FILE_LENGTH) readlen = FILE_LENGTH;
        file.read(buf, readlen);
        dlen -= readlen;
    }

    Serial.printf("%u bytes readed\n", len);
    file.close();
}

void delFile(char* path) {
    if (SD.remove(path)) Serial.println("File deleted");
    else Serial.println("Failed to delete file");
}
