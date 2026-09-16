# AquaGuardian – Smart Water Drinking Reminder System

An embedded water drinking reminder system designed to help users maintain regular hydration through scheduled reminders using an RTC, LCD, keypad, buzzer, and interrupt-based control.

## Table of Contents

- [📌 Project Overview](#project-overview)
- [🎯 Objectives](#objectives)
- [🖼️ Block Diagram](#block-diagram)
- [🏗️ System Architecture](#system-architecture)
- [⚙️ Hardware Requirements](#hardware-requirements)
- [💻 Software Requirements](#software-requirements)
- [📂 Repository Structure](#repository-structure)
- [✨ Features](#features)
- [▶️ Build Instructions](#build-instructions)
- [📈 Future Enhancements](#future-enhancements)
- [👤 Author](#author)

## 📌 Project Overview

AquaGuardian is an embedded healthcare application built on the LPC2148 (ARM7) microcontroller. It uses a Real-Time Clock to track the current time, reminds the user to drink water at scheduled intervals, and lets the user log intake, view progress, and adjust settings — all through an LCD, keypad, LEDs, and buzzer.

## 🎯 Objectives

- Display the current date and time obtained from the RTC on the LCD
- Generate automatic reminders for drinking water
- Allow the user to record each glass of water consumed using a push button
- Maintain and display a configurable daily water intake goal
- Continuously compare the RTC time with the scheduled reminder interval
- Display the number of glasses consumed and the remaining daily target
- Provide LED indications representing hydration status
- Generate buzzer alerts whenever it is time to drink water

## 🖼️ Block Diagram

![AquaGuardian Block Diagram](aquaguardian_block_diagram.svg)

The keypad, switch, and drink button are the system's inputs to the LPC2148. The RTC runs inside the microcontroller to track time. The controller drives the LCD for status information, the green and yellow LEDs for hydration status, and the buzzer for reminder alerts.

## 🏗️ System Architecture

| Layer | Component | Role |
|---|---|---|
| Input | Keypad | Enter settings (goal, RTC time) in configuration mode |
| Input | Switch (interrupt) | Enters configuration mode |
| Input | Drink button (interrupt) | Logs a glass of water consumed |
| Core | LPC2148 (ARM7) | Runs the main loop, timing comparisons, and state logic |
| Core | RTC | Maintains current date/time; drives the reminder schedule and midnight reset |
| Output | 16x2 LCD | Shows time, glasses consumed, remaining target, and settings menu |
| Output | Green LED | Daily hydration goal achieved |
| Output | Yellow LED | Reminder — time to drink water |
| Output | Buzzer | Audible alert when a reminder is triggered |

The system runs in two modes: **Normal Mode**, where it monitors time and hydration status, and **Configuration Mode**, entered via the switch interrupt, where the keypad is used to update settings.

## ⚙️ Hardware Requirements

- LPC2148 (ARM7 microcontroller)
- 16x2 LCD
- 4x4 Matrix Keypad
- LEDs (Green, Yellow)
- Push Button / Switch
- Buzzer
- USB-UART Converter / DB-9 Cable

## 💻 Software Requirements

- Embedded C Programming
- Keil µVision (or equivalent ARM7 IDE)
- Flash Magic

## 📂 Repository Structure

| File | Description |
|---|---|
| `main.c` | Main program and overall system flow |
| `aquaguardian.c` | Main AquaGuardian functionality |
| `aquaguardian.h` | AquaGuardian definitions |
| `rtc-1.c` | RTC handling |
| `rtc.h` | RTC definitions |
| `lcd (1).c` | LCD interfacing |
| `lcd.h` | LCD functions |
| `kpm-1.c` | Keypad interfacing |
| `kpm.h` | Keypad definitions |
| `interrupt-1.c` | Interrupt handling |
| `delay (1).c` | Delay functions |
| `types (1).h` | Data type definitions |

## ✨ Features

- Real-time date and time tracking
- Scheduled drinking reminders
- LCD-based information display
- Keypad-based user interaction
- Buzzer notification for reminders
- RTC-based time management
- Interrupt-based control
- Simple and user-friendly operation

## ▶️ Build Instructions

1. Open the project in Keil µVision and add all `.c` / `.h` files listed under [Repository Structure](#repository-structure).
2. Select the LPC2148 target device and configure the correct crystal frequency in the project settings.
3. Build the project to generate the `.hex` output file.
4. Connect the board to your PC using the USB-UART converter / DB-9 cable.
5. Open Flash Magic, select the correct COM port and baud rate, and load the generated `.hex` file.
6. Flash the microcontroller and reset the board to run the application.

## 📈 Future Enhancements

- Add EEPROM/flash logging to retain hydration history across power cycles
- Add a Red LED to flag missed reminders or significant backlog against the daily target
- Add Bluetooth/Wi-Fi connectivity to sync hydration data to a mobile app
- Support multiple user profiles with individual daily goals

## 👤 Author
Dhadi Ashwini  
Embedded Systems / ARM7 Project

