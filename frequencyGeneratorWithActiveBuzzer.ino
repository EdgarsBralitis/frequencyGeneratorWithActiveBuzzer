/* Frequency generator on Arduino Uno Clone
 * Active buzzer connected to buzzPin
 * readPin is used, to get info from potentiometer
 *  
 * Try changing minFrequency and maxFrequency values
 */


int buzzPin = 8;
int readPin = A0;
long valueRead; //value, read from readPin (is controlled by potentiometer)
long maxValueRead = 1023;

//oscilations in one second
long frequency;
long minFrequency = 0; //minimum frequency in Hz to be generated (0 means silence)
long maxFrequency = 50; //maximum frequency in Hz to be generated

long buzzingTime;



void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  valueRead = analogRead(readPin);
  
  frequency = long(float(maxFrequency - minFrequency)/float(maxValueRead) * float(valueRead));
  buzzingTime = 1000000/(frequency + 1);
  if (frequency == 0) buzzingTime = 0;

  if (frequency>0) {
    for (long i = 0; i < frequency; i++) {
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(buzzingTime);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(buzzingTime);
    }
  }
  Serial.println("Reading from pin: "+ String(valueRead) + " *** Applied frequency: " + String(frequency) + " Hz" + " buzzingTime (microSeconds): " + String(buzzingTime));
  if (frequency == 0) delay(100);
}
