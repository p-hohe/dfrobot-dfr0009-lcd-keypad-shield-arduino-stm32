#include <LiquidCrystal.h>

// DFRobot/DRF0009 LCD Keypad Shield Pins:
// RS=8, EN=9, D4=4, D5=5, D6=6, D7=7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int buttonPin = A0;

// Button-Namen als Enum
enum Button {
  BTN_RIGHT,
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_SELECT,
  BTN_NONE
};

// Liest A0 und gibt Button zurück
Button readButton(int adc) {
  if (adc < 60)   return BTN_RIGHT;
  if (adc < 250)  return BTN_UP;
  if (adc < 450)  return BTN_DOWN;
  if (adc < 650)  return BTN_LEFT;
  if (adc < 850)  return BTN_SELECT;
  return BTN_NONE;
}

const char* buttonToText(Button b) {
  switch (b) {
    case BTN_RIGHT:  return "RIGHT ";
    case BTN_UP:     return "UP    ";
    case BTN_DOWN:   return "DOWN  ";
    case BTN_LEFT:   return "LEFT  ";
    case BTN_SELECT: return "SELECT";
    default:         return "NONE  ";
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DRF0009 Buttons");
  lcd.setCursor(0, 1);
  lcd.print("ADC: ---- NONE");
  delay(1000);
  lcd.clear();
}

void loop() {
  int adc = analogRead(buttonPin);
  Button b = readButton(adc);

  // Zeile 1: ADC-Wert
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  if (adc < 1000) lcd.print(" ");
  if (adc < 100)  lcd.print(" ");
  if (adc < 10)   lcd.print(" ");
  lcd.print(adc);
  lcd.print("     "); // Rest überschreiben

  // Zeile 2: Button-Name
  lcd.setCursor(0, 1);
  lcd.print("Button: ");
  lcd.print(buttonToText(b));
  lcd.print("   "); // Rest überschreiben

  delay(100);
}