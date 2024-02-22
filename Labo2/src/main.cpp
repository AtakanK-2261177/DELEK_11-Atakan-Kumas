#include <Arduino.h>
// 1) Import libraries
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Constructor for the TFT library

// 2) Define constants
#define TFT_GREY 0x5AEB // New colour
#define BTN_PIN_1 2
#define LED_PIN_1 17
#define LED_PIN_2 32

// 3) Init vareables
volatile bool stateLed1 = true;
bool stateLed2 = true;
volatile unsigned long last_switch_time = 0l;


void printTitle() {
  // Print title
  tft.fillScreen(TFT_BLACK);   //Fill screen with random colour
  tft.setCursor(0, 0, 4);   //(cursor at 0,0; font 4, println autosets the cursor on the next line)
  tft.setTextColor(TFT_BLACK, TFT_YELLOW); // Textcolor, BackgroundColor; independent of the fillscreen
  tft.println("- Lab 2 -");    //Print on cursorpos 0,0
}

void displayStateButton1(bool value) {
  // Print aantal
  tft.setCursor(0, 50, 4);   //(cursor at 0,0; font 4, println autosets the cursor on the next line)
  tft.setTextColor(TFT_GREEN, TFT_BLACK); // Green Text with black background
  // Test some print formatting functions
  tft.print("stateButton1 = "); tft.println(value);           // Print floating point number
}

//btn1Handler changed into a short interrupt function (IRS). No print-functions en digitalwrite/read functions make sure the code runs swiftly.
void IRAM_ATTR btn1Handler() {
  unsigned long switch_time = millis();
  if (switch_time - last_switch_time > 200)
  {
    stateLed1 = !stateLed1;
    last_switch_time = switch_time;
  }
  
}


// 4) The setup
void setup(void) {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);   // setRotation: 1: Screen in landscape
  printTitle();

  pinMode(LED_PIN_1, OUTPUT);
  pinMode(BTN_PIN_1, INPUT_PULLUP);
  attachInterrupt(BTN_PIN_1, btn1Handler, FALLING);
  pinMode(LED_PIN_2, OUTPUT);

  digitalWrite(LED_PIN_1, LOW); // apply the correct output for LED_PIN1
  digitalWrite(LED_PIN_2, LOW);
}

// 5) The main loop
void loop() {
  digitalWrite(LED_PIN_2, HIGH);
  delay(1000);
  digitalWrite(LED_PIN_2, LOW);
  delay(1000);

  digitalWrite(LED_PIN_1, stateLed1);

}


