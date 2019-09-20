#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO0 10
#define DIO1 11
#define DIO2 12
#define DIO3 13

#define players 4

int player_score[players] = {2500, 2500, 2500, 2500};
int current_state[players * 2] = {0, 0, 0, 0, 0, 0, 0, 0};
int last_state[players * 2] = {0, 0, 0, 0, 0, 0, 0, 0};
int buttonPins[players * 2] = {6, 7, 8, 9, A1, A2, A3, A4};

TM1637Display display0(CLK, DIO0);
TM1637Display display1(CLK, DIO1);
TM1637Display display2(CLK, DIO2);
TM1637Display display3(CLK, DIO3);

void setup()
{
  for (int i = 0; i < players * 2; i++) {
    pinMode( buttonPins[i] , INPUT_PULLUP );
  }
  display0.setBrightness(1);
  display1.setBrightness(1);
  display2.setBrightness(1);
  display3.setBrightness(1);
  display0.showNumberDec(player_score[0], true, 4, 0);
  display1.showNumberDec(player_score[1], true, 4, 0);
  display2.showNumberDec(player_score[2], true, 4, 0);
  display3.showNumberDec(player_score[3], true, 4, 0);

  Serial.begin(9600);

}

void loop()
{
  Serial.println( current_state[0], DEC);
  Serial.println( current_state[2], DEC);
  Serial.println( current_state[4], DEC);
  Serial.println( current_state[6], DEC);
  for (int i = 0; i < players * 2; i++) {
    current_state[i] = digitalRead( buttonPins[i]);
    if (current_state[i] != last_state[i]) {
      if (current_state[i] == LOW) {
        if (i % 2 == 0) {
          player_score[i / 2] += 100;
        } else {
          player_score[i / 2] -= 100;
        }
      }

      delay(50);
    }

    last_state[i] = current_state[i];
  }


  display0.showNumberDec(player_score[0], true, 4, 0);
  display1.showNumberDec(player_score[1], true, 4, 0);
  display2.showNumberDec(player_score[2], true, 4, 0);
  display3.showNumberDec(player_score[3], true, 4, 0);


}
