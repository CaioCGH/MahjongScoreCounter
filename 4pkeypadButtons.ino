#include <Arduino.h>
#include <TM1637Display.h>
#include <Keypad.h>

// Module connection pins (Digital Pins)
#define CLK A5
#define DIO0 A4
#define DIO1 A3
#define DIO2 A2
#define DIO3 A1

#define WARN 10
#define ERR 11

#define players 4

int player_score[players] = {2500, 2500, 2500, 2500};
int player_quanta[players] = {100, 100, 100, 100};

TM1637Display display0(CLK, DIO0);
TM1637Display display1(CLK, DIO1);
TM1637Display display2(CLK, DIO2);
TM1637Display display3(CLK, DIO3);

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  display0.setBrightness(1);
  display1.setBrightness(1);
  display2.setBrightness(1);
  display3.setBrightness(1);
  display0.showNumberDec(player_score[0], true, 4, 0);
  display1.showNumberDec(player_score[1], true, 4, 0);
  display2.showNumberDec(player_score[2], true, 4, 0);
  display3.showNumberDec(player_score[3], true, 4, 0);
  pinMode(WARN, OUTPUT);
  pinMode(ERR, OUTPUT);

  Serial.begin(9600);

}

void loop()
{

  display0.showNumberDec(player_score[0], true, 4, 0);
  display1.showNumberDec(player_score[1], true, 4, 0);
  display2.showNumberDec(player_score[2], true, 4, 0);
  display3.showNumberDec(player_score[3], true, 4, 0);
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    switch (customKey) {
      case 'C':
        swap_quanta(0);
        break;
      case '3':
        swap_quanta(1);
        break;
      case '4':
        swap_quanta(2);
        break;
      case '0':
        swap_quanta(3);
        break;
      case 'B':
        player_score[0] += player_quanta[0];
        break;
      case 'A':
        player_score[0] -= player_quanta[0];
        break;
      case '2':
        player_score[1] += player_quanta[1];
        break;
      case '1':
        player_score[1] -= player_quanta[1];
        break;
      case '7':
        player_score[2] += player_quanta[2];
        break;
      case '*':
        player_score[2] -= player_quanta[2];
        break;
      case '#':
        player_score[3] += player_quanta[3];
        break;
      case 'D':
        player_score[3] -= player_quanta[3];
        break;
      case '6':
        display1.showNumberDec(abs(player_score[0] - player_score[1]), true, 4, 0);
        display2.showNumberDec(abs(player_score[0] - player_score[2]), true, 4, 0);
        display3.showNumberDec(abs(player_score[0] - player_score[3]), true, 4, 0);
        delay(3000);
        break;
      case '5':
        display0.showNumberDec(abs(player_score[1] - player_score[0]), true, 4, 0);
        display2.showNumberDec(abs(player_score[1] - player_score[2]), true, 4, 0);
        display3.showNumberDec(abs(player_score[1] - player_score[3]), true, 4, 0);
        delay(3000);
        break;
      case '8':
        display0.showNumberDec(abs(player_score[2] - player_score[0]), true, 4, 0);
        display1.showNumberDec(abs(player_score[2] - player_score[1]), true, 4, 0);
        display3.showNumberDec(abs(player_score[2] - player_score[3]), true, 4, 0);
        delay(3000);
        break;
      case '9':
        display0.showNumberDec(abs(player_score[3] - player_score[0]), true, 4, 0);
        display1.showNumberDec(abs(player_score[3] - player_score[1]), true, 4, 0);
        display2.showNumberDec(abs(player_score[3] - player_score[2]), true, 4, 0);
        delay(3000);
        break;
    }
    int total = 0;
    for(int i = 0; i < players; i++){
      total += player_score[i];
    }
    if(total < 10000){
      digitalWrite(WARN, HIGH);
    }
    if(total > 10000 || total < 9600){
      digitalWrite(ERR, HIGH);
    }
    if(total == 10000){
      digitalWrite(ERR, LOW);
      digitalWrite(WARN, LOW);
    }
    
  }
}
void swap_quanta(int player){
  if(player_quanta[player] == 100)
    player_quanta[player] = 10;
  else
    player_quanta[player] = 100;
}
