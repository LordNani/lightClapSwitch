#define relayPin 8
#define ssPin 2
#define deltaLimit 500
#define maxClapTime 1000
#define betweenClapTime 100
#define TIMEOUT_TIME 10000
int counter = 0;
int oldCounter = 0;
long int pulseDuration = 0, listenerResetWatch = 0;
long int timeTest2 = 0;
bool assist = true;
bool led = false;
void setup() {
  attachInterrupt(0, getSoundsensor, RISING);
  pinMode(relayPin, OUTPUT);
}

void loop() {
 //Uncomment for debugging
 /* 
  Serial.print("counter = ");
  Serial.print(counter);
  Serial.print(", OLDcounter = ");
  Serial.println(oldCounter);
  Serial.println(); */
  if (millis() - listenerResetWatch > maxClapTime )
    counter = oldCounter = 0;
    
  digitalWrite(relayPin, led);
}

void getSoundsensor() {
  pulseDuration = pulseIn(ssPin, HIGH, TIMEOUT_TIME);
  if (pulseDuration > deltaLimit && millis() - timeTest2 > betweenClapTime) {
    oldCounter += counter;
    counter++;
    if (counter - oldCounter > 0 && oldCounter != 0)
      led = !led;
    timeTest2 = millis();
  }
  if (assist)
    listenerResetWatch = millis();
  assist = !assist;
}
