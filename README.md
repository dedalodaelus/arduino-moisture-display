# arduino-moisture-display
Arduino simple project that displays moisture and temperature on LCD

## BOM
- Seeeduino 3.0 (Arduino Diecimila compatible)
- DHT11 Moisture and temperature sensor
- Nokia 5110 LCD
- Rotary enconder with press button

## Description
It's a simple proyect where the temperature and ambient moisture is shown on LCD display
### Highlights
- The LCD backlight is controlled by rotary encoder (10 steps)
- The temperature is shown in Celsius and the moisture is shown in %
- The watchdog feature is enabled in order to avoid freezing
- The internal led is used as keep alive every 5 seconds
- If the sensor is missing or malfunction more than 10 times, the display show error

