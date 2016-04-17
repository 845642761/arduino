#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.31.232";
char id[] = "000001";
char type[] = "0000";

EthernetClient client;

void setup() {
  Serial.begin(9600);
  initNetWork();
}

void loop() {
  if (client.connected()) {
    sendTempToServer();  
  }else{
    Serial.println("client lost the server; reconnecting...");
    initNetWork();
  }
  delay(10000);
}

/**
 * 初始化网络
 */
void initNetWork(){
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac);
  }

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting the server...");

  if (client.connect(server, 10000)) {
    Serial.println("connected the server!");
  } else {
    Serial.println("connection the server failed!");
  }
}

/**
 * 发送当前温度到服务器
 */
void sendTempToServer(){
  int temp = getTemp();
  client.print(id);
  client.print(type);
  client.println(temp);
  Serial.print("send temp data success; current temp is : ");
  Serial.print(temp);
  Serial.println("C");
}

/**
 * 读取当前温度
 */
int getTemp(){
  int val;//定义变量
  int dat;//定义变量
  val = analogRead(0); // 读取传感器的模拟值并赋值给val
  dat = (125 * val) >> 8; //温度计算公式
  return dat;
}
