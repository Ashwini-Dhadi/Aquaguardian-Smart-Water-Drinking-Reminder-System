# Aquaguardian-Smart-Water-Drinking-Reminder-System

An embedded water drinking reminder system designed to help users maintain regular hydration through scheduled reminders using an RTC, LCD, keypad, buzzer, and interrupt-based control.

## Features

- Real-time date and time tracking
- Scheduled drinking reminders
- LCD-based information display
- Keypad-based user interaction
- Buzzer notification for reminders
- RTC-based time management
- Interrupt-based control
- Simple and user-friendly operation

## Hardware Used

- ARM7 Microcontroller
- 16x2 LCD
- 4x4 Matrix Keypad
- RTC
- Buzzer
- Push Button / Switch

## Project Flow

The system starts by initializing the required peripherals such as the LCD, RTC, keypad, buzzer, and interrupt system.

The RTC continuously maintains the current time. The system compares the current time with the configured reminder schedule.

When the reminder time is reached, the system provides an alert through the buzzer and displays the required information on the LCD.

The keypad can be used for user interaction and setting the required options.

After providing the reminder, the system continues monitoring the time for the next scheduled reminder.

## Normal Mode

1. Initialize the required hardware peripherals.
2. Read and maintain the current time using the RTC.
3. Continuously monitor the reminder schedule.
4. Compare the current time with the configured reminder time.
5. Display the required information on the LCD.
6. Activate the buzzer when a reminder is triggered.
7. Continue monitoring for the next reminder.

## User Interaction

1. The user interacts with the system through the keypad.
2. Required options or settings are selected.
3. The entered values are processed by the system.
4. The LCD provides the corresponding information.
5. The system continues normal reminder operation.

## Software Modules

- `main.c` – Main program and overall system flow
- `aquaguardian.c` – Main AquaGuardian functionality
- `aquaguardian.h` – AquaGuardian definitions
- `rtc-1.c` – RTC handling
- `rtc.h` – RTC definitions
- `lcd (1).c` – LCD interfacing
- `lcd.h` – LCD functions
- `kpm-1.c` – Keypad interfacing
- `kpm.h` – Keypad definitions
- `interrupt-1.c` – Interrupt handling
- `delay (1).c` – Delay functions
- `types (1).h` – Data type definitions

## About

An embedded hydration reminder system using RTC, LCD, keypad, buzzer, and interrupt functionality to provide timely drinking reminders.

## Project Type

**Embedded Systems / ARM7 / Real-Time Reminder System**
