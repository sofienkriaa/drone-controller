#include <SPI.h>
#include <RF22.h>

RF22 rf22(8, 0, &Hardware_spi);

void setup() 
{
  Serial.begin(115200);
  // init SI4432 tranceiver
  if (!rf22.init())
    Serial.println("RF22 init failed");
}

void loop()
{
  if (rf22.available())
  {
    uint8_t buf[RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))
    {
      Serial.print("got request: ");

      Serial.print("x1: ");
      Serial.print(buf[0]);
    
      Serial.print(" - y1: ");
      Serial.print(buf[1]);
      
      Serial.print(" - x2: ");
      Serial.print(buf[2]);
      
      Serial.print(" - y2: ");
      Serial.print(buf[3]);
      
      Serial.print(" -- Logic: ");  
      Serial.print(buf[4], BIN);
      Serial.print("\n");  

      // This part is not needed for the moment
      // could be useful in the future
      /*uint8_t data[] = "And hello back to you";
      rf22.send(data, sizeof(data));
      rf22.waitPacketSent();
      Serial.println("Sent a reply");*/
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
