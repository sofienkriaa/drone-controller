#include <SPI.h>
#include <RF22.h>

// Singleton instance of the radio
RF22 rf22;

void setup() 
{
  // init serial port
  Serial.begin(115200);

  // setup input
  for (int i = 3; i < 10; i++) 
  { 
    pinMode(i, INPUT); 
  }
  for (int i = 18; i < 21; i++) 
  { 
    pinMode(i, INPUT); 
  }
  
  // init RF-22
  if (!rf22.init())
    Serial.println("RF22 init failed");
}

void loop()
{
  while (1)
  {
    // Collect input values
    uint8_t data[4];

    // Read analog controller values
    data[0] = mMap(analogRead(A2),0 ,640 ,0 ,255); // 640 - 0
    data[1] = mMap(analogRead(A3),35 ,670 ,0 ,255); // 670 - 40
    data[2] = mMap(analogRead(A0),128 ,498 ,255 ,0); // 498 - 128
    data[3] = mMap(analogRead(A1),135 ,535 ,0 ,255); // 535 - 138

    Serial.print(data[0]);
    Serial.print(" :: ");
    Serial.print(data[1]);
    Serial.print(" :: ");
    Serial.print(data[2]);
    Serial.print(" :: ");
    Serial.println(data[3]);
    
    // Send a message to receiver
    rf22.send(data, sizeof(data));
    rf22.waitPacketSent();

    // Now wait for a reply
    // This part is not needed for the moment
    // could be useful in the future
    /*uint8_t buf[RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf22.waitAvailableTimeout(1)) { 
      // Should be a message for us now   
      if (rf22.recv(buf, &len)) {
        Serial.print("got reply: ");
        Serial.println((char*)buf);
      }
      else {
        Serial.println("recv failed");
      }
    }
    else {
      Serial.println("No reply, is rf22_server running?");
    }*/
  }
}

// Map function with specific maximum
long mMap(int input, int minimum, int maximum, int newMinimum, int newMaximum) {
  if (input < minimum) {
    return minimum;
  }
  else if (input > maximum) {
    return maximum;
  }
  else {
    return map(input, minimum, maximum, newMinimum, newMaximum);
  }
}
