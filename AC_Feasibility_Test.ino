#include <Wire.h>
#include <BH1750.h>
#include <i2cdetect.h>

//sensor details
BH1750 sensor;
float margin = 2;
float targetBrightness = 33;
const int lightPin = 3;
float phaseDelay = 7500;

//Pin manipulation setup
int stateChange = 0;

int last_PIN8_state = 0;

void setup() {

  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan                                                 
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change. Input from optocoupler

Serial.begin(115200);
Wire.begin();
//Test the sensor
 if (sensor.begin()) {
    Serial.println(F("BH1750 initialised"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
    i2cdetect();
  }
  readings(); //zero-reading
  
pinMode(4, OUTPUT);
  
}

void loop() {
  if (stateChange)
    {
      //Serial.println("State change");
      delayMicroseconds(phaseDelay);
      digitalWrite(4, HIGH);
      delayMicroseconds(2000);
      digitalWrite(4, LOW); 
      stateChange = 0;
      readings();
    } 

    
}

void readings()
{
    
      float luxVal =  sensor.readLightLevel();
      Serial.print(luxVal);
      Serial.println("lx");
      if(luxVal < targetBrightness - margin )
        phaseDelay = max(phaseDelay -500, 0);
     
      else if(luxVal > targetBrightness + margin )
        phaseDelay = min(phaseDelay+500, 7500);
    
    Serial.println(phaseDelay);
} 
ISR(PCINT0_vect)
{
                                                       
  if(PINB & B00000001){                               
    if(last_PIN8_state == 0){                          
      stateChange = 1;   
      last_PIN8_state = 1;                                 
    }
  }
  else if(last_PIN8_state == 1){                           
    stateChange=1;                                    
    last_PIN8_state = 0;                               
    }
}
  
