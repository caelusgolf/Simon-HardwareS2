#include <elapsedMillis.h>

#define YELLOW_BUTTON_PIN 2
#define BLUE_BUTTON_PIN 3
#define GREEN_BUTTON_PIN 4
#define RED_BUTTON_PIN 5

#define YELLOW_LED_PIN 10
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12
#define RED_LED_PIN 13

#define P1_LED_PIN 8
#define P2_LED_PIN 9

int yellowButtonState;
int blueButtonState;
int greenButtonState;
int redButtonState;


bool hasLost;
int isPlaying;

int player = 1;

int ledArray[32];
int currentLimit;
int currentIndex;




int buzzer = 6;
int volume = 0;
int fadeAmount = 100;

int duty_cycle = 127;

int setting = 0x01;


void setup() {
  hasLost = false;
  isPlaying = 0;
  player = 1;

  currentIndex = 0;
  currentLimit = 0;

  pinMode(YELLOW_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  pinMode(P1_LED_PIN, OUTPUT);
  pinMode(P2_LED_PIN, OUTPUT);
  
  digitalWrite(YELLOW_LED_PIN, LOW);   
  digitalWrite(BLUE_LED_PIN, LOW); 
  digitalWrite(GREEN_LED_PIN, LOW); 
  digitalWrite(RED_LED_PIN, LOW);

  digitalWrite(P1_LED_PIN, LOW);
  digitalWrite(P2_LED_PIN, LOW);

  Serial.begin(9600);



  //TCCR2B = TCCR2B & Ob11111000 | setting;
  pinMode(buzzer, OUTPUT);
}

void loop() {
    yellowButtonState = digitalRead(YELLOW_BUTTON_PIN);
  blueButtonState = digitalRead(BLUE_BUTTON_PIN);
  greenButtonState = digitalRead(GREEN_BUTTON_PIN);
  redButtonState = digitalRead(RED_BUTTON_PIN);
/*
  if (yellowButtonState == LOW) {
     tone(buzzer, 262);
  }
  else if (blueButtonState == LOW) {
    tone(buzzer, 330);
  }
  else if (greenButtonState == LOW) {
    tone(buzzer, 392);
  }
  else if (redButtonState == LOW) {
    tone(buzzer, 493);
  }
  else {
    noTone(buzzer);
  }*/

  /*analogWrite(buzzer, volume);
  volume = volume + fadeAmount;

  if (volume <= 0 || volume >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(100);*/
  
  yellowButtonState = digitalRead(YELLOW_BUTTON_PIN);
  blueButtonState = digitalRead(BLUE_BUTTON_PIN);
  greenButtonState = digitalRead(GREEN_BUTTON_PIN);
  redButtonState = digitalRead(RED_BUTTON_PIN);

  Serial.print("currentIndex ");
  Serial.println(currentIndex);
  Serial.print("currentLimit ");
  Serial.println(currentLimit);
  Serial.print("isPlaying ");
  Serial.println(isPlaying);
  Serial.print("player ");
  Serial.println(player);

  if(!hasLost) {
  if (isPlaying == 0) {
    if (player == 1) {
      displayP1();
      isPlaying = 1;
    }
    else if (player == 2) {
      displayP2();
      isPlaying = 1;
    }

    for (int i = 0; i < currentLimit; i++) {
      Serial.print(ledArray[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
  else if (isPlaying == 1) {
    if (currentIndex < currentLimit && !hasLost) {
      if (yellowButtonState == LOW) {
        displayYellow();
        hasLost = compare(YELLOW_LED_PIN, currentIndex);
      }
      else if (blueButtonState == LOW) {
        displayBlue();
        hasLost = compare(BLUE_LED_PIN, currentIndex);
      }
      else if (greenButtonState == LOW) {
        displayGreen();
        hasLost = compare(GREEN_LED_PIN, currentIndex);
      }
      else if (redButtonState == LOW) {
        displayRed();
        hasLost = compare(RED_LED_PIN, currentIndex);
      }
    }
    else if (currentIndex == currentLimit && !hasLost) {
      if (yellowButtonState == LOW) {
      increment(YELLOW_LED_PIN);
      displayYellow();
      if (player == 1) {
        player = 2;
      }
      else {
        player = 1;
      }
      isPlaying = 0;
      currentIndex = 0;
    }
    else if (blueButtonState == LOW) {
      increment(BLUE_LED_PIN);
      displayBlue();
      if (player == 1) {
        player = 2;
      }
      else {
        player = 1;
      }
      isPlaying = 0;
      currentIndex = 0;
    }
    else if (greenButtonState == LOW) {
      increment(GREEN_LED_PIN);
      displayGreen();
      if (player == 1) {
        player = 2;
      }
      else {
        player = 1;
      }
      isPlaying = 0;
      currentIndex = 0;
    }
    else if (redButtonState == LOW) {
      increment(RED_LED_PIN);
      displayRed();
      if (player == 1) {
        player = 2;
      }
      else {
        player = 1;
      }
      isPlaying = 0;
      currentIndex = 0;
    }
   }
  }
    
  }
  else {
    displayLost();
  }
}

void increment(int ledID) {
  ledArray[currentLimit] = ledID;
  currentLimit++;
}

bool compare(int ledID, int index) {
  if (ledID == ledArray[index]) {
    currentIndex++;
    return false;
  }
  return true;
}

void displayYellow() {
  delay(200);
  tone(buzzer, 261);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(400);
  noTone(buzzer);
  delay(400);
  digitalWrite(YELLOW_LED_PIN, LOW);
}

void displayBlue() {
  delay(200);
  tone(buzzer, 293);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(400);
  noTone(buzzer);
  delay(400);
  digitalWrite(BLUE_LED_PIN, LOW); 
}

void displayGreen() {
  delay(200);
  tone(buzzer, 329);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(400);
  noTone(buzzer);
  delay(400);
  digitalWrite(GREEN_LED_PIN, LOW); 
}

void displayRed() {
  delay(200);
  tone(buzzer, 349);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(400);
  noTone(buzzer);
  delay(400);
  digitalWrite(RED_LED_PIN, LOW);

}

void displayP1() {
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(200);

  digitalWrite(P1_LED_PIN, HIGH);
  digitalWrite(P2_LED_PIN, LOW);
}

void displayP2() {
    digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  delay(200);
  
  digitalWrite(P1_LED_PIN, LOW);
  digitalWrite(P2_LED_PIN, HIGH);
}

void displayLost() {
  digitalWrite(RED_LED_PIN, HIGH);
  
  tone(buzzer, 349);
  delay(400);
  noTone(buzzer);
   tone(buzzer, 300);
  delay(400);
    tone(buzzer, 250);
  delay(1000);
  noTone(buzzer);
  
   
  delay(50);
  digitalWrite(RED_LED_PIN, LOW);
  delay(50);
   digitalWrite(RED_LED_PIN, HIGH);
  delay(50);
  digitalWrite(RED_LED_PIN, LOW);
  delay(50);
   digitalWrite(RED_LED_PIN, HIGH);
  delay(50);
  digitalWrite(RED_LED_PIN, LOW);
  delay(50);
   digitalWrite(RED_LED_PIN, HIGH);
  delay(50);
  digitalWrite(RED_LED_PIN, LOW);
  delay(50);

  delay(99999999999999);
  
  
}
