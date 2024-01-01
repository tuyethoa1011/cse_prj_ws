# cse_prj_ws

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
