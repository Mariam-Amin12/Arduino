// smart gates difinition*******
#define ir1 A1
#define ir2 A2
#include<Servo.h>
Servo my_servo;

// smart led difinition**********
  
#define led1 0
#define led2 2
#define led3 4
#define led4 5 
#define led5 6
#define ldr A0

// showing empty places difintion********
#define a 7
#define b 8
#define c 9
#define d 10
#define e 11
#define f 12
#define g 13

// temp alarm difintion********
#define temp A3
#define bazzer 1  

void setup() {
  // smart gate**********
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  my_servo.attach(3);

// smart leds***********
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(ldr,INPUT);
  Serial.begin(9600);

// show empty placces*********

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
// temprture alarm**********
  pinMode(temp,INPUT);
  pinMode(bazzer,OUTPUT);
}
// number of places***********
int empty_place=4;  

void loop() {
  
//smart gates*******************************
  
int ir1_reading=digitalRead(ir1); 
int ir2_reading=digitalRead(ir2);

if(ir1_reading==0 && empty_place>0 )
{
  empty_place--;
 for(int i=0;i<=90;i++){
  my_servo.write(i);
  delay(20);
 }
delay(1500);
 for(int i=90;i>=0;i--){
  my_servo.write(i);
  delay(20);
 }
 
}

if(ir2_reading==0 && empty_place<4 )
{ 
  empty_place++;
 for(int i=0;i<=90;i++){
  my_servo.write(i);
  delay(20);
 }
delay(1500);
 for(int i=90;i>=0;i--){
  my_servo.write(i);
  delay(20);
 }
}

// show empty place in garage****************************

if (empty_place==0)
{
 digitalWrite(a,HIGH);
 digitalWrite(b,HIGH);
 digitalWrite(c,HIGH);
 digitalWrite(d,HIGH);
 digitalWrite(e,HIGH);
 digitalWrite(f,HIGH);
 digitalWrite(g,LOW);  
}

else if (empty_place==1)
{
 digitalWrite(a,LOW);
 digitalWrite(b,HIGH);
 digitalWrite(c,HIGH);
 digitalWrite(d,LOW);
 digitalWrite(e,LOW);
 digitalWrite(f,LOW);
 digitalWrite(g,LOW);  
}

else if (empty_place==2)
{
 digitalWrite(a,HIGH);
 digitalWrite(b,HIGH);
 digitalWrite(c,LOW);
 digitalWrite(d,HIGH);
 digitalWrite(e,HIGH);
 digitalWrite(f,LOW);
 digitalWrite(g,HIGH); 
}

else if (empty_place==3)
{
 digitalWrite(a,HIGH);
 digitalWrite(b,HIGH);
 digitalWrite(c,HIGH);
 digitalWrite(d,HIGH);
 digitalWrite(e,LOW);
 digitalWrite(f,LOW);
 digitalWrite(g,HIGH); 
}
else 
{
 digitalWrite(a,LOW);
 digitalWrite(b,HIGH);
 digitalWrite(c,HIGH);
 digitalWrite(d,LOW);
 digitalWrite(e,LOW);
 digitalWrite(f,HIGH);
 digitalWrite(g,HIGH); 
} 

// smart led*******************************************

int ldr_reading=analogRead(ldr);
Serial.println(ldr_reading);
if(ldr_reading<500){
 digitalWrite(led1,LOW);
 digitalWrite(led2,LOW);
 digitalWrite(led3,LOW);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
}
else
{  
 digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 digitalWrite(led3,HIGH);
 digitalWrite(led4,HIGH);
 digitalWrite(led5,HIGH);
}

// tmpreture sensor and bazzer*******************

int temp_reading=analogRead(temp);
float voltage=temp_reading*5.0/1023;
float degree=voltage*1/0.01;

if ( degree>45){
digitalWrite(bazzer,HIGH);
delay(500);
digitalWrite(bazzer,LOW);
delay(500);
}
else 
digitalWrite(bazzer,LOW);
}
