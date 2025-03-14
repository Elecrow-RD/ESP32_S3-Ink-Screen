#include "BLEDevice.h"              // BLE driver library
#include "BLEServer.h"              // BLE bluetooth server library
#include "BLEUtils.h"               // BLE utility library
#include "BLE2902.h"                // Characteristic add descriptor library
#include "EPD.h"
#include "Pic.h"
#include <Arduino.h>

#include "FS.h"           // File system library
#include "SPIFFS.h"       // SPIFFS file system library for file read and write.

// Image buffer to store black and white image data
extern uint8_t ImageBW[ALLSCREEN_BYTES];
unsigned char test1[ALLSCREEN_BYTES]; // Array for storing file data
#define txt_size 1728
#define pre_size 528

// UUIDs for BLE service and characteristic
#define SERVICE_UUID "fb1e4001-54ae-4a28-9f74-dfccb248601d"
#define CHARACTERISTIC_UUID "fb1e4002-54ae-4a28-9f74-dfccb248601d"

// BLE characteristic object
BLECharacteristic *pCharacteristicRX;
std::vector<uint8_t> dataBuffer; // Buffer for accumulating received data
size_t totalReceivedBytes = 0;   // Total number of received bytes
bool dataReceived = false;       // Flag indicating whether data has been received.

unsigned char price_formerly[pre_size]; // Store uploaded image data
unsigned char txt_formerly[txt_size]; // Store uploaded image data
// File object for storing uploaded file
File fsUploadFile;

size_t data_size = 0; // Size of file data

String filename; // Array for storing file name

// BLE characteristic callback class
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      // Get the value received via BLE.
      String value = pCharacteristic->getValue();

      // If there is received data.
      if (value.length() > 0) {
        // Print a dot for debugging purposes.
        Serial.printf(".");

        // Assume the client sends a specific end marker ("OK") when data transfer is complete.
        if (value == "OK") {
          dataReceived = true;
          return;
        }

        // Get the length of the received data.
        size_t len = value.length();
        if (len > 0) {
          // Append the received data to the buffer.
          dataBuffer.insert(dataBuffer.end(), value.begin(), value.end());
          // Update the total number of received bytes.
          totalReceivedBytes += len;
        }
      }
    }
};

// Setup function to initialize hardware and BLE.
void setup() {
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200.

  // Start the SPIFFS file system. If it fails to start, try formatting it.
  if (SPIFFS.begin()) {
    Serial.println("SPIFFS Started.");
  } else {
    if (SPIFFS.format()) {
      Serial.println("SPIFFS partition formatted successfully");
      ESP.restart();
    } else {
      Serial.println("SPIFFS partition format failed");
    }
    return;
  }

  // Initialize the BLE device.
  BLEDevice::init("ESP32_S3_BLE");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE characteristic for receiving data.
  pCharacteristicRX = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_WRITE
                      );

  // Set the callback function for the BLE characteristic.
  pCharacteristicRX->setCallbacks(new MyCallbacks());
  pCharacteristicRX->addDescriptor(new BLE2902());

  // Start the BLE service.
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  // Initialize the display.
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH); // Turn on the display power.

  // Display the price interface.
  UI_price();
}

// Process BLE data and save it to a file.
void ble_pic()
{
  // Check if data has been received.
  if (dataReceived) {
    // Ensure the data buffer is not empty.
    if (!dataBuffer.empty()) {
      size_t bufferSize = dataBuffer.size();
      Serial.println(bufferSize);

      // Determine the filename based on the size of the received data.
      if (dataBuffer.size() == txt_size) {
        filename = "txt.bin";
      } else {
        filename = "pre.bin";
      }

      // Ensure the filename starts with a slash.
      if (!filename.startsWith("/")) {
        filename = "/" + filename;
      }

      // Open the file for writing.
      fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
      if (!fsUploadFile) {
        Serial.println("Failed to open file for writing.");
        return;
      }

      // Write the received data to the file.
      fsUploadFile.write(dataBuffer.data(), dataBuffer.size());
      fsUploadFile.close();

      Serial.println("Saved successfully.");
      Serial.printf("Saved:");
      Serial.println(filename);

      // Store the received data in the appropriate array.
      if (bufferSize == txt_size) {
        for (int i = 0; i < txt_size; i++) {
          txt_formerly[i] = dataBuffer[i];
        }
        Serial.println("txt_formerly OK");
      } else {
        for (int i = 0; i < pre_size; i++) {
          price_formerly[i] = dataBuffer[i];
        }
        Serial.println(" price_formerlyOK");
      }

      // Display the price interface.
      UI_price();
    }

    // Clear the buffer after writing.
    dataBuffer.clear();
    totalReceivedBytes = 0;
  }
}

void clear_all()
{
  // Initialize the display.
  EPD_Init();
  // Fill the display with white.
  EPD_ALL_Fill(WHITE);
  // Update the display.
  EPD_Update();
  // Clear the display.
  EPD_Clear_R26H();

  // Put the display to sleep.
  EPD_Sleep();
}

// Main user interface processing function.
void main_ui()
{
  // Process BLE data.
  ble_pic();
}

// User interface function: Display price information.
void UI_price()
{
  // Initialize the display.
  EPD_Init();
  // Fill the display with white.
  EPD_ALL_Fill(WHITE);
  // Update the display.
  EPD_Update();
  // Clear the display.
  EPD_Clear_R26H();

  // Display an image at a specific location.
  EPD_ShowPicture(0, 0, 248, 24, gImage_top, BLACK);

  // If the text file exists.
  if (SPIFFS.exists("/txt.bin")) {
    // Open the file for reading.
    File file = SPIFFS.open("/txt.bin", FILE_READ);
    if (!file) {
      Serial.println("Unable to open file for reading.");
      return;
    }

    // Read data from the file into the array.
    size_t bytesRead = file.read(txt_formerly, txt_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();

    // Display an image using the data from the text file.
    EPD_ShowPicture(8, 36, 192, 72, txt_formerly, BLACK);
  }

  // If the price file exists.
  if (SPIFFS.exists("/pre.bin")) {
    // Open the file for reading.
    File file = SPIFFS.open("/pre.bin", FILE_READ);
    if (!file) {
      Serial.println("Unable to open file for reading.");
      return;
    }

    // Read data from the file into the array.
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();

    // Display an image using the data from the price file.
    EPD_ShowPicture(159, 56, 88, 48, price_formerly, BLACK);
  }

  // Display the image buffer on the display.
  EPD_DisplayImage(ImageBW);
  // Update a portion of the display.
  EPD_PartUpdate();
  // Put the display to sleep.
  EPD_Sleep();
}

// Main loop function.
void loop() {
  // Process main interface update.
  main_ui();
}
