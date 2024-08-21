#define LED1 2
#define LED2 3
#define LED3 4
#define BTN1 5
#define BOUNCE_DELAY 40 //miliseconds
#define SERIAL_SPEED 9600


class Btn{
    public:
        bool isOff = false;
        int pin;

        Btn(int pin){

        }
};


class Project{
    

    public: 
        int led1, led2, led3, btn;

        Project(int led1, int led2, int led3, int btn){
            this->led1 = led1;
            this->led2 = led2;
            this->led3 = led3;
            this->btn = btn;
        }

        void setup(){
            // do some initial setup
            Serial.begin(SERIAL_SPEED);
            
            int pins[] = {led1, led2, led3}, pin;
            for(int i=0; i<3; i++){
                pin = pins[i];
                pinMode(pin, OUTPUT);
            }

            pinMode(btn, INPUT);
            // Serial.println("--SETUP COMPLETE--");
        }

        void loop(){
            if (isBtnDepressed()){
                Serial.println("Im depressed");
            }
        }

        bool isBtnDepressed(){
            bool ret = digitalRead(btn) == LOW;
            delay(BOUNCE_DELAY);
            return ret;
        }

};


Project project(LED1, LED2, LED3, BTN1);

void setup(){
    project.setup();
}

void loop(){
    project.loop();
}
