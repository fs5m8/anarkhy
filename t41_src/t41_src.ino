#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#define SENTENCE_LENGTH 10;

int chipSelect = BUILTIN_SDCARD;
char* content = (char*)calloc((size_t)4096, sizeof(char));
DynamicJsonDocument jcontent(500);

void loadFile(char* fdp, char* path);
void executeProgram(void);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  while (!SD.begin(chipSelect)) delay(2000);
  
  if (content == NULL) {
    Serial.println("Failed to allocate memory for reading");
    return;
  }
  
  loadFile(content, "/test.json");
  DeserializationError deserError = deserializeJson(jcontent, content);
  
  if (deserError) {
    Serial.print("Failed to deserialize JSON: ");
    Serial.println(deserError.c_str());
    if (content != NULL) free(content);
    return;
  }

  executeProgram();
  
  if (content != NULL) free(content);
}

void loop() {
}

void loadFile(char* content, char* path) {
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
  return;
}

void executeProgram(void) {
  int i = 0;
  while (1) {
    String inst = jcontent[String(i)]["inst"];
    if (inst == "end") break;
    else if (inst == "feed") {
      double value = jcontent[String(i)]["value"];
    }
    else if (inst == "drill") {
    }
    else if (inst == "cut") {
    }
    else {
    }
    i++;
  }
}
