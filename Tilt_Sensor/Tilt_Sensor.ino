/* 
 Exmaple interface to small flex sensor
 By: Nathan Seidle (SparkFun Electronics)
 Date: November 26, 2012
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Tilt sensor information: http://www.sparkfun.com/products/10289
 
 The tile sensor has a ball bearing side and will connect the pins together when the sensor is tilted towards
 the earth. It doesn't work great all the time. Try holding the sensor sideways and gently tilt it 45 degrees
 towards the earth then 45 away from it.
 
 To get this code to work, attach the following pins
 Pin 1 (doesn't matter which one) of tilt sensor to Pin 2 on Arduino
 Pin 2 of sensor to GND
 
 Pin 1 (doesn't matter which one) of buzzer to Pin 7 on Arduino
 Pin 2 of buzzer to GND
 
 */

int tilty = 2; //One pin of tilt sensor is connected to pin 2 on Arduino
int bzzz = 7; //One pin of buzzer is connected to pin 7.

int frequency = 1000; //This variable keeps track of the frequency of noise produced. It changes over time.

void setup()
{  
  Serial.begin(9600); //Start the debug terminal at 9600 bps

  pinMode(tilty, INPUT_PULLUP); //Tily sensor is an input and uses the internal pull up resistor
  pinMode(bzzz, OUTPUT); //A buzzer makes noise - it's an output
}

void loop()
{
  if(digitalRead(tilty) == LOW)
  {
    //Make some noise!
    tone(bzzz, frequency);
    
    Serial.println("I'm upside down!");
    
    frequency += 25; //Increment by 25 each time
    if(frequency > 3000) frequency = 1000; //Reset to 1,000Hz once we get over 10,000Hz
  }
  else
  {
    noTone(bzzz); //Stop the noise!

    Serial.println("I'm fine.");
  }
  
  delay(10);
}
