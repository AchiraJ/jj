#include <LiquidCrystal.h> //includes the LiquidCrystal Library
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = 9;
const int echoPin = 8;

long duration;
int distanceCm;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); // Initialises the interface to the LCD screen, and specifies the dimensions (width and height) of the display
 
  pinMode (trigPin, OUTPUT); // sets the trigPin as an output
  pinMode (echoPin, INPUT); //sets the echoPin as an Input
  Serial.begin(9600); //Starts the serial communication
  }

  void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin, LOW);

  //Reads echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn (echoPin, HIGH);

  //Calculating the distance
  distanceCm = duration * 0.034 / 2;
 
  lcd.clear();
  lcd.setCursor (0,0); //Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print ("Distance:"); //Prints the string "Distance" on the LCD
  lcd.print(distanceCm); // Prints the distance value from the sensor
  lcd.print(" cm");
  Serial.println(distanceCm);
  
 
 
  delay (1000);
}
