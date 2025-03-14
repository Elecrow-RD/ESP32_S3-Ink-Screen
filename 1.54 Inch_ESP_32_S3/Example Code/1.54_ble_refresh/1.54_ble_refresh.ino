#include "BLEDevice.h"              // BLE driver library
#include "BLEServer.h"              // BLE server library
#include "BLEUtils.h"               // BLE utility library
#include "BLE2902.h"                // Library for adding descriptors to characteristics
#include "EPD_GUI.h"
#include "Pic.h"
#include <Arduino.h>

#include "FS.h"           // File system library
#include "SPIFFS.h"       // SPIFFS file system library for file reading and writing

// Image buffer for black and white image data.
uint8_t ImageBW[2888];
#define txt_size 1008
#define pre_size 728

// UUIDs for BLE service and characteristic.
#define SERVICE_UUID "fb1e4001-54ae-4a28-9f74-dfccb248601d"
#define CHARACTERISTIC_UUID "fb1e4002-54ae-4a28-9f74-dfccb248601d"

// BLE characteristic object.
BLECharacteristic *pCharacteristicRX;
std::vector<uint8_t> dataBuffer; // Buffer for accumulating received data.
size_t totalReceivedBytes = 0;   // Total number of received bytes.
bool dataReceived = false;       // Flag indicating if data has been received.

unsigned char price_formerly[pre_size]; // Stores uploaded image data.
unsigned char txt_formerly[txt_size]; // Stores uploaded image data.
// File object for uploaded files.
File fsUploadFile;
unsigned char test1[2888]; // Array for storing file data.
size_t data_size = 0; // Size of file data.

String filename; // Array for storing file name.

// Callback class for BLE characteristics.
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();

        if (value.length() > 0) {
            Serial.printf(".");

            // Assuming client sends a specific end marker when data transfer is complete.
            if (value == "OK") {
                dataReceived = true;
                return;
            }

            size_t len = value.length();
            if (len > 0) {
                // Append received data to buffer.
                dataBuffer.insert(dataBuffer.end(), value.begin(), value.end());
                totalReceivedBytes += len; // Update total received bytes.
            }
        }
    }
};

// Setup function to initialize hardware and BLE.
void setup() {
    Serial.begin(115200); // Initialize serial communication.
//    SPIFFS.format();
    if (SPIFFS.begin()) { // Start SPIFFS file system.
        Serial.println("SPIFFS Started.");
    } else {
        // If SPIFFS fails to start, try formatting the partition.
        if (SPIFFS.format()) {
            // Formatting successful, print message and restart device.
            Serial.println("SPIFFS partition formatted successfully");
            ESP.restart();
        } else {
            // Formatting failed, print message.
            Serial.println("SPIFFS partition format failed");
        }
        return;
    }

    // Initialize BLE.
    BLEDevice::init("ESP32_S3_BLE");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristicRX = pService->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_WRITE
    );

    // Set callback function for BLE characteristic.
    pCharacteristicRX->setCallbacks(new MyCallbacks());
    pCharacteristicRX->addDescriptor(new BLE2902());

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    // Initialize display.
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH); // Turn on display power.
    EPD_GPIOInit();
    Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);
    Paint_Clear(WHITE);
    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_FastUpdate();
    EPD_Clear_R26H();

    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_FastUpdate();
    EPD_Clear_R26H();

    UI_price(); // Display price interface.
}

// Main loop function.
void loop() {
    main_ui(); // Handle main interface update.
}

// Function to process BLE data and save to file.
void ble_pic() {
    // Check if data has been received.
    if (dataReceived) {
        // Ensure data buffer is not empty.
        if (!dataBuffer.empty()) {
            size_t bufferSize = dataBuffer.size();
            Serial.println(bufferSize);
            if (dataBuffer.size() == txt_size) // Check if data size is for txt.
                filename = "txt.bin";
            else
                filename = "pre.bin";
            if (!filename.startsWith("/")) filename = "/" + filename;
            fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
            fsUploadFile.write(dataBuffer.data(), dataBuffer.size());
            fsUploadFile.close();
            Serial.println("Save successful.");
            Serial.printf("Saved: ");
            Serial.println(filename);
            if (bufferSize == txt_size) {
                for (int i = 0; i < txt_size; i++) {
                    txt_formerly[i] = dataBuffer[i];
                }
                Serial.println("txt_formerly OK.");
            } else {
                for (int i = 0; i < pre_size; i++) {
                    price_formerly[i] = dataBuffer[i];
                }
                Serial.println("price_formerly OK.");
            }
            EPD_HW_RESET();

            EPD_ShowPicture(0, 0, 24, 152, gImage_top, BLACK); // Display picture on screen.

            if (bufferSize!= txt_size) {
                EPD_ShowPicture(96, 50, 52, 104, price_formerly, BLACK); // Display picture on screen.
//                EPD_ShowPicture(400, 60, 256, 184, price_formerly, WHITE); // Display picture on screen.
            } else {
                EPD_ShowPicture(32, 10, 56, 144, txt_formerly, BLACK); // Display picture on screen.
            }

            EPD_Display(ImageBW);
            EPD_FastUpdate();
            EPD_DeepSleep();

            // Clear data buffer after writing.
            dataBuffer.clear();
            totalReceivedBytes = 0;
        }

        // Reset data received flag after processing.
        dataReceived = false;
    }
}

// Function to clear display content.
void clear_all() {
    EPD_Init();
    EPD_Display_Clear();
    EPD_Update();
    EPD_DeepSleep();
}

// Main user interface processing function.
void main_ui() {
    ble_pic(); // Process BLE data.
}

// User interface function to display price information.
void UI_price() {
    EPD_HW_RESET();
    EPD_ShowPicture(0, 0, 24, 152, gImage_top, BLACK); // Display picture on screen.

    if (SPIFFS.exists("/txt.bin")) {
        // File exists, read its content.
        File file = SPIFFS.open("/txt.bin", FILE_READ);
        if (!file) {
            Serial.println("Unable to open file for reading.");
            return;
        }
        // Read file data into an array.
        size_t bytesRead = file.read(txt_formerly, txt_size);

        Serial.println("File content:");
        while (file.available()) {
            Serial.write(file.read());
        }
        file.close();

        EPD_ShowPicture(32, 10, 56, 144, txt_formerly, BLACK);
    }

    if (SPIFFS.exists("/pre.bin")) {
        // File exists, read its content.
        File file = SPIFFS.open("/pre.bin", FILE_READ);
        if (!file) {
            Serial.println("Unable to open file for reading.");
            return;
        }
        // Read file data into an array.
        size_t bytesRead = file.read(price_formerly, pre_size);

        Serial.println("File content:");
        while (file.available()) {
            Serial.write(file.read());
        }
        file.close();
        EPD_ShowPicture(96, 50, 52, 104, price_formerly, BLACK);
    }
    EPD_Display(ImageBW);
    EPD_FastUpdate();
    EPD_DeepSleep();
}
