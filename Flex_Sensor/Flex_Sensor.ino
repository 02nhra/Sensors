/* 
 Exmaple interface to small flex sensor
 By: Nathan Seidle (SparkFun Electronics)
 Date: November 26, 2012
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Flex sensor information page: http://www.sparkfun.com/products/10264

 My flex sensor reads about 315 when straight and 130 when curled. Adjust the max and min flex variable
 for your specific sensor. 
 
 To get this code to work, attached the following pins
 Pin 1 (doesn't matter which one) of sensor to 5V on Arduino
 Pin 2 of sensor to A4 and a 10K to GND
 
 Green LEN connected from Pin 11 on Adruino to GND.
 
 */

int maxFlex = 315;
int minFlex = 130;

int statusLED = 11; //Green LED on pin 11 to indicate rough amount of flex
int flexSensor = A4; //The flex sensor forms a voltage divider

void setup()
{  
  Serial.begin(9600); //Start the debug terminal at 9600 bps

  pinMode(statusLED, OUTPUT); //The green LED is an output
  digitalWrite(statusLED, LOW); //Turn off the LED

  pinMode(flexSensor, INPUT); //Set analog pin to input to read the sensor
}

void loop()
{
  int sensorReading = analogRead(flexSensor);

  Serial.print("Flex sensor reading: ");
  Serial.print(sensorReading);

  Serial.println(); //Wrap the text so that it's easier to read
  
  //Now control the LED based on the amount of flex
  if (sensorReading < minFlex) minFlex = sensorReading; //Correct the minimum value down if we get a smaller reading
  if (sensorReading > maxFlex) maxFlex = sensorReading; //Correct the max value up if we get a larger reading
  
  int ledAmount = map(sensorReading, minFlex, maxFlex, 0, 255); //Map the sensor reading to what we can display on the LED
  analogWrite(statusLED, ledAmount); //Write this newly mapped value out to the LED
  
  delay(10); //We don't want to print too much too quickly
}
