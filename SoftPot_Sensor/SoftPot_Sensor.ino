/* 
 Exmaple interface to SoftPot sensor
 By: Nathan Seidle (SparkFun Electronics)
 Date: November 26, 2012
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Soft potentiometer sensor information page: http://www.sparkfun.com/products/8680

 My softpot outputs a value of 0 to 1023. It goes a bit haywire when it's not being touched. To fix this, 
 we enable the internal pull up on the A0 pin. This sets the value to about 990 when not being touched.
 
 To get this code to work, attach the following pins
 Pin 1 (doesn't matter which one) of sensor to 5V on Arduino
 Pin 2 of sensor to A0
 Pin 3 of sensor to GND
 
 Pin 1 (doesn't matter which one) of buzzer to GND
 Pin 2 of buzzer to Pin 7

 */

int buzzer = 7; //Can be any pin, we just picked 7
int softPotSensor = A0; //The softpot sensor is basically a trimpot

void setup()
{  
  Serial.begin(9600); //Start the debug terminal at 9600 bps

  pinMode(softPotSensor, INPUT_PULLUP); //Set analog pin to input to read the sensor
  //We enable the internal pullup to try to drive the softpot when it's not being touched
  
  pinMode(buzzer, OUTPUT); //A buzzer makes noise - it's an output
}

void loop()
{
  int sensorReading = analogRead(softPotSensor);

  Serial.print("Softpot sensor reading: ");
  Serial.print(sensorReading);

  Serial.println(); //Wrap the text so that it's easier to read
  
  //Now make noise if we are tounching the softpot
  if(sensorReading < 900)
  {
    //Let's make some noise
    int soundFreq = map(sensorReading, 0, 1023, 1000, 4000); //Map the sensor reading to what we want to hear
    tone(buzzer, soundFreq); //Make some noise on the buzzer
  }
  else
  {
    noTone(buzzer); //Stop the noise! 
  }
  
  delay(10); //We don't want to print too much too quickly
}
