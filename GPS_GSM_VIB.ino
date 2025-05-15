#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);   // RX, TX for GPS
SoftwareSerial gsmSerial(7, 8);   // RX, TX for GSM

const int vibrationPin = 2;
bool accidentDetected = false;
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(vibrationPin, INPUT);
  delay(1000);

  sendSMS("System Ready: Accident Alert Activated");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (digitalRead(vibrationPin) == HIGH) {
    if (!accidentDetected && millis() - lastSendTime > 10000) {
      accidentDetected = true;
      lastSendTime = millis();

      float lat = gps.location.lat();
      float lng = gps.location.lng();

      String smsText = "Accident Detected!\n";
      smsText += "Location: https://maps.google.com/?q=";
      smsText += String(lat, 6) + "," + String(lng, 6);
      sendSMS(smsText);

      Serial.println("Accident Detected! SMS Sent.");
    }
  } else {
    accidentDetected = false;
  }
}

void sendSMS(String message) {
  gsmSerial.println("AT+CMGF=1"); // SMS text mode
  delay(100);
  gsmSerial.println("AT+CMGS=\"+91XXXXXXXXXX\""); // Replace with your number
  delay(100);
  gsmSerial.print(message);
  delay(100);
  gsmSerial.write(26); // Ctrl+Z
  delay(3000);
}
