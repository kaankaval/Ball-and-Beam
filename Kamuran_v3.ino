#include<Servo.h>
#include<PID_v1.h>
const int servoPin = 9;
float Kp = 4;// İlk Oransal Kazanç
float Ki = 1.1; // İlk İntegral Kazancı
float Kd = 1; //İlk Türev Kazancı
double Setpoint, Input, Output, ServoOutput;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
Servo myServo;
#define trigPin 13
#define echoPin 12
void setup() {
 
Serial.begin(9600);
myServo.attach(servoPin);
Input = readPosition();
myPID.SetMode(AUTOMATIC);
myPID.SetOutputLimits(-60,50); // between 300 and 50 degrees
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
 
void loop()
{
Setpoint = 12; // Balance point
Input = readPosition();
 
myPID.Compute();
 
ServoOutput=80+Output;
myServo.write(ServoOutput);
}
 
float readPosition() {
delay(20);
long duration, cm;
unsigned long now = millis();
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
cm = (duration/2) / 29.83; //Calculated from speed of sound equations

/*
331x(1+T/273)^1/2 ) = V m/s

V/10000 = V cm/us

1/V = x for sensor variable



*/
 
if(cm > 28) // mechanical limit for ball
{cm=30;}
//if(cm = 0) 
//{cm=4;}
 
Serial.println(cm);
 
return cm;
}
