#include <Adafruit_LiquidCrystal.h>
#include <cmath>
#include <iostream>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <avr/sleep.h>
#include <avr/power.h>

const int interruptPin = 2; // Pin to trigger the interrupt
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // alamat I2C integrated circuit communication

// LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LiquidCrystal[] = {12,11,5,4,3,2};
const int lengthPivotTuas = lengthPivotTuas;
const int buttons = 1; // number of buttons
const int buttonPins[buttons] = {2}; // Change pin numbers as per your connections
const int buttonTimeout = 5000; // Time in milliseconds before automatic shutdown
int AcceleroMeterValue;
int d1;
int d2;


void setup() {
  // put your setup code here, to run once:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp, LOW);
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
  void autosleepproto() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Choose the desired sleep mode
    sleep_enable();
    sleep_mode();
    stopActions();
  }
  void wakeUp() {
    // This function is called when the interrupt pin triggers the interrupt
    sleep_disable(); // Disable sleep mode
    detachInterrupt(digitalPinToInterrupt(interruptPin)); // Detach the interrupt
    startActions();
  }

  void loop() {
    // display enter input
      lcd.print("Calibrate Sensor?")
      while {
        if (digitalRead(,))
      }
      for (int i = 0; i < buttons; i++) {
      int buttonState = digitalRead(buttonPins[i]);
      lastButtonPressTime = millis();
       if(buttonState == HIGH){
          lcd.print("waking up")
          wakeUp();
       }else{
          delay(500);
          lcd.print("sleep mode, press button to restart.")
          autosleepproto();

  delay(500);
  lcd.print("Input jarak pivot pada ujung tuas berbeban"); 
    // masih memikir cara membuat sistem input data length	
  lengthPivotTuas = ; //Input jarak
    // mendapatkan data accelerometer
  ADXLdata();
    // eksekusi kalkulasi dan memunculkan hasil
  d1d2Calc();
    // hitung d1 dan d2
  lcd.print("Jarak antar benda dan tuas: "+d1+" dan panjang
  pegas adalah: "+d2+”);
  //  hasil
}

void ADXLdata() {
  // fungsi untuk mendapat data akselerometer
    sensors_event_t event;
  accel.getEvent(&event);

  float accelerationX = event.acceleration.x;
  float accelerationY = event.acceleration.y;
  float accelerationZ = event.acceleration.z;

  float roll = atan2(accelerationY, accelerationZ) * 180.0 / PI;
  float pitch = atan2(-accelerationX, sqrt(accelerationY*accelerationY+accelerationZ*accelerationZ)) * 180.0 / PI;

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

void calibrateADXL345() {
  Serial.println("Calibrating ADXL345. Please keep the sensor still...");
  
  float x_offset = 0.0, y_offset = 0.0, z_offset = 0.0;
  const int num_samples = 100; // Number of samples for calibration
  
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
  Serial.print("X-axis Offset: "); Serial.println(x_offset);
  Serial.print("Y-axis Offset: "); Serial.println(y_offset);
  Serial.print("Z-axis Offset: "); Serial.println(z_offset);
  
  // Apply offsets to the accelerometer (optional)
  accel.setOffsets(x_offset, y_offset, z_offset);
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
