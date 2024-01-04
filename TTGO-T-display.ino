#include <WiFi.h>

#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI ();

#define BUTTON1_GPIO 35
#define BUTTON2_GPIO 0
#define BOUNCING_MS 5 // 1 ms should be enough, takt 5 ms to be on the safe side

void setup () {

    tft.init ();
    tft.setRotation (0); // orientation = portrait
    digitalWrite (TFT_BL, TFT_BACKLIGHT_ON); // turn on back-light

    tft.fillScreen (TFT_BLACK);
    tft.drawRect (0, 0, TFT_WIDTH, TFT_HEIGHT, TFT_GOLD); // max viewable rectangle = 135 x 240

    tft.setCursor (0, 16, 4); // x, y, font size = 4
    tft.setTextColor (TFT_GOLD);
    tft.println (" " + String (TFT_WIDTH) + " x " + String (TFT_HEIGHT)); // 135 x 240

    tft.setTextFont (2); // font 2
    tft.setTextColor (TFT_BROWN);
  
    pinMode (BUTTON1_GPIO, INPUT_PULLUP); // push-button 1
    pinMode (BUTTON2_GPIO, INPUT_PULLUP); // push-button 2
}

void loop () {
  // button debouncing code
 
  static byte button1LastState = digitalRead (BUTTON1_GPIO);
  byte button1NewState;
  static byte button1LastReportedState = button1LastState;
  static unsigned long button1LastChange = millis () - BOUNCING_MS; 
  if ((button1NewState = digitalRead (BUTTON1_GPIO)) != button1LastState) {
      button1LastState = button1NewState;
      button1LastChange = millis ();
  } else {
      if (millis () - button1LastChange >= BOUNCING_MS && button1LastReportedState != button1LastState) {
          tft.println ("   right bt " + String (button1LastState ? "released" : "pressed"));
          button1LastReportedState = button1LastState;
      } else 
          button1LastChange = millis () - BOUNCING_MS; // to prevent anomaly when built-in clock turns arroud after prox. 50 days (anomaly would happen after 25 days)
  }
 
  static byte button2LastState = digitalRead (BUTTON2_GPIO);
  byte button2NewState;
  static byte button2LastReportedState = button2LastState;
  static unsigned long button2LastChange = millis () - BOUNCING_MS; 
  if ((button2NewState = digitalRead (BUTTON2_GPIO)) != button2LastState) {
      button2LastState = button2NewState;
      button2LastChange = millis ();
  } else {
      if (millis () - button2LastChange >= BOUNCING_MS && button2LastReportedState != button2LastState) {
          tft.println (" left bt " + String (button2LastState ? "released" : "pressed"));
          button2LastReportedState = button2LastState;
      } else
          button2LastChange = millis () - BOUNCING_MS; // to prevent anomaly when built-in clock turns arroud after prox. 50 days (anomaly would happen after 25 days)
  }
 
}
