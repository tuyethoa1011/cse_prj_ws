#include <ESP32Servo.h>

/* Define the names for ESP32 pin for HC-SR04*/
#define trigger_pin 5
#define Echo_pin 18
#define Servo_pin 26
/* two variables to store duraion and distance value */
long duration;
int distance;
Servo myservo;  // create servo object to control a servo
int pos = 0;

/* configure D9 and D11 as digital input and output respectively */
void setup() {
  pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin, INPUT); // configure the Echo_pin(D11) as an Input
  Serial.begin(115200); // Enable the serial with 9600 baud rate

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(Servo_pin, 544, 2400); // attaches the servo on pin 18 to the servo object
}

void loop() {
  digitalWrite(trigger_pin, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);

  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(trigger_pin, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(trigger_pin, LOW);   // make trigger pin active low

  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2; //Convert pulse duration into distance

  if(distance<50)
  {
    for (pos = 0; pos <= 180; pos += 3) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);    // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 3) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);    // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position
    }
  }
  // print measured distance value on Arduino serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}

#cam bien nhiet do.ino
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;      

const int PIN_TO_SENSOR = 19; // GPIO19 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin

void setup() {
  Serial.begin(115200);            // initialize serial
  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor

  
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}

void loop() {
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state

  if(pinStateCurrent == HIGH)
  {
     Serial.println("Detect!");
  } else if(pinStateCurrent == LOW)
  {
    Serial.println("None");
  }
  delay(10);
}


