// #include <Adafruit_LiquidCrystal.h>
// #include <iostream> // C++ standard library for input/output streams
#include <math.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <avr/sleep.h>
#include <avr/power.h>
// #include <Adafruit_GFX.h> // graphics library
// #include <Adafruit_ILI9341.h>
#include <Adafruit_TFTLCD.h>
#include <SPI.h>
#include <TFT.h>
#include <Adafruit_ST7735.h>  
// The TFT library relies on the SPI library for communication with the screen and SD card, and needs to be included in all sketches.
// #include <UTFT.h>
// #include <UTOUCH.H>

// TFT FUNCTIONS
#define LCD_CS A3  // Chip Select goes to Analog 3
#define LCD_CD A2  // Command/Data goes to Analog 2
#define LCD_WR A1  // LCD Write goes to Analog 1
#define LCD_RD A0  // LCD Read goes to Analog 0

#define LCD_RESET A4  // Can alternately just connect to Arduino's reset pin
#define LCD_RESET A2  // sample pin


const int interruptPin = 2;                                        // Pin to trigger the interrupt
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);  // alamat I2C integrated circuit communication

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

// UTFT myGLCD

// LCD pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// const int LiquidCrystal[LC] = {12,11,5,4,3,2};
const int lengthPivotTuas = 0;
const int buttons = 2;                  // number of buttons
const int buttonPins[buttons] = { 2 };  // Change pin numbers as per your connections
const int buttonTimeout = 5000;         // Time in milliseconds before automatic shutdown
int AcceleroMeterValue;
int d1;
int d2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.begin();
  pinMode(interruptPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, LOW);
  Serial.println(F("TFT LCD Initializing"));
  if (!accel.begin()) {
    // tft.fillScreen(ILI9341_BLACK);  // Clear to black
    tft.print("Error initializing accelerometer");
    }else{
    tft.print("Accelerometer initialized successfully!");
    // set custom params if necessary
    accel.setRange(ADXL345_RANGE_16_G);          // Sets range to 16G
    accel.setDataRate(ADXL345_DATARATE_100_HZ);  // Sets data rate to 100Hz
  }
}
void loop() {
  // Display "enter input"
  while (buttonPins[2], LOW) {
    if (digitalRead(buttonPins[2]) == HIGH) {
      // tft.fillScreen(ILI9341_BLACK);  // Fill the screen with black color

      // Set the text color and size
      // tft.setTextColor(ILI9341_WHITE);  // Set text color to white
      tft.setTextSize(2);               // Set text size (you can change this to your desired size)

      // Set the cursor position (X, Y) from where the text will start
      tft.setCursor(10, 10);

      // Display text on the TFT screen
      tft.println("TFT has been Initialized");  // Print text to the screen
      wakeUp();
    } else {
      tft.println("currently in sleep mode, press button to restart.");
      delay(5000);
      autosleep();
      if (digitalRead(buttonPins[2]) == HIGH) {
        tft.println("Waking Up");
        wakeUp();
      }
    }
  }

  for (int i = 0; i < buttons; i++) {
    int buttonState = digitalRead(buttonPins[i]);
    // lastButtonPressTime = millis();
  }
    tft.println("Press Button 2 to Calibrate Sensor");
    while (digitalRead(buttonPins[2]), LOW) {
      if (digitalRead(buttonPins[2]), HIGH) {
        calibrateADXL345();
      }
    }

  delay(500);
  tft.println("Input jarak pivot pada ujung tuas berbeban");
  // masih memikir cara membuat sistem input data length
  lengthPivotTuas = 0;  //Input jarak

  // mendapatkan data accelerometer
  ADXLdata();

  // eksekusi kalkulasi dan memunculkan hasil
  d1d2Calc();

  // hitung d1 dan d2
  tft.println("Jarak antar benda dan tuas: " + String(d1) + "cm dan panjang pegas adalah: " + String(d2) + "cm");
  //  hasil
}


      void autosleep() {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Choose the desired sleep mode
        sleep_enable();
        sleep_mode();
      }

      void wakeUp() {
        // This function is called when the interrupt pin triggers the interrupt
        sleep_disable();                                       // Disable sleep mode
        detachInterrupt(digitalPinToInterrupt(interruptPin));  // Detach the interrupt
      }

      void ADXLdata() {
        // Function to obtain accelerometer data
        sensors_event_t event;   // Library
        accel.getEvent(&event);  // Library

        float accelerationX = event.acceleration.x;
        float accelerationY = event.acceleration.y;
        float accelerationZ = event.acceleration.z;

        float roll = atan2(accelerationY, accelerationZ) * 180.0 / PI;
        float pitch = atan2(-accelerationX, sqrt(accelerationY * accelerationY + accelerationZ * accelerationZ)) * 180.0 / PI;

        // tft.clear(ST7735_BLACK);
        // lcd.setCursor(0, 0);
        // lcd.print("Roll: ");
        // lcd.print(roll);
        // lcd.print(" degrees");

        tft.setCursor(0, 1);
        tft.println("Pitch: "); //ln or no ln since ln gives new line, dilemna
        tft.println(pitch);
        tft.println(" degrees");
      }

      void d1d2Calc() {
        // Calculate d1 and d2 from accelerometer data and the length between lever and pivot 
        int d1 = lengthPivotTuas * sin(pitch);
        int d2 = d1;
        return d1 return d2;
      }

      void calibrateADXL345() {
        Serial.println("Calibrating ADXL345. Please keep the sensor still");

        float x_offset = 0.0, y_offset = 0.0, z_offset = 0.0;
        const int num_samples = 100;  // Number of samples for calibration

        for (int i = 0; i < num_samples; ++i) {
          sensors_event_t event;
          accel.getEvent(&event);

          x_offset += event.acceleration.x;
          y_offset += event.acceleration.y;
          z_offset += event.acceleration.z;

          delay(10);
        }

        x_offset /= num_samples;
        y_offset /= num_samples;
        z_offset /= num_samples;

        Serial.println("Calibration complete.");
        Serial.print("X-axis Offset: ");
        Serial.println(x_offset);
        Serial.print("Y-axis Offset: ");
        Serial.println(y_offset);
        Serial.print("Z-axis Offset: ");
        Serial.println(z_offset);

        // Apply offsets to the accelerometer (optional)
        accel.setOffsets(x_offset, y_offset, z_offset);
        }


// old code


// #include <Adafruit_LiquidCrystal.h>
// #include <math.h>
// // #include <iostream>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_ADXL345_U.h>

// Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Change the I2C address if necessary
// // LCD pins
// // LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// const int LiquidCrystal[] = {12,11,5,4,3,2};
// const int lengthPivotTuas = lengthPivotTuas;
// int InclinoMeterValue = ;

// void setup() {
//   // put your setup code here, to run once:
//   lcd.begin(16,2);
//   lcd.print("Initializing");
//   loop();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   delay(500);
//   lcd.print("Input jarak pivot kepada ujung tuas berbeban");
//   String lengthPivotTuas = "";
//   lengthPivotTuas = ; //Input jarak
//   int d1 = lengthPivotTuas*sin();
//   int d2 = d1;
//   return d1
//   return d2
//   lcd.print("Jarak antar benda dan tuas: "+d1+" dan panjang pegas adalah: "+d2+);

// }

// void sin() {
//   //Add angle function
//   angle = InclinoMeterValue;
//   return angle
// }
