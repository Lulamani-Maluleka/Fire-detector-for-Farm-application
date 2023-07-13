

// include the library code:
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
 #include <dht.h>

#include <LiquidCrystal.h>

dht DHT;
#define moisture 8
#define motor 9
#define fire 13
#define DHT11_PIN 7
#define buzzer 6
int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor
String data="";
String d="1024";
String f="512";
// initialize the library with the numbers of the interface pins
//Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
  Serial.begin(9600);
  pinMode(motor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(fire,INPUT);
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
 sensorValue = analogRead(sensorPin); 

/*=========RECIEVING THE SIGNAL FORM APP=========*/
if(Serial.available()>0)
{
  data = Serial.readString();
  Serial.print("Data received");
  Serial.println(data);
  
  
  }
  /*---------------------------------*/
   if(data=="ON")
   {
    digitalWrite(motor,HIGH);
    
   }
   else if(data=="OFF")
   {
     digitalWrite(motor,LOW);
      
    }
  /*==============================*/
   if(digitalRead(fire)==HIGH)
   {
    //Conditions when the fire is on
    digitalWrite(buzzer,HIGH);
    }
    else
    {
     //Conditions when the fire is off
     
     digitalWrite(buzzer,LOW);
    }
  if(DHT.humidity>40)
  {
   digitalWrite(motor,HIGH);
   }
   else
    {
    digitalWrite(motor,LOW);
    }


  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");



/*==================PLEASE DONT TOUCH===============*/
 Serial.print((int)DHT.temperature); 
 Serial.print(";");
 Serial.print((int)DHT.humidity);
 Serial.print(";");
 Serial.print(sensorValue);
 //Serial.print(";");
 //Serial.print(d);
 Serial.print("\n");
 delay(500);
/*==================PLEASE DONT TOUCH===============*/

}
