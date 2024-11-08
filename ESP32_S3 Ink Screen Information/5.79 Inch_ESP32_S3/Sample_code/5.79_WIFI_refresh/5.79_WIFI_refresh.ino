#include <Arduino.h>           // Include Arduino core library file
#include "EPD.h"               // Include electronic paper screen library file
#include "Ap_29demo.h"         // Include custom function library
#include "FS.h"               // File system library for file operations
#include "SPIFFS.h"           // SPIFFS file system library for file read/write
#include <WiFi.h>             // WiFi library for creating and managing WiFi connections
#include <Ticker.h>           // Ticker library for timed operations
#include <WebServer.h>        // WebServer library for creating HTTP server

// Define an array to store image data, size 27200 bytes
uint8_t ImageBW[27200];

#define txt_size 9280         // Define the size of the txt file
#define pre_size 13688        // Define the size of the pre file

// Clear the display content on the electronic paper
void clear_all()
{
  EPD_FastMode1Init(); // Initialize the fast mode of the electronic paper
  EPD_Display_Clear(); // Clear the display content on the electronic paper
  EPD_Update();        // Update the electronic paper display
}

// Create a WebServer instance, listening on port 80
WebServer server(80);
const char *AP_SSID = "ESP32_Config"; // WiFi hotspot name

// HTML form for the upload page
String HTML_UPLOAD = "<form method=\"post\" action=\"ok\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"msg\"><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\"></form>";

// HTML page for successful upload
String HTML_OK = "<!DOCTYPE html>\
<html>\
<body>\
<h1>OK</h1>\
</body>\
</html>";

// Object to store the uploaded file
File fsUploadFile;          // Used to operate files in the SPIFFS file system
unsigned char test1[26928]; // Array to store file data
size_t data_size = 0;      // Size of the file data
String filename;           // Variable to store the filename
int i = 0;                // Index for the filename array
unsigned char price_formerly[pre_size]; // Array to store the uploaded preview image data
unsigned char txt_formerly[txt_size];   // Array to store the uploaded text image data

int flag_txt = 0; // Flag to indicate if the txt file has been uploaded
int flag_pre = 0; // Flag to indicate if the preview file has been uploaded

// Handle the request to upload a file
void okPage()
{
  server.send(200, "text/html", HTML_OK); // Send the success page
  HTTPUpload &upload = server.upload();    // Get the uploaded file object

  // Note: The initial size of upload.buf is only 1436 bytes, adjust to support large file uploads
  // Modify the HTTP_UPLOAD_BUFLEN definition in WebServer.h to increase the initial size to 14360 bytes
  if (upload.status == UPLOAD_FILE_END) // File upload ends
  {
    Serial.println("draw file");
    Serial.println(upload.filename);  // Print the uploaded filename
    Serial.println(upload.totalSize); // Print the total size of the file

    // Determine the file type based on the file size
    if (upload.totalSize == txt_size) // If the file size is 9280 bytes, it is a txt file
      filename = "txt.bin";
    else
      filename = "pre.bin"; // Otherwise, it is a preview file

    // Save the received file
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, FILE_WRITE); // Open the file in write mode
    fsUploadFile.write(upload.buf, upload.totalSize); // Write the file data
    fsUploadFile.close(); // Close the file
    Serial.println("Save successful");
    Serial.printf("Saved: ");
    Serial.println(filename);

    Serial.printf("Size: ");
    Serial.println(upload.totalSize);

    // Store the data in the appropriate array based on the file size
    if (upload.totalSize == txt_size)
    {
      for (int i = 0; i < txt_size; i++) {
        txt_formerly[i] = upload.buf[i];
      }
      Serial.println("txt_formerly OK");
      flag_txt = 1; // Set the flag to indicate the txt file has been uploaded
    } 
    else
    {
      for (int i = 0; i < pre_size; i++) {
        price_formerly[i] = upload.buf[i];
      }
      Serial.println("price_formerly OK");
      flag_pre = 1; // Set the flag to indicate the preview file has been uploaded
    }

    EPD_GPIOInit();            // Initialize the GPIO pins configuration for the EPD e-ink screen
    EPD_FastMode1Init();       // Initialize the fast mode 1 of the EPD screen

    EPD_ShowPicture(0, 0, 792, 40, gImage_conference_1, WHITE); // Display the background image on the screen, background color is white

    // Display the appropriate image based on the uploaded file type
    if (upload.totalSize != txt_size)
    {
        EPD_ShowPicture(320, 40, 472, 232, price_formerly, WHITE); // Display the preview image
    }
    else
    {
        EPD_ShowPicture(0, 40, 320, 232, txt_formerly, WHITE); // Display the text image
    }
    
    EPD_Display(ImageBW);      // Display the image stored in the ImageBW array
    EPD_FastUpdate();          // Perform a fast update to refresh the screen
    EPD_DeepSleep();          // Set the screen to deep sleep mode to save power
  }
}

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  SPIFFS.format();
  if (SPIFFS.begin()) {  // Start the SPIFFS file system
    Serial.println("SPIFFS Started.");  // SPIFFS started successfully, print a message
  } else {
    // If SPIFFS fails to start, try formatting the SPIFFS partition
    if (SPIFFS.format()) {
      // Format successful, print a message and restart the device
      Serial.println("SPIFFS partition formatted successfully");
      ESP.restart();  // Restart the device
    } else {
      // Format failed, print a message
      Serial.println("SPIFFS partition format failed");
    }
    return;  // Exit the setup function
  }

  //  //Print the wakeup reason for ESP32
  // print_wakeup_reason();
  // //First we configure the wake up source
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 0); //1 = High, 0 = Low

  Serial.println("Trying to connect to ");

  WiFi.mode(WIFI_AP);  // Set the WiFi mode to AP (Access Point)
  boolean result = WiFi.softAP(AP_SSID, "");  // Start the WiFi hotspot, SSID is AP_SSID, password is empty
  if (result) {
    IPAddress myIP = WiFi.softAPIP();  // Get the IP address of the hotspot
    // Print the hotspot information
    Serial.println("");
    Serial.print("Soft-AP IP address = ");
    Serial.println(myIP);
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
    Serial.println("Waiting ...");
  } else {
    // If starting the hotspot fails, print a message and delay for 3 seconds
    Serial.println("WiFiAP Failed");
    delay(3000);
  }

  // Configure the routes for the HTTP server
  server.on("/", handle_root);  // Root directory route, call handle_root function when accessing the root directory
  server.on("/ok", okPage);  // /ok route, call okPage function when accessing /ok
  server.begin();  // Start the HTTP server
  Serial.println("HTTP server started");  // Print a message indicating the HTTP server has started
  delay(100);  // Delay for 100 milliseconds

  // Set the screen power control pin
  pinMode(7, OUTPUT);  // Set pin 7 to output mode
  digitalWrite(7, HIGH);  // Set pin 7 to high level to turn on the screen power

  // Initialize the EPD (electronic paper display) screen
  EPD_GPIOInit();  // Initialize the GPIO pins for the EPD
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);  // Create a new canvas, dimensions EPD_W x EPD_H, background color is white
  Paint_Clear(WHITE);  // Clear the canvas, background color is white

  EPD_FastMode1Init();  // Initialize the fast mode 1 of the EPD
  EPD_Display_Clear();  // Clear the EPD display content
  EPD_Update();  // Update the display
  UI_price();  // Display price information
}

void loop() {
  server.handleClient();  // Handle client requests
}

void UI_price()
{
  EPD_GPIOInit();  // Reinitialize the GPIO pins configuration for the EPD e-ink screen
  EPD_FastMode1Init();  // Reinitialize the fast mode 1 of the EPD screen
  
  EPD_ShowPicture(0, 0, 792, 40, gImage_conference_1, WHITE); 
  EPD_Display(ImageBW);  // Display the image stored in the ImageBW array
  EPD_FastUpdate();  // Perform a fast update to refresh the screen
  EPD_DeepSleep();  // Set the screen to deep sleep mode to save power

  if (SPIFFS.exists("/txt.bin")) {  // Check if the file /txt.bin exists
    // File exists, read the file content
    File file = SPIFFS.open("/txt.bin", FILE_READ);  // Open the file for reading
    if (!file) {
      Serial.println("Failed to open file for reading");  // If the file cannot be opened, print a message
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(txt_formerly, txt_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read());  // Print the file content
    }
    file.close();  // Close the file

    flag_txt = 1;  // Set the flag to indicate the text file exists

    EPD_GPIOInit();  // Reinitialize the GPIO pins configuration for the EPD e-ink screen
    EPD_FastMode1Init();  // Reinitialize the fast mode 1 of the EPD screen

    // Display the read image on the screen, position (30, 80), size 376x144, background color is white
    EPD_ShowPicture(0, 40, 320, 232, txt_formerly, WHITE);

    EPD_Display(ImageBW);  // Display the image stored in the ImageBW array
    EPD_FastUpdate();  // Perform a fast update to refresh the screen
    EPD_DeepSleep();  // Set the screen to deep sleep mode to save power
  }

  if (SPIFFS.exists("/pre.bin")) {  // Check if the file /pre.bin exists
    // File exists, read the file content
    File file = SPIFFS.open("/pre.bin", FILE_READ);  // Open the file for reading
    if (!file) {
      Serial.println("Failed to open file for reading");  // If the file cannot be opened, print a message
      return;
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read());  // Print the file content
    }
    file.close();  // Close the file
    flag_pre = 1;  // Set the flag to indicate the price file exists

    EPD_GPIOInit();  // Reinitialize the GPIO pins configuration for the EPD e-ink screen
    EPD_FastMode1Init();  // Reinitialize the fast mode 1 of the EPD screen

    // Display the read price image on the screen, position (500, 80), size 256x184, background color is white
    EPD_ShowPicture(320, 40, 472, 232, price_formerly, WHITE);

    EPD_Display(ImageBW);  // Display the image stored in the ImageBW array
    EPD_FastUpdate();  // Perform a fast update to refresh the screen
    EPD_DeepSleep();  // Set the screen to deep sleep mode to save power
  }
  // // Go to sleep now
  // Serial.println("Going to sleep now ....");
  // esp_deep_sleep_start();
}


//  -----Turn on when low-power mode is required
// // Print the wakeup reason
// void print_wakeup_reason() {
//   esp_sleep_wakeup_cause_t wakeup_reason;

//   wakeup_reason = esp_sleep_get_wakeup_cause();

//   switch (wakeup_reason)
//   {
//     case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
//     case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
//     case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
//     case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
//     case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
//     default : Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
//   }
// }