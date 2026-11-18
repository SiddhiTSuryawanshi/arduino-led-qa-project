/*
 * ============================================================================
 * Project: Arduino LED Blinking & Diagnostic System
 * Course: Project Management (2307476T) - Department of E&TC Engineering
 * Institute: MIT Academy of Engineering, Alandi (D), Pune
 * Academic Year: 2026-2027
 * Author: Siddhi T. Suryawanshi
 * Repository: https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project
 * ============================================================================
 */

#include "Arduino.h"

// Hardware Configuration
const uint8_t LED_PIN = 13;
const unsigned long DEFAULT_INTERVAL = 500;
const unsigned long HEARTBEAT_INTERVAL = 2000;

// State Variables
unsigned long previousBlinkMillis = 0;
unsigned long previousHeartbeatMillis = 0;
unsigned long blinkInterval = DEFAULT_INTERVAL;
uint8_t ledState = LOW;
unsigned long toggleCount = 0;

void runPowerOnSelfTest() {
  Serial.println(F("[POST] Running Power-On Self-Test..."));
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  Serial.println(F("[POST] LED Pin self-test PASSED. Hardware functional."));
}

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 1000) {}

  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(F(" Arduino LED Blinking & Diagnostic System v1.0.0"));
  Serial.println(F(" MIT AOE | E&TC Dept | Project Management 2307476T"));
  Serial.println(F("=================================================="));
  Serial.print(F("[SYS_INIT] Configured Target LED Pin: "));
  Serial.println(LED_PIN);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  ledState = LOW;

  runPowerOnSelfTest();

  Serial.print(F("[SYS_INIT] Non-blocking blink loop active. Interval: "));
  Serial.print(blinkInterval);
  Serial.println(F(" ms."));
}

void updateLedBlink(unsigned long currentMillis) {
  if (currentMillis - previousBlinkMillis >= blinkInterval) {
    previousBlinkMillis = currentMillis;
    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN, ledState);
    toggleCount++;
  }
}

void emitHeartbeat(unsigned long currentMillis) {
  if (currentMillis - previousHeartbeatMillis >= HEARTBEAT_INTERVAL) {
    previousHeartbeatMillis = currentMillis;

    Serial.print(F("[HEARTBEAT] Uptime: "));
    Serial.print(currentMillis / 1000);
    Serial.print(F("s | LED State: "));
    Serial.print(ledState == HIGH ? F("HIGH (ON) ") : F("LOW (OFF)"));
    Serial.print(F(" | Toggles: "));
    Serial.print(toggleCount);
    Serial.print(F(" | Interval: "));
    Serial.print(blinkInterval);
    Serial.println(F("ms | Power: OK"));
  }
}

void processSerialCommands() {
  if (Serial.available() > 0) {
    char cmd = (char)Serial.read();
    switch (cmd) {
      case 'f':
      case 'F':
        blinkInterval = 250;
        Serial.println(F("[CMD] Blink rate set to FAST (250 ms)"));
        break;
      case 'm':
      case 'M':
        blinkInterval = 500;
        Serial.println(F("[CMD] Blink rate set to MEDIUM (500 ms)"));
        break;
      case 's':
      case 'S':
        blinkInterval = 1000;
        Serial.println(F("[CMD] Blink rate set to SLOW (1000 ms)"));
        break;
      case '?':
        Serial.println(F("[CMD_HELP] Commands: 'f' (Fast), 'm' (Medium), 's' (Slow), '?' (Help)"));
        break;
      default:
        break;
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();
  updateLedBlink(currentMillis);
  emitHeartbeat(currentMillis);
  processSerialCommands();
}
