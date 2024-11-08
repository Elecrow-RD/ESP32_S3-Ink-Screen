#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "EPD.h"
#include "pic.h"

#include <time.h>

#define pic_temp_X 216  //The width of the resolution of the temperature icon
#define pic_temp_Y 64   //The height of the resolution of the temperature icon
#define pic_humi_X 192  //The width c of the resolution of the humidity icon
#define pic_humi_Y 88   //The height c of the resolution of the humidity icon

//Define a black and white image array as a buffer for electronic paper display
uint8_t ImageBW[27200];  //Define the buffer size based on the resolution of the electronic paper display screen

const char* ssid = "yanfa_software";       // WiFi network name
const char* password = "yanfa-123456";     // WiFi password

unsigned long lastUpdateTime = 0;  // The timestamp of the last update time
unsigned long lastAnalysisTime = 0;  // Last analysis timestamp
//****************************************************************************************
//OpenWeatherMap API Key
String openWeatherMapApiKey = "c856cfe14f96599694231c794c9862f8";
//Example API Key: String openWeatherMapApiKey = "bd939aa3d23ff33d3c8f5dd1dd435";

// Replace with actual city and country codes
String city = "Shenzhen";                    // City Name
String countryCode = "1795564";            // The country code of the city

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

//****************************************************************************************
void setup() {
  WiFi.begin(ssid, password); //  Connect to WIFI
    
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting...");
    delay(3000);//  Waiting - Connect to WIFI
  }
  Serial.println("WiFi is connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  pinMode(7, OUTPUT);        
  digitalWrite(7, HIGH);     

  EPD_GPIOInit();           
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); 
  Paint_Clear(WHITE);     

  // Draw partition lines
  EPD_DrawLine(0, 150, 792, 150, BLACK); // Draw a horizontal line
  EPD_DrawLine(504, 0, 504, 150, BLACK); // Draw a vertical line (next to time)
  EPD_DrawLine(435, 150, 435, 270, BLACK); // Draw a vertical line (next to the day of the week)

  EPD_ShowPicture(0, 160, pic_temp_X, pic_temp_Y, gImage_pic_temp, WHITE);  //  Display temperature icon
  EPD_ShowPicture(220, 152, pic_humi_X, pic_humi_Y, gImage_pic_humi, WHITE);  //  Display humidity icon

  const char* ntpServer = "pool.ntp.org";//The name of the server
  configTime(8 * 3600, 0, ntpServer);// time zone
  delay(3000);//  Waiting - Update Time

  clear_all();
  EPD_Clear_R26A6H();// Write the first frame into the 26h register to ensure that the screen does not flicker during refresh
  js_analysis();
  Update_Display(); 
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastUpdateTime >= 60000) { // Execute every minute
    Update_Display();   //  Update time, temperature and humidity
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

void clear_all()
{
  EPD_FastMode1Init();     
  EPD_Display_Clear();     
  EPD_Update();           
}

//  Update time and temperature/humidity
void Update_Display() {
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

  //Update time
  static char buff1[20];//Storage Year Month Day
  static char buff2[20];//Storage hour minute
  char buffer[40];  // Used for storing temperature and humidity
  sprintf(buff1, "%04d-%02d-%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);//  Storage Year、Month and Day
  sprintf(buff2, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);//Storage hour and minute

  //Obtain the day of the week
  const char *daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  const char *dayOfWeek = daysOfWeek[timeinfo->tm_wday];//Store the day of the week (tmw_day represents Sunday from 0 to 6, Monday to Saturday)

  // Display new time
  EPD_ShowString(0, 10, buff1, 96, BLACK);//  Print Year Month Day
  EPD_ShowString(528, 10, buff2, 96, BLACK);//  Printing time
  EPD_ShowString(510, 187, dayOfWeek, 48, BLACK); //  Print the day of the week
  //  Display temperature
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%s C", temperature); // Format temperature as a string
  EPD_ShowString(90, 220, buffer, 24, BLACK); //  Display temperature
  // Display humidity
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%s %", humidity); // Format humidity as a string
  EPD_ShowString(330, 220, buffer, 24, BLACK); // Display humidity
  Serial.println("* * * * * * The screen time display has been refreshed * * * * * *");

  // update display
  EPD_Display(ImageBW);
  EPD_PartUpdate();
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
      delay(2000); //Wait for 2 seconds and retry
    }

    // Extract weather information from parsed JSON data
    temperature = JSON.stringify(myObject["main"]["temp"]); // Extract temperature
    humidity = JSON.stringify(myObject["main"]["humidity"]); // Extract humidity
    city_js = JSON.stringify(myObject["name"]); // Extract  city

    // Print extracted weather information
    Serial.print("Obtained temperature: ");
    Serial.println(temperature);
    Serial.print("Obtained humidity: ");
    Serial.println(humidity);
    Serial.print("Obtained city_js: ");
    Serial.println(city_js);
  }
  else {
    //If WiFi is disconnected, print a prompt message
    Serial.println("WiFi Disconnected");
  }
}

//Define the function for HTTP GET requests
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  //Initialize the HTTP client and specify the requested server URL
  http.begin(client, serverName);

  // Send HTTP GET request
  httpResponseCode = http.GET();

  // The response content returned by initialization
  String payload = "{}";

  //Check the response code and process the response content
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode); // Print response code
    payload = http.getString(); // Obtain response content
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode); // Print error code
  }
  //Release HTTP client resources
  http.end();

  return payload; // Return response content
}
