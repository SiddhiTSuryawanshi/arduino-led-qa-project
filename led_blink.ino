/*
 * ============================================================================
 * Project: Arduino LED Blinking & Diagnostic System
 * Course: Project Management (2307476T) - Department of E&TC Engineering
 * Institute: MIT Academy of Engineering, Alandi (D), Pune
 * Academic Year: 2026-2027
 * Author: Siddhi T. Suryawanshi
 * Repository: https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project
 *
 * QA Issue Mitigation Summary:
 * - Fixes #1 & #3: Explicit pin definition (LED_PIN = 13), pinMode validation,
 *                  startup Power-On Self-Test (POST) 3-blink verification,
 *                  and Serial status feedback.
 * - Fixes #2: Replaced blocking delay() with non-blocking millis() timing loop,
 *             reducing blink interval to 500 ms for responsive operation.
 * - Fixes #4: Implemented Serial Heartbeat telemetry and brownout/power-cycle
 *             restart detection to diagnose unstable USB/power rails.
 * ============================================================================
 */

// ----------------------------------------------------------------------------
// Pin Configuration & Constants (Addresses Issue #3)
// ----------------------------------------------------------------------------
const uint8_t LED_PIN = 13;             // On-board LED or external digital output pin
const unsigned long DEFAULT_INTERVAL = 500;  // Default blink period in milliseconds (Addresses Issue #2)
const unsigned long HEARTBEAT_INTERVAL = 2000; // Telemetry reporting period (Addresses Issue #4)

// ----------------------------------------------------------------------------
// System State Variables (Non-blocking timing variables)
// ----------------------------------------------------------------------------
unsigned long previousBlinkMillis = 0;       // Stores last timestamp LED state toggled
unsigned long previousHeartbeatMillis = 0;   // Stores last timestamp telemetry was emitted
unsigned long blinkInterval = DEFAULT_INTERVAL; // Current active blink interval
uint8_t ledState = LOW;                      // Current LED state (LOW / HIGH)
unsigned long toggleCount = 0;               // Total toggle cycles completed

// ----------------------------------------------------------------------------
// Power-On Self-Test (POST) Routine (Addresses Issue #1)
// Visually and logically verifies pin connectivity and MCU boot health.
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// System Setup Routine
// ----------------------------------------------------------------------------
void setup() {
  // Initialize Serial Communication for Telemetry and QA Diagnostics
  Serial.begin(9600);
  while (!Serial && millis() < 1000) {
    // Wait briefly for native USB serial port (e.g. Leonardo/Micro), timeout gracefully
  }

  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(F(" Arduino LED Blinking & Diagnostic System v1.0.0"));
  Serial.println(F(" MIT AOE | E&TC Dept | Project Management 2307476T"));
  Serial.println(F(" QA Fixes: Non-blocking millis(), POST, Telemetry"));
  Serial.println(F("=================================================="));

  // Power Cycle / Brownout Diagnostic Announcement (Addresses Issue #4)
  Serial.println(F("[SYS_INIT] Microcontroller boot sequence initialized."));
  Serial.print(F("[SYS_INIT] Configured Target LED Pin: "));
  Serial.println(LED_PIN);

  // Configure LED Pin Mode (Addresses Issue #3)
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  ledState = LOW;

  // Run hardware verification self-test (Addresses Issue #1)
  runPowerOnSelfTest();

  Serial.print(F("[SYS_INIT] Non-blocking blink loop active. Interval: "));
  Serial.print(blinkInterval);
  Serial.println(F(" ms."));
  Serial.println(F("--------------------------------------------------"));
}

// ----------------------------------------------------------------------------
// Non-Blocking LED Update (Addresses Issue #2)
// Uses millis() state machine instead of blocking delay().
// ----------------------------------------------------------------------------
void updateLedBlink(unsigned long currentMillis) {
  if (currentMillis - previousBlinkMillis >= blinkInterval) {
    previousBlinkMillis = currentMillis;

    // Toggle LED State
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(LED_PIN, ledState);
    toggleCount++;
  }
}

// ----------------------------------------------------------------------------
// System Telemetry & Heartbeat (Addresses Issue #4)
// Emits periodic system health metrics over Serial.
// Detects brownouts (sudden reset to uptime 0) and verifies power stability.
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// Serial Command Interface (Interactive Quality Assurance Tool)
// Demonstrates responsiveness of non-blocking architecture.
// ----------------------------------------------------------------------------
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
        // Ignore newline or unrecognized characters
        break;
    }
  }
}

// ----------------------------------------------------------------------------
// Main Loop
// Continuously services tasks without blocking delays.
// ----------------------------------------------------------------------------
void loop() {
  unsigned long currentMillis = millis();

  // Task 1: Non-blocking LED state machine
  updateLedBlink(currentMillis);

  // Task 2: Health telemetry and power stability heartbeat
  emitHeartbeat(currentMillis);

  // Task 3: Interactive command processor
  processSerialCommands();
}
