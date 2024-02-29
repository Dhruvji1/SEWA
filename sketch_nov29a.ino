#include <Arduino.h>
#include <TM1637Display.h>

// Define pin numbers
#define IRsensorPin 2
#define ir2 11
#define CLK 3 // Clock pin connected to Pin 3 on Aries Vega 3
#define DIO 4 // Data pin connected to Pin 4 on Aries Vega 3
#define RED_LED     21     // Connect Red LED pin to GPIO-0
#define YELLOW_LED  20    // Connect Yellow LED pin to GPIO-1
#define GREEN_LED   19    // Connect Green LED pin to GPIO-2

TM1637Display display(CLK, DIO);

unsigned long startTime = 0;
bool timing = false;
void setup() {
  display.setBrightness(0x0a); // Set the brightness (adjust as needed)
  pinMode(IRsensorPin, INPUT);
  pinMode(ir2, INPUT);
   pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(IRsensorPin);
  int sensorValue2 = digitalRead(ir2);
   if(sensorValue == LOW){
    digitalWrite(GREEN_LED,LOW);
     digitalWrite(RED_LED, HIGH);      // Red LED ON
  delay(500);
  digitalWrite(RED_LED, LOW);       // Red LED OFF
  delay(500);
  digitalWrite(YELLOW_LED, HIGH);   // Yellow LED ON
  delay(500);
  digitalWrite(YELLOW_LED, LOW);    // Yellow LED OFF
  delay(500);
   }
   if(sensorValue == HIGH){
    digitalWrite(GREEN_LED, HIGH);    // Green LED ON
   }

 
  
  if (sensorValue == LOW && sensorValue2 == LOW && !timing) {
    startTime = millis(); // Start the stopwatch
    timing = true;
    Serial.print("Engaged\t");
     Serial.println("  Engaged");
  }
   if (sensorValue == LOW && sensorValue2 == HIGH && !timing) {
    startTime = millis(); // Start the stopwatch
    timing = true;
    Serial.print("Engaged\t");
    Serial.println(" Available");
    
  }
  if (sensorValue == HIGH && sensorValue2==HIGH && timing) {
    timing = false; // Stop the stopwatch
    display.showNumberDec(0, false); // Reset the display to zero
    Serial.print("Available\t");
    Serial.println("Available ");
  }
   if (sensorValue2 == LOW && sensorValue==HIGH && timing) {
    timing = false; // Stop the stopwatch
    display.showNumberDec(0, false); // Reset the display to zero
    Serial.print("Engaged\t");
    Serial.println("Available ");
  }
  
  if (timing) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;

    unsigned int minutes = (elapsedTime / 1000) / 60;
    unsigned int seconds = (elapsedTime / 1000) % 60;

    int timeToDisplay = minutes * 100 + seconds; // Format the time to display as mmss

    display.showNumberDecEx(timeToDisplay, 0b01000000, true); // Display the time (no leading zeros)
    // The 0b01000000 argument turns on the colon on most displays
  }
}
