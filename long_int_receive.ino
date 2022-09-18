#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
long result = 1;



MCP2515 mcp2515(10);

void setup() {
  // put your setup code here, to run once:
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  Serial.println("Long int transfer");
}

void loop() {
  long e = 1;
  long x=0;
  // put your main code here, to run repeatedly:
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    /*Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    */
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      //Serial.print(canMsg.data[i]);
      //Serial.print(" ");
      x += e*canMsg.data[i];
      e = e*256;    
    }
    
    Serial.println(x);

    Serial.println();      
  }
}
