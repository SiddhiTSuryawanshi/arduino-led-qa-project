## Description of Changes
Brief description of firmware or documentation modifications introduced in this pull request.

## Quality Assurance Traceability
Resolves the following logged GitHub QA issues:
- Fixes #1 (LED is not blinking)
- Fixes #2 (LED blinking delay is too high)
- Fixes #3 (Incorrect LED pin configuration)
- Fixes #4 (Power supply problem)

## Key Technical Modifications
- [x] **Non-blocking Timing**: Transitioned from blocking `delay()` to `millis()` asynchronous state machine.
- [x] **Pin Safety**: Standardized pin definitions using `const uint8_t LED_PIN` with explicit `pinMode` verification.
- [x] **Power-On Self-Test (POST)**: Implemented 3-cycle startup blink routine to test GPIO connectivity.
- [x] **System Telemetry**: Added 2-second Serial Heartbeat reporting uptime, state, and power continuity.
- [x] **Documentation**: Added comprehensive README, Project Plan, and QA Log.

## Verification & Testing Evidence
- **Build Status**: Compiled cleanly in Arduino AVR compiler with zero warnings.
- **Serial Diagnostics**: Verified baud rate 9600 telemetry output on serial terminal.
- **Responsiveness**: Tested interactive serial command processing during active blinking.
