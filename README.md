# 🦇 Bat Clock

This is a simple digital alarm clock with a Batman theme to it.

A simulation on how the project works can be found on Wokwi [here](https://wokwi.com/projects/446649526542284801).

---

## 🧰 Parts used

- Arduino Uno  
- **DS3231 RTC Module**
  - SDA → A4  
  - SCL → A5  
- TM1637 (4-digit 7-segment) display  
- **3× Push Buttons**
  - Mode  
  - Hour Increment  
  - Enter  
- **A Potentiometer** (A0) 
- Buzzer 

---

## 🔧 Mode Overview

### **Normal Mode**
- Displays the current time.  
- If current time == alarm time → buzzer output triggers.

---

### **Alarm Mode**
Used to **set alarm time**.

- **Hour Increment button** → increases hour
- **Potentiometer** → changes minutes  
- **Enter** → sets the alarm time

---

### **Set Mode**
Used to **change the actual clock time**.

- **Hour Increment button** → increases hour  
- **Potentiometer** → changes minutes  
- **Enter** → set the time

---

## 🧱 Enclosure

Here is an image of the enclosure design:

![Enclosure Preview](CAD_image.png)

You can find the latest version of the 3d model here:
```
Bat Clock/
├── 3D Models/
   └── Bat Clock v2.f3d
```

And you can find the different parts for 3d printing here:
```
Bat Clock/
├── 3D Models/
  │ 
  └── Parts/
      ├── Base.stl
      ├── Lid.stl
      ├── Pole.stl
      ├── Bat symbol.stl
      └── Bat Lid.stl

```
---
## Wiring
Here is a preview of the wiring
:

![Schematic Preview](alarm_clock.jpg)

You can find the wiring diagram here:
```
Bat Clock/
├── Schematics/
   └── alarm_clock.jpg
```

---

---
## Disclaimer
The project is not done and stil need to under go some revisions especially with the 3d model.

Still yet to check the tolerances and make sure everything fits well

