// Code for Frightened Fred Project
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Variables
// Motor
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

// Speaker
SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// Function for serial output Speaker
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

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

  // Speaker
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
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

  // Speaker
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}
