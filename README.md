# IoT Smart Farming Project

## Project Overview

The IoT Smart Farming project aims to develop an automated system to monitor and control various environmental parameters such as soil moisture, humidity, and temperature in an agricultural setting. This system uses sensors to gather data and actuators to control devices like fans and pumps based on the sensor readings.

## Components Used

- **Arduino Uno**: The main microcontroller board used to interface with sensors and actuators.
- **DHT11 Sensor**: Used to measure humidity and atmospheric temperature.
- **LM35 Sensor**: Used to measure soil temperature.
- **Soil Moisture Sensor**: Used to measure the moisture content in the soil.
- **LiquidCrystal Display (LCD)**: Used to display sensor readings and system status.
- **Fan and Pump**: Actuators controlled based on temperature and soil moisture readings.
- **Relays**: Used to switch the fan and pump on and off.

## Pin Definitions

- **DHT11 Sensor**: Connected to digital pin 2.
- **LM35 Sensor**: Connected to analog pin A1.
- **Soil Moisture Sensor**: Connected to analog pin A0.
- **Fan**: Connected to digital pin 6.
- **Pump**: Connected to digital pin 7.
- **LCD**: Connected to digital pins 13, 12, 11, 10, 9, 8.

## Software Components

The project uses the following libraries:
- `Wire.h`: For I2C communication.
- `LiquidCrystal.h`: For interfacing with the LCD.
- `DHT.h`: For interfacing with the DHT11 sensor.

## Setup Instructions

1. **Hardware Setup**:
   - Connect the DHT11 sensor to digital pin 2.
   - Connect the LM35 sensor to analog pin A1.
   - Connect the soil moisture sensor to analog pin A0.
   - Connect the fan to digital pin 6 via a relay.
   - Connect the pump to digital pin 7 via a relay.
   - Connect the LCD to digital pins 13, 12, 11, 10, 9, 8.

2. **Library Installation**:
   - Install the `DHT sensor library` by Adafruit.
   - Install the `LiquidCrystal` library.

3. **Arduino Code**:
   - Copy and paste the provided code into the Arduino IDE.
   - Upload the code to the Arduino Uno board.

```cpp
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
    digitalWrite(Pump_Pin, HIGH);
    Serial.println("Irrigation: Good");
  } else {
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
```

## Working Principle

1. **Reading Sensor Data**:
   - The system reads humidity and temperature from the DHT11 sensor.
   - The LM35 sensor provides soil temperature readings.
   - The soil moisture sensor provides soil moisture levels.

2. **Displaying Data**:
   - The sensor readings are displayed on the serial monitor.
   - The sensor readings are also displayed on the LCD.

3. **Controlling Actuators**:
   - The fan is turned on if the atmospheric temperature exceeds 30°C.
   - The pump is turned on if the soil moisture is below a threshold value or if the soil temperature exceeds a threshold value (25°C).

## Notes

- Adjust the threshold values for temperature and soil moisture according to your specific requirements.
- Ensure all connections are secure and double-check the wiring before powering the system.

## Contributors

- Shuddhi Jain
- Vishal Morya
- Sambhu Jana

## Acknowledgments

- Project Mentor: Prof. Santanu Koley

This README provides an overview of the IoT Smart Farming project, including component details, setup instructions, and code explanation. This system aims to facilitate efficient farming by automating environmental monitoring and control processes.
