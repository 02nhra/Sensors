/* 
 Exmaple interface to alcohol sensor
 By: Nathan Seidle (SparkFun Electronics)
 Date: November 26, 2012
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 The alcohol sensor is finnicky. The sensor will get slightly warm because there is a heater built in. 
 The analog value will increase as more alcohol is detected. The value will go down with normal breathe 
 because you are cooling the heater off. Try blowing across the sensor rather than directly into it.
 
 I've seen an average value range from 300-500 just sitting there. And a jump up to 600 or 700 after
 drinking a nice red Chianti with a side of fava beans.
 
 To get this code to work, attach the following pins
 A1 on sensor to VIN on Arduino
 H1 on sensor to VIN on Arduino
 B1 on sensor to A0 on Arduino and 10K to GND
 GND on sensor to GND
 Green LEN connected from Pin 11 on Adruino to GND.
 
 */

int drunkLED = 11; //Green LED on pin 11 to indicate if alcohol is above a certain threshold
int alcoholSensor = A0; //Pin A on the sensor is connected to A0 on the Arduino

int readings[100]; //This keeps track of previous readings
int readingCounter = 0; //The spot in the array of readings

void setup()
{  
  Serial.begin(9600); //Start the debug terminal at 9600 bps

  pinMode(drunkLED, OUTPUT); //The green LED is an output
  digitalWrite(drunkLED, LOW); //Turn off the LED

  pinMode(alcoholSensor, INPUT); //Set analog 0 to input to read the sensor

  //Pre-fill the array with readings from the sensor
  for(int x = 0 ; x < 100 ; x++)
    readings[x] = analogRead(alcoholSensor);
}

void loop()
{
  int sensorReading = analogRead(alcoholSensor);

  readings[readingCounter] = sensorReading; //Store this reading into the array
  readingCounter++;
  if(readingCounter == 100) readingCounter = 0; //Wrap the variable back around to zero

  int avgReading = findReadingAverage();

  Serial.print("Alcohol level: ");
  Serial.print(sensorReading);

  Serial.print(" avg reading: ");
  Serial.print(avgReading);

  if(sensorReading - avgReading > 30)
  {
    Serial.print(" You're drunk!");
    digitalWrite(drunkLED, HIGH);
  } 
  else
    digitalWrite(drunkLED, LOW);

  Serial.println();

}

int findReadingAverage(void)
{
  long total = 0;
  for(int x = 0 ; x < 100 ; x++)
    total += readings[x];

  total /= 100; //Find the average of the readings

  return(total);
}

