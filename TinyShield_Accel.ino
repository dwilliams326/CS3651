/*************************************************************************
 * BMA250 Tutorial:
 * This example program will show the basic method of printing out the 
 * accelerometer values from the BMA250 to the Serial Monitor, and the
 * Serial Plotter
 * 
 * Hardware by: TinyCircuits
 * Code by: Laverena Wienclaw for TinyCircuits
 *
 * Initiated: Mon. 11/1/2018
 * Updated: Tue. 11/2/2018
 ************************************************************************/
 
#include <Wire.h>         // For I2C communication with sensor
#include "BMA250.h"       // For interfacing with the accel. sensor

// Accelerometer sensor variables for the sensor and its values
BMA250 accel_sensor;
int x, y, z;
int initial_x, initial_y, initial_z;
double temp;

#if defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#else
#define SerialMonitorInterface Serial
#endif

void setup() {
  SerialMonitorInterface.begin(115200);
  Wire.begin();

  SerialMonitorInterface.print("Initializing BMA...");
  // Set up the BMA250 acccelerometer sensor
  accel_sensor.begin(BMA250_range_2g, BMA250_update_time_64ms);
  accel_sensor.read(); 
  initial_x = accel_sensor.X;
  initial_y = accel_sensor.Y;
  initial_z = accel_sensor.Z;
  SerialMonitorInterface.println(initial_x);
  SerialMonitorInterface.println(initial_y);
  SerialMonitorInterface.println(initial_z);

  
}

void loop() {
  accel_sensor.read();//This function gets new data from the acccelerometer
  SerialMonitorInterface.println(initial_x);
  SerialMonitorInterface.println(initial_y);
  SerialMonitorInterface.println(initial_z);
  // Get the acceleration values from the sensor and store them into global variables
  // (Makes reading the rest of the program easier)
  x = accel_sensor.X;
  y = accel_sensor.Y;
  z = accel_sensor.Z;
  temp = ((accel_sensor.rawTemp * 0.5) + 24.0);

  // If the BMA250 is not found, nor connected correctly, these values will be produced
  // by the sensor 
  if (x == -1 && y == -1 && z == -1) {
    // Print error message to Serial Monitor
    SerialMonitorInterface.print("ERROR! NO BMA250 DETECTED!");
  }
  
  else { // if we have correct sensor readings: 
    showSerial();                 //Print to Serial Monitor or Plotter
    calculateInput();
  }

  // The BMA250 can only poll new sensor values every 64ms, so this delay
  // will ensure that we can continue to read values
  delay(70);
  // ***Without the delay, there would not be any sensor output*** 
}

// Prints the sensor values to the Serial Monitor, or Serial Plotter (found under 'Tools')
void showSerial() {
  SerialMonitorInterface.print("X = ");
  SerialMonitorInterface.print(x);
  
  SerialMonitorInterface.print("  Y = ");
  SerialMonitorInterface.print(y);
  
  SerialMonitorInterface.print("  Z = ");
  SerialMonitorInterface.print(z);
  
  SerialMonitorInterface.print("  Temperature(C) = ");
  SerialMonitorInterface.println(temp);
  
}

void calculateInput() {
  if (x > initial_x + 20 or x < initial_x - 20) {
    SerialMonitorInterface.println("We have an x motion");
  } else {
    SerialMonitorInterface.println("No x motion");
  }
  if (y > initial_y + 20 or y < initial_y - 20) {
    SerialMonitorInterface.println("We have an y motion");
  } else {
    SerialMonitorInterface.println("No y motion");
  }
  if (z > initial_z + 20 or z < initial_z - 20) {
    SerialMonitorInterface.println("We have an z motion");
  } else {
    SerialMonitorInterface.println("No z motion");
  }
  
  
}
