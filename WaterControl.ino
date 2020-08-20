#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT11_PIN 7

dht DHT;
LiquidCrystal_I2C lcd(0x27, 12, 2);
int sensorValue = 0;
int sensorPin = A0;
int ledPin = 13;
int relePin = 10;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, LOW);
}

void loop() {
  
  lcd.clear();
  
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
  lcd.setCursor(1,0);
  if (sensorValue <= 100) {
    lcd.print("Water Level Empty ");
    digitalWrite(ledPin, HIGH);
    digitalWrite(relePin, HIGH);
    
  } else if (sensorValue > 100 && sensorValue <= 200) {
    lcd.print("Water Level Low");
    digitalWrite(ledPin, HIGH);
    digitalWrite(relePin, HIGH);
    
  } else if (sensorValue > 200 && sensorValue <= 400) {
    lcd.print("Water Level Medium");
    digitalWrite(ledPin, LOW);
    digitalWrite(relePin, LOW);
    
  } else if (sensorValue > 400) {
    lcd.print("Water Level High");
    digitalWrite(ledPin, LOW);
    digitalWrite(relePin, LOW);
  }
  
  lcd.setCursor(1,1);
  int chk = DHT.read11(DHT11_PIN);
  float t = DHT.temperature;
  float h = DHT.humidity;

  lcd.print(t);
  lcd.print("o ");
  lcd.print(h);
  lcd.print("%");
  
  delay(2000);
}