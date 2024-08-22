#define LED1 2
#define LED2 3
#define LED3 4
#define BTN1 5
#define BOUNCE_DELAY 10 //miliseconds
#define SERIAL_SPEED 9600


class Btn{
    public:
        bool isTouched = false;
        int pin;

        Btn(int pin){
            this->pin = pin;
        }

        bool isPressed(){
            // Serial. 
            // The button says yes to is pressed after it has just been depressed
            if (digitalRead(this->pin == HIGH)){
                if (this->isTouched){
                    this->isTouched == false;
                    return true;
                }
            }else{
                // beign touched coz pin == LOW
                this->isTouched == true;
                delay(BOUNCE_DELAY);
            }

            return false;
        }

};


class Project{
    private:
        bool _is_pressed = false;
        int state = 0;

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

            Serial.println("--SETUP COMPLETE2--");
        }

        void loop(){
            if(this->buttonIsClicked()){
                // switch state 
            }
        }

        void setPressed(bool v){
            this->_is_pressed = v;
        }

        bool buttonIsClicked(){
            if (digitalRead(this->btn) == HIGH){
                if(!this->_is_pressed){
                    setPressed(true);
                }    
            } else{
                if(this->_is_pressed){
                    // Serial.println("clicked!!");
                    setPressed(false);
                    delay(BOUNCE_DELAY);
                    return true;
                }
            }
            return false;
        }
};


Project project(LED1, LED2, LED3, BTN1);

void setup(){
    project.setup();
}

void loop(){
    project.loop();
}
