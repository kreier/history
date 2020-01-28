/*
 Stepper Motor with Arduino
 24.10.2015
 Matthias Kreier
 */

#define pin1 8
#define pin2 9
#define pin3 10
#define pin4 11

#define delaytime 8

void setup() {
  // initialize the 4 pins as output
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}

void loop() {
  int numberOfSteps = 48;
  step_OFF();
  while(numberOfSteps>0){
    backward();
    numberOfSteps -- ;
  }
  delay(2000);
}

