#include <Arduino.h>

// Read 8 buttons using 74HC165 shift register and play tones with a buzzer

const int Clock = D2;
const int Shift_Load = D1;
const int Q_H_Pin = D5;
const int Buzzer_Pin = D7;

int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};  // Notes C4 to C5

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nStarting Serial Monitor...");

  pinMode(Clock, OUTPUT);
  pinMode(Shift_Load, OUTPUT);
  pinMode(Q_H_Pin, INPUT);
  pinMode(Buzzer_Pin, OUTPUT);

  digitalWrite(Clock, LOW);
}

byte readParallelData() {
  // Capture input states into shift register
  digitalWrite(Shift_Load, LOW);
  delayMicroseconds(5);
  digitalWrite(Shift_Load, HIGH);  // Latch data for serial read

  // Read 8 bits (from A to H, with A as MSB)
  // IMPORTANT:
  // Bit positions in a byte are from 0 (LSB) to 7 (MSB)
  // So to store input A as bit 7, we shift it left by (7 - i)
  byte data = 0;
  for (int i = 0; i < 8; i++) {
  data |= (digitalRead(Q_H_Pin) << i);
  digitalWrite(Clock, HIGH);
  delayMicroseconds(2);
  digitalWrite(Clock, LOW);
}
  return data;
}

byte lastData = 0;

void loop() {
  byte currentData = readParallelData();

  if (currentData != lastData) {
    Serial.print("New data: ");
    for (int i = 7; i >= 0; i--) {
      Serial.print(bitRead(currentData, i)); // Print from MSB to LSB
    }
    Serial.println();
    lastData = currentData;

    for (int i = 0; i < 8; i++) {
      if (bitRead(currentData, 7 - i)) {
        tone(Buzzer_Pin, notes[i]);
        delay(150);
        noTone(Buzzer_Pin);
        delay(50);
      }
    }
  }

  delay(10);
}
