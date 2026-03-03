# 🔐 Smart Security Lock System with TFT Display (Arduino Mega)

> 🚀 A fully interactive **Embedded Security System** built using Arduino Mega,  
> featuring Password Protection, Master Reset, TFT Graphics UI, Ultrasonic Detection, Servo Locking Mechanism, and Buzzer Feedback.

---

## 🌟 Project Overview

This project is a **Smart Digital Lock System** that activates when a person approaches.  
It provides:

- 🎨 Graphical TFT Interface (ILI9341)
- 🔢 4x4 Keypad Password Entry
- 🔐 Servo Motor Lock Mechanism
- 📡 Ultrasonic Distance Detection
- 🔊 Audio Feedback (Buzzer)
- 💾 EEPROM Password Storage
- 🛠 Master Reset Feature

---

## 🧠 System Workflow

1. 📡 Ultrasonic sensor detects a person within 25cm.
2. 🎵 Buzzer gives activation sound.
3. 🖥 TFT screen prompts for password.
4. 🔑 If correct:
   - Green UI
   - Happy Emoji 😊
   - Servo Unlocks
5. ❌ If wrong:
   - Red UI
   - Angry Emoji 😡
   - Error Alarm
6. 🔁 Master Key allows password reset.

---

## 🛠 Hardware Used

| Component | Model |
|-----------|--------|
| Microcontroller | Arduino Mega |
| TFT Display | ILI9341 320x240 |
| Keypad | 4x4 Matrix Keypad |
| Servo Motor | SG90 / MG90 |
| Ultrasonic Sensor | HC-SR04 |
| Buzzer | Active Buzzer |
| Memory | EEPROM (Internal) |

---

## 📌 Pin Configuration

### 🎨 TFT Display
```
TFT_CS  -> 53
TFT_DC  -> 49
TFT_RST -> 48
```

### 🔐 Servo
```
SERVO_PIN -> 9
```

### 🔊 Buzzer
```
BUZZER_PIN -> 8
```

### 📡 Ultrasonic Sensor
```
TRIG_PIN -> 11
ECHO_PIN -> 12
```

### 🔢 Keypad
```
Row Pins: 22, 24, 26, 28
Col Pins: 30, 32, 34, 36
```

---

## 💾 Password System

- Default: User sets password at first boot
- Stored in EEPROM
- 4-digit numeric password
- 🔑 Master Reset Key: `951478632`

---

## 🎨 UI Features

✔ Centered Dynamic Text  
✔ Lock / Unlock Icons  
✔ Radar Animation Standby Mode  
✔ Happy & Angry Emojis  
✔ Color Feedback System  

---

## 📷 Project Preview

> Add your project simulation or hardware image here

```
/images/project-preview.png
```

---

## 📦 Libraries Required

Install via Arduino Library Manager:

- Adafruit GFX
- Adafruit ILI9341
- Keypad
- Servo
- EEPROM (Built-in)

---

## 🚀 How to Run

1. Clone the repository
2. Open in Arduino IDE
3. Install required libraries
4. Select **Arduino Mega**
5. Upload code
6. Power the system
7. Set password on first boot

---

## 🔥 Features Highlight

✨ Real-time Proximity Activation  
✨ Secure EEPROM Password Storage  
✨ Interactive UI  
✨ Master Reset Mode  
✨ Embedded System Design  
✨ Hardware + Software Integration  

---

## 🏗 Future Improvements

- 📲 Bluetooth Unlock
- 🧠 Face Recognition
- 📡 WiFi Logging
- 🔔 GSM Alert System
- 📊 Access Log System

---

## 👨‍💻 Author

**AnanthaKrishna M Ghate**  
Embedded Systems Developer | AI + Hardware Enthusiast  

---

## ⭐ If you like this project

Give this repository a ⭐ and share your feedback!

---

# 🔒 Secure • Smart • Interactive • Embedded Innovation
