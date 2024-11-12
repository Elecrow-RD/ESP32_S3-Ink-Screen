#include <Arduino.h>                  // Include Arduino library for using Arduino functions
#include "EPD.h"                      // Include EPD library for controlling e-paper display
#include "Ap_29demo.h"                // Include custom header file, may contain other functions or definitions
#include <WiFi.h>                     // Include WiFi library for WiFi functionality
#include <WebServer.h>                // Include WebServer library for creating a web server
#include <FS.h>
#include <SPIFFS.h>

// File object for uploading files
File fsUploadFile;
extern uint8_t ImageBW[ALLSCREEN_BYTES];  // Externally defined variable, stores image data
#define txt_size 1664  // Define the size of text image
#define pre_size 2184   // Define the size of price image

// Function to clear the screen display
void clear_all() {
  EPD_Init();                          // Initialize the e-paper display
  EPD_Clear(0, 0, 296, 128, WHITE);    // Clear the display area to white
  EPD_ALL_Fill(WHITE);                 // Fill the entire screen with white
  EPD_Update();                        // Update the display
  EPD_Clear_R26H();                    // Clear the R26H area on the display (specific purpose)
}

WebServer server(80);                 // Create a web server that listens on port 80

const char* AP_SSID = "ESP32_Config"; // Name of the Wi-Fi hotspot

// HTML form for uploading files
String HTML_UPLOAD = "<form method=\"post\" action=\"ok\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"msg\"><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\"></form>";

// Function to handle root path requests
void handle_root() {
  server.send(200, "text/html", HTML_UPLOAD); // Send HTML form to the client
}

// HTML content for displaying the "OK" page
String HTML_OK = "<!DOCTYPE html>\
<html>\
<body>\
<h1>OK</h1>\
</body>\
</html>";

uint8_t test1[4736]; // Temporary storage for image data
size_t data_size = 0; // Size of image data
unsigned char price_formerly[pre_size]; // Store the uploaded price image data
unsigned char txt_formerly[txt_size]; // Store the uploaded text image data
String filename; // Uploaded file name
int flag_txt = 0; // Flag whether text image data has been uploaded
int flag_pre = 0; // Flag whether price image data has been uploaded

// Function to handle file uploads and display
void okPage() {
  server.send(200, "text/html", HTML_OK); // Send the "OK" page to the client
  HTTPUpload& upload = server.upload();    // Get the uploaded file information

  if (upload.status == UPLOAD_FILE_END) {  // If the file upload ends
    Serial.println("Image file");
    Serial.println(upload.filename);       // Print the uploaded file name
    Serial.println(upload.totalSize);     // Print the uploaded file size

    // Determine the file name based on the file size
    if (upload.totalSize == txt_size)
      filename = "txt.bin";
    else
      filename = "pre.bin";

    // Save the received file
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, FILE_WRITE);
    fsUploadFile.write(upload.buf, upload.totalSize);
    fsUploadFile.close();
    Serial.println("Saved successfully");
    Serial.printf("Saved: ");
    Serial.println(filename);
    Serial.printf("Size: ");
    Serial.println(upload.totalSize);
    // Determine the storage method based on the file size
    if (upload.totalSize == txt_size) {
      for (int i = 0; i < txt_size; i++) {
        txt_formerly[i] = upload.buf[i];
      }
      Serial.println("txt_formerly OK");
      flag_txt = 1;
    } else {
      for (int i = 0; i < pre_size; i++) {
        price_formerly[i] = upload.buf[i];
      }
      Serial.println("price_formerly OK");
      flag_pre = 1;
    }

    // Display the image
    EPD_HW_RESET();
    if (upload.totalSize != pre_size) {
      if (flag_txt == 1) {
        // Display both text and price images
        EPD_ShowPicture(0, 24, 128, 104, txt_formerly, BLACK);
        EPD_ShowPicture(128, 24, 168, 104, price_formerly, BLACK);
      } else {
        // Display only the price image
        EPD_ShowPicture(128, 24, 168, 104, price_formerly, BLACK);
      }
    } else {
      if (flag_pre == 1) {
        // Display both price and text images
        EPD_ShowPicture(0, 24, 128, 104, txt_formerly, BLACK);
        EPD_ShowPicture(128, 24, 168, 104, price_formerly, BLACK);
      } else {
        // Display only the text image
        EPD_ShowPicture(0, 24, 128, 104, txt_formerly, BLACK);
      }
    }

    EPD_DisplayImage(ImageBW);  // Display the background image
    EPD_FastUpdate();          // Quickly update the display
    EPD_Sleep();              // Enter sleep mode
  }
}

void setup() {
  Serial.begin(115200);              // Initialize serial communication, set baud rate to 115200
  if (SPIFFS.begin()) {              // Try to start the SPIFFS file system
    Serial.println("SPIFFS started."); // If successful, print message
  } else {
    // If failed, try to format the SPIFFS file system
    if (SPIFFS.format()) {
      Serial.println("SPIFFS partition formatted successfully"); // If formatting is successful, print message
      ESP.restart();                 // Restart the ESP32
    } else {
      Serial.println("SPIFFS partition formatting failed"); // If formatting fails, print message
    }
    return; // Exit the setup function
  }

  Serial.println("Trying to connect to");

  WiFi.mode(WIFI_AP);               // Set WiFi to AP mode (Access Point mode)
  bool result = WiFi.softAP(AP_SSID, ""); // Start the WiFi hotspot, SSID is AP_SSID, password is empty
  if (result) {
    IPAddress myIP = WiFi.softAPIP(); // Get the IP address of the hotspot
    Serial.println("");
    Serial.print("SoftAP IP Address=");
    Serial.println(myIP);           // Print the IP address
    Serial.println(String("MAC Address = ") + WiFi.softAPmacAddress().c_str()); // Print the MAC address
    Serial.println("Waiting...");
  } else {
    Serial.println("WiFiAP failed");   // If the WiFi hotspot fails to start, print message
    delay(3000);                     // Wait for 3 seconds
  }

  server.on("/", handle_root);      // Set the handler function for the root path request
  server.on("/ok", okPage);         // Set the handler function for the /ok path request
  server.begin();                   // Start the web server
  Serial.println("HTTP server started"); // Print message indicating the HTTP server has started
  delay(100);                       // Wait for 100 milliseconds

  // Screen power settings
  pinMode(7, OUTPUT);              // Set pin 7 as output mode
  digitalWrite(7, HIGH);           // Set pin 7 to high level, turn on the screen power

  // Initialize the e-paper display
  EPD_Init();                      // Initialize the e-paper display
  EPD_Clear(0, 0, 296, 128, WHITE);  // Clear the screen area (0,0) to (296,128), background color is white
  EPD_ALL_Fill(WHITE);             // Fill the entire screen with white
  EPD_Update();                    // Update the display
  EPD_Clear_R26H();                // Clear a specific area (possibly to clear some old content on the e-paper)

  UI_price();                      // Initialize the user interface's price display
}

void loop() {
  // Handle client requests from the server
  server.handleClient();           // Handle client requests
}

void UI_price() {
  EPD_HW_RESET();                 // Hardware reset the e-paper display

  EPD_ShowPicture(0, 0, 296, 24, gImage_conference_4, BLACK); // Display the background image on the screen, area is (0,0) to (296,24), background color is black

  EPD_DisplayImage(ImageBW);      // Display the black and white image
  EPD_FastUpdate();               // Quickly update the display
  EPD_Sleep();                    // Put the display into sleep mode

  // If the "/txt.bin" file exists in SPIFFS
  if (SPIFFS.exists("/txt.bin")) {
    // The file exists, read the file content
    File file = SPIFFS.open("/txt.bin", FILE_READ); // Open the file in read-only mode
    if (!file) {
      Serial.println("Failed to open file for reading"); // If the file cannot be opened, print message
      return; // Exit the function
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(txt_formerly, txt_size); 

    Serial.println("File content:"); // Print file content identifier
    while (file.available()) {
      Serial.write(file.read());    // Read and print the file content byte by byte
    }
    file.close(); // Close the file

    flag_txt = 1;  // Set the flag indicating the text file exists

    EPD_HW_RESET(); // Hardware reset the e-paper display

    EPD_ShowPicture(0, 24, 128, 104, txt_formerly, BLACK);
    

    EPD_DisplayImage(ImageBW);  // Display the black and white image
    EPD_FastUpdate();           // Quickly update the display
    EPD_Sleep();                // Put the display into sleep mode
  }

  // If the "/pre.bin" file exists in SPIFFS
  if (SPIFFS.exists("/pre.bin")) {
    // The file exists, read the file content
    File file = SPIFFS.open("/pre.bin", FILE_READ); // Open the file in read-only mode
    if (!file) {
      Serial.println("Failed to open file for reading"); // If the file cannot be opened, print message
      return; // Exit the function
    }
    // Read data from the file into the array
    size_t bytesRead = file.read(price_formerly, pre_size);

    Serial.println("File content:"); // Print file content identifier
    while (file.available()) {
      Serial.write(file.read());    // Read and print the file content byte by byte
    }
    file.close(); // Close the file
    flag_pre = 1; // Set the flag indicating the price file exists

    EPD_HW_RESET(); // Hardware reset the e-paper display

    EPD_ShowPicture(128, 24, 168, 104, price_formerly, BLACK); // Display the price image read from the file, area is (220,50) to (80,48), background color is black

    EPD_DisplayImage(ImageBW);  // Display the black and white image
    EPD_FastUpdate();           // Quickly update the display
    EPD_Sleep();                // Put the display into sleep mode
  }
}