#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "EPD_GUI.h"
#include "Pic.h"

#define pic_temp_X 72  // The width of the resolution of the temperature icon
#define pic_temp_Y 56   // The height of the resolution of the temperature icon
#define pic_humi_X 72  // The width of the resolution of the humidity icon
#define pic_humi_Y 56   // The height of the resolution of the humidity icon

// Define an array for black and white image data, which serves as the buffer for the e-paper display.
// The size of the buffer is determined according to the resolution of the e-paper display.
uint8_t ImageBW[2888];

const char* ssid = "yanfa_software";        // WiFi SSID
const char* password = "yanfa-123456";      // WiFi password

unsigned long lastUpdateTime = 0;  // The timestamp of the last update time
unsigned long lastAnalysisTime = 0;  // Last analysis timestamp
// Replace with your OpenWeatherMap API key
String openWeatherMapApiKey = "c856cfe14f96599694231c794c9862f8";
// Example:
// String openWeatherMapApiKey = "bd939aa3d23ff33d3c8f5dd1dd435";

// Replace with your city and country code
String city = "Shenzhen";        // City name
String countryCode = "1795564"; // Country code (this is the ID for London)

// Define variables related to JSON data
String jsonBuffer;
int httpResponseCode;
JSONVar myObject;

// Define variables related to weather information
String temperature;
String humidity;
String city_js;

// Build URL for OpenWeatherMap API request
String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&units=metric";

// Function to display weather forecast on the e-paper display.
void Update_Display()
{
 // Get current time information
  time_t t;
  time(&t);
  struct tm *timeinfo = localtime(&t);
  if (timeinfo == NULL) {
    Serial.println("Failed to get time");
    return;
  }
  Serial.println("----------The screen time display is about to refresh----------");
  delay(1000);
  Serial.print("Current time: ");
  Serial.println(asctime(timeinfo));

  // Update time
  static char buff1[20]; // Store Year Month Day
  static char buff2[20]; // Store hour minute
  char buffer[40];  // Used for storing temperature and humidity
  sprintf(buff1, "%04d-%02d-%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday); // Store Year, Month, and Day
  sprintf(buff2, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min); // Store hour and minute

  // Obtain the day of the week
  const char *daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  const char *dayOfWeek = daysOfWeek[timeinfo->tm_wday]; // Store the day of the week (tm_wday represents Sunday from 0 to 6, Monday to Saturday)

   // Display temperature and humidity icons
  EPD_ShowPicture(0, 72, pic_temp_X, pic_temp_Y, gImage_pic_temp, BLACK);  // Display temperature icon
  EPD_ShowPicture(80, 72, pic_humi_X, pic_humi_Y, gImage_pic_humi, BLACK);  // Display humidity icon

  // Display new time
  EPD_ShowString(16, 0, buff1, 24, BLACK); // Print Year Month Day
  EPD_ShowString(12, 24, buff2, 48, BLACK); // Print time
  //EPD_ShowString(25, 128, dayOfWeek, 24, BLACK); // Print the day of the week
  
  // Display temperature
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%s C", temperature); // Format temperature as a string
  EPD_ShowString(10, 128, buffer, 16, BLACK); // Display temperature
  // Display humidity
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%s %", humidity); // Format humidity as a string
  EPD_ShowString(105, 128, buffer, 16, BLACK); // Display humidity
  Serial.println("* * * * * * The screen time display has been refreshed * * * * * *");


  // Update the e-paper display with the new content.
  EPD_Display(ImageBW);
  EPD_PartUpdate();
  
}

void setup() {
  Serial.begin(115200); // Initialize the serial communication.

  // Connect to the WiFi network.
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address of the device after successful connection.

  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

  // Set pin 7 as an output pin to control the power of the e-paper display.
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  const char* ntpServer = "pool.ntp.org";
  configTime(8 * 3600, 0, ntpServer); // Time zone
  delay(3000); // Waiting - Update Time
  js_analysis();

  EPD_GPIOInit();
  Paint_NewImage(ImageBW, EPD_W, EPD_H, 0, WHITE);
  Paint_Clear(WHITE);

  EPD_Init();
  EPD_Display(ImageBW);
  Paint_Clear(WHITE);
  EPD_Update();

  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_FastUpdate();
  EPD_Clear_R26H();

  Update_Display(); 
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastUpdateTime >= 60000) { // Execute every minute
    Update_Display();   // Update time, temperature, and humidity
    lastUpdateTime = currentTime;
  }
  // Check if it's been more than thirty minutes since the last analysis
  if (currentTime - lastAnalysisTime >= 30 * 60000) { // Execute every 30 minutes
    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer); // Print the obtained JSON data
    js_analysis();   // Analyze weather data to obtain temperature and humidity
    lastAnalysisTime = currentTime;
  }
}

void js_analysis()
{
  // Check if successfully connected to WiFi network
  if (WiFi.status() == WL_CONNECTED) {
    // // Build URL for OpenWeatherMap API request
    // String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&units=metric";

    // Loop until a valid HTTP response code of 200 is obtained
    while (httpResponseCode != 200) {
      // Send HTTP GET request and retrieve response content
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer); // Print the obtained JSON data
      myObject = JSON.parse(jsonBuffer); // Parse JSON data

      // Check if JSON parsing is successful
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!"); // Prompt message when parsing fails
        return; // If parsing fails, exit the function
      }
      delay(2000); // Wait for 2 seconds and retry
    }

    // Extract weather information from parsed JSON data
    temperature = JSON.stringify(myObject["main"]["temp"]); // Extract temperature
    humidity = JSON.stringify(myObject["main"]["humidity"]); // Extract humidity
    city_js = JSON.stringify(myObject["name"]); // Extract city

    // Print extracted weather information
    Serial.print("Obtained temperature: ");
    Serial.println(temperature);
    Serial.print("Obtained humidity: ");
    Serial.println(humidity);
    Serial.print("Obtained city_js: ");
    Serial.println(city_js);
  }
  else {
    // If WiFi is disconnected, print a prompt message
    Serial.println("WiFi Disconnected");
  }
}

// Send HTTP GET request and return the response data
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Initialize HTTP request, specify server address
  http.begin(client, serverName);

  // Send HTTP GET request
  httpResponseCode = http.GET();

  String payload = "{}"; // Initialize the returned data as an empty JSON object

  // Handle the returned data based on the response code
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode); // Print HTTP response code
    payload = http.getString(); // Get the string data of the response
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode); // Print error code
  }
  // Release HTTP resources
  http.end();

  return payload; // Return the response data
}
