/*
* Ultrasonic Sensor HC-SR04 interfacing with  ESP32 
*
*/

/* Define the names for ESP32 pin for HC-SR04*/
#define trigger_pin 5
#define Echo_pin 18

/* two variables to store duraion and distance value */
long duration;
int distance;

/* configure D9 and D11 as digital input and output respectively */
void setup() {
  pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
 // pinMode(LED_BUILTIN, OUTPUT); // Set the LED bulit in pin as a digital output
  pinMode(Echo_pin, INPUT); // configure the Echo_pin(D11) as an Input
  Serial.begin(115200); // Enable the serial with 9600 baud rate
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

  /* if distance greater than 10cm, turn on LED */
  //if ( distance < 10)
   // digitalWrite(LED_BUILTIN, HIGH);
  //else 
   // digitalWrite(LED_BUILTIN, LOW);
  // print measured distance value on Arduino serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
