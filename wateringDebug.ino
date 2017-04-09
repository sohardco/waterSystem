#define pumpPin 2
#define valve1Pin 3
#define valve2Pin 4
#define valve3Pin 5
#define valve4Pin 6
#define valve5Pin 7
#define sensorPower 8

#define humiditySensor1 A0
#define humiditySensor2 A1
#define humiditySensor3 A2
#define humiditySensor4 A3
#define humiditySensor5 A6

// Timing control section
#define delayHour 3000//1000L * 60 * 60  // Watering cycle shutdown delay

int middleOfDayStart = 12; // Used to define sleep time diapason
int middleOfDayStop = 15;
int dusk = 0;
int dawn = 6;

#include <DS3231.h>
DS3231  rtc(A4, A5); // Init the DS3231 using the hardware interface

//Time rtcTime = rtc.getTime();  // get RTC compund data (object)
// int MySec = MyTime.sec;  // extract seconds - not used in condition further below
// int MyMin = MyTime.min;  //extract minutes
int rtcHour = 7;//rtcTime.hour;  // extrac hour

// boolean startCheckCycle = false;

int valvePowerPins[] = {valve1Pin, valve2Pin, valve3Pin, valve4Pin, valve5Pin};
int pinCount = 5;

int humidityData[] = {1000, 0, 0, 0, 1000};
int sensorCount = 5;

boolean potsNeedWatering[5];
int potsCount = 5;

void setup() {

   Serial.begin(9600);

  rtc.begin();

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);

  configurePowerPinMode();
  configureSensorPinMode();

}

void loop() {

  if(isTimeToWater() == true){
    Serial.println("Start Check/Watering");
    moistureLevelChecker();
    potWatering();
  }
  else{
  Serial.println("No need to water");
  delay(delayHour);
  }
}

// Transistor pins status and type declaration

void configurePowerPinMode() {
  for(int i = 0; i < pinCount; i++) {
    pinMode(valvePowerPins[i], OUTPUT);
    digitalWrite(valvePowerPins[i], LOW);
   }
}

// Sensor pins status and type declaration

void configureSensorPinMode() {
  for(int i=0; i < sensorCount; i++) {
    pinMode(humidityData[i],INPUT);
  }
}

boolean isTimeToWater() {
  if((rtcHour >= middleOfDayStart) && (rtcHour <= middleOfDayStop) || (rtcHour >= dusk) && (rtcHour <= dawn)) {
    return false;
  }
  return true;
}

// Checks soil moisture level from sensors, maps values to percents and records data to new array in boolean

void moistureLevelChecker() {

  digitalWrite(sensorPower, HIGH);

  for(int i = 0; i < sensorCount; i++) {
    int rawSensorData = humidityData[i];
    Serial.print("Rawdata: ");
    Serial.println(rawSensorData);
    delay(1000);
    int sensorDataInPercent = map(rawSensorData, 1020, 0, 0, 100);
    Serial.print("Mapdata: ");
    Serial.println(sensorDataInPercent);
    delay(1000);

    if(sensorDataInPercent <= 60) {
      potsNeedWatering[i] = true;
    }
    else {
      potsNeedWatering[i] = false;
    }
  }
  for (int i = 0; i < potsCount; i++) {
    Serial.print("Pots needs watering: ");
    Serial.println(potsNeedWatering[i]);
  }
}

void potWatering() {
  for(int i = 0; i < potsCount; i++) {
    if(potsNeedWatering[i] == true) {
      digitalWrite(pumpPin, HIGH);
      Serial.print("pumpPin: ");
      Serial.println(pumpPin);
      digitalWrite(valvePowerPins[i], HIGH);
    }
  }
  for (int i = 0; i < potsCount; i++) {
    if(potsNeedWatering[i] == true) {
      Serial.print("Engaged valves ");
      Serial.println(valvePowerPins[i]);
    }
  }
  delay(5000);
  digitalWrite(pumpPin, LOW);

  for(int i = 0; i < potsCount; i++) {
    digitalWrite(valvePowerPins[i], LOW);
  }

}
