# CAN Automotive Dashboard

A three-node automotive dashboard project built with embedded C for Microchip PIC18F4580 microcontrollers. Two ECU projects read driver/sensor inputs and publish vehicle data over CAN; a third project receives those messages and presents the values on a character LCD with indicator outputs.

## System Overview

| MPLAB X project | Role | Inputs and outputs |
| --- | --- | --- |
| `ecu1_rpm_ind.X` | RPM and turn-indicator ECU | Reads RPM from ADC channel 4 and indicator selection from the keypad; transmits RPM and indicator state. |
| `ecu2_spd_gr.X` | Speed and gear ECU | Reads speed from ADC channel 4 and gear changes from the keypad; transmits speed and gear. |
| `ecu3_dashboard.X` | Dashboard ECU | Receives CAN messages, displays gear, speed, RPM, and indicator state on the character LCD, and drives indicator outputs. |

The message IDs are defined in each project's `msg_id.h`. Keep these definitions consistent across all three nodes.

| CAN ID | Signal | Payload |
| --- | --- | --- |
| `0x10` | Speed | Three ASCII digits (space-padded when needed) |
| `0x20` | Gear | One ASCII character: `N`, `R`, or a forward gear digit |
| `0x30` | RPM | Four ASCII digits (space-padded when needed) |
| `0x40` | Engine temperature | Reserved; temperature acquisition and dashboard handling are not implemented yet |
| `0x50` | Indicators | One ASCII character: `0` off, `1` left, `2` right, `3` hazard |

The CAN drivers use standard 11-bit identifiers. CAN timing is configured in each project's `can.c`; all nodes and the physical bus must use compatible bit timing.

## Requirements

- MPLAB X IDE
- MPLAB XC8 C compiler (the projects are configured for XC8 3.10)
- Microchip `PIC18Fxxxx_DFP` device pack (project configuration specifies 1.2.26)
- PIC18F4580 hardware for each ECU, with suitable CAN transceivers and a correctly terminated CAN bus

The firmware source defines a 20 MHz oscillator frequency for delay calculations. Check the actual oscillator and project configuration against your hardware before programming the devices.

## Build

1. Open each `.X` folder as an MPLAB X project.
2. Select the `default` configuration and the appropriate PIC18F4580 programming/debug tool, if available.
3. Build each project in MPLAB X. Build the three projects separately; each produces its own firmware image.
4. Program each image to its corresponding ECU and connect the nodes to the CAN bus.

Generated production HEX files are placed under each project's `dist/default/production/` directory. Build output and IDE metadata are not source files; rebuild the images after changing firmware.

## Hardware Notes

- The firmware configures CAN TX on RB2 and CAN RX on RB3. A CAN transceiver is required between the PIC's CAN pins and the differential bus.
- Confirm that all nodes use matching CAN bit timing, common ground, and appropriate termination at the ends of the bus.
- The keypad, ADC inputs, LCD, and indicator output wiring must match the board design. Board schematics and a complete pin map are not included here.
- The ADC-to-RPM and ADC-to-speed conversions are project-specific demo calculations and should be calibrated for the sensors used.

## Repository Layout

```text
ecu1_rpm_ind.X/   RPM and indicator transmitter
ecu2_spd_gr.X/    Speed and gear transmitter
ecu3_dashboard.X/ CAN receiver, LCD display, and indicator outputs
```