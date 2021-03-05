// Code for Frightened Fred Project

// Variables
// Motor
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

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

  // Motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
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

  
  // If under 10 cm do this
  if(tocm <= 10){

     // Turn off Motors before switching directions
     digitalWrite(motor1pin1, LOW);
     digitalWrite(motor1pin2, LOW);
     digitalWrite(motor2pin1, LOW);
     digitalWrite(motor2pin2, LOW);
     delay(500);
     
     // Turn off Motor1 / Motor2 and engage the brake
     digitalWrite(motor1pin1, LOW);
     digitalWrite(motor1pin2, HIGH);
     digitalWrite(motor2pin1, LOW);
     digitalWrite(motor2pin2, HIGH);
     delay(1500);

     
     // Turns after 2 seconds of going backwards for 3 seconds
     digitalWrite(motor1pin1, HIGH);
     digitalWrite(motor1pin2, LOW);
     digitalWrite(motor2pin2, LOW);
     digitalWrite(motor2pin1, LOW);
     delay(1500);
  }
  else{
    // Turns Motor1 on and disengages the brake
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    // Turns Motor2 on and disengages the brake
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }
}
