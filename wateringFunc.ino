int pumpPin = 2;
int valve1Pin = 3;
int valve2Pin = 4;
int valve3Pin = 5;
int valve4Pin = 6;
int valve5Pin = 7;

int humidityRawSensor1 = A0;
int humidityRawSensor2 = A1;
int humidityRawSensor3 = A2;
int humidityRawSensor4 = A3;
int humidityRawSensor5 = A4;

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
  configurePinMode(humidityRawData);
  mapSensordataToPercent(humidityRawData);

void loop() {

}

void waterThePlant(){
    digitalWrite(pumpPin, HIGH);
    delay (5000);
    digitalWrite(pumpPin, LOW);
    delay (35000);
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
    int sensorValuesinPercent[5] = for(int i=0; i < sensorCount; i++){
      map(sensorArray[i], 1020, 0, 0, 100);
    }
    return sensorValuesinPercent;
}

int moistureLevelChecker(sensorArray);
int potsNeedWatering
for(int i=0; i < sensorCount; i++){
    if (sensorArray[i] < 60){
      int
    }
    else
}
