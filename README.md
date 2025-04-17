# Control code for I2C Ozone Sensor
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub stars](https://img.shields.io/github/stars/SmarThinks/OzoneSensor)](https://github.com/SmarThinks/OzoneSensor/stargazers)


## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Dependencies](#software-dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [API Reference](#api-reference)
- [Example](#example)
- [License](#license)

## 🌐 Overview

An microcontroller-compatible C++ library for interfacing with the Ozone Sensor. This library provides a structured approach to initialize the sensor, configure measurement modes, and read ozone concentration data via the I2C interface

## ✨ Features

- Supports multiple I2C addresses: 0x70, 0x71, 0x72, 0x73
- Configurable measurement modes: Active (automatic) and Passive (manual)
- Reads ozone concentration in parts per billion (ppb)
- Compatible with Arduino, ESP32, Raspberry Pi, and other I2C-capable platforms

## 🔌 Installation

### Using the Arduino Library Manager
1. Open the Arduino IDE.
2. Navigate to **Sketch** > **Include Library** > **Manage Libraries...**
3. In the Library Manager, enter `OzoneSensor` into the search box.
4. Locate the library and click **Install**.

### Manual Installation

1. Download the [ZIP archive](https://github.com/SmarThinks/OzoneSensor/archive/refs/heads/main.zip) of this repository.
2. Extract the contents into your Arduino libraries directory (typically located at `~/Arduino/libraries/`).
3. Restart the Arduino IDE to recognize the new library.

## 🚀 Usage

### Wiring Diagram

```lua
[Microcontroller]     [Ozone Sensor]
   5V   ----------->       VCC
   GND  ----------->        GND
   SDA   ---------->       SDA
   SCL  ----------->        SCL
```
### Basic Example

```c++
/*!
 * @file  ReadOzoneData.ino
 * @brief Reads ozone concentration in parts per billion (PPB).
 * 
 * @n Steps:
 * - Determine the I2C device address. Use the DIP switches A0 and A1:
 *     ADDRESS_0 → [0 0], ADDRESS_1 → [1 0], ADDRESS_2 → [0 1], ADDRESS_3 → [1 1]
 * - Set the measurement mode: active or passive.
 * - Begin reading the ozone concentration data.
 *
 * @note The ozone sensor needs approximately 3 minutes to stabilize before readings become reliable.
 *
 * @n This sketch prints the ozone concentration value to the serial monitor in PPB.
 * @n Since the sensor readings are typically below 10000, returned values will generally be within that range.
 */

#include "OzoneSensor.h"

#define COLLECT_NUMBER   120             // Number of samples to collect for averaging (recommended: 1–100)
int16_t data[COLLECT_NUMBER];            // Array to store ozone readings

int IndexCurrently = 0;                  // Index for current position in circular buffer
float sum = 0;                           // Sum of collected values
int cont = 0;                            // Counter for number of values collected
float avgData = 0;                       // Averaged ozone value

#define Ozone_IICAddress OZONE_ADDRESS_3
/*
 * I2C slave address. Default is OZONE_ADDRESS_3
 *   ADDRESS_0 → 0x70
 *   ADDRESS_1 → 0x71
 *   ADDRESS_2 → 0x72
 *   ADDRESS_3 → 0x73
 */

OzoneSensor Ozone;

void setup() {
  Serial.begin(115200);

  // Initialize the sensor with selected I2C address
  while (!Ozone.begin(Ozone_IICAddress)) {
    Serial.println("I2C device connection failed!");
    delay(1000);
  }
  Serial.println("I2C connection established successfully!");

  /*
   * Set I2C measurement mode:
   *   MEASURE_MODE_AUTOMATIC → active mode (continuous)
   *   MEASURE_MODE_PASSIVE   → passive mode (on-demand)
   */
  Ozone.setModes(MEASURE_MODE_PASSIVE);

  // Initialize data array with zeros
  for (int i = 0; i < COLLECT_NUMBER; i++) {
    data[i] = 0;
  }
}

void loop() {
  /*
   * Read ozone data in passive mode
   * Use PASSIVE_READ_DATA to trigger manual reading
   */
  int16_t ozoneConcentration = Ozone.readOzoneDataReal(PASSIVE_READ_DATA);
  Serial.print("Ozone concentration (raw): ");
  Serial.print(ozoneConcentration);
  Serial.println(" PPB");

  delay(1000); // Wait 1 second between readings
}

/**
 * @brief Adds a new ozone value to the rolling average buffer.
 * @param newData The latest ozone value to add.
 */
void addData(int16_t newData) {
  // If buffer is full, subtract the oldest value from the sum
  if (cont == COLLECT_NUMBER) {
    sum -= data[IndexCurrently];
  }

  // Add the new value to the buffer and update the sum
  data[IndexCurrently] = newData;
  sum += newData;

  // Advance index in circular buffer
  IndexCurrently = (IndexCurrently + 1) % COLLECT_NUMBER;

  // Increase the sample count up to the buffer limit
  if (cont < COLLECT_NUMBER) {
    cont++;
  }
}

/**
 * @brief Applies calibration formula to raw ozone sensor data.
 * @param OzoneDataReal The raw ozone value from the sensor.
 * @return Calibrated ozone value in PPB.
 */
uint16_t calculateData(uint16_t OzoneDataReal) {
  uint16_t DataResult = (0.0002 * OzoneDataReal * OzoneDataReal) + (0.7 * OzoneDataReal) + 100.4;
  return DataResult;
}

/**
 * @brief Calculates the average of collected ozone data.
 * @return The average ozone concentration in PPB.
 */
float averageData() {
  if (cont > 0) {
    return sum / cont;
  } else {
    return 0; // Return zero if no data collected yet
  }
}


```
## 🔄 API Reference

`bool begin(uint8_t addr = 0x70);`

Initializes the sensor with the specified I2C address. Returns true if successful, false otherwise.

`void setModes(uint8_t mode);`
Sets the measurement mode of the sensor.​

`MEASURE_MODE_AUTOMATIC: Active mode`
`MEASURE_MODE_PASSIVE: Passive mode​`

`int16_t readOzoneData(uint8_t collectNum = 20);`

Reads the ozone concentration. collectNum specifies the number of samples to average (range: 1–100). Returns the concentration in ppb.​

## 🥇Example
For a practical implementation, refer to the [example](https://github.com/SmarThinks/OzoneSensor/example/basic) sketch provided in the examples directory.


## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/SmarThinks/OzoneSensor/blob/main/LICENSE) file for details.

## 📞 Contact

- Project Maintainer: [SmarThinks Team](https://github.com/SmarThinks)
- Email: contact@smarthinkscorp.com
- Website: [https://smarthinkscorp.com](https://smarthinkscorp.com)

-----------------------------------------
Made with 🧠 by the SMARTHINKS CORP S.A.S
