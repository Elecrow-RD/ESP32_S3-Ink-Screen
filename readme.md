![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32_S3-brightgreen.svg)
![Framework](https://img.shields.io/badge/framework-PlatformIO-blue.svg)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Getting Started with VSCode and PlatformIO](#getting-started-with-vscode-and-platformio)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Where to Buy](#where-to-buy)

## Introduction

Welcome to the **ESP32_S3-Ink-Screen** repository! This project demonstrates how to interface an ESP32-S3 microcontroller with an e-ink display. It provides example code and configurations to help you get started with developing low-power, high-visibility applications using e-ink technology.

## Features

- **ESP32-S3 Support**: Optimized for the ESP32-S3 microcontroller.
- **E-Ink Display Integration**: Seamless connection with popular e-ink screens.
- **Low Power Consumption**: Ideal for battery-powered applications.
- **PlatformIO Compatible**: Easy setup and development using PlatformIO in VSCode.
- **Modular Codebase**: Easily extendable and customizable for various projects.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- **Hardware**:
  - ESP32-S3 development board
  - Compatible e-ink display
  - USB cable for programming
- **Software**:
  - [Visual Studio Code](https://code.visualstudio.com/) installed on your computer.
  - [PlatformIO](https://platformio.org/) extension installed in VSCode.
  - Git installed on your machine.

## Installation

Follow these steps to set up the project on your local machine:

1. **Clone the Repository**

   Open your terminal or command prompt and run:

   ```bash
   git clone https://github.com/robouden/ESP32_S3-Ink-Screen.git


2. **Navigate to the Project Directory**

   ```bash
   cd ESP32_S3-Ink-Screen
   ```

3. **Open the Project in VSCode**

   Launch Visual Studio Code and open the cloned repository folder:

   - Click on `File` > `Open Folder...`
   - Select the `ESP32_S3-Ink-Screen` folder.

4. **Install PlatformIO Extension**

   If you haven't installed PlatformIO yet:CrowPanel ESP32 2.13” E-paper HMI Display 

   - Go to the Extensions view by clicking on the Extensions icon in the Activity Bar on the side of VSCode or press `Ctrl+Shift+X`.
   - Search for `PlatformIO IDE` and click `Install`.

5. **Build and Upload the Firmware**

>>>>>>> c501214 (Modified screen for business card)
   - Open the PlatformIO sidebar by clicking on the alien icon in the Activity Bar.
   - Click on `Build` (checkmark icon) to compile the project.
   - Once the build is successful, connect your ESP32-S3 board via USB.
   - Click on `Upload` (right arrow icon) to flash the firmware to your device.

## Getting Started with VSCode and PlatformIO

### Setting Up PlatformIO

1. **Launch PlatformIO**

   After installing the PlatformIO extension, you can access it from the PlatformIO icon in the VSCode sidebar.

2. **Configure the Environment**

   Ensure that the `platformio.ini` file is correctly set up for your ESP32-S3 board. A typical configuration might look like:

   ```ini
   [env:esp32-s3]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   monitor_speed = 115200
   ```

   Adjust the `board` parameter according to your specific ESP32-S3 model.

3. **Install Required Libraries**

   The project may depend on specific libraries for the e-ink display. PlatformIO will automatically install the libraries listed in `platformio.ini`. If additional libraries are needed, add them under the `lib_deps` section.

   ```ini
   lib_deps =
     GxEPD
     Adafruit GFX Library
   ```

4. **Configure Serial Port**

   PlatformIO usually detects the correct serial port automatically. If not, specify it in `platformio.ini`:

   ```ini
   upload_port = /dev/ttyUSB0
   ```

   Replace `/dev/ttyUSB0` with the appropriate port for your system.

### Debugging

PlatformIO provides integrated debugging tools. To start debugging:

1. Set breakpoints in your code by clicking next to the line numbers.
2. Click on the `Start Debugging` button in the PlatformIO sidebar.
3. Use the debugging controls to step through your code.

## Usage

Once you have successfully uploaded the firmware to your ESP32-S3 board, the e-ink display should initialize and display the default content. You can modify the `src/main.cpp` file to customize the display output according to your project's requirements.

### Example: Displaying Text

```cpp
#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>
#include <Adafruit_GFX.h>

// Initialize the display
GxIO_Class io(SPI, /* CS= */ 5, /* DC= */ 17, /* RST= */ 16);
GxEPD_Class display(io, /* RST= */ 16, /* BUSY= */ 4);

void setup() {
  display.init();
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(10, 30);
  display.print("Hello, ESP32-S3!");
  display.display();
}

void loop() {
  // Your code here
}
```

Upload the modified code to see the changes on your e-ink display.

## Project Structure

```
ESP32_S3-Ink-Screen/
├── include/            # Header files
├── lib/                # Libraries
├── src/                # Source files
│   └── main.cpp        # Main application code
├── test/               # Test files
├── platformio.ini      # PlatformIO configuration file
├── README.md           # Project documentation
└── LICENSE             # License information
```

## Contributing

Contributions are welcome! Please follow these steps:

1. **Fork the Repository**

   Click the `Fork` button at the top-right corner of the repository page.

2. **Create a New Branch**

   ```bash
   git checkout -b feature/YourFeatureName
   ```

3. **Commit Your Changes**

   ```bash
   git commit -m "Add your message here"
   ```

4. **Push to the Branch**

   ```bash
   git push origin feature/YourFeatureName
   ```

5. **Open a Pull Request**

   Go to the repository on GitHub and click `New Pull Request`.

## License

This project is licensed under the MIT License.

## Contact

If you have any questions or suggestions, feel free to reach out:

- **Author**: Rob Oudendijk
- **Email**: [rob@yr-design.biz](mailto:rob@yr-design.biz)
- **GitHub**: [robouden](https://github.com/robouden)
  
![IMG_20241113_223312](https://github.com/user-attachments/assets/0a381edf-e7c7-4d3d-8596-d396a0e435ea)

## Where to Buy

You can purchase the [CrowPanel ESP32 2.13" E-paper HMI Display](https://www.elecrow.com/crowpanel-esp32-2-13-e-paper-hmi-display-with-122-250-resolution-black-white-color-driven-by-spi-interface.html?srsltid=AfmBOorFAVknIuU0zAzCok_W3I7MrcxQjEt1l9C7vXLtkImsX2zo0K8A) from Elecrow using the link provided above. This display is essential for setting up the project and ensuring compatibility with the ESP32-S3 microcontroller.


