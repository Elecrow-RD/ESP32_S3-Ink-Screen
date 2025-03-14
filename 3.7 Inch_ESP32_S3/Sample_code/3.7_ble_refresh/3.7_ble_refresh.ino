#include <BLEDevice.h>          // Include BLE device library
#include <BLEServer.h>          // Include BLE server library
#include <BLEUtils.h>           // Include BLE utility library
#include <BLE2902.h>            // Include BLE descriptor library
#include <FS.h>                 // Include file system library
#include <SPIFFS.h>             // Include SPIFFS file system library
#include <Arduino.h>            // Include Arduino library
#include "EPD.h"                // Include E-Paper driver library
#include "EPD_GUI.h"            // Include E-Paper GUI library
#include "Ap_29demo.h"          // Include custom application demo library

uint8_t ImageBW[12480];         // Define an array to store image data
#define txt_size 3536           // Define text data size
#define pre_size 2208           // Define preset data size

#define SERVICE_UUID "fb1e4001-54ae-4a28-9f74-dfccb248601d" // BLE service UUID
#define CHARACTERISTIC_UUID "fb1e4002-54ae-4a28-9f74-dfccb248601d" // BLE characteristic UUID

BLECharacteristic *pCharacteristicRX;  // BLE characteristic object
std::vector<uint8_t> dataBuffer;        // Data buffer to accumulate received data
size_t totalReceivedBytes = 0;          // Record the total number of bytes received
bool dataReceived = false;              // Data reception completion flag
// Object to store uploaded files
File fsUploadFile;
unsigned char price_formerly[pre_size]; // Array to store uploaded image data
unsigned char txt_formerly[txt_size]; // Array to store uploaded text data
String filename; // Array to store the filename

// BLE characteristic callback class
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue(); // Get the written data

      if (value.length() > 0) { // If the length of received data is greater than 0
        Serial.printf("."); // Print a dot in the serial monitor to indicate data reception
        if (value == "OK") { // If the received data is "OK"
          dataReceived = true; // Set the data reception flag to true
          return; // Exit the function
        }
        size_t len = value.length(); // Get the data length
        if (len > 0) { // If the data length is greater than 0
          // Append the received data to the buffer
          dataBuffer.insert(dataBuffer.end(), value.begin(), value.end());
          totalReceivedBytes += len; // Update the total number of bytes received
        }
      }
    }
};

void setup() {
  Serial.begin(115200); // Initialize serial communication, set baud rate to 115200

  // Start the SPIFFS file system
  if (SPIFFS.begin()) {
    Serial.println("SPIFFS Started."); // If SPIFFS starts successfully, print the message
  } else {
    // Format the SPIFFS partition
    if (SPIFFS.format()) {
      Serial.println("SPIFFS partition formatted successfully"); // If formatting is successful, print the message
      ESP.restart(); // Restart the device after successful formatting
    } else {
      Serial.println("SPIFFS partition format failed"); // If formatting fails, print the message
    }
    return; // Exit the function
  }

  // Initialize the BLE device
  BLEDevice::init("ESP32_S3_BLE"); // Initialize the BLE device, set the device name to "ESP32_S3_BLE"
  BLEServer *pServer = BLEDevice::createServer(); // Create a BLE server
  BLEService *pService = pServer->createService(SERVICE_UUID); // Create a BLE service

  pCharacteristicRX = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_WRITE // Create a writable characteristic
                      );

  pCharacteristicRX->setCallbacks(new MyCallbacks()); // Set the characteristic callback function
  pCharacteristicRX->addDescriptor(new BLE2902()); // Add a BLE2902 descriptor

  pService->start(); // Start the service
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); // Get the BLE advertising object
  pAdvertising->addServiceUUID(SERVICE_UUID); // Add the service UUID to the advertisement
  pAdvertising->start(); // Start the advertisement

  // Initialize the E-Paper display
  pinMode(7, OUTPUT); // Set pin 7 to output
  digitalWrite(7, HIGH); // Set pin 7 to high level, power on
  EPD_GPIOInit(); // Initialize the GPIO pins of the E-Paper
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 180, WHITE); // Create a new image canvas
  Paint_Clear(WHITE); // Clear the canvas, fill with white

  EPD_FastInit(); // Fast initialize the E-Paper display
  EPD_Display_Clear(); // Clear the E-Paper display
  EPD_Update(); // Update the E-Paper display
  UI_price(); // Update the price on the interface
}

void loop() {
  // If the dataReceived flag is true, process the data
  main_ui(); // Call the main UI function
}

// Process the data received via BLE
void ble_pic()
{
  // Check if data has been received
  if (dataReceived) {
    // If the data buffer is not empty
    if (!dataBuffer.empty()) {
      size_t bufferSize = dataBuffer.size(); // Get the size of the data buffer
      Serial.println(bufferSize); // Print the size of the data buffer to the serial monitor

      // Determine the filename based on the size of the data buffer
      if (dataBuffer.size() == txt_size) // If the data size equals txt_size
        filename = "txt.bin"; // Set the filename to txt.bin
      else
        filename = "pre.bin"; // Otherwise, set the filename to pre.bin

      // Ensure the filename starts with a slash
      if (!filename.startsWith("/")) filename = "/" + filename;

      // Open the file for writing
      fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
      fsUploadFile.write(dataBuffer.data(), dataBuffer.size()); // Write the data to the file
      fsUploadFile.close(); // Close the file
      Serial.println("Save successful"); // Print the success message
      Serial.printf("Saved: "); 
      Serial.println(filename); // Print the saved filename
      Serial.printf("Size: "); 
      Serial.println(bufferSize); // Print the size of the saved file
      // Copy the data to different arrays based on the data size
      if (bufferSize == txt_size)
      {
        for (int i = 0; i < txt_size; i++) {
          txt_formerly[i] = dataBuffer[i]; // Copy the data to the txt_formerly array
        }
        Serial.println("txt_formerly OK"); // Print the success message for processing the txt_formerly array
      } else
      {
        for (int i = 0; i < pre_size; i++) {
          price_formerly[i] = dataBuffer[i]; // Copy the data to the price_formerly array
        }
        Serial.println("price_formerly OK"); // Print the success message for processing the price_formerly array
      }

      EPD_FastInit(); // Initialize the partial display mode of the E-Paper screen
      EPD_ShowPicture(0, 0, EPD_H, 40, background_top, WHITE); // Show the background image

      // Display different images on the screen based on the data size
      if (bufferSize != txt_size)
      {
        EPD_ShowPicture(30, 180, 368, 48, price_formerly, WHITE); // Show the price image
      } else
      {
        EPD_ShowPicture(30, 60, 272, 104, txt_formerly, WHITE); // Show the text image
      }

      EPD_Display(ImageBW); // Update the screen display content
      EPD_Update(); // Refresh the screen display content
      EPD_DeepSleep(); // Enter deep sleep mode to save power

      // Clear the buffer after writing the data
      dataBuffer.clear();
      totalReceivedBytes = 0; // Reset the total number of bytes received
    }

    // Reset the flag after processing the data
    dataReceived = false;
  }
}

// Clear the display canvas and refresh the screen
void clear_all()
{
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // Create a new canvas, color white
  Paint_Clear(WHITE); // Clear the canvas
  EPD_FastInit(); // Initialize the fast mode of the E-Paper screen
  EPD_Display_Clear(); // Clear the screen display content
  EPD_Update(); // Update the screen display
}

// Main UI functionality handling
void main_ui()
{
  // Process the data received via BLE
  ble_pic();
}

// Display the price interface
void UI_price()
{
  // Predefined: txt size is 3536, pre size is 2208
  EPD_FastInit(); // Initialize the fast mode of the E-Paper screen
  EPD_ShowPicture(0, 0, EPD_H, 40, background_top, WHITE); // Show the background image
  EPD_Display(ImageBW); // Update the screen display content
  EPD_Update(); // Refresh the screen display content
  EPD_DeepSleep(); // Enter deep sleep mode to save power

  // If the txt.bin file exists, read and display it
  if (SPIFFS.exists("/txt.bin")) {
    File file = SPIFFS.open("/txt.bin", FILE_READ); // Open the txt.bin file for reading
    if (!file) {
      Serial.println("Failed to open file for reading"); // If the file cannot be opened, print the error message
      return;
    }
    // Read the data from the file into the array
    size_t bytesRead = file.read(txt_formerly, txt_size);
    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print the file content to the serial monitor
    }
    file.close(); // Close the file

    EPD_FastInit(); // Initialize the fast mode of the E-Paper screen
    EPD_ShowPicture(30, 60, 272, 104, txt_formerly, WHITE); // Show the text image on the screen
    EPD_Display(ImageBW); // Update the screen display content
    EPD_Update(); // Refresh the screen display content
    EPD_DeepSleep(); // Enter deep sleep mode to save power
  }

  // If the pre.bin file exists, read and display it
  if (SPIFFS.exists("/pre.bin")) {
    File file = SPIFFS.open("/pre.bin", FILE_READ); // Open the pre.bin file for reading
    if (!file) {
      Serial.println("Failed to open file for reading"); // If the file cannot be opened, print the error message
      return;
    }
    // Read the data from the file into the array
    size_t bytesRead = file.read(price_formerly, pre_size);
    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print the file content to the serial monitor
    }
    file.close(); // Close the file

    EPD_FastInit(); // Initialize the fast mode of the E-Paper screen
    EPD_ShowPicture(30, 180, 368, 48, price_formerly, WHITE); // Show the price image on the screen
    EPD_Display(ImageBW); // Update the screen display content
    EPD_Update(); // Refresh the screen display content
    EPD_DeepSleep(); // Enter deep sleep mode to save power
  }
}