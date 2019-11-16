#include <SoftwareSerial.h>
#include <LiquidCrystal.h> //includes the LiquidCrystal Library

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int moistureSensor = A5;
const int pump = 13;
const int valve = 12;
const int trigPin = 9;
const int echoPin = 8;
int analogvalue = 0;
int percent = 0;
long duration;
int distanceCm;

bool is_filling = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialises the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.print ("A GSM-BASED AUTO");
  lcd.setCursor(0, 1);
  lcd.print("IRRIGATION SYS");
  delay (3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("By JONATHAN");
  lcd.setCursor(0, 1);
  lcd.print ("ACHIRA");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REG. NO:");
  lcd.setCursor(0, 1);
  lcd.print("EEEI/00978/2015");
  delay(2000);
  lcd.clear();
  
  pinMode(pump, OUTPUT);
  pinMode(valve, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  soilMoisture();
  levelSensor();
  lcd.clear();
}

void levelSensor() {
  //maintains water level in the tank
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite (trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Reads echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn (echoPin, HIGH);
  //Calculating the distance
  distanceCm = duration * 0.034 / 2;
  int tankHeightCm = (50 - distanceCm);
  int percentage = (tankHeightCm * 100 / 50);
  Serial.println("Distance");
  Serial.println(distanceCm);
  Serial.println("tank height");
  Serial.println(tankHeightCm);
  Serial.println("percentage");
  Serial.println(percentage);

 
  //control section
 
  if (percentage <= 50) {

    is_filling = true;
    digitalWrite (pump, LOW);
    lcd.setCursor (0, 1);
    lcd.print("PUMP ON,");
    lcd.setCursor(8, 1);
    lcd.print("TANK");
    lcd.setCursor(13, 1);
    lcd.print(percentage);
    lcd.setCursor(15, 1);
    lcd.print("%");
    delay(2000);
  }
  if (percentage >= 90) {

    is_filling = false;
    
    digitalWrite (pump, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("TANK FULL");
    lcd.setCursor(11, 1);
    lcd.print(percentage);
    lcd.setCursor(13, 1);
    lcd.print("%");
    delay(2000);
  }

  if(is_filling){
    
        is_filling = true;
        
    digitalWrite (pump, LOW);
    lcd.setCursor (0, 1);
    lcd.print("PUMP ON,");
    lcd.setCursor(8, 1);
    lcd.print("TANK");
    lcd.setCursor(13, 1);
    lcd.print(percentage);
    lcd.setCursor(15, 1);
    lcd.print("%");
    delay(2000);
    
  }
  else {
    digitalWrite(pump, HIGH);
    lcd.setCursor(0, 1);
    //lcd.print("PUMP OFF");
    lcd.setCursor(9, 1);
    lcd.print("TANK");
    lcd.setCursor(13, 1);
    lcd.print(percentage);
    lcd.setCursor(15, 1);
    lcd.print("%");
    delay (2000);
  }
  
}

  void soilMoisture() {
    analogvalue = analogRead(moistureSensor);
    percent = map(analogvalue, 298, 1019, 100, 0);
    Serial.println("analog Value");
    Serial.println(analogvalue);
    Serial.println("Percent");
    Serial.println(percent);
  
    //irrigation control section
    if (percent <= 30) {
      digitalWrite(valve, LOW);
      lcd.setCursor(0, 0);
      lcd.print("IRRIGATING");
      delay(2000);
    }
    else if (percent == 100) {
      digitalWrite (valve, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("VALVE OFF");
      delay(2000);
    }
    else {
      digitalWrite(valve, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("VALVE OFF");
      delay(2000);
    }
    
  }
