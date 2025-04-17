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
#include <Wire.h>
#include "OzoneSensor.h"

OzoneSensor ozone;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (ozone.begin(0x70)) {
    Serial.println("Ozone sensor initialized successfully.");
  } else {
    Serial.println("Failed to initialize ozone sensor.");
    while (1);
  }

  ozone.setModes(MEASURE_MODE_AUTOMATIC);
}

void loop() {
  int16_t ozone_ppb = ozone.readOzoneData(20);
  Serial.print("Ozone Concentration: ");
  Serial.print(ozone_ppb);
  Serial.println(" ppb");
  delay(1000);
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
