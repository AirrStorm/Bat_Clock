# 🦇 Bat Clock — DIY Arduino Alarm Clock

Bat Clock is a simple but clean digital alarm clock built using an Arduino, a DS3231 real-time clock module, and physical buttons for input.  
It displays real time, lets you view/set an alarm, and fits neatly into a 3D-printed enclosure.

---

## ✨ Features

- Accurate timekeeping with **DS3231 RTC**
- **Three operating modes** controlled by the *Mode* button:
  - **Normal Mode** → shows current real time
  - **Alarm Mode** → view/edit alarm time
  - **Set Mode** → adjust the actual clock time
- **Buttons:**
  - **Mode** — cycle between modes
  - **Hour Increment** — increases hour value during editing
  - **Enter** — save time/alarm settings
- **Potentiometer** to set minutes (0–59)
- Alarm pin for buzzer/DFPlayer (optional)
- Fully 3D-printed enclosure

---

## 🧰 Hardware Used

- Arduino Nano or Uno  
- **DS3231 RTC Module**
  - SDA → A4  
  - SCL → A5  
- TM1637 (4-digit 7-segment) display  
- **3× Push Buttons**
  - Mode  
  - Hour Increment  
  - Enter  
- **1× Potentiometer** (A0) — controls minutes  
- Optional: Buzzer (digital output pin)  
- 5V power  
- 3D-printed enclosure  

---

## 🔧 Mode Overview

### **Normal Mode**
- Displays the current real time.  
- If current time == alarm time → buzzer output triggers.

---

### **Alarm Mode**
Used to **view or edit the alarm time**.

- **Hour Increment button** → changes hour  
- **Potentiometer** → changes minutes  
- **Enter** → saves alarm time

---

### **Set Mode**
Used to **change the actual clock time stored in the DS3231**.

- **Hour Increment button** → changes hour  
- **Potentiometer** → changes minutes  
- **Enter** → saves clock time to RTC

---

## 🧱 Enclosure

Here is an image of the enclosure design:

![Enclosure Preview](CAD_image.jpeg)


The case is designed for:

- TM1637 display  
- 3 buttons (Mode, Enter, Hour Increment)  
- Potentiometer knob  
- Optional buzzer  

---

