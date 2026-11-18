# Quality Assurance Methodology & 5-Why Investigation

## QA Defect Lifecycle
All hardware and firmware quality concerns in this project are tracked using GitHub Issues and classified under standard severity tiers:
- **High**: Blocking defects causing hardware stall, infinite loops, or electrical stress.
- **Medium**: Performance latency, sluggish responsiveness, or lack of diagnostic logging.
- **Low**: Feature requests, code formatting, or minor telemetry enhancements.

## 5-Why Investigation Summary

### 1. Defect #1: Inactive LED on Boot (Severity: High)
- **Root Cause**: Absence of a startup Power-On Self-Test (POST) and hardware diagnostic feedback loop in firmware.
- **Resolution**: Implemented 3-pulse POST routine in `runPowerOnSelfTest()` with serial confirmation.

### 2. Defect #2: Sluggish Blinking & Blocking Execution (Severity: Medium)
- **Root Cause**: Architectural reliance on blocking synchronous delay functions (`delay()`) rather than asynchronous timer polling.
- **Resolution**: Migrated to `millis()` state machine with 500 ms default interval and interactive serial command controls.

### 3. Defect #3: Unsafe Pin Assignment (Severity: High)
- **Root Cause**: Use of untyped/mutable global variables (`int led = 13`) for hardware GPIO definitions and omission of pin-state verification logging.
- **Resolution**: Defined `const uint8_t LED_PIN = 13;` with explicit `pinMode` verification and Serial echo.

### 4. Defect #4: Power Brownout & Intermittent Reset (Severity: Medium)
- **Root Cause**: Lack of power-cycle/brownout diagnostic detection and absence of continuous heartbeat health telemetry.
- **Resolution**: Added 2-second Serial Heartbeat reporting uptime, state, and power continuity, plus current-limiting resistor specifications.
