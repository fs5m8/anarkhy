#include "SPI.h"
#include "SD.h"
#define 
#define SENTENCE_LENGTH 10;
int chipSelect = BUILTIN_SDCARD;
size_t loadFile(char* fdp, char* path);
char* content = (char*)calloc((size_t)4096, sizeof(char));

void setup() {
  Serial.begin(115200);
  while (!Serial);
  while (!SD.begin(chipSelect)) delay(2000);
  if (content == NULL) {
    Serial.println("Failed to allocate memory for reading");
    return;
  }
  size_t len = loadFile(content, "/test.json");
  
  if (content != NULL) free(fdp);
}

void loop() {
}

size_t loadFile(char* content, char* path) {
  File file;
  file = SD.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  size_t len = file.size();
  for (size_t dlen = len; dlen > 0; dlen--) {
    if (dlen > len) dlen = len;
    file.read(content, dlen);
  }
  Serial.printf("%u bytes readed\n", len);
  file.close();
  return len;
}
