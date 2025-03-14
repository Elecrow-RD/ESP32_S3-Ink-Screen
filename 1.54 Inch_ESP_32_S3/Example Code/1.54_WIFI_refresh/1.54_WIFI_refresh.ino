#include <Arduino.h>           // Include Arduino core library file
#include "EPD_GUI.h"              // Include library file for electronic paper screen
#include "Pic.h"        // Include custom function library
#include "FS.h"               // File system library for file operations
#include "SPIFFS.h"           // SPIFFS file system library for file reading and writing
#include <WiFi.h>             // WiFi library for creating and managing WiFi connections
#include <Ticker.h>           // Ticker library for timing operations
#include <WebServer.h>        // WebServer library for creating HTTP server

// Define an array to store image data with size 2888 bytes.
uint8_t ImageBW[2888];
#define txt_size 912
#define pre_size 1520

// Define pin numbers for control buttons.
#define HOME_KEY 2
#define EXIT_KEY 1
#define PRV_KEY 6
#define NEXT_KEY 4
#define OK_KEY 5

int NUM = 0; // Current page number.

// Function to clear all content on the display.
void clear_all()
{
    EPD_Init();
    EPD_Display_Clear();
    EPD_Update();
    EPD_DeepSleep();
}

// Create a WebServer instance listening on port 80.
WebServer server(80);
const char *AP_SSID = "ESP32_Config"; // WiFi hotspot name.

// HTML form for uploading files.
String HTML_UPLOAD = "<form method=\"post\" action=\"ok\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"msg\"><input class=\"btn\" type=\"submit\" name=\"submit\"value=\"Submit\"></form>";

// Function to handle requests to the root path.
void handle_root()
{
    server.send(200, "text/html", HTML_UPLOAD); // Send HTML upload page.
}

// HTML page after successful upload.
String HTML_OK = "<!DOCTYPE html>\
<html>\
<body>\
<h1>OK</h1>\
</body>\
</html>";

// File object for uploaded files.
File fsUploadFile;
unsigned char test1[2888];
size_t data_size = 0;
String filename;
int i = 0;
unsigned char price_formerly[pre_size];
unsigned char txt_formerly[txt_size];

int flag_txt = 0; // Flag to indicate if a txt file has been uploaded.
int flag_pre = 0; // Flag to indicate if a preview file has been uploaded.

// Function to handle file upload requests.
void okPage()
{
    server.send(200, "text/html", HTML_OK); // Send success page.
    HTTPUpload &upload = server.upload(); // Get the uploaded file object.

    // Note: The initial size of upload.buf is only 1436 bytes. Adjust it to support large file uploads.
    // Modify the HTTP_UPLOAD_BUFLEN definition in WebServer.h to increase the initial size to 14360 bytes.
    if (upload.status == UPLOAD_FILE_END) // If file upload is complete.
    {
        Serial.println("draw file");
        Serial.println(upload.filename); // Print the uploaded file name.
        Serial.println(upload.totalSize); // Print the total file size.

        // Determine file type based on file size.
        if (upload.totalSize == txt_size) // If file size is 1008 bytes, it's a txt file.
            filename = "txt.bin";
        else
            filename = "pre.bin"; // Otherwise, it's a preview file.

        // Save the received file.
        if (!filename.startsWith("/")) filename = "/" + filename;
        fsUploadFile = SPIFFS.open(filename, FILE_WRITE); // Open file in write mode.
        fsUploadFile.write(upload.buf, upload.totalSize); // Write file data.
        fsUploadFile.close(); // Close the file.
        Serial.println("Save successful.");
        Serial.printf("Saved: ");
        Serial.println(filename);
        Serial.printf("size: ");
        Serial.println(upload.totalSize);

        // Store data in the appropriate array based on file size.
        if (upload.totalSize == txt_size)
        {
            for (int i = 0; i < txt_size; i++) {
                txt_formerly[i] = upload.buf[i];
            }
            Serial.println("txt_formerly OK");
            flag_txt = 1; // Set flag to indicate txt file has been uploaded.
        } 
        else
        {
            for (int i = 0; i < pre_size; i++) {
                price_formerly[i] = upload.buf[i];
            }
            Serial.println("price_formerly OK");
            flag_pre = 1; // Set flag to indicate preview file has been uploaded.
        }

        EPD_HW_RESET();
        EPD_ShowPicture(0, 0, 24, 152, gImage_conference_1_54, BLACK); // Display a picture on the screen.

        // Display the appropriate image based on file type.
        if (upload.totalSize!= txt_size)
        {
            EPD_ShowPicture(72, 0, 80, 152, price_formerly, BLACK); // Display a picture on the screen.
        }
        else
        {
            EPD_ShowPicture(24, 0, 48, 152, txt_formerly, BLACK); // Display a picture on the screen.
        }
        
        EPD_Display(ImageBW);
        EPD_FastUpdate();
        EPD_DeepSleep();
    }
}


void setup() {
    Serial.begin(115200); // Start serial communication at 115200 baud rate.

    if (SPIFFS.begin()) { // Start SPIFFS file system.
        Serial.println("SPIFFS Started.");
    } else {
        // If SPIFFS fails to start, try formatting the SPIFFS partition.
        if (SPIFFS.format()) {
            // Formatting successful, print message and restart the device.
            Serial.println("SPIFFS partition formatted successfully");
            ESP.restart(); // Restart the device.
        } else {
            // Formatting failed, print message.
            Serial.println("SPIFFS partition format failed");
        }
        return; // Exit setup function.
    }

    Serial.println("Try Connecting to ");

    WiFi.mode(WIFI_AP); // Set WiFi mode to AP (access point).
    boolean result = WiFi.softAP(AP_SSID, ""); // Start WiFi hotspot with SSID AP_SSID and no password.
    if (result) {
        IPAddress myIP = WiFi.softAPIP(); // Get the IP address of the hotspot.
        // Print hotspot information.
        Serial.println("");
        Serial.print("Soft-AP IP address = ");
        Serial.println(myIP);
        Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
        Serial.println("waiting...");
    } else {
        // If hotspot fails to start, print message and delay for 3 seconds.
        Serial.println("WiFiAP Failed");
        delay(3000);
    }

    // Configure HTTP server routes.
    server.on("/", handle_root); // Route for root directory, call handle_root function.
    server.on("/ok", okPage); // Route for /ok, call okPage function.
    server.begin(); // Start HTTP server.
    Serial.println("HTTP server started"); // Print HTTP server start message.
    delay(100); // Delay for 100 milliseconds.

    // Set up screen power control pin.
    pinMode(7, OUTPUT); // Set pin 7 as output.
    digitalWrite(7, HIGH); // Set pin 7 high to turn on screen power.

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
    UI_price(); // Display price information.
}

void loop() {
    server.handleClient(); // Handle client requests.
}

void UI_price()
{
    EPD_HW_RESET();
    EPD_ShowPicture(0, 0, 24, 152, gImage_conference_1_54, BLACK); // Display a picture on the screen.

    if (SPIFFS.exists("/txt.bin")) { // Check if file /txt.bin exists.
        // File exists, read its content.
        File file = SPIFFS.open("/txt.bin", FILE_READ); // Open file for reading.
        if (!file) {
            Serial.println("Unable to open file for reading.");
            return;
        }
        // Read file data into an array.
        size_t bytesRead = file.read(txt_formerly, txt_size);

        Serial.println("File content:");
        while (file.available()) {
            Serial.write(file.read()); // Print file content.
        }
        file.close(); // Close the file.

        flag_txt = 1; // Set flag to indicate text file exists.


        EPD_ShowPicture(24, 0, 48, 152, txt_formerly, BLACK);

    }

    if (SPIFFS.exists("/pre.bin")) { // Check if file /pre.bin exists.
        // File exists, read its content.
        File file = SPIFFS.open("/pre.bin", FILE_READ); // Open file for reading.
        if (!file) {
            Serial.println("Unable to open file for reading.");
            return;
        }
        // Read file data into an array.
        size_t bytesRead = file.read(price_formerly, pre_size);

        Serial.println("File content:");
        while (file.available()) {
            Serial.write(file.read()); // Print file content.
        }
        file.close(); // Close the file.
        flag_pre = 1; // Set flag to indicate price file exists.


        EPD_ShowPicture(72, 0, 80, 152, price_formerly, BLACK);
    }
    EPD_Display(ImageBW);
    EPD_FastUpdate();
    EPD_DeepSleep();
}
