# Arduino LED QA & Diagnostic System Wiki

Welcome to the **Arduino LED Blinking & Diagnostic System** technical documentation wiki.

## Project Navigation
1. [Project Overview & System Architecture](Home#system-architecture)
2. [Hardware Wiring & Electrical Schematics](Hardware-Setup)
3. [QA Problem Solving & 5-Why Analysis](QA-Process)
4. [Firmware Non-blocking Timing Engine](Firmware-Design)
5. [Serial Telemetry & Diagnostic Commands](Telemetry-Guide)

---

## System Architecture
The Arduino LED Diagnostic System is an embedded firmware solution running on ATmega328P. It transitions traditional blocking delay routines into a non-blocking asynchronous state machine using `millis()`.

### Key System Capabilities:
- **Startup Power-On Self-Test (POST)**: Flashes the target pin 3 times at 100ms intervals to verify diode junction conductivity and MCU boot state.
- **Heartbeat Telemetry**: Transmits system uptime, toggle cycle counts, and current voltage state over UART every 2 seconds.
- **Command Parser**: Accepts runtime frequency changes over the Serial Monitor without stalling MCU execution.
