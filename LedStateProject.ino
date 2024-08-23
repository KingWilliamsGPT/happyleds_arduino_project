#define LED1 9
#define LED2 10
#define LED3 11
#define BTN1 5
#define BOUNCE_DELAY 10 //miliseconds
#define SERIAL_SPEED 9600
#define FLICKER_DELAY 100 //ms

const int LEDS[] = {LED1, LED2, LED3};
const int NO_LEDS = 3;

int currentState = 0;
int states[] = {
    0,       // all bulbs are off
    1,       // all bulbs are on
    2,       // only bulb 1 is on
    3,       // only bulb 2 is on
    4,       // only bulb 3 is on
    5,       // continuous flickery
    6,       // all bulbs are on low power
};
const int NO_STATES = 7;

bool btn_is_pressed = false;
bool allOn = false;

void writeToPins(int pins[], int pins_len, int val, int avoid=-1, bool analog=false);


void setup(){
    Serial.begin(SERIAL_SPEED);

    for(int i=0; i<NO_LEDS; i++){
        int pin = LEDS[i];
        pinMode(pin, OUTPUT);
    }

    pinMode(BTN1, INPUT);

    Serial.println("Done");
}


void loop(){

    if(btnIsPressed()){
        nextState();
    }

    doState();

}


bool btnIsPressed(){
    if(digitalRead(BTN1) == HIGH){
        btn_is_pressed = true;
    }else{
        if(btn_is_pressed){
            btn_is_pressed = false;
            delay(BOUNCE_DELAY);
            return true;
        }
    }
    return false;
}

void nextState(){
    currentState++;
    if(currentState>NO_STATES-1){
        currentState=0;
    }
}

void doState(){
    int state = currentState;
    if(state == 0){
        offLeds();
    } else if(state == 1){
        onLeds();
    } else if (state == 2 || state == 3 || state == 4){
        int pin = LEDS[state-2];
        writeToPins(LEDS, NO_LEDS, LOW, pin);     // turn off other pins
        digitalWrite(pin, HIGH);
    } else if (state == 5){
        onLeds();
        delay(FLICKER_DELAY);
        offLeds();
        delay(FLICKER_DELAY);
    } else if (state == 6){
        // allOn = !allOn;  // toggle on/off
        // writeToPins(LEDS, 3, allOn);
        writeToPins(LEDS, NO_LEDS, 125, -1, true);
    }
}


void onLeds(){
    writeToPins(LEDS, NO_LEDS, HIGH);
}

void offLeds(){
    writeToPins(LEDS, NO_LEDS, LOW);
}

void writeToPins(int pins[], int pins_len, int val, int avoid, bool analog){
    for(int i=0; i<pins_len; i++){
        int pin = LEDS[i];
        if (pin == avoid){
            continue;
        }
        if(analog){
            analogWrite(pin, val);
        }else{
            digitalWrite(pin, val);
        }
    }
}
