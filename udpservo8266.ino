
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>


// nodemcu 1.0 (eps12e module)
// Servo on D4

const char* ssid     = "xxx";
const char* password = "xxx";

WiFiUDP UDPTestServer;
unsigned int UDPPort = 2807;

const int packetSize = 2;   // turns out on my module this is pin 4
byte packetBuffer[packetSize];
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.config(IPAddress(192, 168, 1, 60), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  UDPTestServer.begin(UDPPort);

}

int value = 0;

void loop() {
  handleUDPServer();
  delay(1);
//      myservo.write(pos);              // tell servo to go to position in variable 'pos'  0-180

}

void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = "";
    for (int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.println(myData);
  }
}

void loop() {
  int pos;

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
