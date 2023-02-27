#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(0); 

uint8_t buf1[1024];
uint16_t i1=0;

uint8_t buf2[1024];
uint16_t i2=0;

const char* ssid = "yourssid";
const char* password = "yourpasswd";

WiFiServer server(8880);
bool isTcpConnected = false; // Flag to indicate whether a TCP client is connected

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, -1, -1);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  // Handle TCP client connection
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New TCP client connected");
    isTcpConnected = true;

    while (client.connected())  {
      while(mySerial.available()) {
      buf2[i2] = (char)mySerial.read(); // read char from UART
      if(i2<1023) i2++;
    }
    // now send to WiFi:
    client.write((char*)buf2, i2);
    i2 = 0;       
while(client.available()) {
      buf1[i1] = (uint8_t)client.read(); // read char from client 
      if(i1<1023) i1++;
    }
    // now send to UART:
    mySerial.write(buf1, i1);
    i1 = 0;
  }
client.stop();  

    Serial.println("TCP client disconnected");
    isTcpConnected = false;
  }

  // If no TCP client is connected, bridge between Serial and HardwareSerial
  if (!isTcpConnected) {
    if (Serial.available()) {
      char c = Serial.read();
      mySerial.write(c);
    }
    if (mySerial.available()) {
      char c = mySerial.read();
      Serial.write(c);
    }
  }
}
