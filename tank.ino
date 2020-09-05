#include <Servo.h> 
#include <SoftwareSerial.h>
#include <FastLED.h> 

# define NUM_LEDS 10//number of LEDs
# define LED_PIN 2

 CRGB leds[NUM_LEDS];

//Esc pins
int escPin1 = 3;
int escPin2 = 5;
int escPin3 = 6;
int escPin4 = 10;
String readString;

int ind1; 
int ind2;
int ind3;
int ind4;

double x1 = 0;
double x2 = 0;
double y1 = 0;
double y2 = 0;
char incomingByte = 0;              

String message = "";

//SETUP
void setup() {
  FastLED.addLeds < WS2812B, LED_PIN, GRB > (leds, NUM_LEDS);
  FastLED.showColor(leds, CRGB::Blue);

  Serial.begin(9600);
  Serial.println("init");
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}
 
//LOOP
void loop() {
  
  while(Serial.available() > 0) 
  {
    delay(3);
    incomingByte = Serial.read(); //Reads incoming bytes
    message += incomingByte; //Creates string of bytes
  }
  if(!(Serial.available() > 0)){
    if(message != ""){
      Serial.println(message);
      bool comma = message.indexOf(",") > 0; //If using joystick
      if(comma){
          joystickUpdate(); 
      }
      readString = message;
      message = "";
   }
  }

arcadeDrive();
}
void arcadeDrive(){
  double left = y1 + x2;
  double right = y1 - x2;
  tankDrive(left, right);
}
void tankDrive(){
  if(y1 > 0){
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);

  }else if(y1 < 0){
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
  }else{
    analogWrite(7, LOW);
    analogWrite(6, LOW);
  }
  analogWrite(5, abs(y1 * 255));
  
  if(y2 > 0){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);

  }else if(y2 < 0){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }else{
    analogWrite(8, LOW);
    analogWrite(9, LOW);
  }
  analogWrite(10, abs(y2 * 255));

}
void tankDrive(double left, double right){
  if(left > 0){
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);

  }else if(left < 0){
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
  }else{
    analogWrite(7, LOW);
    analogWrite(6, LOW);
  }
  analogWrite(5, abs(left * 255));

  if(right > 0){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);

  }else if(right < 0){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }else{
    analogWrite(8, LOW);
    analogWrite(9, LOW);
  }
  analogWrite(10, abs(right * 255));

}


void joystickUpdate(){
  ind1 = readString.indexOf(',');  //finds location of first ,
  x1 = readString.substring(0, ind1).toDouble();   //captures first data String
  ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
  y1 = readString.substring(ind1+1, ind2+1).toDouble();   //captures second data String
  ind3 = readString.indexOf(',', ind2+1);
  x2 = readString.substring(ind2+1, ind3+1).toDouble();
  y2 = readString.substring(ind3+1, readString.length()).toDouble(); 
}
