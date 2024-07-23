#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define LCD_COLUMNS 20
#define LCD_LINES 4
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

#define VERT_PIN A0
#define SEL_PIN 2

const int ledPin = 9;
const int buttonPin = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buzzerPin = 10;

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int alphabetLength = sizeof(alphabet) - 1;

String morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
  "..-", "...-", ".--", "-..-", "-.--", "--.." 
};

int currentLetterIndex = 0;
String selectedString = "";

unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200;

unsigned long lastResetPress = 0;
const unsigned long resetDebounceDelay = 200;

unsigned long lastVertChange = 0;
const unsigned long vertDebounceDelay = 200;

const int dotDuration = 100;
const int dashDuration = 300;
const int charPause = 300;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(VERT_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  updateLCD();
}

void loop() {
  checkVerticalMovement();
  checkSelectButton();
  checkResetButton();
  checkTranscribeButton();
  checkRemoveButton();
}

void checkVerticalMovement() {
  int vertValue = analogRead(VERT_PIN);
  unsigned long currentMillis = millis();

  if (currentMillis - lastVertChange > vertDebounceDelay) {
    if (vertValue < 400) {
      currentLetterIndex--;
      if (currentLetterIndex < 0) {
        currentLetterIndex = alphabetLength - 1;
      }
      updateLCD();
      lastVertChange = currentMillis;
    } else if (vertValue > 600) {
      currentLetterIndex++;
      if (currentLetterIndex >= alphabetLength) {
        currentLetterIndex = 0;
      }
      updateLCD();
      lastVertChange = currentMillis;
    }
  }
}

void checkSelectButton() {
  if (digitalRead(SEL_PIN) == LOW) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPress > debounceDelay) {
      selectedString += alphabet[currentLetterIndex];
      updateLCD();
      lastButtonPress = currentMillis;
    }
  }
}

void checkResetButton() {
  if (digitalRead(buttonPin) == LOW) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastResetPress > resetDebounceDelay) {
      selectedString = "";
      updateLCD();
      lastResetPress = currentMillis;
    }
  }
}

void checkTranscribeButton(){
  if(digitalRead(buttonPin2) == LOW){
    unsigned long currentMillis = millis();
    if (currentMillis - lastResetPress > resetDebounceDelay) {
      transcribeString();
      lastResetPress = currentMillis;
    }
  }
}

void checkRemoveButton() {
  if(digitalRead(buttonPin3) == LOW) {
    
    unsigned long currentMillis = millis();
    if (currentMillis - lastResetPress > resetDebounceDelay) {
      if (selectedString.length() > 0) {
        selectedString.remove(selectedString.length() - 1);
        updateLCD();
      }
      lastResetPress = currentMillis;
    }
  }
}

void transcribeString() {
  for (int i = 0; i < selectedString.length(); i++) {
    char letter = selectedString[i];
    int index = letter - 'A';
    if (index >= 0 && index < alphabetLength) {
      String morse = morseCode[index];
      for (int j = 0; j < morse.length(); j++) {
        if (morse[j] == '.') {
          tone(buzzerPin, 1000, dotDuration);
          delay(dotDuration);
        } else if (morse[j] == '-') {
          tone(buzzerPin, 1000, dashDuration);
          delay(dashDuration);
        }
        delay(dotDuration);
      }
      delay(charPause);
    }
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MorseCode Translator");
  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(alphabet[currentLetterIndex]);
  lcd.setCursor(0, 2);
  lcd.print("String: ");
  lcd.print(selectedString);
  lcd.setCursor(0, 3);
  lcd.print("                    ");
}
