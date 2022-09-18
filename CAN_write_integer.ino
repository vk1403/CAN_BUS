#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);
int x;
int a = 100;
bool flag = 0;
void setup() {
 
  //canMsg1.data[2] = 0x32;
  //canMsg1.data[3] = 0xFA;
  //canMsg1.data[4] = 0x26;
  //canMsg1.data[5] = 0x8E;
  //canMsg1.data[6] = 0xBE;
  //canMsg1.data[7] = 0x86;

  canMsg2.can_id  = 0x036;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x0E;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x08;
  canMsg2.data[4] = 0x01;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0xA0;
  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  if (flag == 0) {
    while(Serial.available() == 0){}
    x  = Serial.parseInt();
    canMsg1.can_id  = 0x0F6;
    canMsg1.can_dlc = 2;
    canMsg1.data[0] = a;
    canMsg1.data[1] = x;  
    flag = 1;
  }
  if (flag == 1){
    mcp2515.sendMessage(&canMsg1);
    //mcp2515.sendMessage(&canMsg2);
    flag = 0;
  }
 
  Serial.println(x);
  Serial.println("Messages sent");
  
  delay(100);
}
