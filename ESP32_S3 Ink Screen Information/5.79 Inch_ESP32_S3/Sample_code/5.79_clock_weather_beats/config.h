#ifndef _CONFIG_H_
#define _CONFIG_H_

// ---- WiFi ----
#define WIFI_SSID     "your-wifi-name"
#define WIFI_PASSWORD "your-wifi-password"

// ---- Location (weather comes from Open-Meteo: free, no API key) ----
#define LATITUDE   39.1732    // Germantown, MD
#define LONGITUDE -77.2717

// ---- Local time ----
// POSIX TZ string; handles daylight saving automatically.
// Other examples: "PST8PDT,M3.2.0,M11.1.0"  "CET-1CEST,M3.5.0,M10.5.0/3"  "UTC0"
#define TZ_INFO "EST5EDT,M3.2.0,M11.1.0"

// ---- Units ----
#define USE_FAHRENHEIT 1      // 1 = F and mph, 0 = C and km/h

// ---- Refresh timing ----
#define CLOCK_REFRESH_MS    60000UL            // partial refresh each minute
#define WEATHER_REFRESH_MS  (15UL * 60000UL)   // re-fetch weather every 15 min
#define FULL_REFRESH_MS     (30UL * 60000UL)   // full clear to remove ghosting

#endif
