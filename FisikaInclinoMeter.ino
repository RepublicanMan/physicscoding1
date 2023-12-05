#include <Adafruit_LiquidCrystal.h>
#include <cmath>
#include <iostream>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // alamat I2C
// LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LiquidCrystal[] = {12,11,5,4,3,2};
const int lengthPivotTuas = lengthPivotTuas;
int AcceleroMeterValue = ;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Initializing");
    if (!accel.begin()) {
      lcd.clear();
      lcd.print("Error initializing accelerometer");
      while (1); // Loop if accelerometer initialization fails
    }else {
      lcd.print("Accelerometer initialized successfully!");
      // set custom params if necessary
      accel.setRange(ADXL345_RANGE_16_G); // Sets range to 16G
      accel.setDataRate(ADXL345_DATARATE_100_HZ); // Sets data rate to 100Hz
    }
  }

}
void loop() {
    // display enter input
  delay(500);
  lcd.print("Input jarak pivot pada ujung tuas berbeban"); 
    // masih memikir cara membuat sistem input data length	
  lengthPivotTuas = ; //Input jarak
    // mendapatkan data accelerometer
  ADXLdata();
    // eksekusi kalkulasi dan memunculkan hasil
  d1d2Calc();
  lcd.print("Jarak antar benda dan tuas: "+d1+" dan panjang
  pegas adalah: "+d2+”);
}

void ADXLdata() {
  // fungsi untuk mendapat data akselerometer
    sensors_event_t event;
  accel.getEvent(&event);

  float accelerationX = event.acceleration.x;
  float accelerationY = event.acceleration.y;
  float accelerationZ = event.acceleration.z;

  float roll = atan2(accelerationY, accelerationZ) * 180.0 / PI;
  float pitch = atan2(-accelerationX, sqrt(accelerationY * accelerationY + accelerationZ * accelerationZ)) * 180.0 / PI;

  lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Roll: ");
  // lcd.print(roll);
  // lcd.print(" degrees");

  lcd.setCursor(0, 1);
  lcd.print("Pitch: ");
  lcd.print(pitch);
  lcd.print(" degrees");
}

void d1d2Calc() {
  // menghitung d1, dan d2 dari data akselerometer,
  dan panjang antara tuas dan pivot
  int d1 = lengthPivotTuas*sin(pitch);
  int d2 = d1;
  return d1
  return d2 
}


// #include <Adafruit_LiquidCrystal.h>
// #include <cmath>
// #include <iostream>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_ADXL345_U.h>

// Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Change the I2C address if necessary
// // LCD pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
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
