//Random clock source with probability
//From (almost) no ticks per input trigger
//to a tick on (almost) every trigger
//works by comparing a clock input to a random value with
//treshold
//Ekkoflok, November, 2017
//CC-BY-SA

byte thresh;
int randomNumber;

//In and output definitions
byte out1 = 3; //clock output 1
byte in1 = A1; //Threshold input (with pot voltage divider)

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(in1, INPUT);
  pinMode(out1, OUTPUT);

}

void loop() {
randomNumber = random(1024);
thresh = analogRead(in1);

/* //Print values of analog input and the random value to the serial monitor
Serial.println("Random number:");
Serial.println(randomNumber);
Serial.println("Threshold:");
Serial.println(thresh);
*/

 if(in1 == HIGH && randomNumber > thresh)

 {
  digitalWrite(out1, HIGH);
  
  
  }

  else {
    digitalWrite(out1, LOW);
    }

}
