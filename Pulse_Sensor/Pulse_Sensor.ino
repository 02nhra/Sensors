/*
 Exmaple for Pulse Sensor
 By: Nathan Seidle (SparkFun Electronics)
 Date: November 26, 2012
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Pulse sensor information page: http://www.sparkfun.com/products/11574
 
 The pulse sensor is finnicky. I had the best luck using the double sided velcro and wrapping it around my finger.
 Holding the sensor against my finger tip rarely worked. Holding it lightly againt my finger tip worked better.
 
 To get this code to work, attach the following pins
 Red wire on Pulse Sensor to 5V on Arduino
 Black wire to GND on Arduino
 Purple wire to A0 on Arduino
 
 Note: PWM on pins 3 and 11 will not work when using this code, because it uses Timer 2
 
 The example code provided by Joel and Yury has a lot more features. Find it here:
 
 */


//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

void setup()
{
  Serial.begin(9600); //Setup serial port at 9600 bps
  Serial.println("Hello!");
  Serial.println("Hold the white heart gently against your finger tip");

  pinMode(blinkPin, OUTPUT);  // Pin that will blink to your heartbeat

  interruptSetup();  // Sets up to read Pulse Sensor signal every 2mS 
}

void loop()
{
  if (QS == true) // Quantified Self flag is true when arduino finds a heartbeat
  {                       
    Serial.print("Beats per minute: ");
    Serial.println(BPM); //Print the beats per minute
    QS = false;  // Reset the Quantified Self flag for next time    
  }

  delay(20); // Take a break
}

