#include <BLEDevice.h>         // Include BLE device library
#include <BLEServer.h>         // Include BLE server library
#include <BLEUtils.h>          // Include BLE utility library
#include <BLE2902.h>           // Include BLE descriptor library
#include <FS.h>
#include <SPIFFS.h>
#include <Arduino.h>           // Include Arduino core library
#include "EPD.h"               // Include EPD library (for e-paper screen)
#include "Ap_29demo.h"

// Externally declared image data
extern uint8_t ImageBW[ALLSCREEN_BYTES]; 
#define txt_size 1944       // Text data size
#define pre_size 480        // Preview data size

#define SERVICE_UUID "fb1e4001-54ae-4a28-9f74-dfccb248601d" // BLE service UUID
#define CHARACTERISTIC_UUID "fb1e4002-54ae-4a28-9f74-dfccb248601d" // BLE characteristic UUID

BLECharacteristic *pCharacteristicRX; // BLE characteristic object
std::vector<uint8_t> dataBuffer; // Data buffer for accumulating received data
size_t totalReceivedBytes = 0;   // Total number of bytes received
bool dataReceived = false;       // Data reception completion flag
String filename;                 // Filename variable
uint8_t test1[4736];            // Array to store test data
size_t data_size = 0;           // Data size
File fsUploadFile;              // File object for uploading files
unsigned char price_formerly[pre_size]; // Array to store uploaded image data
unsigned char txt_formerly[txt_size];   // Array to store uploaded text data
int flag_txt = 0;               // Text data flag
int flag_pre = 0;               // Preview data flag

// BLE characteristic callback class
class MyCallbacks : public BLECharacteristicCallbacks {
    // Write callback function
    void onWrite(BLECharacteristic *pCharacteristic) {
        String value = pCharacteristic->getValue(); // Get the written data

        if (value.length() > 0) {
            Serial.printf("."); // Output a dot to the serial port each time data is received
            if (value == "OK") {
                dataReceived = true; // Set the data reception completion flag
                return;
            }
            size_t len = value.length();
            if (len > 0) {
                // Append the received data to the buffer
                dataBuffer.insert(dataBuffer.end(), value.begin(), value.end());
                totalReceivedBytes += len; // Update the total number of bytes received
            }
        }
    }
};

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    if (SPIFFS.begin()) {              // Start the SPIFFS file system
        Serial.println("SPIFFS has started.");
    } else {
        // Try to format the SPIFFS file system
        if (SPIFFS.format()) {
            Serial.println("SPIFFS partition formatted successfully");
            ESP.restart();                 // Restart the ESP32
        } else {
            Serial.println("Failed to format SPIFFS partition");
        }
        return;
    }

    // Initialize BLE device
    BLEDevice::init("ESP32_S3_BLE"); // Set BLE device name
    BLEServer *pServer = BLEDevice::createServer(); // Create BLE server
    BLEService *pService = pServer->createService(SERVICE_UUID); // Create service

    pCharacteristicRX = pService->createCharacteristic(
                            CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_WRITE
                          ); // Create writable characteristic

    pCharacteristicRX->setCallbacks(new MyCallbacks()); // Set characteristic callbacks
    pCharacteristicRX->addDescriptor(new BLE2902()); // Add descriptor

    pService->start(); // Start the service

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); // Get BLE advertising object
    pAdvertising->addServiceUUID(SERVICE_UUID); // Add service UUID to advertising
    pAdvertising->start(); // Start advertising

    // Initialize e-paper screen
    pinMode(7, OUTPUT); // Set the screen power pin as output
    digitalWrite(7, HIGH); // Turn on the screen power
    EPD_Init(); // Initialize e-paper
    EPD_Clear(0, 0, 296, 128, WHITE); // Clear screen and set background color to white
    EPD_ALL_Fill(WHITE); // Fill the entire screen with white
    EPD_Update(); // Update screen display
    EPD_Clear_R26H(); // Clear part of the screen area
    UI_price(); // Update price display
}

// Main loop function
void loop() {
  // UI interface update data function
    main_ui();
}

// Process Bluetooth data and save it to a file
void ble_pic()
{
  if (dataReceived) {
    // Check if the data buffer is not empty
    if (!dataBuffer.empty()) {
      // Choose the filename based on the current size of the data buffer and save the data
      if (dataBuffer.size() == txt_size)
        filename = "txt.bin"; // Use txt.bin as the filename when the data size matches txt_size
      else
        filename = "pre.bin"; // Otherwise use pre.bin as the filename
      
      // Ensure the file path starts with "/"
      if (!filename.startsWith("/")) filename = "/" + filename;
      
      // Open the file for writing
      fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
      fsUploadFile.write(dataBuffer.data(), dataBuffer.size()); // Write the data to the file
      fsUploadFile.close(); // Close the file
      Serial.println("Saved successfully");
      Serial.printf("Saved: ");
      Serial.println(filename);

      // Print the data buffer size
      size_t bufferSize = dataBuffer.size();
      Serial.println(bufferSize);
      
      // Choose the corresponding array to save based on the size of the data buffer
      if (bufferSize == txt_size)
      {
        for (int i = 0; i < txt_size; i++) {
          txt_formerly[i] = dataBuffer[i]; // Copy the contents of the data buffer to txt_formerly
        }
        Serial.println("txt_formerly OK");
        flag_txt = 1; // Set the flag indicating that txt_formerly has been updated
      } 
      else
      {
        for (int i = 0; i < pre_size; i++) {
          price_formerly[i] = dataBuffer[i]; // Copy the contents of the data buffer to price_formerly
        }
        Serial.println("price_formerly OK");
        flag_pre = 1; // Set the flag indicating that price_formerly has been updated
      }
      
      // Display the price image
      EPD_HW_RESET(); // Reset the display
      if (bufferSize != pre_size)
      {
        if (flag_txt == 1)
        {
          // Display both txt_formerly and price_formerly images
          EPD_ShowPicture(10, 30, 216, 72, txt_formerly, BLACK); 
          EPD_ShowPicture(220, 50, 80, 48, price_formerly, BLACK);
        } 
        else
        {
          // Only display the price_formerly image
          EPD_ShowPicture(220, 50, 80, 48, price_formerly, BLACK);
        }
      } 
      else
      {
        if (flag_pre == 1)
        {
          // Display both price_formerly and txt_formerly images
          EPD_ShowPicture(220, 50, 80, 48, price_formerly, BLACK);
          EPD_ShowPicture(10, 30, 216, 72, txt_formerly, BLACK);
        } 
        else
        {
          // Only display the txt_formerly image
          EPD_ShowPicture(10, 30, 216, 72, txt_formerly, BLACK);
        }
      }

      EPD_DisplayImage(ImageBW); // Display black and white image
      EPD_FastUpdate(); // Quickly update the displayed content
      EPD_Sleep(); // Put the display into sleep mode

      // Clear the buffer after writing the data
      dataBuffer.clear(); 
      totalReceivedBytes = 0; // Reset the total number of received bytes
    }

    // Reset the flag after processing the data
    dataReceived = false;
  }
}

// Clear all content on the display
void clear_all()
{
  EPD_Init(); // Initialize the display
  EPD_Clear(0, 0, 296, 128, WHITE); // Clear the display area
  EPD_ALL_Fill(WHITE); // Fill the entire screen with white
  EPD_Update(); // Update the display content
  EPD_Clear_R26H(); // Clear specific content in the display area
}

// Main interface logic handling function
void main_ui()
{
  // Process Bluetooth data and save to file
  ble_pic();
}

// Display price interface
void UI_price()
{
  EPD_HW_RESET(); // Reset the display

  // Display top background image
  EPD_ShowPicture(0, 0, 296, 24, background_top, BLACK); // Display background image on the screen, background color is black

  EPD_DisplayImage(ImageBW); // Display black and white image
  EPD_FastUpdate(); // Quickly update the displayed content
  EPD_Sleep(); // Put the display into sleep mode

  // Check if the txt.bin file exists
  if (SPIFFS.exists("/txt.bin")) {
    // The file exists, open the file for reading
    File file = SPIFFS.open("/txt.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading"); // Failed to open file
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(txt_formerly, txt_size);

    Serial.println("File content:"); // Output file content to the serial port
    while (file.available()) {
      Serial.write(file.read()); // Read file content byte by byte and print
    }
    file.close(); // Close the file

    flag_txt = 1; // Set the flag indicating that txt_formerly has been updated

    EPD_HW_RESET(); // Reset the display

    // Display the txt_formerly image
    EPD_ShowPicture(10, 30, 216, 72, test1, BLACK);

    EPD_DisplayImage(ImageBW); // Display black and white image
    EPD_FastUpdate(); // Quickly update the displayed content
    EPD_Sleep(); // Put the display into sleep mode
  }

  // Check if the pre.bin file exists
  if (SPIFFS.exists("/pre.bin")) {
    // The file exists, open the file for reading
    File file = SPIFFS.open("/pre.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading"); // Failed to open file
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:"); // Output file content to the serial port
    while (file.available()) {
      Serial.write(file.read()); // Read file content byte by byte and print
    }
    file.close(); // Close the file
    flag_pre = 1; // Set the flag indicating that price_formerly has been updated

    EPD_HW_RESET(); // Reset the display

    // Display the price_formerly image
    EPD_ShowPicture(220, 50, 80, 48, price_formerly, BLACK);

    EPD_DisplayImage(ImageBW); // Display black and white image
    EPD_FastUpdate(); // Quickly update the displayed content
    EPD_Sleep(); // Put the display into sleep mode
  }
}