#include <Keyboard.h>

int changeMode = 0;
int Mode = 3;
bool isCopyMode = true;



int shoulddo = 0;
void setup() {
  pinMode(LED_BUILTIN_TX,OUTPUT);
  pinMode(LED_BUILTIN_RX,OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {

  ModeEvent();
  KeysPress();
}

void OnLED(int pin){
  digitalWrite(pin,HIGH);
}
void OffLED(int pin){
  digitalWrite(pin,LOW);
}



void KeysPress(){
  if(digitalRead(2) == LOW){
    if(isCopyMode){
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
    }else{
      Keyboard.press('x');
    }
    
    Modes(3,true);
    
  }else{
    if(isCopyMode){
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release('v');
    }else{
      Keyboard.release('x');
    }
    Modes(3,false);
    
  }
  if(digitalRead(4) == LOW){
    if(isCopyMode){
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
    }else{
      Keyboard.press('z');
    }
    Modes(5,true);
  }else{
    if(isCopyMode){
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release('c');
    }else{
      Keyboard.release('z');
    }
    Modes(5,false);
  }
  if(digitalRead(4) == LOW && digitalRead(2) == LOW){
    shoulddo = shoulddo + 1;
    Serial.println(shoulddo);
    delay(0.02f);
    Modes(5,true);
  }else{
    shoulddo = 0;
    Modes(5,false);
  }

  if(shoulddo >= 300){
    Keyboard.press('`');
  }else{
    Keyboard.release('`');
    
  }
}


void ModeEvent(){
  /*
  if(digitalRead(2) == LOW && digitalRead(3) == LOW){
    if(changeMode >= 1000){
      
      Mode++;
      if(Mode >= 5){
        Mode = 0;
      }
      changeMode = 0;
      Serial.print("Mode : ");
      Serial.println(Mode);
      digitalWrite(LED_BUILTIN_TX,LOW);
      digitalWrite(LED_BUILTIN_RX,LOW);
      delay(200);
    }
      changeMode++;
      delay(0.5f);
  }else{
    changeMode = 0;
  }*/
}

void Modes(int pin, bool state){
  if(Mode == 0){
      pinMode(LED_BUILTIN_TX,OUTPUT);
      pinMode(LED_BUILTIN_RX,OUTPUT);
      if(state == true){
        digitalWrite(pin,HIGH);
        digitalWrite(LED_BUILTIN_TX,LOW);
        digitalWrite(LED_BUILTIN_RX,LOW);
      }else{
        digitalWrite(pin,LOW);
        digitalWrite(LED_BUILTIN_TX,HIGH);
        digitalWrite(LED_BUILTIN_RX,HIGH);
      }
  }

  if(Mode == 1){
      pinMode(LED_BUILTIN_TX,INPUT);
      pinMode(LED_BUILTIN_RX,INPUT);
      digitalWrite(pin,HIGH);
  }

  if(Mode == 2){
      digitalWrite(pin,LOW);
      pinMode(LED_BUILTIN_TX,INPUT);
      pinMode(LED_BUILTIN_RX,INPUT);
  }

  if(Mode == 3){
      pinMode(LED_BUILTIN_TX,INPUT);
      pinMode(LED_BUILTIN_RX,INPUT);
      if(state == true){
        digitalWrite(pin,HIGH);
      }else{
        digitalWrite(pin,LOW);
      }
  }
}

void FadeLEDON(int pin, int amount, int Delay){
  int brightness = 0;
  analogWrite(pin, brightness);
  while (brightness <= 255){
    KeysPress();
    brightness = brightness + amount;
    analogWrite(pin, brightness);
    delay(Delay);
  }
}

void FadeLEDOFF(int pin, int amount, int Delay){
  int brightness = 255;
  analogWrite(pin, brightness);
  while (brightness >= 0){
    KeysPress();
    brightness = brightness - amount;
    analogWrite(pin, brightness);
    delay(Delay);
  }
  brightness = 0;
  analogWrite(pin, brightness);
}
