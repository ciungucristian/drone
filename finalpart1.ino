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
int MP1 = 9;
int MP2 = 10;
int MP3 = 11;
int MP4 = 6;
float Speed = 0; 

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
  if ( inData == "n") {
     Serial.println("TURNING");
     motor1.writeMicroseconds(1100); // 4 motors run 
     motor2.writeMicroseconds(1100);
     motor3.writeMicroseconds(1100);
     motor4.writeMicroseconds(1100);
    
     float Speed = (1100-1000)/10;  // speed percentage displayed on Serial monitor 
     Serial.println("Motor speed:"); 
     Serial.print("  "); 
     Serial.print(Speed); 
     Serial.print("%"); 
   // Serial.println("LED OFF");
   // digitalWrite(13, LOW); // switch OFF LED
   delay(2000);
   }
  
  if ( inData == "f") {
     motor1.writeMicroseconds(1000); // 4 motors run 
     motor2.writeMicroseconds(1000);
     motor3.writeMicroseconds(1000);
     motor4.writeMicroseconds(1000);

     float Speed = 0;  // speed percentage displayed on Serial monitor 
     Serial.println("Motor speed:"); 
     Serial.print("  "); 
     Serial.print(Speed); 
     Serial.print("%"); 
    //Serial.println("LED ON");
    //digitalWrite(13, HIGH); // switch OFF LED
    //digitalWrite(13, LOW); // switch OFF LED
    //delay(500);
    delay(2000);

  }
  delay(100);
  }


  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }

 
}
