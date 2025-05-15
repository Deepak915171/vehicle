  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <NewPing.h>
  // Define pins
  #define TRIG_PIN 11
  #define ECHO_PIN 12
  #define MOTOR_A_EN 5
  #define MOTOR_A_1 6
  #define MOTOR_A_2 7
  #define MOTOR_B_EN 10
  #define MOTOR_B_1 8
  #define MOTOR_B_2 9
  #define BUZZER_PIN 13       // Pin for the buzzer
  #define BLINK_SENSOR_PIN 4  // Pin for the eye blink sensor
  #define MQ2_SENSOR_PIN A3   // Pin for the MQ2 gas sensor
  #define MAX_DISTANCE 200
  #define MIN_DISTANCE_STOP 20      // Stop if obstacle is within 20 cm
  #define MIN_DISTANCE_SLOWDOWN 50  // Slow down if obstacle is within 50 cm
  #define GAS_THRESHOLD 500         // Adjust this threshold as needed
  #define BLINK_TIMEOUT 5000        // 5 seconds in milliseconds
  NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
  // Define LCD
  LiquidCrystal_I2C lcd(0x27, 16, 2);
  unsigned long lastBlinkTime = 0;
  // Setup function
  void setup() {
    // Initialize LCD
    lcd.init();
    lcd.backlight();
    // Motor pins setup
    pinMode(MOTOR_A_EN, OUTPUT);
    pinMode(MOTOR_A_1, OUTPUT);
    pinMode(MOTOR_A_2, OUTPUT);
    pinMode(MOTOR_B_EN, OUTPUT);
    pinMode(MOTOR_B_1, OUTPUT);
    pinMode(MOTOR_B_2, OUTPUT);
    // Set motor enable pins initially low
    digitalWrite(MOTOR_A_EN, LOW);
    digitalWrite(MOTOR_B_EN, LOW);
    // Buzzer pin setup
    pinMode(BUZZER_PIN, OUTPUT);
    // Eye blink sensor pin setup
    pinMode(BLINK_SENSOR_PIN, INPUT);  // setting eyeblink pin as INPUT
    // Initialize serial monitor
    Serial.begin(9600);
  }
  // Loop function
  void loop() {
    // Read distance from ultrasonic sensor
    int distance = sonar.ping_cm();
    // Read gas level from MQ2 sensor
    int gasLevel = analogRead(MQ2_SENSOR_PIN);
    // Update LCD with distance information
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
    // Check if there is an obstacle within the specified range
    if (distance > 0 && distance <= MIN_DISTANCE_STOP) {
      // If obstacle detected within 20cm, stop motors and sound the buzzer
      stopMotors();
      soundBuzzer();
      lcd.setCursor(0, 1);
      lcd.print("Obstacle Detected");
    } else {
      // If no obstacle within 20cm, move forward
      if (distance <= MIN_DISTANCE_SLOWDOWN) {
        // Slow down motors if obstacle detected within 50cm
        moveForwardSlow();
        lcd.setCursor(0, 1);
        lcd.print("Slowing Down");
      } else {
        // Move forward at normal speed
        moveForward();
        lcd.setCursor(0, 1);
        lcd.print("Moving Forward");
      }
    }
    // Check eye blink sensor state
    int blinkState = digitalRead(BLINK_SENSOR_PIN);
    // Read eye blink sensor state
    if (blinkState == LOW) {
      // If eyes are closed, update last blink time
      lastBlinkTime = millis();
    }
    // Check if there was no blink within the last 5 seconds
    if (millis() - lastBlinkTime >= BLINK_TIMEOUT) {
      // If no blink detected within 5 seconds, sound the buzzer and display on LCD
      soundBuzzer();
      lcd.setCursor(0, 2);
      lcd.print("Eyes Closed");
    }
    delay(50);  // providing a delay of 50ms between each loop
  }
  // Function to stop motors
  void stopMotors() {
    digitalWrite(MOTOR_A_EN, LOW);
    digitalWrite(MOTOR_B_EN, LOW);
  }
  // Function to move forward
  void moveForward() {
    digitalWrite(MOTOR_A_1, HIGH);
    digitalWrite(MOTOR_A_2, LOW);
    digitalWrite(MOTOR_B_1, HIGH);
    digitalWrite(MOTOR_B_2, LOW);
    // Set motor enable pins to enable movement
    digitalWrite(MOTOR_A_EN, HIGH);
    digitalWrite(MOTOR_B_EN, HIGH);
  }
  // Function to move forward slowly
  void moveForwardSlow() {
    // Adjust motor speed to slow down
    analogWrite(MOTOR_A_EN, 150);
    analogWrite(MOTOR_B_EN, 150);
    digitalWrite(MOTOR_A_1, HIGH);
    digitalWrite(MOTOR_A_2, LOW);
    digitalWrite(MOTOR_B_1, HIGH);
    digitalWrite(MOTOR_B_2, LOW);
  }
  // Function to sound the buzzer
  void soundBuzzer() {
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
    delay(100);                      // Buzzer on time
    digitalWrite(BUZZER_PIN, LOW);
  }