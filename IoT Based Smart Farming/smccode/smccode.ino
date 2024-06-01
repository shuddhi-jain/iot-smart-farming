#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// Pin Definitions
#define DHTPIN 2
#define DHTTYPE DHT11
#define LM35PIN A1  // Analog pin for LM35 sensor


// Sensor Initialization
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Constants and Variables
const int Fan_Pin = 6;
const int Pump_Pin = 7;
const int SoilMoisture_Pin = A0;
float soil_temp_Celsius = 0;
int relayOnState = LOW;
int relayOffState = HIGH;

void setup() {
  // Initialize Sensors and Serial Communication
  Serial.begin(9600);
  dht.begin();
  
  // Initialize LCD
  lcd.begin(16, 2);

    pinMode(Fan_Pin, OUTPUT);
  pinMode(Pump_Pin, OUTPUT);
  pinMode(SoilMoisture_Pin, INPUT);
  
  // Initial LCD Display

   lcd.setCursor(0, 0);
  lcd.print("IoT SMART FARMING");
  delay(500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Project Mentor");
  lcd.setCursor(0, 1);
  lcd.print("Prof Santanu Koley");
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Students Name:");
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Shuddhi Jain");
  delay(500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vishal Morya");
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sambhu Jana");
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System ON");
  delay(500);
  lcd.clear();
}

void loop() {
  // Reading Sensors
  int soil_moisture = analogRead(SoilMoisture_Pin);
  int humidity = dht.readHumidity();
  int atmosphere_tempC = dht.readTemperature();
  float lm35_temp_Celsius = analogRead(LM35PIN) * 0.48875855327;  // Convert analog reading to temperature
  
  // Check for failed readings
  if (isnan(humidity) || isnan(atmosphere_tempC) || isnan(lm35_temp_Celsius)) {
    Serial.println("Failed to read from sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }
  
  // Displaying the readings on the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Atmospheric Temp: ");
  Serial.print(atmosphere_tempC);
  Serial.print(" °C\t");
  Serial.print("Soil Moisture: ");
  Serial.print(soil_moisture);
  Serial.print(" \t");
  Serial.print("LM35 Temp: ");
  Serial.print(lm35_temp_Celsius);
  Serial.println(" °C");
  

  // Displaying the readings on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.print(soil_moisture);
  lcd.setCursor(7, 0);
  lcd.print("L_T:");
  lcd.print(lm35_temp_Celsius);
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(9, 1);
  lcd.print("T:");
  lcd.print(atmosphere_tempC);
  lcd.print("C");

delay(500);
  // Control Logic for Fan and Pump
  if (atmosphere_tempC > 30) {
    digitalWrite(Fan_Pin, HIGH);
    Serial.println("Fan: ON");
    lcd.setCursor(0, 0);
    lcd.print("Fan: ON");
  } else {
    digitalWrite(Fan_Pin, LOW);
    Serial.println("Fan: OFF");
    lcd.setCursor(0, 0);
    lcd.print("Fan: OFF");
  }

    // Control Logic for Pump based on LM35 temperature
  if (lm35_temp_Celsius > 25) {  // Adjust the threshold temperature as per your requirement
    // If LM35 temperature is high, irrigation is good
    digitalWrite(Pump_Pin, HIGH);
    Serial.println("Irrigation: Good");
  } else {
    // If LM35 temperature is not high enough, irrigation is bad
    digitalWrite(Pump_Pin, LOW);
    Serial.println("Irrigation: Bad");
  }

  
  if (soil_moisture < 400) {
    digitalWrite(Pump_Pin, HIGH);
    Serial.println("Pump: ON");
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON");
  } else {
    digitalWrite(Pump_Pin, LOW);
    Serial.println("Pump: OFF");
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF");
  }
  
  delay(2000); // Wait 2 seconds before the next loop
}