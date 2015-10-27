const int demoSwitch = A3;
const int toggleLight = 7;
const int amberButtonLight = 8;
const int blueButtonLight = 3;
const int whiteButtonLight = A2;
const int amberButton = 14;
const int blueButton = 4;
const int whiteButton = A1;
const int greenToggle = A0;
const int blueToggle = 16;
const int yellowToggle = 9;
const int springToggle = 15;
const int guard = 2;
const int rockerLight = 10;
const int yellowButton = 6;
const int copyToggle = 5;

bool blueToggleState;
bool greenToggleState;
bool yellowToggleState;
bool amberButtonState;
bool whiteButtonState;
bool blueButtonState;
bool demoState;

bool blueTogglePrimed = true;
bool demoSwitchPrimed = true;
bool yellowTogglePrimed = true;
bool greenTogglePrimed = true;
bool amberButtonPrimed = true;
bool blueButtonPrimed = true;
bool whiteButtonPrimed = true;

/* 
 *  Modifier Keys:
KEY_LEFT_CTRL   0x80    128
KEY_LEFT_SHIFT  0x81    129
KEY_LEFT_ALT    0x82    130
KEY_LEFT_GUI    0x83    131
KEY_RIGHT_CTRL  0x84    132
KEY_RIGHT_SHIFT 0x85    133
KEY_RIGHT_ALT   0x86    134
KEY_RIGHT_GUI   0x87    135
KEY_UP_ARROW    0xDA    218
KEY_DOWN_ARROW  0xD9    217
KEY_LEFT_ARROW  0xD8    216
KEY_RIGHT_ARROW 0xD7    215
KEY_BACKSPACE   0xB2    178
KEY_TAB         0xB3    179
KEY_RETURN      0xB0    176
KEY_ESC         0xB1    177
KEY_INSERT      0xD1    209
KEY_DELETE      0xD4    212
KEY_PAGE_UP     0xD3    211
KEY_PAGE_DOWN   0xD6    214
KEY_HOME        0xD2    210
KEY_END         0xD5    213
KEY_CAPS_LOCK   0xC1    193
KEY_F1  0xC2    194
KEY_F2  0xC3    195
...
KEY_F12 0xCD    205 
 */

void off(){
    while(digitalRead(guard) == HIGH){}
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(2), off, RISING);
  digitalWrite(2, HIGH);
    
  //pinMode(guard, INPUT_PULLUP);
  pinMode(toggleLight, OUTPUT);
  pinMode(amberButtonLight, OUTPUT);
  pinMode(blueButtonLight, OUTPUT);
  pinMode(whiteButtonLight, OUTPUT);
  pinMode(amberButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(whiteButton, INPUT_PULLUP);
  pinMode(greenToggle, INPUT_PULLUP);
  pinMode(yellowToggle, INPUT_PULLUP);
  pinMode(blueToggle, INPUT_PULLUP);
  pinMode(springToggle, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(copyToggle, INPUT_PULLUP);
  pinMode(demoSwitch, INPUT);
  pinMode(rockerLight, OUTPUT);
  digitalWrite(toggleLight, HIGH);
  while(digitalRead(guard) == HIGH){} //Safety for repogramming
  
  Keyboard.begin();
  delay(100);
}

void loop() {
    blueToggleState = digitalRead(blueToggle);
    
    if(blueToggleState == LOW && blueTogglePrimed == true){
        chrome();
        blueTogglePrimed = false;//Prevents chrome being lauched repeatedly
        delay(200);//Prevent bouncing
    }
    else if(blueToggleState == HIGH && blueTogglePrimed == false){
        blueTogglePrimed = true;
        delay(200);//Prevent bouncing
    }

    greenToggleState = digitalRead(greenToggle);

    if(greenToggleState == LOW && greenTogglePrimed == true){
        explorer();
        greenTogglePrimed = false;//Prevents explorer being lauched repeatedly
        delay(500);//Prevent bouncing/launching again too soon
    }
    else if(greenToggleState == HIGH && greenTogglePrimed == false){
        greenTogglePrimed = true;
        delay(200);//Prevent bouncing
    }

    amberButtonState = digitalRead(amberButton);

    if(amberButtonState == LOW && amberButtonPrimed == true){
        closeWindow();
        amberButtonPrimed = false;//Prevents windows being closed repeatedly
        delay(100);//Prevent bouncing
    }
    else if(amberButtonState == HIGH && amberButtonPrimed == false){
        amberButtonPrimed = true;
        delay(100);//Prevent bouncing
    }

    blueButtonState = digitalRead(blueButton);
    
    if(blueButtonState == LOW && blueButtonPrimed == true){
        switchWindow();
        blueButtonPrimed = false;//Prevents windows being closed repeatedly
        delay(100);//Prevent bouncing
    }
    else if(blueButtonState == HIGH && blueButtonPrimed == false){
        blueButtonPrimed = true;
        delay(100);//Prevent bouncing
    }

    whiteButtonState = digitalRead(whiteButton);
    
    if(whiteButtonState == LOW && whiteButtonPrimed == true){
        if(digitalRead(copyToggle) == LOW){
            copy();
        }
        else{
            cut();
        }
        
        whiteButtonPrimed = false;//Prevents windows being closed repeatedly
        delay(100);//Prevent bouncing
    }
    else if(whiteButtonState == HIGH && whiteButtonPrimed == false){
        whiteButtonPrimed = true;
        delay(100);//Prevent bouncing
    }

    yellowToggleState = digitalRead(yellowToggle);
    
    if(yellowToggleState == LOW && yellowTogglePrimed == true){
        taskMgr();
        yellowTogglePrimed = false;//Prevents taskMgr being lauched repeatedly
        delay(200);//Prevent bouncing
    }
    else if(yellowToggleState == HIGH && yellowTogglePrimed == false){
        yellowTogglePrimed = true;
        delay(200);//Prevent bouncing
    }

    if(digitalRead(yellowButton) == LOW){
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.print("v");
        delay(400);
        while(digitalRead(yellowButton) == LOW){
            Keyboard.print("v");
            delay(100);    
        }
        Keyboard.release(KEY_LEFT_CTRL);
    }

    if(digitalRead(springToggle) == LOW){
        int start = millis();
        delay(300); //Prevent bouncing
        while(digitalRead(springToggle) == LOW){}
        if((millis() - start) > 2500){ //Make sure it's been held before shutting down
            shutDown();
            //Keyboard.print("Shutting Down...");
            delay(2000);
        }
        else{
            delay(750);//Bouncing
        }
    }

    demoState = digitalRead(demoSwitch); 

    if(demoState == HIGH && demoSwitchPrimed == true){
        demo();
        demoSwitchPrimed = false;//Prevents windows being closed repeatedly
        delay(100);//Prevent bouncing
    }
    else if(demoState == LOW && demoSwitchPrimed == false){
        demoSwitchPrimed = true;
        delay(100);//Prevent bouncing
    }
    
    //demo();
    //delay(7500);

    flashLights();
}

void flashLights(){
    switch(random(0, 1250)){
        case 0:
            switchState(amberButtonLight);
        case 1: 
            switchState(blueButtonLight);
        case 2:
            switchState(whiteButtonLight);
    }
    
    if(random(0, 2000) == 0){
        switchState(rockerLight);
    }
    
    if(random(0, 2000) == 0){
        digitalWrite(toggleLight, LOW);//MUST be on almost all the time as demo switch relies on it
    }
    if(random(0, 500) == 0){
        digitalWrite(toggleLight, HIGH);
    }
}

void switchState(int pin){
    digitalWrite(pin, !digitalRead(pin));
}

void flash(int pin, int duration, int pause){
    int start = millis();
    while((millis() - start) < duration){
        digitalWrite(pin, HIGH);
        delay(pause);
        digitalWrite(pin, LOW);
        delay(pause);
    }
    
}

void winRun(String command){
    Keyboard.press(KEY_LEFT_GUI);
    delay(5);
    Keyboard.print("r");
    Keyboard.release(KEY_LEFT_GUI);
    delay(85);//Wait for Run to pop up
    Keyboard.print(command);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(200);
}

void taskManager(){
    winRun("taskmgr");
}

void chrome(){
    winRun("chrome");
}

void explorer(){
    winRun("explorer");
}

void taskMgr(){
    winRun("taskmgr");
}

void switchWindow(){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_TAB);
    delay(5);
    Keyboard.release(KEY_LEFT_ALT);
    Keyboard.release(KEY_TAB);
}

void closeWindow(){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    delay(1);
    Keyboard.release(KEY_LEFT_ALT);
    Keyboard.release(KEY_F4);
}

void shutDown(){
    Keyboard.press(KEY_LEFT_GUI);
    delay(5);
    Keyboard.print("d");
    Keyboard.release(KEY_LEFT_GUI);
    closeWindow();
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
}

void cut(){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("x");
    delay(1);
    Keyboard.release(KEY_LEFT_CTRL);
}

void copy(){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("c");
    delay(1);
    Keyboard.release(KEY_LEFT_CTRL);
}

void paste(){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("v");
    delay(1);
    Keyboard.release(KEY_LEFT_CTRL);
}

void demo(){
    winRun("notepad");
    type("This is the control panel speaking!", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(750);
    type("I can do lots of cool stuff, like: ", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    
    type("Launch applications", 40);
    delay(500);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    explorer();
    delay(1500);
    switchWindow();
    delay(100);
    
    type("Switch windows", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(500);
    switchWindow();
    delay(1000);
    switchWindow();
    delay(50);

    type("Close windows", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(500);
    switchWindow();
    delay(750);
    closeWindow();
    delay(500);

    type("I can select, cut, copy and paste text as well", 40);
    delay(1500);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ARROW);
    delay(2);
    Keyboard.release(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.press(KEY_LEFT_ARROW);
    delay(2);
    Keyboard.release(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.press(KEY_LEFT_ARROW);
    delay(2);
    Keyboard.release(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.release(KEY_LEFT_SHIFT);
    Keyboard.print("c");
    Keyboard.release(KEY_LEFT_CTRL);
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(100);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("v");
    delay(300);
    Keyboard.print("v");
    delay(300);
    Keyboard.print("v");
    delay(300);
    Keyboard.release(KEY_LEFT_CTRL);
    delay(1000);

    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    type("Lastly, I can shutdown your computer...", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(500);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.print("d");
    delay(2);
    Keyboard.release(KEY_LEFT_GUI);
    delay(750);
    closeWindow();
    delay(750);
    Keyboard.press(KEY_ESC);
    delay(2);
    Keyboard.release(KEY_ESC);
    delay(500);
    switchWindow();
    type("..... But I won't do that now!", 40);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    delay(500);
    type("Hope you enjoyed the demo :)", 40);
    delay(500);
    closeWindow();
    delay(300);
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(300);
    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
    Keyboard.release(KEY_RIGHT_ARROW);
}

void type(String message, int pause){
    delay(200);
    for(int i = 0; i < message.length(); i++){
        Keyboard.print(message[i]);
        delay(pause);
    }
}
