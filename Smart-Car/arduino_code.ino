//Christopher Sutjiono

#include <AFMotor.h>                              //Import library to control motor shield
#include <Servo.h>                                //Import library to control the servo

AF_DCMotor leftBack(1);
AF_DCMotor rightBack(4);
Servo servoLook;                                  //Create an object to control the servo

char command;                                     //Global Variable to store input from BT app
int motorspeed = 100;                                  // speed variable (0 - 255)
byte trig = 2;                                    //Assign the ultrasonic sensor pins
byte echo = 13;
byte stopDist = 50;                               //Distance from an object to stop in cm
float timeOut = 2 * (maxDist + 10) / 100 / 340 * 1000000; //Maximum time to wait for a return signal


void setup() {
  Serial.begin(9600);                             //Set the baud rate to the Bluetooth module.
  StopMove();                                     //Ensure all motors are stopped
  servoLook.attach(10);                           //Assign the servo pin
  servoLook.write(180);
  pinMode(trig, OUTPUT);                          //Assign ultrasonic sensor pin modes
  pinMode(echo, INPUT);
}


void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.read();                                 //Stores input to variable
    switch (command) {                                       //Use input as case for switch statement
      case 'F':
        servoLook.write(180);                                //Set the servo to look front
        if (getDistance() >= stopDist)                       //If there are no objects within the stopping distance, move forward
        {
          Drive();
        }
        else StopMove();                                     //If there are object within stopping distance, stop the car
        break;
      case 'B':
        servoLook.write(0);                                  //Set the servo to look back
        if (getDistance() >= stopDist)                       //If there are no objects within the stopping distance, move backward
        {
          Reverse();                                         //If there are object within stopping distance, stop the car
        }
        else StopMove();
        break;
      case 'L': TurnLeft(); break;
      case 'R': TurnRight(); break;
      case 'G': DriveLeft(); break;
      case 'I': DriveRight(); break;
      case 'H': ReverseLeft(); break;
      case 'J': ReverseRight(); break;
      case 'S': StopMove(); break;
      case '0': motorspeed = 0; break;
      case '1': motorspeed = 25; break;
      case '2': motorspeed = 50; break;
      case '3': motorspeed = 75; break;
      case '4': motorspeed = 100; break;
      case '5': motorspeed = 125; break;
      case '6': motorspeed = 150; break;
      case '7': motorspeed = 175; break;
      case '8': motorspeed = 200; break;
      case '9': motorspeed = 225; break;
      case 'q': motorspeed = 250; break;
    }

  }
}


void Drive()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(FORWARD); //rotate the motor clockwise
  rightBack.setSpeed(motorspeed);//Define maximum velocity
  rightBack.run(FORWARD); //rotate the motor clockwise
}

void Reverse()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(BACKWARD); //rotate the motor anti-clockwise
  rightBack.setSpeed(motorspeed); //Define maximum velocity
  rightBack.run(BACKWARD); //rotate the motor anti-clockwise
}


void TurnLeft()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(BACKWARD); //rotate the motor anti-clockwise
  rightBack.setSpeed(motorspeed); //Define maximum velocity
  rightBack.run(FORWARD);  //rotate the motor clockwise
}

void TurnRight()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(FORWARD); //rotate the motor clockwise
  rightBack.setSpeed(motorspeed); //Define maximum velocity
  rightBack.run(BACKWARD); //rotate the motor anti-clockwise
}

void DriveRight()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(FORWARD); //rotate the motor clockwise
  rightBack.setSpeed(motorspeed / 4); //Define maximum velocity
  rightBack.run(FORWARD); //rotate the motor clockwise
}
void ReverseRight()
{
  leftBack.setSpeed(motorspeed / 4); //Define maximum velocity
  leftBack.run(BACKWARD); //rotate the motor anti-clockwise
  rightBack.setSpeed(motorspeed); //Define maximum velocity
  rightBack.run(BACKWARD); //rotate the motor anti-clockwise
}
void DriveLeft()
{
  leftBack.setSpeed(motorspeed / 4); //Define maximum velocity
  leftBack.run(FORWARD); //rotate the motor clockwise
  rightBack.setSpeed(motorspeed); //Define maximum velocity
  rightBack.run(FORWARD); //rotate the motor clockwise
}
void ReverseLeft()
{
  leftBack.setSpeed(motorspeed); //Define maximum velocity
  leftBack.run(BACKWARD); //rotate the motor clockwise
  rightBack.setSpeed(motorspeed / 4); //Define maximum velocity
  rightBack.run(BACKWARD); //rotate the motor anti-clockwise
}

void StopMove()                                   //Set all motors to stop
{
  leftBack.setSpeed(0); //Define minimum velocity
  leftBack.run(RELEASE); //rotate the motor clockwise
  rightBack.setSpeed(0); //Define minimum velocity
  rightBack.run(RELEASE); //stop the motor when release the button
}


int getDistance()                                   //Get the distance between the ultrasonic sensor and an object
{
  unsigned long pulseTime;                          //Create a variable to store the pulse travel time
  int distance;                                     //Create a variable to store the calculated distance
  digitalWrite(trig, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pulseTime = pulseIn(echo, HIGH, timeOut);         //Measure the time for the pulse to return
  distance = (float)pulseTime * 340 / 2 / 10000;    //Calculate the object distance based on the pulse time
  return distance;
}
