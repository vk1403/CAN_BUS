#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);
int x[8];
int a = 100;
bool flag = 0;
int n_entry;
void setup() {
 
  //

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
    Serial.println("Please enter number of entries :");
    while(Serial.available() == 0){}
    n_entry = Serial.parseInt();
    Serial.println("bleh");
    for(int j=1; j <= n_entry/8; j++){
      for(int k = 0; k < 8; k++){
        while(Serial.available() == 0){}
        x[k] = Serial.parseInt();
        // ATTENTION ATTENTION
        // Make sure serial monitor is on no line ending mode otherwise
        // it will keep storing 0s after every input.
        Serial.println("You are enetering"+(String)k+"th integer.");
        canMsg1.data[k] = x[k];
        Serial.println(x[k]);
         
      }
       canMsg1.can_id  = 0x0F6;
       canMsg1.can_dlc = 8; 
       mcp2515.sendMessage(&canMsg1);
    }
  
    flag = 1;
  }
  if (flag == 1){
    //mcp2515.sendMessage(&canMsg1);
    //mcp2515.sendMessage(&canMsg2);
    flag = 0;
  }
 
  //Serial.println(x);
  Serial.println("Messages sent");
  
  delay(100);
}
