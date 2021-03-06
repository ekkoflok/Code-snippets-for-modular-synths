//Arduino based clock divider class using interrupt for the clock input
//Intended for use inside a modular synthesizer system
//A timer class is made and used to use an internal oscillator/ clock to increment the counter
//Ekkoflok, August 2019
//not tested

class Time
{
//variables
unsigned long time;         // the last time the output pin was toggled
unsigned long timer_var; // the debounce time, increase if the output flickers

bool timer_state;

public:
    Time()
    {
    timer_var = 200; 
    timer_state = LOW; 
	time = 0;
	
    }
    
    bool update_time(unsigned long TIMER_VAR){
	    //bool timer_state = 0;
	    
        unsigned long current_time = millis();
	    if(current_time - time >= TIMER_VAR){ 
	    time = current_time;
	    timer_state = 1;
	    //TIME = millis(); //this part is done from the code calling the function
	    }
	    else timer_state = 0;
	
	    return timer_state;
}    

}; Time T; //initialize



volatile int count = 0; //the main counter variable

class Clock_div
{
    int state = 0;
    int Pin;

    public:
    Clock_div(int pin_)
    {
    Pin = pin_; 
    pinMode(Pin, OUTPUT);
}

void divide(int div)
{
    //int Pin = cd.pin_;
    if( (count % div == 0 ) ){state = 1; }
    else state = 0;
    digitalWrite(Pin, state);
 }
}; 
//initialize - make a new instance for each new output pin you wish to add
Clock_div cd1(17); //output pin in ()
Clock_div cd2(9);
Clock_div cd3(8);

bool internal_clock = 0; //set to 0 if using external clock, 1 if using internal
const int clock_input = 2; //the interrupt clock input, needs a pulldown resistor

void setup()
{
    
    pinMode(clock_input, INPUT);
    attachInterrupt(1, ISR_clock, RISING); //interrupt vector - 0 and 1 corresponds to pin 2 and 3 on the 328 IC, calls the pin_ISR function on rising edges on pin 2
 }

void loop()
{
   if(internal_clock)
   {
        if(T.update_time(50)) count ++; //update the clock
   }
  
    
    cd1.divide(7); //division in ()
    cd2.divide(4); 
    cd3.divide(5); 
   
   if(!internal_clock)
    { 
    ISR_clock();
    }
}

void ISR_clock() //external clock using interrupt
     {
        count ++; //increment the counter
     }
