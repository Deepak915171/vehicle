# 🚗 Vehicle Accident Avoidance and Collision Alert System

This Arduino-based project is a smart safety system designed to prevent accidents and alert for critical conditions like driver drowsiness and smoke/fire. It uses sensors to detect obstacles, monitor the driver’s eyes, and check for harmful gases. Based on these readings, it controls the vehicle's motors and activates alerts accordingly.

---

## 🔧 Features

- **Obstacle Detection** using Ultrasonic Sensor
- **Fire/Smoke Detection** using MQ2 Gas Sensor
- **Driver Drowsiness Detection** using Eye Blink Sensor
- **Motor Speed and Direction Control**
- **Real-Time Alerts** via LCD and Buzzer
- **Failsafe Mechanism** to stop the vehicle when a threat is detected

---

## 📦 Components Used

- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- MQ2 Gas Sensor
- Eye Blink Sensor (IR-based)
- L298N Motor Driver Module
- Two DC Motors
- LCD Display (16x2 with I2C)
- Buzzer
- Jumper Wires, Breadboard, Power Supply

---

## ⚙️ How It Works

1. **Obstacle Detection**:
   - Uses the ultrasonic sensor to measure the distance to any object in front of the vehicle.
   - If the object is too close (≤ 20 cm), the vehicle stops.
   - If it's within a moderate range (≤ 50 cm), the vehicle slows down.

2. **Smoke/Gas Detection**:
   - MQ2 gas sensor constantly monitors the surrounding air.
   - If it detects harmful gas/smoke above a set threshold, the vehicle stops and a long buzzer alert is sounded.

3. **Driver Eye Monitoring**:
   - The eye blink sensor checks if the driver’s eyes are open.
   - If eyes remain closed for over 5 seconds, the system assumes drowsiness and stops the vehicle, activating a short alert.

4. **Display and Alerts**:
   - A 16x2 I2C LCD displays distance, status, and alerts.
   - A buzzer provides short and long beeps for different warning levels.

5. **Motor Control**:
   - Motors move forward normally if the path is clear.
   - Motors slow down or stop based on sensor conditions.

---

## 🧠 Function Summary

- `moveForward()`: Moves the vehicle forward at full speed.
- `moveForwardSlow()`: Moves the vehicle forward at reduced speed.
- `stopMotors()`: Stops both motors immediately.
- `soundBuzzerShort()`: Emits a short beep (used for minor alerts).
- `soundBuzzerLong()`: Emits a long beep (used for critical alerts like fire/gas).

---

## 🚀 Getting Started

1. Upload the Arduino sketch to your board using the Arduino IDE.
2. Connect all components as per the schematic (refer to your circuit diagram).
3. Power the system and observe the LCD for sensor readings.
4. Test each safety scenario (e.g., place an object ahead, simulate closed eyes, or bring smoke near MQ2).

---

## 📋 Applications

- Autonomous Vehicles
- Robotics Safety Systems
- Driver Monitoring for Transportation
- Smart Emergency Response Vehicles

---

## 📄 License

This project is open-source and free to use for educational and non-commercial purposes.

---

## 🙋‍♂️ Author

**Project By:** [Your Name]  
**College:** BIET  
**Guided By:** [Faculty/Instructor Name]

---

## 📷 Screenshots / Demo (Optional)

*Add images or a GIF showing your system working here.*

---

