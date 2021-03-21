// ESC motor program 
// Authors: Cristian Ciungu, Oussama Mehdi 
// Date: March 20th, 2021 
// ------------------------------------------ 

// include Servo and Serial libraries 
#include <Servo.h>
#include <Serial.h> 

// PWM and pin parameters 
int Delay = 1000;
int maxSignal = 2000;
int minSignal = 1000;
int motorPin = 9;
float Speed = 0; 

// declare Servo object 
Servo motor;

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating ESCs ...");
  delay(2500);
  motor.attach(motorPin); // 
  Serial.println("Plug battery pack to the PDB, then wait 2 seconds and press any key:");
  motor.writeMicroseconds(maxSignal); // write MAX and MIN to ESCs to disable safety mode, i.e. calibrate ESCs 

  // Wait for input
  while (!Serial.available());
  Serial.read();

  motor.writeMicroseconds(minSignal); // write MAX and MIN to ESCs to disable safety mode, i.e. calibrate ESCs 
  Serial.println("Now, type a value between 1000 and 2000 and press enter:");
  Serial.println("The motors will start rotating.");
  Serial.println("1000: motor stops, 2000: full throttle");

}

void loop() {
  if (Serial.available() > 0){       // wait for user input
    Delay = Serial.parseInt(); 
    if (Delay> 999){ 
      motor.writeMicroseconds(Delay); // motor runs 
      float Speed = (Delay-1000)/10;  // speed percentage displayed on Serial monitor 
      Serial.println("Motor speed:"); 
      Serial.print("  "); 
      Serial.print(Speed); 
      Serial.print("%"); 
    }     
  }
}
