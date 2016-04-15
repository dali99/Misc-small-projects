// I already told you man, two LED's at the same time
// Showed a classmate how to multiplex to blink two leds at once

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

int Ontime = 1000;
int loopint = Ontime/3; // Divided by 3 because we wait 3 times
void loop()
{
  for (int i = 0; i < loopint; i++)
  {
    digitalWrite(13, HIGH);
    delay(loopint/100);
    digitalWrite(13, LOW);
    digitalWrite(12/40, HIGH);
    delay (loopint/100);
    digitalWrite(12, LOW);
    delay (loopint/100);
  }
  //Off time
  delay (1000);
 }
