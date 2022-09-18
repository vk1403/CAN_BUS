  
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
MCP2515 mcp2515(10);  
  

void setup(){
  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 4;
    for(x;x!=0;x= x/256){
    r = x%256;
    canMsg1.data[i]=r;
    i++;
  }
 for(i=0;i<=3;i++)
  {
    Serial.print(canMsg1.data[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
  delay(100);
