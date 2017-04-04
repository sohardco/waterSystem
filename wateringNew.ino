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
#define humiditySensor5 A4

int valvePowerPins[] = {valve1Pin, valve2Pin, valve3Pin, valve4Pin, valve5Pin};
int pinCount = 5;

int humidityData[] = {humiditySensor1, humiditySensor2, humiditySensor3, humiditySensor4, humiditySensor5};
int sensorCount = 5;

boolean potsNeedWatering[5];
int potsCount = 5;

void setup() {

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);

  configurePowerPinMode();
  configureSensorPinMode();

}

void loop() {

  moistureLevelChecker();
  potWatering();
  delay(1000 * 60 * 60);

}

// Transistor pins status and type declaration

void configurePowerPinMode() {

  for(int i = 0; i < pinCount; i++) {
    pinMode(valvePowerPins[i], OUTPUT);
    digitalWrite(valvePowerPins[i], LOW);

   }
}

// Sensor pins status and type declaration

void configureSensorPinMode(){

    for(int i=0; i < sensorCount; i++) {
      pinMode(humidityData[i],INPUT);

   }
}

// Checks soil moisture level from sensors, maps values to percents and records data to new array in boolean

void moistureLevelChecker() {

  digitalWrite(sensorPower, HIGH);

    for(int i = 0; i < sensorCount; i++) {
        int rawSensorData = analogRead(humidityData[i]);
        int sensorDataInPercent = map(rawSensorData, 1020, 0, 0, 100);

          if(sensorDataInPercent <= 60) {
            potsNeedWatering[i] = true;
          }
          else {
            potsNeedWatering[i] = false;
          }
    }
}

void potWatering() {

  digitalWrite(pumpPin, HIGH);

    for(int i = 0; i < potsCount; i++){
      if(potsNeedWatering[i] == true) {
        digitalWrite(valvePowerPins[i], HIGH);
      }

    delay(5000);
    digitalWrite(pumpPin, LOW);
    
    for(int i = 0; i < potsCount; i++){
      if(potsNeedWatering[i] == true) {
        digitalWrite(valvePowerPins[i], HIGH);
      }


    }
}
