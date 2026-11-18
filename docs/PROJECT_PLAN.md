# Project Management Plan: Arduino LED QA & Diagnostic System

**Department of Electronics & Telecommunication Engineering**  
**MIT Academy of Engineering, Alandi (D), Pune - 412105**  
**Academic Year:** 2026–2027 | **Semester:** VII | **Class:** BTech Div C  
**Course:** Project Management (Course Code: 2307476T)  
**Course Teacher:** Dr. Ashish Mulajkar  
**Student:** Siddhi T. Suryawanshi (Email: siddhisuryawanshi010@gmail.com)  
**Repository:** [arduino-led-qa-project](https://github.com/SiddhiTSuryawanshi/arduino-led-qa-project)

---

## 1. Executive Summary & Activity Scope
This project management plan establishes the collaborative quality assurance (QA) framework, issue lifecycle, and firmware implementation roadmap for an embedded electronics system: the **Arduino LED Blinking & Diagnostic System**.

The primary objective is to apply industry-standard QA methodologies—specifically **GitHub Issues**, **Root Cause Analysis (5-Why Technique)**, **Branch-and-PR Workflows**, and **Documentation Traceability**—to identify, document, and resolve embedded firmware and hardware-interface anomalies.

---

## 2. Course Outcomes (CO) & Rubric Alignment
- **Course Outcome Addressed**: CO2 – Implementation of Collaborative Tools and QA Processes.
- **RBT Level**: Level 3 (Apply).
- **Assessment Criteria**:
  1. *Analysis of QA Documentation & GitHub Usage* (5 Points): Structured issue templates, Wiki documentation, Pull Request reviews, and Git branch strategy.
  2. *Problem Identification & Root Cause Analysis* (5 Points): Formal identification of 4+ real-world electronics/firmware defects using the 5-Why RCA framework.
  3. *Solution Implementation & Documentation* (5 Points): Verifiable code refactoring, non-blocking timing, commit-to-issue traceability, and resolution logs.

---

## 3. Work Breakdown Structure (WBS)

```
Arduino LED QA Project
├── 1.0 Project Initiation & Repository Architecture
│   ├── 1.1 Remote Repository Setup (GitHub)
│   ├── 1.2 Baseline Arduino Firmware v0.1 (Simple Delay Blink)
│   └── 1.3 Issue Template Configuration (.github/ISSUE_TEMPLATE)
├── 2.0 Quality Assurance Problem Identification
│   ├── 2.1 Issue #1: LED Inactivity (Pin Mapping & State Defect)
│   ├── 2.2 Issue #2: Timing Latency & Blocking Delay (1000ms freeze)
│   ├── 2.3 Issue #3: Pin Configuration & Magic Number Hazard
│   ├── 2.4 Issue #4: Power Supply Brownout & Stability Hazard
│   └── 2.5 Issue #5: Dynamic Rate Control Enhancement (Backlog)
├── 3.0 Root Cause Analysis & 5-Why Investigation
│   ├── 3.1 Trace mechanical, electrical, and firmware dependencies
│   ├── 3.2 Formalize 5-Why analysis tables in docs/QA_LOG.md
│   └── 3.3 Prioritize defect resolution by Severity (High, Medium, Low)
├── 4.0 Firmware Refactoring & Solution Implementation
│   ├── 4.1 Git Branch Creation (qa-fixes-and-docs)
│   ├── 4.2 Non-blocking timing engine using millis()
│   ├── 4.3 Power-On Self-Test (POST) 3-blink verification routine
│   ├── 4.4 Telemetry heartbeat & Serial diagnostic monitor
│   └── 4.5 Interactive serial command parser
├── 5.0 Verification, Code Review & Pull Request Lifecycle
│   ├── 5.1 Verification against AVR compiler
│   ├── 5.2 Pull Request submission & cross-issue linkage
│   ├── 5.3 Code review validation & merge into main branch
│   └── 5.4 Issue closure with resolution traceability logs
└── 6.0 Project Closeout & Academic Reporting
    ├── 6.1 GitHub Wiki deployment
    ├── 6.2 Generation of Moodle submission report (.docx / PDF)
    └── 6.3 Learning outcomes synthesis
```

---

## 4. Project Schedule & Milestones

| Milestone ID | Description | Target Date | Status | Deliverable |
| :--- | :--- | :--- | :--- | :--- |
| **M1** | Baseline repository creation & initial sketch commit | Nov 18, 2026 | **Completed** | `led_blink.ino` v0.1 |
| **M2** | QA issue logging with severity labels (#1 to #4) | Nov 18, 2026 | **Completed** | GitHub Issues #1–#4 |
| **M3** | 5-Why Root Cause Analysis & QA Log compilation | Nov 18, 2026 | **Completed** | `docs/QA_LOG.md` |
| **M4** | Non-blocking firmware development on feature branch | Nov 18, 2026 | **Completed** | Branch `qa-fixes-and-docs` |
| **M5** | Pull Request creation, review, and merge to `main` | Nov 18, 2026 | **Completed** | PR #1 Merged |
| **M6** | Issue resolution documentation & closure | Nov 18, 2026 | **Completed** | Closed Issues #1–#4 |
| **M7** | GitHub Wiki creation and Moodle report generation | Nov 18, 2026 | **Completed** | Wiki + Report `.docx` |

---

## 5. Risk Assessment & Management

| Risk ID | Identified Risk | Impact | Probability | Mitigation Strategy |
| :--- | :--- | :--- | :--- | :--- |
| **R1** | Microcontroller freezes due to blocking `delay()` | High | High | Implement non-blocking asynchronous timing loop using `millis()`. |
| **R2** | Wrong GPIO pin assigned causing circuit malfunction | High | Medium | Enforce typed constant `const uint8_t LED_PIN` and startup POST verification. |
| **R3** | Unstable USB supply voltage causing silent brownouts | Medium | High | Add periodic Serial Heartbeat and power-cycle initialization alert. |
| **R4** | Lost traceability between QA issues and code changes | High | Low | Enforce keyword linking (`Fixes #1`) in commit messages and Pull Requests. |

---

## 6. Hardware & Tool Specifications
- **Hardware Platform**: Arduino Uno R3 / ATmega328P (16 MHz, 5V logic).
- **Indicators**: Onboard LED (Pin 13) and external 5mm green/red LED via 220Ω ballast resistor.
- **Development & QA Tools**: Arduino IDE / CLI, Git, GitHub Issues, GitHub Pull Requests, GitHub Wiki.
