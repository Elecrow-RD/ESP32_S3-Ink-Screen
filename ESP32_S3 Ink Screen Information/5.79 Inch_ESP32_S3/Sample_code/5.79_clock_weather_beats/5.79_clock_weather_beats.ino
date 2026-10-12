// CrowPanel ESP32 5.79" e-ink: clock + weather + Swatch Internet Time (.beats)
//
// - Time:    NTP, local time zone via POSIX TZ string (see config.h)
// - Beats:   Swatch Internet Time. 1 day = 1000 .beats, based on BMT = UTC+1,
//            so @000 is midnight in Biel and the value is the same worldwide.
// - Weather: Open-Meteo (https://open-meteo.com), no API key needed.
//
// Libraries: Arduino_JSON (bundled in the repo's libraries folder). WiFi,
// HTTPClient and WiFiClientSecure come with the ESP32 Arduino core.

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <time.h>
#include "EPD.h"
#include "config.h"

uint8_t ImageBW[27200];

struct Weather {
  bool   valid = false;
  float  temp = 0, hi = 0, lo = 0, wind = 0;
  int    humidity = 0;
  int    code = 0;
  time_t fetchedAt = 0;
} weather;

unsigned long lastClock = 0, lastWeather = 0, lastFull = 0;
int lastMinute = -1;  // minute currently shown on the display

// ---------------------------------------------------------------- helpers

// Swatch .beats (0..999) for a UTC epoch. BMT = UTC+1.
int beatsFromEpoch(time_t epoch) {
  long secOfDayUtc = (long)(epoch % 86400);
  long bmt = (secOfDayUtc + 3600) % 86400;
  return (int)(bmt / 86.4) % 1000;
}

// WMO weather interpretation code -> short text (fits 24px font, <= 30 chars)
const char *weatherText(int c) {
  switch (c) {
    case 0:  return "Clear sky";
    case 1:  return "Mostly clear";
    case 2:  return "Partly cloudy";
    case 3:  return "Overcast";
    case 45: case 48: return "Fog";
    case 51: case 53: case 55: return "Drizzle";
    case 56: case 57: return "Freezing drizzle";
    case 61: return "Light rain";
    case 63: return "Rain";
    case 65: return "Heavy rain";
    case 66: case 67: return "Freezing rain";
    case 71: return "Light snow";
    case 73: return "Snow";
    case 75: return "Heavy snow";
    case 77: return "Snow grains";
    case 80: case 81: return "Rain showers";
    case 82: return "Violent showers";
    case 85: case 86: return "Snow showers";
    case 95: return "Thunderstorm";
    case 96: case 99: return "Thunderstorm, hail";
    default: return "Unknown";
  }
}

bool connectWiFi(uint32_t timeoutMs = 20000) {
  if (WiFi.status() == WL_CONNECTED) return true;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < timeoutMs) {
    delay(250);
  }
  Serial.println(WiFi.status() == WL_CONNECTED ? "WiFi connected" : "WiFi failed");
  return WiFi.status() == WL_CONNECTED;
}

bool timeIsSet() { return time(nullptr) > 1700000000; }  // after Nov 2023

void syncTime() {
  configTzTime(TZ_INFO, "pool.ntp.org", "time.nist.gov", "time.google.com");
  uint32_t start = millis();
  while (!timeIsSet() && millis() - start < 15000) delay(250);
  Serial.println(timeIsSet() ? "NTP synced" : "NTP failed");
}

bool fetchWeather() {
  if (!connectWiFi()) return false;

  char url[400];
  snprintf(url, sizeof(url),
    "https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f"
    "&current=temperature_2m,relative_humidity_2m,weather_code,wind_speed_10m"
    "&daily=temperature_2m_max,temperature_2m_min&forecast_days=1&timezone=auto"
    "%s",
    LATITUDE, LONGITUDE,
    USE_FAHRENHEIT ? "&temperature_unit=fahrenheit&wind_speed_unit=mph" : "");

  WiFiClientSecure client;
  client.setInsecure();  // public weather data; skips certificate pinning
  HTTPClient http;
  http.setTimeout(10000);
  if (!http.begin(client, url)) return false;
  int code = http.GET();
  String body = (code == 200) ? http.getString() : String();
  http.end();
  if (code != 200) {
    Serial.printf("Weather HTTP %d\n", code);
    return false;
  }

  JSONVar j = JSON.parse(body);
  if (JSON.typeof(j) == "undefined") {
    Serial.println("Weather JSON parse failed");
    return false;
  }
  weather.temp     = (double)j["current"]["temperature_2m"];
  weather.humidity = (int)j["current"]["relative_humidity_2m"];
  weather.code     = (int)j["current"]["weather_code"];
  weather.wind     = (double)j["current"]["wind_speed_10m"];
  weather.hi       = (double)j["daily"]["temperature_2m_max"][0];
  weather.lo       = (double)j["daily"]["temperature_2m_min"][0];
  weather.valid    = true;
  time(&weather.fetchedAt);
  Serial.printf("Weather: %.1f, code %d\n", weather.temp, weather.code);
  return true;
}

// ---------------------------------------------------------------- drawing

void drawFrame() {
  Paint_Clear(WHITE);

  time_t now;
  time(&now);
  struct tm lt;
  localtime_r(&now, &lt);
  char buf[48];

  // --- Local time (top left)
  snprintf(buf, sizeof(buf), "%02d:%02d", lt.tm_hour, lt.tm_min);
  EPD_ShowString(12, 6, buf, 96, BLACK);
  strftime(buf, sizeof(buf), "%Z", &lt);
  EPD_ShowString(258, 14, buf, 24, BLACK);

  // --- Internet time (top right)
  int beats = beatsFromEpoch(now);
  snprintf(buf, sizeof(buf), "@%03d", beats);
  EPD_ShowString(420, 6, buf, 96, BLACK);
  EPD_ShowString(624, 44, ".beats", 48, BLACK);
  EPD_ShowString(624, 96, "BMT = UTC+1", 12, BLACK);

  EPD_DrawLine(0, 112, 791, 112, BLACK);
  EPD_DrawLine(404, 0, 404, 271, BLACK);

  // --- Date (bottom left)
  static const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                               "Thursday", "Friday", "Saturday"};
  static const char *months[] = {"January", "February", "March", "April", "May",
                                 "June", "July", "August", "September",
                                 "October", "November", "December"};
  EPD_ShowString(12, 124, days[lt.tm_wday], 48, BLACK);
  snprintf(buf, sizeof(buf), "%d %s %d", lt.tm_mday, months[lt.tm_mon], lt.tm_year + 1900);
  EPD_ShowString(12, 178, buf, 24, BLACK);

  // --- .beats day progress bar (1000 beats, tick every 100)
  const int bx = 12, by = 218, bw = 370, bh = 18;
  EPD_DrawRectangle(bx, by, bx + bw, by + bh, BLACK, 0);
  EPD_DrawRectangle(bx, by, bx + (bw * beats) / 1000, by + bh, BLACK, 1);
  for (int i = 1; i < 10; i++) {
    int tx = bx + (bw * i) / 10;
    EPD_DrawLine(tx, by + bh, tx, by + bh + 5, BLACK);
  }
  EPD_ShowString(bx, 246, "@000", 12, BLACK);
  EPD_ShowString(bx + bw - 24, 246, "@999", 12, BLACK);

  // --- Weather (bottom right)
  const int wx = 416;
  if (!weather.valid) {
    EPD_ShowString(wx, 124, "Weather unavailable", 24, BLACK);
  } else {
    EPD_ShowString(wx, 124, weatherText(weather.code), 24, BLACK);

    snprintf(buf, sizeof(buf), "%d", (int)lroundf(weather.temp));
    EPD_ShowString(wx, 152, buf, 96, BLACK);
    int ux = wx + strlen(buf) * 48 + 4;
    EPD_DrawCircle(ux + 6, 160, 5, BLACK, 0);  // degree sign
    EPD_ShowString(ux + 16, 152, USE_FAHRENHEIT ? "F" : "C", 48, BLACK);

    const int sx = 624;
    snprintf(buf, sizeof(buf), "Hi %d Lo %d", (int)lroundf(weather.hi), (int)lroundf(weather.lo));
    EPD_ShowString(sx, 156, buf, 24, BLACK);
    snprintf(buf, sizeof(buf), "Hum %d%%", weather.humidity);
    EPD_ShowString(sx, 184, buf, 24, BLACK);
    snprintf(buf, sizeof(buf), "Wind %d %s", (int)lroundf(weather.wind), USE_FAHRENHEIT ? "mph" : "km/h");
    EPD_ShowString(sx, 212, buf, 24, BLACK);

    struct tm wt;
    localtime_r(&weather.fetchedAt, &wt);
    snprintf(buf, sizeof(buf), "updated %02d:%02d", wt.tm_hour, wt.tm_min);
    EPD_ShowString(wx, 252, buf, 12, BLACK);
  }
}

void fullClear() {
  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_Update();
  EPD_Clear_R26A6H();  // prime the 0x26 RAM so partial updates don't flicker
}

void refreshClock() {
  drawFrame();
  EPD_Display(ImageBW);
  EPD_PartUpdate();
}

// ---------------------------------------------------------------- Arduino

void setup() {
  Serial.begin(115200);

  pinMode(7, OUTPUT);       // screen power
  digitalWrite(7, HIGH);

  EPD_GPIOInit();
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE);

  fullClear();

  if (connectWiFi()) {
    syncTime();
    fetchWeather();
  }
  lastClock = lastWeather = lastFull = millis();

  refreshClock();
  time_t now;
  time(&now);
  struct tm lt;
  localtime_r(&now, &lt);
  lastMinute = lt.tm_min;
}

void loop() {
  unsigned long ms = millis();

  // Refresh at the top of each minute (falls back to the interval if no time).
  time_t now;
  time(&now);
  struct tm lt;
  localtime_r(&now, &lt);
  bool minuteTick = timeIsSet() ? (lt.tm_min != lastMinute) : (ms - lastClock >= CLOCK_REFRESH_MS);

  if (minuteTick) {
    lastMinute = lt.tm_min;
    lastClock = ms;

    if (!timeIsSet() && connectWiFi()) syncTime();

    if (ms - lastWeather >= WEATHER_REFRESH_MS) {
      // On failure keep the last reading and retry in a minute.
      if (fetchWeather()) lastWeather = ms;
      else lastWeather = ms - WEATHER_REFRESH_MS + 60000UL;
    }
    if (ms - lastFull >= FULL_REFRESH_MS) {
      fullClear();
      lastFull = ms;
    }
    refreshClock();
  }
  delay(500);
}
