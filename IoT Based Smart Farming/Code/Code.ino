// include the library code:
#include <LiquidCrystal.h>

//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int Fan_Pin = 6;
const int Pump_Pin = 7;

void setup() {
  lcd.begin(20, 4);     // set up the LCD's number of columns and rows:
  lcd.setCursor(0, 0);  // set the cursor position:
  lcd.print(" IoT SMART FARMING    ");

  pinMode(Fan_Pin, OUTPUT);
  pinMode(Pump_Pin, OUTPUT);
  pinMode(A1, INPUT);
}

void loop() {
  //Temperature Sensing
  int S1 = analogRead(A0);          // Read Temperature
  float mV = (S1 / 1023.0) * 5000;  // Storing value in Degree Celsius
  int Temp = mV / 10;
  lcd.setCursor(0, 1);
  lcd.print(" T=");
  lcd.print(Temp);
  lcd.print("'C  ");

  //Rain Sensing
  int R = digitalRead(A1);  // Read Rain Sensor
  if (R == 0) {
    lcd.setCursor(10, 1);
    lcd.print(" R=NO ");
  }
  if (R == 1) {
    lcd.setCursor(10, 1);
    lcd.print(" R=YES ");
  }


  //Soil Moisture
  int S3 = analogRead(A2);  // Read Soil Moisture
  int SM = S3 / 10;
  lcd.setCursor(0, 2);
  lcd.print(" S=");
  lcd.print(SM);
  lcd.print("%  ");

  //Air Humidity
  int S4 = analogRead(A3);  // Read Air Humidity
  int H = S4 / 10;
  lcd.setCursor(10, 2);
  lcd.print(" H=");
  lcd.print(H);
  lcd.print("%  ");

  if (Temp > 30) {
    digitalWrite(Fan_Pin, HIGH);
    lcd.setCursor(0, 3);
    lcd.print(" Fan:ON  ");
  } else {
    digitalWrite(Fan_Pin, LOW);
    lcd.setCursor(0, 3);
    lcd.print(" Fan:OFF ");
  }

  if (SM < 40 && R == 0) {
    digitalWrite(Pump_Pin, HIGH);
    lcd.setCursor(10, 3);
    lcd.print(" Motor:ON  ");
  } else {
    digitalWrite(Pump_Pin, LOW);
    lcd.setCursor(10, 3);
    lcd.print(" Motor:OFF  ");
  }
}


