#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int xPin = A0;
const int yPin = A1;
const int xPin2 = A3;
const int yPin2 = A2;
const int swPin = 2;
const int swPin2 = 4;

byte manCharacter[8] = {
  B00100,
  B00100,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B01110
};

byte pointCharacter[8] = {
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011
};

int playerX = 10;
int playerY = 3;
int pointX = 10;
int pointY = 0;
bool pointEaten = false;
int score = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, manCharacter);
  lcd.createChar(1, pointCharacter);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(swPin2, INPUT_PULLUP);
  redraw();
}

void loop() {
  updatePlayer();
  updatePoint();
  checkCollision();
  if (pointEaten) {
    pointEaten = false;
    newPoint();
    redraw();
  }
  
  delay(100);
}

void updatePlayer() {
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  bool selPressed = digitalRead(swPin) == LOW;
  
  if (xVal < 100 && playerX < 19) {
    playerX++;
  } else if (xVal > 900 && playerX > 0) {
    playerX--;
  }
  
  if (yVal > 900 && playerY < 3) {
    playerY++;
  } else if (yVal < 100 && playerY > 0) {
    playerY--;
  }

  if(selPressed){
    playerX = 10;
    playerY = 3;
    score = 0;
  }

  redraw();
}

void updatePoint(){
  int xVal2 = analogRead(xPin2);
  int yVal2 = analogRead(yPin2);
  bool selPressed2 = digitalRead(swPin2) == LOW;

  if (xVal2 < 100 && pointX < 19) {
    pointX++;
  } else if (xVal2 > 900 && pointX > 0) {
    pointX--;
  }
  
  if (yVal2 > 900 && pointY < 3) {
    pointY++;
  } else if (yVal2 < 100 && pointY > 0) {
    pointY--;
  }

  if(selPressed2){
    lcd.clear();
    lcd.print(score);
    delay(200);
  }
}

void redraw() {
  lcd.clear();
  lcd.setCursor(playerX, playerY);
  lcd.write(byte(0));
  lcd.setCursor(pointX, pointY);
  lcd.write(byte(1));
}

void newPoint() {
  pointX = random(0, 19);
  pointY = random(0, 3);
}

void checkCollision() {
  if (playerX == pointX && playerY == pointY) {
    pointEaten = true;
    score++;
    lcd.clear();
    lcd.print("Nice Hit!");
    delay(2000);
  }
}
