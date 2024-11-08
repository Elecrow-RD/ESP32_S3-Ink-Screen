#include <Arduino.h>           // Include Arduino core library
#include "EPD.h"               // Include EPD library for controlling the electronic paper display
#include "EPD_GUI.h"           // Include EPD_GUI library for GUI operations
#include "Ap_29demo.h"         // Include Ap_29demo library, possibly a custom application library
#include <WiFi.h>              // Include WiFi library for Wi-Fi functionality
#include <Ticker.h>            // Include Ticker library for timer tasks
#include <WebServer.h>         // Include WebServer library for creating a web server
#include "FS.h"                // Include file system library for file operations
#include "SPIFFS.h"            // Include SPIFFS library for the SPIFFS file system

// Define an array to store image data, 15000 bytes in size
uint8_t ImageBW[15000];

// Define the sizes of txt and pre image data
#define txt_size 5600
#define pre_size 7400

// Clear all content on the display
void clear_all()
{
  EPD_Clear(); // Clear display content
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer, filled with white
  EPD_Full(WHITE); // Fill the entire screen with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW); // Update display content
}

// Create a WebServer instance, listening on port 80
WebServer server(80);

// Define hotspot name
const char *AP_SSID = "ESP32_Config"; // Define ESP32 hotspot name

// Define the HTML form for uploading files
String HTML_UPLOAD = "<form method=\"post\" action=\"ok\" enctype=\"multipart/form-data\">\
<input type=\"file\" name=\"msg\">\
<input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\">\
</form>";

// Handle root directory request, return upload form
void handle_root()
{
  server.send(200, "text/html", HTML_UPLOAD); // Send upload form to client
}

// HTML page after successful upload
String HTML_OK = "<!DOCTYPE html>\
<html>\
<body>\
<h1>OK</h1>\
</body>\
</html>";

// Object to store uploaded file
File fsUploadFile;  // File object for storing uploaded file

// Define an array to store uploaded image data
unsigned char test1[15000]; // Temporary array to store image data
unsigned char price_formerly[pre_size]; // Array to store price image data
unsigned char txt_formerly[txt_size]; // Array to store text image data

String filename; // String to store filename

// Flags to mark different image data
int flag_txt = 0; // Flag to mark whether text image data exists
int flag_pre = 0; // Flag to mark whether price image data exists

// Function to handle file upload request
void okPage()
{
  server.send(200, "text/html", HTML_OK); // Return the success page
  HTTPUpload &upload = server.upload(); // Get the uploaded file

  // Note: The default size of upload.buf may not be enough to handle large files
  // Please refer to the definition of HTTP_UPLOAD_BUFLEN in WebServer.h, adjust the initial size to support large file transfers
  if (upload.status == UPLOAD_FILE_END) // If file upload is complete
  {
    Serial.println("draw file"); // Print debug information: file upload complete
    Serial.println(upload.filename); // Print uploaded filename
    Serial.println(upload.totalSize); // Print uploaded file size
    if (upload.totalSize == txt_size) // Check if uploaded file size equals predefined txt_size
      filename = "txt.bin"; // Set filename to txt.bin
    else
      filename = "pre.bin"; // Otherwise set filename to pre.bin
    if (!filename.startsWith("/")) filename = "/" + filename; // If filename does not start with '/', add '/' prefix
    fsUploadFile = SPIFFS.open(filename, FILE_WRITE); // Open file for writing
    fsUploadFile.write(upload.buf, upload.totalSize); // Write uploaded file data to file
    fsUploadFile.close(); // Close file
    Serial.println("Save succeeded"); // Print save succeeded message
    Serial.printf("Saved: "); // Print saved filename
    Serial.println(filename);
    
    // Copy uploaded file data to corresponding buffer arrays
    if (upload.totalSize == txt_size)
    {
      for (int i = 0; i < txt_size; i++) {
        txt_formerly[i] = upload.buf[i]; // Copy data to txt_formerly
      }
      Serial.println("txt_formerly OK"); // Print txt_formerly updated successfully message
      flag_txt = 1; // Set flag_txt to 1
    } else
    {
      for (int i = 0; i < pre_size; i++) {
        price_formerly[i] = upload.buf[i]; // Copy data to price_formerly
      }
      Serial.println("price_formerly OK"); // Print price_formerly updated successfully message
      flag_pre = 1; // Set flag_pre to 1
    }

    clear_all();  // Clear all content on the display

    // Display background image
    EPD_ShowPicture(0, 0, EPD_W, 40, gImage_conference_2, WHITE); // Display background image on screen, background color is white

    if (upload.totalSize != txt_size) // If uploaded file size does not equal txt_size
    {
      if (flag_txt == 1) // If flag_txt is 1
      {
        // Display images from txt_formerly and price_formerly
        EPD_ShowPicture(0, 40, 400, 112, txt_formerly, WHITE); // Display txt_formerly image
        EPD_ShowPicture(0, 152, 400, 148, price_formerly, WHITE); // Display price_formerly image
      } else
      {
        // Only display image from price_formerly
        EPD_ShowPicture(0, 152, 400, 148, price_formerly, WHITE); // Display price_formerly image
      }
    } else
    {
      // When uploaded file size equals txt_size, handle different display content
      if (flag_pre == 1) // If flag_pre is 1
      {
        // Display images from price_formerly and txt_formerly
        EPD_ShowPicture(0, 152, 400, 148, price_formerly, WHITE); // Display price_formerly image
        EPD_ShowPicture(0, 40, 400, 112, txt_formerly, WHITE); // Display txt_formerly image
      } else
      {
        // Only display image from txt_formerly
        EPD_ShowPicture(0, 40, 400, 112, txt_formerly, WHITE); // Display txt_formerly image
      }
    }
    
    // Quickly display the image stored in the Image_BW array
    EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);

    EPD_Sleep(); // Enter sleep mode
  }
}

void setup() {
  // Initialize serial communication, set baud rate to 115200
  Serial.begin(115200);

  // Start the SPIFFS file system
  if (SPIFFS.begin()) {
    Serial.println("SPIFFS Started.");
  } else {
    // If SPIFFS fails to start, try formatting the SPIFFS partition
    if (SPIFFS.format()) {
      Serial.println("SPIFFS partition formatted successfully");
      ESP.restart(); // Restart device after successful formatting
    } else {
      Serial.println("SPIFFS partition format failed");
    }
    return;
  }

  // Print connection information
  Serial.println("Trying to connect...");

  // Set WiFi to Access Point (AP) mode
  WiFi.mode(WIFI_AP);
  // Start WiFi hotspot, AP_SSID is the SSID of the hotspot, password is empty
  boolean result = WiFi.softAP(AP_SSID, "");
  if (result) {
    IPAddress myIP = WiFi.softAPIP();
    // Print the IP address and MAC address of the hotspot
    Serial.println("");
    Serial.print("Soft-AP IP address = ");
    Serial.println(myIP);
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
    Serial.println("Waiting for connections...");
  } else {
    // If starting the hotspot fails, print error message
    Serial.println("WiFiAP Failed");
    delay(3000);
  }

  // Set up HTTP server routes and handler functions
  server.on("/", handle_root);
  server.on("/ok", okPage);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);

  // Configure screen power
  pinMode(7, OUTPUT); // Set GPIO 7 as output mode
  digitalWrite(7, HIGH); // Turn on screen power
  EPD_GPIOInit();  // Initialize screen GPIO
  EPD_Clear();     // Clear screen
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);  // Create a new canvas, set canvas to white
  EPD_Full(WHITE); // Clear canvas, fill with white
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);    // Display blank canvas

  EPD_Init_Fast(Fast_Seconds_1_5s);  // Initialize screen, set update speed to 1.5 seconds

  UI_price();  // Display price interface
}

void loop() {
  // Handle client requests
  server.handleClient();
}

// UI_price function: Update price display interface
void UI_price() {
  clear_all();  // Clear all display content

  EPD_ShowPicture(0, 0, EPD_W, 40, gImage_conference_2, WHITE); // Display top background image on screen, background color is white

  if (SPIFFS.exists("/txt.bin")) {
    // If file exists, read file content
    File file = SPIFFS.open("/txt.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading");
      return;
    }
    // Read data from file into array
    size_t bytesRead = file.read(txt_formerly, txt_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print file content
    }
    file.close();

    EPD_ShowPicture(0, 40, 400, 112, txt_formerly, WHITE); // Display txt_formerly image
    flag_txt = 1; // Set flag
  }

  if (SPIFFS.exists("/pre.bin")) {
    // If file exists, read file content
    File file = SPIFFS.open("/pre.bin", FILE_READ);
    if (!file) {
      Serial.println("Failed to open file for reading");
      return;
    }
    // Read data from file into array
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:");
    while (file.available()) {
      Serial.write(file.read()); // Print file content
    }
    file.close();

    EPD_ShowPicture(0, 152, 400, 148, price_formerly, WHITE); // Display price_formerly image
    flag_pre = 1; // Set flag
  }

  // Display the image stored in the Image_BW array
  EPD_Display_Part(0, 0, EPD_W, EPD_H, ImageBW);

  EPD_Sleep(); // Enter sleep mode to save energy
}