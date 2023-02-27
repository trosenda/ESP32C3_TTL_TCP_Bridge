#include <HardwareSerial.h>

HardwareSerial mySerial(0);  

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, -1, -1); // -1 is default, GPIO21/D6 for TX, GPIO20/D7 for RX on the seed xiao
}

void loop() {
  // Read data from Serial and write to HardwareSerial
  while (Serial.available()) {
    char c = Serial.read();
    mySerial.write(c);
  }

  // Read data from HardwareSerial and write to Serial
  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }
}
