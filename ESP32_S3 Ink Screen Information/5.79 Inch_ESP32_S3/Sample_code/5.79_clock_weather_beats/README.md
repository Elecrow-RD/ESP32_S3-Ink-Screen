# 5.79" Clock + Weather + .beats

Sketch for the CrowPanel ESP32-S3 5.79" (792x272) e-ink display.

- **Local time** from NTP, with DST handled by a POSIX TZ string.
- **Swatch Internet Time (.beats)**: 1000 beats per day, based on BMT (UTC+1), so `@000` is midnight in Biel and the number is the same everywhere. A progress bar shows how much of the beat-day has elapsed.
- **Weather** from [Open-Meteo](https://open-meteo.com) (no API key): condition, temperature, hi/lo, humidity, wind.

## Setup
1. Edit `config.h`: WiFi credentials, latitude/longitude, `TZ_INFO`, units.
2. Arduino IDE: board ESP32S3 Dev Module, install `Arduino_JSON` (copy from the repo's `libraries` folder).
3. Open `5.79_clock_weather_beats.ino` and upload.

## Refresh behaviour
- Partial refresh at the top of every minute (the display tracks the clock).
- Weather re-fetched every 15 min (retries after 1 min on failure and keeps the last reading).
- Full clear every 30 min to remove ghosting. All three intervals are in `config.h`.

Note: weather requests use HTTPS with certificate verification disabled (`setInsecure()`); the data is public.
