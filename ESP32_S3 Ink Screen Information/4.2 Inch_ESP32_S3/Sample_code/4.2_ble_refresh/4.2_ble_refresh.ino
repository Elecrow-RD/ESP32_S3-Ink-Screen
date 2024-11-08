#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "EPD.h"
#include "EPD_GUI.h"
#include "Ap_29demo.h"
#include "FS.h"           // File system library
#include "SPIFFS.h"       // SPIFFS file system library for file read/write

// Image data buffer to store received image data
uint8_t ImageBW[15000];
#define txt_size 3808      // Text data size
#define pre_size 4576      // Image data size

// Object to store the uploaded file
File fsUploadFile;

// BLE service and characteristic UUID definitions
#define SERVICE_UUID "fb1e4001-54ae-4a28-9f74-dfccb248601d"          // Custom service UUID
#define CHARACTERISTIC_UUID "fb1e4002-54ae-4a28-9f74-dfccb248601d" // Custom characteristic UUID

// Pointer to the BLE characteristic
BLECharacteristic *pCharacteristicRX;

// Data buffer to accumulate received data
std::vector<uint8_t> dataBuffer;
// Total number of bytes received
size_t totalReceivedBytes = 0;
// Flag to indicate if data reception is complete
bool dataReceived = false;
String filename; // Variable to store the filename

int flag_txt = 0; // Flag to indicate the status of text data processing
int flag_pre = 0; // Flag to indicate the status of image data processing

// Buffer for testing
unsigned char price_formerly[pre_size]; // Store the uploaded image data
unsigned char txt_formerly[txt_size];   // Store the uploaded text data

// BLE characteristic callback class
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String value = pCharacteristic->getValue(); // Get the characteristic value

        if (value.length() > 0) {
            Serial.printf("."); // Output a dot for each data block received

            // Check if the complete data has been received
            if (value == "OK") {
                dataReceived = true; // Set the data received flag
                return;
            }
            // Append the received data to the buffer
            size_t len = value.length(); // Get the data length
            if (len > 0) {
                dataBuffer.insert(dataBuffer.end(), value.begin(), value.end()); // Add data to the buffer
                totalReceivedBytes += len; // Update the total number of bytes received
            }
        }
    }
};

// Initialization setup
void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate

    // Start the SPIFFS file system
    if (SPIFFS.begin()) {
        Serial.println("SPIFFS Started."); // SPIFFS started successfully
    } else {
        // If SPIFFS fails to start, try formatting the SPIFFS partition
        if (SPIFFS.format()) {
            Serial.println("SPIFFS partition formatted successfully"); // SPIFFS partition formatted successfully
            ESP.restart(); // Restart the device after formatting
        } else {
            Serial.println("SPIFFS partition format failed"); // SPIFFS partition format failed
        }
        return;
    }

    // Initialize BLE
    BLEDevice::init("ESP32_S3_BLE"); // Initialize the BLE device
    BLEServer *pServer = BLEDevice::createServer(); // Create a BLE server
    BLEService *pService = pServer->createService(SERVICE_UUID); // Create a BLE service

    pCharacteristicRX = pService->createCharacteristic(
                            CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_WRITE // Create a characteristic with write property
                        );

    // Set the BLE characteristic callback function
    pCharacteristicRX->setCallbacks(new MyCallbacks());
    pCharacteristicRX->addDescriptor(new BLE2902()); // Add a descriptor

    pService->start(); // Start the BLE service
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); // Get the BLE advertising
    pAdvertising->addServiceUUID(SERVICE_UUID); // Add the service UUID to the advertising
    pAdvertising->start(); // Start the BLE advertising

    // Initialize the screen
    pinMode(7, OUTPUT); // Set pin 7 to output mode
    digitalWrite(7, HIGH); // Set pin 7 to high level
    EPD_GPIOInit(); // Initialize the EPD (electronic paper display) interface
    EPD_Clear(); // Clear the EPD screen
    Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer
    EPD_Full(WHITE); // Clear the canvas with white
    EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW); // Display a blank image

    EPD_Init_Fast(Fast_Seconds_1_5s); // Initialize the EPD display speed settings

    UI_price(); // Update the price information in the UI
}

void loop() {
  // Handle the main UI
  main_ui();
}

// Function: Process Bluetooth data
void ble_pic()
{
  // Check if data has been received
  if (dataReceived) {
    // If the data buffer is not empty
    if (!dataBuffer.empty()) {
      // Get the size of the data buffer
      size_t bufferSize = dataBuffer.size();
      Serial.println(bufferSize);

      // Determine the filename based on the size of the data buffer
      if (dataBuffer.size() == txt_size) // If the data size equals txt_size
        filename = "txt.bin"; // Filename is txt.bin
      else
        filename = "pre.bin"; // Otherwise, filename is pre.bin

      // Ensure the filename starts with "/"
      if (!filename.startsWith("/")) filename = "/" + filename;

      // Open the file for writing
      fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
      fsUploadFile.write(dataBuffer.data(), dataBuffer.size()); // Write the data
      fsUploadFile.close(); // Close the file

      Serial.println("Save successful");
      Serial.printf("Saved: ");
      Serial.println(filename);

      // Update flag_txt or flag_pre based on the size of the data buffer
      if (bufferSize == txt_size) {
        for (int i = 0; i < txt_size; i++) {
          txt_formerly[i] = dataBuffer[i]; // Copy the data to txt_formerly
        }
        Serial.println("txt_formerly OK");
        flag_txt = 1; // Set the flag_txt flag
      } else {
        for (int i = 0; i < pre_size; i++) {
          price_formerly[i] = dataBuffer[i]; // Copy the data to price_formerly
        }
        Serial.println("price_formerly OK");
        flag_pre = 1; // Set the flag_pre flag
      }

      // Clear all display content
      clear_all(); 

      // Display the background image on the screen
      EPD_ShowPicture(0, 0, EPD_W, 40, wifi_background_top, WHITE);

      // Determine what to display based on the size of the data buffer and flags
      if (bufferSize != txt_size) {
        if (flag_txt == 1) {
          EPD_ShowPicture(20, 60, 272, 112, txt_formerly, WHITE); // Display txt_formerly
          EPD_ShowPicture(20, 190, 352, 104, price_formerly, WHITE); // Display price_formerly
        } else {
          EPD_ShowPicture(20, 190, 352, 104, price_formerly, WHITE); // Display price_formerly
        }
      } else {
        // If the data size equals txt_size, determine what to display based on flag_pre
        if (flag_pre == 1) {
          EPD_ShowPicture(20, 190, 352, 104, price_formerly, WHITE); // Display price_formerly
          EPD_ShowPicture(20, 60, 272, 112, txt_formerly, WHITE); // Display txt_formerly
        } else {
          EPD_ShowPicture(0, 80, 152, 160, txt_formerly, WHITE); // Display txt_formerly
        }
      }

      // Quickly display the image stored in the Image_BW array
      EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);

      // Enter sleep mode
      EPD_Sleep();
      
      // Clear the data buffer after writing
      dataBuffer.clear();
      // Reset the total number of bytes received
      totalReceivedBytes = 0;

      // Reset the data received flag after processing the data
      dataReceived = false;
    }
  }
}

// Function: Clear the display
void clear_all()
{
  // Clear the EPD display
  EPD_Clear();
  // Create a new canvas image
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);
  // Fill the canvas with white
  EPD_Full(WHITE);
  // Update all areas on the display
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);
}

// Function: Main user interface handling
void main_ui()
{
  // Process Bluetooth data
  ble_pic();
}

// Function: Update the price interface
void UI_price()
{
  // Clear all display content
  clear_all(); 
  // Display the top background image
  EPD_ShowPicture(0, 0, EPD_W, 40, background_top, WHITE);

  // If the txt.bin file exists, read its content
  if (SPIFFS.exists("/txt.bin")) {
    File file = SPIFFS.open("/txt.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading");
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(txt_formerly, txt_size);
    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print the file content
    }
    file.close();

    // Display txt_formerly on the screen
    EPD_ShowPicture(20, 60, 272, 112, txt_formerly, WHITE); 
    flag_txt = 1; // Set the flag_txt flag
  }

  // If the pre.bin file exists, read its content
  if (SPIFFS.exists("/pre.bin")) {
    File file = SPIFFS.open("/pre.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading");
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(price_formerly, pre_size);
    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print the file content
    }
    file.close();

    // Display price_formerly on the screen
    EPD_ShowPicture(20, 190, 352, 104, price_formerly, WHITE);
    flag_pre = 1; // Set the flag_pre flag
  }
  
  // Quickly display the image stored in the Image_BW array
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);

  // Enter sleep mode
  EPD_Sleep();
}