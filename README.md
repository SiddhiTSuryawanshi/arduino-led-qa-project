# Arduino LED Blinking & Diagnostic System with QA Documentation

[![C++](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Arduino-00599C?logo=c%2B%2B)](https://www.arduino.cc/)
[![GitHub Issues](https://img.shields.io/github/issues/SiddhiTSuryawanshi/arduino-led-qa-project?color=red)](https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project/issues)
[![GitHub Closed Issues](https://img.shields.io/github/issues-closed/SiddhiTSuryawanshi/arduino-led-qa-project?color=green)](https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project/issues?q=is%3Aissue+is%3Aclosed)
[![Branch](https://img.shields.io/badge/Branch-main-blue.svg)](https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project/tree/main)
[![Academic Year](https://img.shields.io/badge/Academic%20Year-2026--2027-orange)](https://mitaoe.ac.in)
[![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)](LICENSE)

An embedded systems project implementing a robust, non-blocking **Arduino LED Blinking & Diagnostic System** alongside an end-to-end **GitHub-based Quality Assurance (QA) and Problem-Solving Workflow**. Developed for the course **Project Management (2307476T)** at **MIT Academy of Engineering, Alandi (D), Pune**.

---

## 📌 Executive Summary
In embedded firmware engineering, even seemingly trivial tasks like blinking an LED introduce real-world quality, timing, and electrical reliability hazards:
1. **Blocking delays** stall CPU execution and prevent multitasking.
2. **Untyped GPIO definitions** cause pin collisions and unsafe mutability.
3. **Absence of diagnostic routines** makes hardware failures opaque.
4. **Power fluctuations / brownouts** cause silent resets on breadboard prototypes.

This repository demonstrates how to manage these risks using industry-standard QA methodologies: **GitHub Issues tracking**, **Severity classification**, **5-Why Root Cause Analysis (RCA)**, **Branch-and-PR workflows**, and **Serial telemetry verification**.

---

## 🛠️ Hardware Specifications & Circuit Design

### Wiring Schematics (ASCII Representation)
```
  [Arduino Uno R3]
       +5V --------------> Breadboard Positive Rail (+)
       GND --------------> Breadboard Ground Rail (-)
       Pin 13 (D13) -----> [220Ω Resistor] -----> [LED Anode (+)]
                                                   [LED Cathode (-)] -----> GND
```

### Component Details
| Component | Specification | Function |
| :--- | :--- | :--- |
| **Microcontroller** | ATmega328P (Arduino Uno / Nano) | Executes non-blocking firmware at 16 MHz |
| **Indicator** | 5mm High-Efficiency Red/Green LED | Visual state indicator (ON / OFF) |
| **Ballast Resistor** | 220 Ω / 0.25 W ($\pm 5\%$) | Current limiter ($I \approx \frac{5V - 2.0V}{220\Omega} \approx 13.6\text{ mA}$) |
| **Interface** | USB UART (CH340 / ATmega16U2) | Serial telemetry and host communications at 9600 baud |

---

## 🧠 Firmware Architecture: Baseline vs. Production

### 1. Baseline Draft (v0.1 - Buggy)
```cpp
// Legacy Blocking Approach
int led = 13;
void setup() { pinMode(led, OUTPUT); }
void loop() {
  digitalWrite(led, HIGH); delay(1000); // FREEZES CPU
  digitalWrite(led, LOW);  delay(1000); // FREEZES CPU
}
```
*Problems*: Blocking `delay()` completely halts execution, mutable `int` pin definition, no boot diagnostics, no power telemetry.

### 2. Upgraded QA-Verified Architecture (v1.0.0 - Production)
- **Non-blocking asynchronous timing loop** using `millis()`.
- **Typed, immutable GPIO configuration** (`const uint8_t LED_PIN = 13;`).
- **Power-On Self-Test (POST)** routine: 3 fast verification pulses on boot.
- **2-second Serial Heartbeat Telemetry** reporting uptime, LED state, and brownout recovery.
- **Interactive command parser** over Serial (`'f'` fast, `'m'` medium, `'s'` slow).

---

## 📋 Quality Assurance (QA) Issues & Resolution Traceability

| Issue # | Title | Severity | Status | Root Cause (5-Why Summary) | Verified Fix |
| :---: | :--- | :---: | :---: | :--- | :--- |
| **#1** | **LED is not blinking** | **High** | `Closed` | No startup hardware self-test or visual diagnostic; polarity or pin check omitted. | Implemented 3-pulse Power-On Self-Test (`runPowerOnSelfTest()`) and Serial status echo. |
| **#2** | **LED blinking delay is too high** | **Medium** | `Closed` | Blocking `delay(1000)` halts CPU execution for 2000ms, making system unresponsive. | Replaced `delay()` with `millis()` non-blocking timing loop; default set to responsive 500ms. |
| **#3** | **Incorrect LED pin configuration** | **High** | `Closed` | Unsafe mutable integer variable `int led = 13` without pinMode validation. | Defined `const uint8_t LED_PIN = 13` with explicit `pinMode` verification. |
| **#4** | **Power supply problem** | **Medium** | `Closed` | Unstable USB/breadboard rails lead to silent MCU resets and brownout freezes. | Added 2-second Serial Heartbeat and brownout restart detection telemetry. |
| **#5** | **Dynamic blink rate control** | **Low** | `Open` | Runtime frequency adjustment without reprogramming currently in backlog. | Active feature request for future sensor-driven adaptation. |

*For complete 5-Why analysis transcripts, refer to [`docs/QA_LOG.md`](docs/QA_LOG.md).*

---

## 🌿 Git Branching & Pull Request Lifecycle
To adhere to professional software engineering standards, changes were developed and integrated using a feature branch:
1. **Branch Created**: `qa-fixes-and-docs` branched from `main`.
2. **Modular Commits**: Each commit addressed specific QA issue IDs with clear commit messages (`Fixes #1, Fixes #3`, etc.).
3. **Pull Request (PR #1)**: Created with full traceability, peer verification checklist, and linked issue keywords.
4. **Merge**: Merged cleanly into `main`, triggering automated issue closure and synchronization.

---

## 🚀 How to Build and Run

### 1. Prerequisites
- Arduino IDE (v1.8.x or v2.x) or `arduino-cli`.
- Arduino Uno / Nano / Mega board.
- USB cable (Type A-to-B or Mini-USB).

### 2. Flashing the Firmware
1. Clone this repository:
   ```bash
   git clone https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project.git
   ```
2. Open `led_blink.ino` in the Arduino IDE.
3. Select **Tools > Board > Arduino Uno** (or corresponding board).
4. Select the matching COM port under **Tools > Port**.
5. Click **Upload** (`Ctrl + U`).

### 3. Monitoring Telemetry & Sending Commands
1. Open the **Serial Monitor** (`Ctrl + Shift + M`).
2. Set the baud rate to **9600 baud** and line ending to **Newline**.
3. Observe the boot banner and POST self-test:
   ```text
   ==================================================
    Arduino LED Blinking & Diagnostic System v1.0.0
    MIT AOE | E&TC Dept | Project Management 2307476T
    QA Fixes: Non-blocking millis(), POST, Telemetry
   ==================================================
   [SYS_INIT] Configured Target LED Pin: 13
   [POST] Running Power-On Self-Test...
   [POST] LED Pin self-test PASSED. Hardware functional.
   [HEARTBEAT] Uptime: 2s | LED State: HIGH (ON)  | Toggles: 4 | Interval: 500ms | Power: OK
   ```
4. Enter commands into the Serial input bar:
   - Type `f` + Enter: Sets blink interval to **250 ms (Fast)**.
   - Type `m` + Enter: Sets blink interval to **500 ms (Medium)**.
   - Type `s` + Enter: Sets blink interval to **1000 ms (Slow)**.
   - Type `?` + Enter: Displays command help menu.

---

## 📂 Repository Directory Structure

```text
arduino-led-qa-project/
├── .github/
│   ├── ISSUE_TEMPLATE/
│   │   └── qa_bug_report.md       # Standardized defect reporting template
│   └── pull_request_template.md   # Pull request review & verification template
├── docs/
│   ├── PROJECT_PLAN.md            # Work Breakdown Structure, milestones & schedule
│   └── QA_LOG.md                  # Detailed QA issue matrix & 5-Why root cause analysis
├── led_blink.ino                  # Complete upgraded production firmware with non-blocking timing
└── README.md                      # Comprehensive project overview, wiring & QA guide
```

---

## 🎓 Academic Information
- **Course**: Project Management (Course Code: 2307476T)
- **Academic Year**: 2026–2027 (Semester VII)
- **Department**: Department of Electronics & Telecommunication Engineering
- **Institution**: MIT Academy of Engineering, Alandi (D), Pune - 412105
- **Course Teacher**: Dr. Ashish Mulajkar
- **Student Author**: Siddhi T. Suryawanshi (PRN: 202301070039 / Class: BTech Div C)
