 /**************************************************************************
 * SINDEN LIGHT GUN PEDAL FOR PLAYING TIME CRISIS AND OTHER ARCADE GAMES
 * 
 * Description:  
 * Emulates and XBOX controller button press for custom pedals developed for Arcade light gun games.
 * It includes a tri-colour LED for status updates.
 * 
 * Note: Code is designed for an Audrino Micro, it could be used with other Arduinos which have a USB controller (such as Leonardos)
 * See refence sites for more detailed information
 * 
 * Main reference sites:- 
 * https://github.com/dmadison/ArduinoXInput/blob/master/src/XInput.h
 **************************************************************************/
 
#include <XInput.h>

// Input Pins;
const uint8_t Pin_ButtonL3  = 2;  
const uint8_t Pin_ButtonR3  = 3;  
const uint8_t Pin_ButtonLB  = 4;   
const uint8_t Pin_ButtonRB  = 7;  

// Output Pins
int red_light_pin= 9;
int green_light_pin = 6;
int blue_light_pin = 5;
const uint8_t Pin_LED = LED_BUILTIN;    

void setup() {

  // Set LED pins
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  // Set input pin modes
  pinMode(Pin_ButtonLB, INPUT_PULLUP);
  pinMode(Pin_ButtonRB, INPUT_PULLUP);
  pinMode(Pin_ButtonL3, INPUT_PULLUP);
  pinMode(Pin_ButtonR3, INPUT_PULLUP);
 
  // Set output pin mode
  pinMode(Pin_LED, OUTPUT);
  digitalWrite(Pin_LED, HIGH);  // Turn 'off'
 
  // Setup library
  XInput.begin();

  // TEMP LED TEST
  for (int i = 0; i < 5; i++) {
  RGB_color(255, 0, 0); // Red
  delay(300);
  RGB_color(0, 255, 0); // Green
  delay(300);
  RGB_color(0, 0, 255); // Blue
  delay(300);
  }
  RGB_color(0, 0, 255); 
}
 
void loop() {

  //Read pin states
  boolean pressLB = !digitalRead(Pin_ButtonLB);
  boolean pressRB = !digitalRead(Pin_ButtonRB);
  boolean pressL3 = !digitalRead(Pin_ButtonL3);
  boolean pressR3 = !digitalRead(Pin_ButtonR3);
  
  // Set button and trigger states
  XInput.setButton(BUTTON_LB, pressLB);
  XInput.setButton(BUTTON_RB, pressRB);
  XInput.setButton(BUTTON_L3, pressL3);
  XInput.setButton(BUTTON_R3, pressR3);

  if (pressLB || pressRB || pressL3 || pressR3) {
    RGB_color(0, 255, 0);
  } else {
    RGB_color(0, 0, 255);
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, 255-red_light_value);
  analogWrite(green_light_pin, 255-green_light_value);
  analogWrite(blue_light_pin, 255-blue_light_value);
}
