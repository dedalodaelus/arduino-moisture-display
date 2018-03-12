#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>
#include <avr/wdt.h>
#include <RotaryEncoder.h>
#include "pin_def.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE,
		PIN_RESET);
DHT dht(DHTPIN, DHTTYPE);
float h = 0;
float t = 0;
String total;

#define read_dht_time 1000
unsigned long prev_ms_dht = 0;

int led_state = LOW;

#define alive_on_time 50
#define alive_cycle_time 5000
unsigned long prev_ms_alive = 0;

#define watchdog_time 250
unsigned long prev_ms_wd = 0;

#define display_time 500
unsigned long prev_ms_display = 0;

unsigned long timer = 0;
#define max_inconsistent 10
unsigned int inconsistent_cnt = max_inconsistent;
bool na_display = false;
bool consistant = true;

void setup() {
	wdt_disable();
	dht.begin();
	display.begin();
	// init done

	display.clearDisplay();   // clears the screen and buffer
	// you can change the contrast around to adapt the display
	// for the best viewing!
	display.setContrast(50);
	display.setTextSize(2);

	display.setTextColor(BLACK);
	pinMode(led_id, OUTPUT);
	wdt_enable(WDTO_4S);
}

void loop() {
	timer = millis();

	if (timer - prev_ms_wd >= watchdog_time) {
		wdt_reset();
		prev_ms_wd = timer;
	}

	if (led_state == HIGH && (timer - prev_ms_alive >= alive_on_time)) {
		led_state = LOW;
		prev_ms_alive = timer;
		digitalWrite(led_id, led_state);
	}

	if (led_state == LOW
			&& (timer - prev_ms_alive >= alive_cycle_time - alive_on_time)) {
		led_state = HIGH;
		prev_ms_alive = timer;
		digitalWrite(led_id, led_state);
	}

	if (timer - prev_ms_dht >= read_dht_time) {
		prev_ms_dht = timer;
		// Read humidity
		h = dht.readHumidity();
		// Read temperature as Celsius (the default)
		t = dht.readTemperature();

		if (isnan(h) || isnan(t)) {
			consistant = false;
			inconsistent_cnt--;
			if (inconsistent_cnt == 0) {
				na_display = true;
			}
		} else {
			consistant = true;
			na_display = false;
			inconsistent_cnt = max_inconsistent;
		}
	}

	if (timer - prev_ms_display >= display_time) {
		prev_ms_display = timer;
		if (consistant) {
			display.clearDisplay();
			display.setCursor(0, 0);
			total = "t: " + String(t, 0) + "C";
			display.println(total.c_str());

			total = "h: " + String(h, 0) + "%";
			display.setCursor(0, 20);
			display.println(total.c_str());
			display.display();
		} else {
			if (na_display) {
				display.clearDisplay();
				display.setCursor(0, 0);
				total = "t:Error";
				display.println(total.c_str());

				total = "h:Error";
				display.setCursor(0, 20);
				display.println(total.c_str());
				display.display();
			}
		}
	}

}
