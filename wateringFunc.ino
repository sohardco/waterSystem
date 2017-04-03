#define pumpPin = 2;
#define valve1Pin = 3;
#define valve2Pin = 4;
#define valve3Pin = 5;
#define valve4Pin = 6;
#define valve5Pin = 7;

#define humidityRawSensor1 = A0;
#define humidityRawSensor2 = A1;
#define humidityRawSensor3 = A2;
#define humidityRawSensor4 = A3;
#define humidityRawSensor5 = A4;

pinmode(pumpPin, OUTPUT);
digitalWrite(pumpPin, LOW);

pinmode(sensorPower, OUTPUT);
digitalWrite(sensorPower, LOW);


int valvePowerPins[] = {valve1Pin, valve2Pin, valve3Pin, valve4Pin, valve5Pin};
int pinCount = 5;

int humidityRawData[] = {humidityRawSensor1, humidityRawSensor2, humidityRawSensor3, humidityRawSensor4, humidityRawSensor5};
int sensorCount = 5;

void setup() {
  Serial.begin(250000);
  configurePowerPinMode(valvePowerPins);
  configureSensorPinMode(humidityRawData);

void loop() {

}

void waterThePlant(sortedPotsNeedsWatering){
  i = 0;
  while(sortedPotsNeedsWatering[i] == true)
  {
    digitalWrite(sortedPotsNeedsWatering[i], HIGH);
    digitalWrite(pumpPin, HIGH);
    delay(5000);
    digitalWrite(sortedPotsNeedsWatering[i], LOW);
    digitalWrite(pumpPin, LOW);
  }
  i++;

}

void configurePowerPinMode(arrayName){
  for(int i=0; i < pinCount; i++){
    pinMode(arrayName[i], OUTPUT);
    digitalWrite(arrayName[i], LOW);
   }
}

void configureSensorPinMode(sensorArray){
    for(int i=0; i < sensorCount; i++){
      pinMode(sensorArray[i],INPUT);
   }
}

int mapSensordataToPercent(sensorArray){
    int sensorValuesInPercent[5] = for(int i=0; i < sensorCount; i++){
      map(sensorArray[i], 1020, 0, 0, 100);
    }
    return sensorValuesInPercent;
}

int moistureLevelChecker(sensorArray);
    boolean potsNeedWatering[5];
    int checkHumidity = for(int i=0; i < sensorCount; i++){
        analogRead(sensorArray[i]);
        map(sensorArray[i], 1020, 0, 0, 100);
        if(sensorArray[i] <= 60){
          return potsNeedWatering[i] = true;
        }
        else{
          return potsNeedWatering[i] = false;
        }
    }
}
