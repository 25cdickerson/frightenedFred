// Code for Frightened Fred Project

// Function to calculate distance (cm) based on microseconds.
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void setup() {
  // put your setup code here, to run once:
  // Distance Sensor
  Serial.begin(9600);
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Distance Sensor
  // Declaring long values
  long dur;
  long tocm;
  // Turn off the Trig pin in case it was on before. Wait for 2 Micro Seconds.
  digitalWrite(12,LOW);
  delayMicroseconds(2);
  // Turn on and Send a sound wave and wait for 10 Micro seconds so that the operation happens and then turn off the pin.
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  // Get the sound wave reflection time and convert the duration to centimeters and print on serial monitor.
  dur=pulseIn(13,HIGH);
  tocm=microsecondsToCentimeters(dur);
  Serial.println(String(tocm));
  delay(100);

  // If under a foot do this
  // https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-relay
  if(tocm == 30.5){
    digitalWrite(10, HIGH);
  }
  else{
    digitalWrite(10,LOW);
  }
}
