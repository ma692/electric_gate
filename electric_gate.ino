#include <Servo.h>
Servo door;
#define in A0
#define out A5
int count=0;
int blueLED = 10;
int redLED = 3;
/*int valuein;
int valueout;
int readingIn;
int readingOut;
int val1;
int val2;
int persons = 0; */
int inPin = 2;         // the number of the input pin
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

//function for counting in
void IN()
{
    count++;
    if(count>5)
    {
      count=10;
      }
    Serial.print("Person In Room: \t");
    Serial.print(count);
    delay(1000);
}
 //function for counting out
void OUT()
{
    count--;
    if(count<=0)
    {
      count=0;
      }
    Serial.print("Person In Room: \t");
    Serial.println(count);
    delay(1000);
}

void setup()
{
  door.attach (6);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
  reading = digitalRead(inPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);
  /*Serial.print("staateee: \t");
  Serial.println (state);

  previous = reading;*/

  
  if (state == 1) {
    if(digitalRead(in) != 1){
    IN();
    door.write(90);
    digitalWrite (blueLED, HIGH);
    delay(300);
    digitalWrite (blueLED, LOW);
    delay(300);
  } 
    if(digitalRead(out) != 1) {
    OUT();
    door.write(90);
    digitalWrite (redLED, HIGH);
    delay(300);
    digitalWrite (redLED, LOW);
    delay(300);
    } 
    
  if  (count > 5) {
    Serial.print("That is enough! \n");
    tone (9, 300, 1000);  
  }
    if(count<=0)
  {
    Serial.print("Nobody In Room \n");
    Serial.print("Light Is Off \n");
    delay(200);
  }
    
  }  
else {
digitalWrite (redLED, LOW);
digitalWrite (blueLED, LOW);
digitalWrite (outPin, LOW);
door.write(0);    
}
}
