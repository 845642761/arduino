#include <SPI.h>
#include <Ethernet.h>

int led0 = 8; //定义数字8
int led1 = 9; //定义数字9

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 31, 234);

EthernetServer server(23);

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  
  Ethernet.begin(mac,ip);
  server.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.print("server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    if (client.available()) {
      char code = client.read();
      dealLED(code);
      Serial.write(code);
      Serial.write('\n');
      client.flush();
    }
  }
}

/**
 * 处理LED
 */
void dealLED(char code){
  if(code == '1'){
    digitalWrite(led0, HIGH);
  }
  if(code == '2'){
    digitalWrite(led0, LOW);
  }
  
  if(code == '3'){
    digitalWrite(led1, HIGH);
  }
  if(code == '4'){
    digitalWrite(led1, LOW);
  }
}



