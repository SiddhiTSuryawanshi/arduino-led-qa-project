---
name: QA Bug Report
about: Log a Quality Assurance (QA) defect or anomaly identified in the embedded system
title: '[BUG]: '
labels: bug
assignees: SiddhiTSuryawanshi
---

## Summary
Brief description of the observed defect or quality concern in the Arduino LED system.

## Hardware & Environment Details
- **Microcontroller**: Arduino Uno R3 / Nano (ATmega328P)
- **Clock Speed**: 16 MHz
- **Operating Voltage**: 5V USB / External Barrel Jack
- **Pin Connected**: Pin 13 (Digital Output)
- **External Components**: 220 Ohm current-limiting resistor, 5mm LED

## Steps to Reproduce
1. Upload sketch to Arduino Uno.
2. Connect external hardware / observe onboard LED.
3. Observe behavior during power application or serial monitoring.

## Expected Behavior
Clear and concise description of what the system was expected to do according to project specifications.

## Actual Behavior
Clear description of what actually occurred (e.g. freeze, incorrect timing, failure to illuminate).

## Severity Classification
- [ ] **High** (Blocks core system execution or poses hardware/timing hazard)
- [ ] **Medium** (Degrades performance, user experience, or operational responsiveness)
- [ ] **Low** (Minor cosmetic, documentation, or logging defect)

## Root Cause Analysis (5-Why Methodology)
1. **Why 1**: 
2. **Why 2**: 
3. **Why 3**: 
4. **Why 4**: 
5. **Why 5**: 
- **Root Cause**: 

## Proposed Solution / Fix
Describe the recommended firmware or hardware modification to resolve the defect.
