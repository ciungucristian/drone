// ESC motor program 
// Authors: Cristian Ciungu, Oussama Mehdi 
// Date: March 28th, 2021 
// ------------------------------------------ 

// include Servo library 
#include <Servo.h>

// PWM and pin parameters 
int Delay = 1000;
int maxSignal = 2000;
int minSignal = 1000;
int MP1 = 9;
int MP2 = 10;
int MP3 = 11;
int MP4 = 6;
float Speed = 0; 

// declare Servo objects 
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup() {
  Serial.begin(9600);
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
  while (!Serial.available());
  Serial.read();

  motor1.writeMicroseconds(minSignal); // write MAX and MIN to ESCs to disable safety mode, i.e. calibrate ESCs 
  motor2.writeMicroseconds(minSignal);
  motor3.writeMicroseconds(minSignal);
  motor4.writeMicroseconds(minSignal);

  
  Serial.println("Now, type a value between 1000 and 2000 and press enter:");
  Serial.println("The motors will start rotating.");
  Serial.println("1000: motor stops, 2000: full throttle");

}

void loop() {
  if (Serial.available() > 0){       // wait for user input
    Delay = Serial.parseInt(); 
    if (Delay> 999){ 
      motor1.writeMicroseconds(Delay); // 4 motors run 
      motor2.writeMicroseconds(Delay);
      motor3.writeMicroseconds(Delay);
      motor4.writeMicroseconds(Delay);

      float Speed = (Delay-1000)/10;  // speed percentage displayed on Serial monitor 
      Serial.println("Motor speed:"); 
      Serial.print("  "); 
      Serial.print(Speed); 
      Serial.print("%"); 
    }     
  }
}