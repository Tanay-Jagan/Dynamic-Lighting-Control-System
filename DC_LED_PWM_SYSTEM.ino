#include <Wire.h>
#include <BH1750.h>
#include <i2cdetect.h>
BH1750 sensor;
float luxThresh;
float recoVal;
const int LEDpin = 3;
float brightness;

void setup() {
  Serial.begin(9600);
  Wire.begin();
 if (sensor.begin()) {
    Serial.println(F("BH1750 initialised"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
    i2cdetect();
  }
  Serial.println(F("BH1750 Test"));

  pinMode(LEDpin, OUTPUT);
  luxThresh = 0.5;
  recoVal = 5;
  brightness = 25;
}

void loop() {
  float luxVal =  sensor.readLightLevel();
  
  Serial.print(luxVal);
  Serial.println("lx");
   Serial.print(brightness/255.0 * 2);
    Serial.println(" PulseWidth in ms");
  if(luxVal < recoVal - luxThresh && brightness < 255)
     brightness = min(brightness + 10, 255);
     
  else if(luxVal > recoVal + luxThresh && brightness > 0)
     brightness = max(brightness-10, 0);

   
;  analogWrite(LEDpin, brightness);  
  delay(500);  
}
