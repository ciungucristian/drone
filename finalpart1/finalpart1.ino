// ESC motor program 
// Authors: Cristian Ciungu, Oussama Mehdi 
// Date: March 28th, 2021 
// ------------------------------------------ 

// include Servo library 

#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
char appData;  
String inData = "";

// initializing PWM and pin parameters 
int Delay = 1000;
int maxSignal = 2000;
int minSignal = 1000;

int MP1 = 5; //front left motor
int MP2 = 10; // front right
int MP3 = 11; //back left
int MP4 = 6; // back right
float Speed = 0; 
int speedCheck = 1000;

// variables for time
int currMS = 0;
int startMS = 0; 
int interval = 1000;

// declaring Servo objects 
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  
  // setting up motors
  Serial.println("Calibrating ESCs ..."); 
  delay(2500); 
  motor1.attach(MP1); 
  motor2.attach(MP2); 
  motor3.attach(MP3); 
  motor4.attach(MP4); 

  Serial.println("Plug battery pack to the PDB, then wait 2 seconds and press any key:");
  motor1.writeMicroseconds(maxSignal); // write MAX and MIN to ESCs to disable safety mode, i.e. calibrate ESCs 
  motor2.writeMicroseconds(maxSignal);
  motor3.writeMicroseconds(maxSignal);
  motor4.writeMicroseconds(maxSignal);

  // Wait for input
  //while (!Serial.available());
 // Serial.read();

 delay(10000);

  motor1.writeMicroseconds(minSignal); // write MAX and MIN to ESCs to disable safety mode, i.e. calibrate ESCs 
  motor2.writeMicroseconds(minSignal);
  motor3.writeMicroseconds(minSignal);
  motor4.writeMicroseconds(minSignal);

  
  Serial.println("Now, type a value between 1000 and 2000 and press enter:");
  Serial.println("The motors will start rotating.");
  Serial.println("1000: motor stops, 2000: full throttle");
  //done setting up motors
}

void loop()
{
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);

    
     //rewriting if conditions for motors:
     //i function is used to increase the motor speeds by 10% (1100)
  if ( inData == "i") {
     Serial.println("TURNING");
     speedCheck = speedCheck + 100;
     motor1.writeMicroseconds(speedCheck); // 4 motors run 
     motor2.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);
    
     float Speed = (speedCheck-1000)/10;  // speed percentage displayed on Serial monitor 
     Serial.println("Motor speed:"); 
     Serial.print("  "); 
     Serial.print(Speed); 
     Serial.print("%"); 
   // Serial.println("LED OFF");
   // digitalWrite(13, LOW); // switch OFF LED
   }
    //d function is used to decrease the motor speeds by 10% (1100)
 if ( inData == "d") {
     Serial.println("DECREASING");
     speedCheck = speedCheck - 100;
     motor1.writeMicroseconds(speedCheck); // 4 motors run 
     motor2.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);
    
     float Speed = (speedCheck-1000)/10;  // speed percentage displayed on Serial monitor 
     Serial.println("Motor speed:"); 
     Serial.print("  "); 
     Serial.print(Speed); 
     Serial.print("%"); 
   // Serial.println("LED OFF");
   // digitalWrite(13, LOW); // switch OFF LED
   }
  // s function from bluetooth module is used to turn off the motors
  if ( inData == "s") {
     speedCheck = 1000;
     motor1.writeMicroseconds(speedCheck); // 4 motors run 
     motor2.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);

     float Speed = 0;  // speed percentage displayed on Serial monitor 
     Serial.println("Motor speed:"); 
     Serial.print("  "); 
     Serial.print(Speed); 
     Serial.print("%"); 
    //Serial.println("LED ON");
    //digitalWrite(13, HIGH); // switch OFF LED
    //digitalWrite(13, LOW); // switch OFF LED
    //delay(500);
  }
  // things to do:
  // function for moving forward, backward, left, right
//for moving forward
    if ( inData == "f") {
     Serial.println("MOVING FORWARD");
     startMS = millis();
     while(currMS <= interval) {
     motor1.writeMicroseconds(speedCheck); // 4 motors run 
     motor2.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck + 100);
     motor4.writeMicroseconds(speedCheck + 100);
     currMS = millis()-startMS;  
     }
     currMS = 0; 
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);
  }
  
  //for moving backward
    if ( inData == "b") {
     Serial.println("MOVING BACKWARD");
     startMS = millis();
     while(currMS <= interval) {
     motor1.writeMicroseconds(speedCheck + 100); // 4 motors run 
     motor2.writeMicroseconds(speedCheck + 100);
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);
     currMS = millis()-startMS;  
     }
     currMS = 0; 
     motor1.writeMicroseconds(speedCheck);
     motor2.writeMicroseconds(speedCheck);
    // delay(100);
  }
//for moving right
    if ( inData == "r") {
     Serial.println("MOVING RIGHT");
     startMS = millis();
     while(currMS <= interval) {
     motor1.writeMicroseconds(speedCheck + 100); // 4 motors run 
     motor2.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck + 100);
     motor4.writeMicroseconds(speedCheck);
     currMS = millis()-startMS;  
     }
     currMS = 0; 
     motor1.writeMicroseconds(speedCheck);
     motor3.writeMicroseconds(speedCheck);
     //delay(100);
  }
  
  //for moving left
    if ( inData == "l") {
     Serial.println("MOVING LEFT");
     startMS = millis();
     while(currMS <= interval) {
     motor1.writeMicroseconds(speedCheck); // 4 motors run 
     motor2.writeMicroseconds(speedCheck + 100);
     motor3.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck + 100);
     currMS = millis()-startMS;  
     }
     currMS = 0; 
     motor2.writeMicroseconds(speedCheck);
     motor4.writeMicroseconds(speedCheck);
    // delay(100);
  }


  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }

  }
}
