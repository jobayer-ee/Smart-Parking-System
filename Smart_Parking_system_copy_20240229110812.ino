/*
This code is created 29th Feb 2024
Abdullah Al Jobayer
Electrical & Electronic Engineer
Official Guithub : https://github.com/jobayer-ee 
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//define the i2c address of the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

//connect the 2 ultrasonic sensor and the servo motor accordinng to the connection 
const int trigPin1 = 9; // First ultrasonic sensor trigger pin D9
const int echoPin1 = 8; // First ultrasonic sensor echo pin D8
const int trigPin2 = 10; // Second ultrasonic sensor trigger pin D10
const int echoPin2 = 11; // Second ultrasonic sensor echo pin D11
const int servoPin = 7; // Servo motor Pin D7

int carCount = 0; // initially the car counnt start with 0

// Function declarations
void openDoor();
void closeDoor();
float checkDistance(int trigPin, int echoPin);
void updateDisplay();

// Create an OLED display instance
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
   // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Initialize LCD display
  lcd.init();
  lcd.backlight();
  lcd.print("Car count: ");
  lcd.setCursor(0, 1);
  
  //activating the servo motor
  doorServo.attach(servoPin);
  closeDoor(); // Ensure the door is closed initially

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  // Check if a car is approaching the entrance
  if (carCount < 7 && checkDistance(trigPin1, echoPin1) <= 20) { // this line diclare 7 max viacle can enter the parking and the sensor will pin the car if the distance is 20CM
    openDoor();
    delay(3000); // Adjust this delay as needed to allow time for the car to pass the door
    closeDoor();
    carCount++;
    updateDisplay();
  }

  // Check if a car is leaving the parking
  if (checkDistance(trigPin2, echoPin2) <= 10 && carCount > 0) {
    openDoor();
    delay(3000); // Adjust this delay as needed to allow time for the car to pass the door
    closeDoor();
    carCount--;
    updateDisplay();
  }
}

// Function to check the distance using an ultrasonic sensor
float checkDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

// Function to open the door using the servo motor
void openDoor() {
  doorServo.write(0); // Assuming 0 degrees is the open position
}

// Function to close the door using the servo motor
void closeDoor() {
  doorServo.write(90); // Assuming 90 degrees is the closed position
}

// Function to update the car count on the LCD display
void updateDisplay() {
  lcd.setCursor(12, 1);
  lcd.print("carCount : ");
  lcd.print(carCount);
// Function to update the disply color and text size
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
// Function to update the car count on the OLED display
  display.setCursor(0, 0);
  display.print("IP: ");
  display.println("Car count: ");
  display.println(carCount);
  display.display();
}
// END of the code 