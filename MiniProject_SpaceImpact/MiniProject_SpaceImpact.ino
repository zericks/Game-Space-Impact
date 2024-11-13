// Game space attack

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t area[4][15] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

const byte pinBuzzer = 12;  // to pin 12
const byte pinFire = 2;     // Fire button to pin 2
const int pinX = 0;         // joystick x to analog-pin 0
const int pinY = 1;         // joystick y to analog-pin 1
const byte pinPause = 3;    // Pause button to pin 3

bool isPaused = false;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  byte a[8] = {             // rocket atas
    B11100,
    B01111,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  };
  lcd.createChar(0, a);
  byte b[8] = {             // rocket bawah
    B00000,
    B00000,
    B00000,
    B00000,
    B11100,
    B01111,
    B11100,
    B00000,
  };
  lcd.createChar(1, b);
  byte c[8] = {             // rocket di atas sejajar dengan block 
    B11100,
    B01111,
    B11100,
    B00000,
    B11100,
    B10100,
    B11100,
    B00000,
  };
  lcd.createChar(2, c);
  byte d[8] = {             // rocket di bawah sejajar dengan block 
    B11100,
    B10100,
    B11100,
    B00000,
    B11100,
    B01111,
    B11100,
    B00000,
  };
  lcd.createChar(3, d);
  byte e[8] = {             // 2 block sejajar atas bawah
    B11100,
    B10100,
    B11100,
    B00000,
    B11100,
    B10100,
    B11100,
    B00000,
  };
  lcd.createChar(4, e);
  byte f[8] = {             // peluru bawah
    B00000,
    B00000,
    B00000,
    B00000,
    B00100,
    B10010,
    B01000,
    B00000,
  };
  lcd.createChar(5, f);
  byte g[8] = {             // peluru atas sejajar dengan block
    B00100,
    B10010,
    B01000,
    B00000,
    B11100,
    B10100,
    B11100,
    B00000,
  };
  lcd.createChar(6, g);
  byte h[8] = {             // peluru bawah sejajar dengan block
    B11100,
    B10100,
    B11100,
    B00000,
    B00100,
    B10010,
    B01000,
    B00000,
  };
  lcd.createChar(7, h);
  // byte rocket[8] ={
  //   B00000,
  //   B00000,
  //   B00100,
  //   B00100,
  //   B01110,
  //   B11111,
  //   B11011,
  //   B10001,
  // };
  // lcd.createChar(8, rocket);
  lcd.home();
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinFire, INPUT_PULLUP);
  pinMode(pinPause, INPUT_PULLUP);
  // lcd.clear();
  // for (uint8_t y = 0; y < 2; y++) {
  //   for (uint8_t x = 0; x < 16; x++) {
  //     lcd.setCursor(x, y);
  //     lcd.print(char(1));
  //     delay(100);
  //     lcd.setCursor(x, y);
  //     if (y == 0) {
  //       lcd.print(" MINI PROJECT   "[x]);
  //     } else {
  //       lcd.print("     KELOMPOK 1 "[x]);
  //     }
  //   }
  // }
  // delay(1000);
  lcd.clear();
  for (uint8_t y = 0; y < 2; y++) {
    for (uint8_t x = 0; x < 16; x++) {
      lcd.setCursor(x, y);
      lcd.print(char(1));
      delay(100);
      lcd.setCursor(x, y);
      if (y == 0) {
        lcd.print("    SPACE       "[x]);
      } else {
        lcd.print("      IMPACT    "[x]);
      }
    }
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("3 -> LIFE POINTS");
  lcd.setCursor(0, 1);
  lcd.print("9 -> WEAPON LOAD");
  delay(3000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("  PRESS BUTTON  ");
  lcd.setCursor(0, 1);
  lcd.print("    TO START    ");

  while (digitalRead(pinFire) && digitalRead(pinPause)) {
  }

  lcd.clear();
  delay(500);

  for (uint8_t y = 0; y < 4; y++) {
    for (uint8_t x = 0; x < 15; x++) {
      area[y][x] = 0;
    }
  }
  area[0][0] = 1;
  uint8_t sleep = 400;
  uint8_t junkRisk = 10;
  uint8_t fireLoad = 0;
  uint8_t fireConsumption = 9;
  unsigned long score = 0;
  uint8_t life = 3;
  unsigned long count = 0;

  lcd.setCursor(0,0);
  lcd.print(life);
  lcd.setCursor(0, 1);
  lcd.print(fireLoad);

  draw();
  bool gameover = false;

  while (!gameover) {
    // Check for pause button press
    if (!digitalRead(pinPause)) {
      delay(50); // Debounce delay
      if (!digitalRead(pinPause)) {  // Confirm button press
        isPaused = !isPaused;  // Toggle pause state
        if (isPaused) {
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("PAUSED");
          // lcd.setCursor(14, 1);
          // lcd.print(">>");
          // lcd.setCursor(0, 1);
          // lcd.write(byte(8));
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(life);
          lcd.setCursor(0, 1);
          lcd.print(fireLoad);
          draw();
        }
      }
      // Wait for button to be released
      while (!digitalRead(pinPause)) {}  // Wait until button is released
      delay(50); // Small delay for debounce
    }

    // If game is paused, skip the rest of the loop
    if (isPaused) {
      continue;
    }

    for (uint8_t y = 0; y < 4; y++) {
      for (uint8_t x = 15; x > 0; x--) {
        if (area[y][x - 1] == 4) {
          area[y][x - 1] = 0;
          if (x < 15) {
            area[y][x] += 4;
          }
        }
      }
    }

    if (!digitalRead(pinFire) && fireLoad >= fireConsumption) {
      fireLoad -= fireConsumption;
      for (uint8_t y = 0; y < 4; y++) {
        for (uint8_t x = 0; x < 14; x++) {
          if (area[y][x] == 1) {  // raumschiff
            area[y][x + 1] += 4;
          }
        }
      }
    }
    if (fireLoad < 9) {
      fireLoad++;
      lcd.setCursor(0, 1);
      lcd.print(fireLoad);
    }

    draw();
    delay(sleep);

    bool doBreak = false;
    for (uint8_t y = 0; y < 4; y++) {
      for (uint8_t x = 0; x < 15; x++) {
        if (area[y][x] == 1) {
          doBreak = true;
          int dx = analogRead(pinX);
          int dy = analogRead(pinY);
          if (dy > 534 && x > 0) {
            area[y][x] = 0;
            area[y][x - 1] += 1;
          } else if ((dy < 490) && x < 14) {
            if (area[y][x + 1] != 4) {
              area[y][x] = 0;
              area[y][x + 1] += 1;
            }
          } else if (dx < 490 && y > 0) {
            area[y][x] = 0;
            area[y - 1][x] += 1;
          } else if (dx > 534 && y < 3) {
            area[y][x] = 0;
            area[y + 1][x] += 1;
          }
        }
        if (doBreak) {
          break;
        }
      }
      if (doBreak) {
        break;
      }
    }

    for (uint8_t y = 0; y < 4; y++) {
      for (uint8_t x = 0; x < 15; x++) {
        if (area[y][x] == 2) {
          area[y][x] = 0;
          if (x > 0) {
            area[y][x - 1] += 2;
          }
        }
      }
    }

    for (uint8_t y = 0; y < 4; y++) {
      if (random(100) < junkRisk) {
        area[y][14] += 2;
      }
    }

    draw();
    delay(sleep);

    for (uint8_t y = 0; y < 4; y++) {
      for (uint8_t x = 0; x < 15; x++) {
        if (area[y][x] == 3) {  // kollidiertes schiff
          area[y][x] = 1;
          blinkShip();
          life--;
          lcd.setCursor(0, 0);
          lcd.print(life);
          if (life == 0) {
            gameover = true;
            lcd.clear();
            lcd.setCursor(6, 0);
            lcd.print("GAME");
            lcd.setCursor(6, 1);
            lcd.print("OVER");
            for (uint8_t y = 0; y < 2; y++) {
              for (uint8_t x = 0; x < 16; x++) {
                lcd.setCursor(x, y);
                lcd.print(char(1));
                delay(100);
                lcd.setCursor(x, y);
                lcd.print(" ");
              }
            }
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SCORE:");
            lcd.setCursor(0, 1);
            lcd.print(score);
            delay(1000);
            for (uint8_t y = 0; y < 2; y++) {
              for (uint8_t x = 0; x < 16; x++) {
                lcd.setCursor(x, y);
                lcd.print(char(1));
                delay(100);
                lcd.setCursor(x, y);
                lcd.print(" ");
              }
            }
            delay(1000);
          }
        } else if (area[y][x] > 4) {
          for (uint8_t i = 0; i < 10; i++) {
            digitalWrite(pinBuzzer, HIGH);
            delay(3);
            digitalWrite(pinBuzzer, LOW);
            delay(3);
          }
          score += 10;
          area[y][x] -= 6;
        }
      }
    }

    score++;
    count++;

    if (count % 100 == 0) {
      sleep -= 5;
      junkRisk += 3;
      fireConsumption--;
    }
  }
}

void draw() {
  for (uint8_t y = 0; y < 4; y += 2) {
    for (uint8_t x = 0; x < 15; x++) {
      lcd.setCursor(x + 1, y / 2);

      if (area[y][x] == 1) {
        if (area[y + 1][x] == 0) {
          lcd.print(char(0));
        } else if (area[y + 1][x] == 2 || area[y + 1][x] == 6 || area[y + 1][x] == 10) {  // unten hindernis
          lcd.print(char(2));
        }
      } else if (area[y][x] == 2 || area[y][x] == 6 || area[y][x] == 10) {
        if (area[y + 1][x] == 0) {
          lcd.write(0b11011111);
        } else if (area[y + 1][x] == 1) {
          lcd.print(char(3));
        } else if (area[y + 1][x] == 2) {
          lcd.print(char(4));
        } else if (area[y + 1][x] == 4 || area[y + 1][x] == 6 || area[y + 1][x] == 10) {
          lcd.print(char(7));
        }
      } else if (area[y][x] == 4) {
        if (area[y + 1][x] == 0) {
          lcd.write(0b11011110);
        } else if (area[y + 1][x] == 2 || area[y + 1][x] == 6 || area[y + 1][x] == 10) {
          lcd.print(char(6));
        }
      } else if (area[y][x] == 0) {  // oben nichts
        if (area[y + 1][x] == 0) {   // unten nichts
          lcd.print(" ");
        } else if (area[y + 1][x] == 1) {  // unten schiff
          lcd.print(char(1));
        } else if (area[y + 1][x] == 2 || area[y + 1][x] == 6 || area[y + 1][x] == 10) {
          lcd.write(0b10100001);
        } else if (area[y + 1][x] == 4) {
          lcd.print(char(5));
        }
      } else {
        lcd.print(" ");
      }
    }
  }
}

void blinkShip() {
  for (uint8_t y = 0; y < 4; y++) {
    for (uint8_t x = 0; x < 15; x++) {
      if (area[y][x] == 1) {

        for (uint8_t i = 0; i < 3; i++) {
          lcd.setCursor(x + 1, y > 1);
          if (y == 0 || y == 2) {
            if (area[y + 1][x] == 0) {
              lcd.print(" ");
            } else {
              lcd.write(0b10100001);
            }
          } else {
            if (area[y - 1][x] == 0) {
              lcd.print(" ");
            } else {
              lcd.write(0b11011111);
            }
          }
          for (uint8_t i = 0; i < 10; i++) {
            digitalWrite(pinBuzzer, HIGH);
            delay(25);
            digitalWrite(pinBuzzer, LOW);
            delay(5);
          }

          lcd.setCursor(x + 1, y > 1);
          if (y == 0 || y == 2) {
            if (area[y + 1][x] == 0) {
              lcd.print(char(0));
            } else {
              lcd.print(char(2));
            }
          } else {
            if (area[y - 1][x] == 0) {
              lcd.print(char(1));
            } else {
              lcd.print(char(3));
            }
          }
          for (uint8_t i = 0; i < 10; i++) {
            digitalWrite(pinBuzzer, HIGH);
            delay(25);
            digitalWrite(pinBuzzer, LOW);
            delay(5);
          }
        }
      }
    }
  }
}