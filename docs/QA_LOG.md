# Quality Assurance (QA) Log & Root Cause Analysis

**Project**: Arduino LED Blinking & Diagnostic System  
**Course**: Project Management (2307476T) - Department of E&TC Engineering  
**Institute**: MIT Academy of Engineering, Alandi (D), Pune  
**Repository**: [arduino-led-qa-project](https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project)  
**Author**: Siddhi T. Suryawanshi  

---

## 1. QA Defect & Issue Summary Matrix

| Issue ID | Issue Title | Type | Severity | Status | Identified Root Cause | Verified Resolution | Commit / PR Reference |
| :---: | :--- | :---: | :---: | :---: | :--- | :--- | :---: |
| **#1** | LED is not blinking | Defect | **High** | **Closed** | No startup hardware self-test or visual diagnostic; polarity or pin check omitted. | Implemented 3-pulse Power-On Self-Test (POST) and serial verification. | Branch `qa-fixes-and-docs` / PR #1 |
| **#2** | LED blinking delay is too high | Performance | **Medium** | **Closed** | Blocking `delay(1000)` halts CPU execution for 2000ms, making system unresponsive. | Replaced `delay()` with `millis()` non-blocking timing loop; default 500ms. | Branch `qa-fixes-and-docs` / PR #1 |
| **#3** | Incorrect LED pin configuration | Defect | **High** | **Closed** | Unsafe mutable integer variable `int led = 13` without pinMode validation. | Defined `const uint8_t LED_PIN = 13` with explicit `pinMode` verification. | Branch `qa-fixes-and-docs` / PR #1 |
| **#4** | Power supply problem | Reliability | **Medium** | **Closed** | Unstable USB/breadboard rails lead to silent MCU resets and brownout freezes. | Added 2-second Serial Heartbeat and brownout restart detection telemetry. | Branch `qa-fixes-and-docs` / PR #1 |
| **#5** | Feature Request: Dynamic blink rate control | Enhancement | **Low** | **Open** | Baseline system lacks runtime frequency configuration without reprogramming. | Future enhancement logged in backlog for sensor-based dynamic adjustment. | Open (Backlog) |

---

## 2. In-Depth Root Cause Analysis (5-Why Technique)

### 2.1 Issue #1: LED is not blinking
- **Problem Statement**: When powered, the LED remains completely inactive, and the developer/user cannot ascertain whether the MCU is executing code, hung, or wired incorrectly.
- **Why 1**: Why does the LED fail to blink? Because either the digital output signal is not reaching the diode junction or the MCU firmware is stuck before entering the blink loop.
- **Why 2**: Why can the user not determine where the failure occurred? Because the initial sketch provides zero feedback, telemetry, or diagnostic indicators.
- **Why 3**: Why was there no diagnostic feedback? Because the firmware lacked an initialization confirmation routine and serial communication was not configured.
- **Why 4**: Why was an initialization routine omitted? The initial draft was designed as an absolute minimum proof-of-concept without considering embedded QA practices.
- **Why 5**: Why was embedded QA omitted in the initial design? Standard design-for-testability (DFT) and power-on self-test (POST) requirements were not defined prior to coding.
- **Root Cause**: Absence of a startup Power-On Self-Test (POST) and hardware diagnostic feedback loop in firmware.
- **Implemented Fix**: Integrated `runPowerOnSelfTest()` which blinks the LED 3 times quickly (100ms ON / 100ms OFF) upon boot, and outputs `[POST] LED Pin self-test PASSED` over Serial at 9600 baud.

---

### 2.2 Issue #2: LED blinking delay is too high
- **Problem Statement**: The LED blinks too slowly (1000ms ON, 1000ms OFF = 2.0s period), and the microcontroller is locked during delays, blocking all other operations.
- **Why 1**: Why is the blinking perceived as sluggish and unresponsive? Because each half-cycle pauses for 1000 milliseconds using `delay(1000)`.
- **Why 2**: Why does `delay(1000)` make the entire system unresponsive? Because `delay()` is a blocking busy-wait loop that monopolizes MCU cycles, preventing serial reads, interrupts, or future sensor polling.
- **Why 3**: Why was `delay(1000)` chosen originally? It was used as a rudimentary beginner mechanism to produce a visible flash.
- **Why 4**: Why was a non-blocking architecture not adopted initially? The software architecture did not account for modularity, multi-tasking, or reactive input.
- **Why 5**: Why was multi-tasking not considered? Timing constraints and asynchronous execution requirements were not formalized in the initial project scope.
- **Root Cause**: Architectural reliance on blocking synchronous delay functions (`delay()`) rather than asynchronous timer polling.
- **Implemented Fix**: Refactored the core timing engine to use `millis()` state tracking (`updateLedBlink(currentMillis)`), allowing simultaneous LED blinking at a responsive 500ms default rate while continuously listening for serial commands and emitting telemetry.

---

### 2.3 Issue #3: Incorrect LED pin configuration
- **Problem Statement**: Pin 13 was defined using a mutable global integer (`int led = 13`), creating risks of accidental modification, pin reassignment collisions, and lack of pin-level validation.
- **Why 1**: Why is `int led = 13` problematic? Because a standard signed `int` consumes 2 bytes on AVR and is mutable, allowing any function to accidentally corrupt the GPIO address.
- **Why 2**: Why was it defined as a mutable `int`? It followed legacy starter tutorial conventions rather than production-grade embedded C++ best practices.
- **Why 3**: Why were embedded C++ guidelines not applied? Code linting, MISRA/embedded safety standards, and static configuration rules were not enforced during early development.
- **Why 4**: Why was there no validation of pin configuration? The setup function lacked assertions or serial echoing of configured hardware resources.
- **Why 5**: Why was there no design rule for hardware abstraction? Hardware configuration was coupled directly into application logic without a dedicated configuration header or constants block.
- **Root Cause**: Use of untyped/mutable global variables for hardware GPIO definitions and omission of pin-state verification logging.
- **Implemented Fix**: Replaced with `const uint8_t LED_PIN = 13;`, added explicit `pinMode(LED_PIN, OUTPUT);`, set safe initial state `digitalWrite(LED_PIN, LOW);`, and echoed the assigned pin over Serial during boot.

---

### 2.4 Issue #4: Power supply problem
- **Problem Statement**: Voltage fluctuations on the 5V USB rail or loose breadboard power jumpers cause intermittent microcontroller restarts, Brown-Out Resets (BOR), or LED flickering.
- **Why 1**: Why does the system fail when power fluctuates? Because the ATmega328P Brown-Out Detector triggers a hardware reset when $V_{CC}$ drops below the brownout threshold (~2.7V or 4.3V).
- **Why 2**: Why does the user not know a brownout occurred? Because without telemetry, a reset simply looks like the program froze or an arbitrary delay happened.
- **Why 3**: Why was there no indication of brownout resets? The firmware lacked a persistent boot message and heartbeat monitoring system to signal restarts to the host workstation.
- **Why 4**: Why was heartbeat telemetry omitted? Telemetry logging was not treated as a primary non-functional quality requirement in early iterations.
- **Why 5**: Why were non-functional electrical reliability requirements overlooked? The electronics project initially focused solely on software logic without accounting for real-world breadboard power delivery constraints.
- **Root Cause**: Lack of power-cycle/brownout diagnostic detection and absence of continuous heartbeat health telemetry.
- **Implemented Fix**: Added `emitHeartbeat(currentMillis)` emitting `[HEARTBEAT] Uptime: Xs | LED State: ... | Power: OK` every 2 seconds, and printed a dedicated boot announcement on power cycle so resets are immediately flagged. Also documented the mandatory 220Ω current-limiting resistor to protect the 5V rail from excess current draw.

---

## 3. Verification & Test Execution Results

| Test Case ID | Target Feature / Issue | Test Procedure | Expected Outcome | Actual Result | Status |
| :---: | :--- | :--- | :--- | :--- | :---: |
| **TC-01** | POST Startup Routine (Issue #1) | Power on Arduino and observe onboard LED and Serial Monitor. | LED flashes 3 times quickly; `[POST] PASSED` printed. | Verified. 3 quick pulses followed by normal blink. | **PASS** |
| **TC-02** | Non-blocking Timing (Issue #2) | Verify LED toggles every 500 ms while typing characters in Serial. | LED blinks continuously without pausing or freezing during user input. | Verified. No timing jitter observed. | **PASS** |
| **TC-03** | Pin Configuration Safety (Issue #3) | Verify `LED_PIN` is read-only and echoed correctly at startup. | Pin 13 logged as target output; initial state set to LOW. | Verified. Correct pin initialized. | **PASS** |
| **TC-04** | Heartbeat Telemetry (Issue #4) | Connect Serial Monitor at 9600 baud for 10 seconds. | Periodic heartbeat messages output every 2 seconds with incrementing uptime. | Verified. Uptime 2s, 4s, 6s... logged accurately. | **PASS** |
| **TC-05** | Brownout Simulation (Issue #4) | Unplug and reconnect USB cable to simulate power disruption. | Instant boot message printed; uptime resets to 0s, identifying restart. | Verified. Restart explicitly announced. | **PASS** |
| **TC-06** | Interactive Commands (Issue #5) | Send `'f'`, `'m'`, `'s'` over Serial Monitor. | Blink interval dynamically changes to 250ms, 500ms, and 1000ms. | Verified. Immediate rate adaptation. | **PASS** |
