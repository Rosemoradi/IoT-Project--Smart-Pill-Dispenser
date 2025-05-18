# IoT-Project--Smart-Pill-Dispenser
A smart Arduino-based pill dispenser that uses a servo motor, buzzer, RTC, and LCD to automate and remind users about medication schedules. With 3D-printed compartments, it ensures timely dispensing for elderly or chronic patients—affordable, portable, and user-friendly :)
# 💊 Smart Pill Dispenser with Alarm | Arduino IoT Project

This project presents an IoT-enabled **automated medicine dispenser** designed to support medication adherence for elderly patients or those with chronic conditions. It combines a servo-driven dispensing mechanism, a buzzer-based alarm, LCD interaction, and an RTC for time tracking, all controlled by an Arduino Uno.

---

## 🧠 Project Overview

- **Microcontroller**: Arduino Uno
- **Functionality**:
  - Dispenses pills at scheduled times using a **servo motor**
  - Alerts users with a **buzzer**
  - Displays time & messages on a **16x2 LCD**
  - Tracks time with a **DS3231 RTC module**
- **Power Supply**: 5V USB or portable battery (~12 hrs on 2000 mAh)

---

## 🛠️ Components Used

| Component        | Purpose                          |
|------------------|----------------------------------|
| Arduino Uno      | Core controller                  |
| Servo Motor      | Rotates pill compartments        |
| RTC DS3231       | Maintains real-time clock        |
| Buzzer           | Audio alert for missed doses     |
| LCD Display      | User interface & scheduler       |
| Button           | Manual interaction input         |
| 3D-Printed Box   | Holds pill compartments          |

---

## 🔁 How It Works

1. **User inputs medication times** using the LCD and button.
2. **RTC** keeps track of time.
3. At the correct time:
   - **Buzzer** sounds
   - **Servo motor** rotates to correct compartment
   - **LCD** displays a reminder
4. If dose is missed, alarm repeats after a delay.

---

## 📊 Results

- ✅ **95% dispensing accuracy** (some misalignment due to irregular pill shapes)
- ✅ **User setup time**: <2 minutes
- ✅ **Buzzer reliability**: 80% across test cycles
- ⚠️ Room for improvements in larger fonts and app integration

---

## 🔧 Programming

The Arduino `.ino` file uses:

- `Servo.h` – to control the rotation
- `Wire.h` & `RTClib.h` – for I2C and RTC
- `LiquidCrystal.h` – for LCD control
- **Debounced button input** for reliability
- Timing logic for pill dispensing and alerts

---

## 🧪 Testing

| Metric                 | Result                  |
|------------------------|-------------------------|
| Dispensing Accuracy    | ~95%                    |
| Alarm Reliability      | 80%                     |
| LCD Usability          | Fast, but font size limited |
| Battery Runtime        | ~12 hrs on 2000 mAh     |

---

## 🧱 Future Improvements

- 📱 Mobile app or Bluetooth scheduling
- 🗣️ Voice alert and speech-based interaction
- 📦 Smarter container to handle pill shape variance



---

## 📎 References

- Arduino Documentation: https://www.arduino.cc/
- WHO: Adherence to long-term therapies
- IoT Healthcare Journals (2022–2023)
