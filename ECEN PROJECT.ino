//Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//fonts
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>
#include <Fonts/FreeMono12pt7b.h  >

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define sensor A0
#define DHTPIN 2       // Digital pin 2
#define DHTTYPE DHT22  // DHT 11

int gasLevel = 0;  //int variable for gas level
String quality = "";
DHT dht(DHTPIN, DHTTYPE);

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed   to read from DHT sensor!");
    return;
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont();
  display.setCursor(3, 35);
  display.println("Temp :");
  display.setCursor(80, 35);
  display.println(t);
  display.setCursor(114, 35);
  display.println("C");
  display.setCursor(3, 47);
  display.println("Hum  :");
  display.setCursor(80, 47);
  display.println(h);
  display.setCursor(114, 47);
  display.println("%");
  display.drawLine(1, 44, 128, 44, WHITE);
  display.drawRect(1, 32, 127, 24, WHITE);
}

void air_sensor() {
  gasLevel = analogRead(sensor);

  if (gasLevel < 200) {
    quality = "   GOOD!";
  } else if (gasLevel > 200 && gasLevel < 400) {
    quality = "    Poor!";   
  } else if (gasLevel > 400 && gasLevel < 600) {
    quality = "Very bad!";   
  } else {
    quality = " Toxic";
  }

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(1, 6);
  display.setFont();
  display.println("Air Quality:");
  display.setTextSize(1);
  display.setCursor(20, 17);
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.println(quality);
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address   0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.invertDisplay(true);
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.setCursor(24, 15);
  display.println("ECEN 75");
  display.setFont(&FreeSansBoldOblique12pt7b);
  display.setCursor(5, 35);
  display.println("PROJECT");
  display.drawLine(0, 38, 128, 38, WHITE);
  display.setFont();
  display.setTextSize(1);
  display.setCursor(110, 40);
  display.println("3-3");
  display.setCursor(1, 46);
  display.println("- Geran");
  display.setTextSize(1);
  display.setCursor(1, 55);
  display.println("- Longalong");
  display.display();
  delay(3000);
  display.clearDisplay();

  display.invertDisplay(false);
  display.setTextSize(1.5);
  display.setCursor(30, 0);
  display.println("Air Quality,");
  display.setTextSize(1.5);
  display.setCursor(30, 10);
  display.println("Temperature &");
  display.setTextSize(1.5);
  display.setCursor(40, 20);
  display.println("Humidity");
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.setCursor(18, 43);
  display.println("Monitoring");
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.setCursor(30, 59);
  display.println("System");
  display.display();
  delay(4000);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  display.invertDisplay(false);
  display.setTextColor(WHITE);
  display.setFont(&FreeMonoOblique9pt7b);
  air_sensor();
  sendSensor();
  display.display();
}