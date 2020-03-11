//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi network info.
char ssid[] = "DarkWeb3.0";
char wifiPassword[] = "Danil2033";

#define SENSOR_PIN 0 // подключаем на пин D3 = GPO0

#define VCh_temp0 7 // виртуальный пин 7 датчик температуры
#define VCh_temp1 8 // виртуальный пин 8 датчик температуры
#define VCh_temp2 9 // виртуальный пин 9 датчик температуры
#define VCh_temp3 10 // виртуальный пин 10 датчик температуры

// Переменные для хранения данных температуры
int temp_0;
int temp_1;
int temp_2;
int temp_3;

#define VCh_Relay3 3 // виртуальный пин 3 Реле
#define VCh_Relay4 4 // виртуальный пин 4 Реле
#define VCh_Relay5 5 // виртуальный пин 5 Реле
#define VCh_Relay6 6 // виртуальный пин 6 Реле

int relayPin1 = 14; // подключаем на пин D5 = GPO14
int relayPin2 = 12; // подключаем на пин D6 = GPO12
int relayPin3 = 13; // подключаем на пин D7 = GPO13
int relayPin4 = 15; // подключаем на пин D8 = GPO15

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);

// Cayenne authentication info
char username[] = "6cb73310-49c2-11ea-a38a-d57172a4b4d4";
char password[] = "09c3a19d8ab478b3c502e2331f099f9dcb745788";
char clientID[] = "75380da0-5658-11ea-84bb-8f71124cfdfb";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(relayPin1, OUTPUT); // Пин состояние выход
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  digitalWrite(relayPin1, LOW); // Состояние пина низкое 0
  digitalWrite(relayPin2, LOW);
  digitalWrite(relayPin3, LOW);
  digitalWrite(relayPin4, LOW);
  sensors.begin();
}

void loop() {
  Cayenne.loop();
}
//-------Работа с реле-------//
CAYENNE_IN(VCh_Relay3) {
 if (getValue.asInt() == 1) { // запрашиваем с виртуального пина значение, Если значение равно 1
 digitalWrite(relayPin1, HIGH); // Включаем реле
 }
 else {
 digitalWrite(relayPin1, LOW);  // Выключаем реле
 }
}
CAYENNE_IN(VCh_Relay4) {
 if (getValue.asInt() == 1) {
 digitalWrite(relayPin2, HIGH);
 }
 else {
 digitalWrite(relayPin2, LOW);
 }
}
CAYENNE_IN(VCh_Relay5) {
 if (getValue.asInt() == 1) {
 digitalWrite(relayPin3, HIGH);
 }
 else {
 digitalWrite(relayPin3, LOW);
 }
}
CAYENNE_IN(VCh_Relay6) {
 if (getValue.asInt() == 1) {
 digitalWrite(relayPin4, HIGH);
 }
 else {
 digitalWrite(relayPin4, LOW);
 }
}
//-------Работа с датчиками DS18B12-------//
CAYENNE_OUT(VCh_temp0)
{
  sensors.requestTemperatures();  //опрос датчика
  temp_0 = sensors.getTempCByIndex(0);  // присвоем значение с id 0 в temp_*
  Cayenne.celsiusWrite(VCh_temp0, temp_0);  // присваеваем температуру с датчика id 0 в виртуальную переменную с пином
  temp_1 = sensors.getTempCByIndex(1);
  Cayenne.celsiusWrite(VCh_temp1, temp_1);
  temp_2 = sensors.getTempCByIndex(2);
  Cayenne.celsiusWrite(VCh_temp2, temp_2);
  temp_3 = sensors.getTempCByIndex(3);
  Cayenne.celsiusWrite(VCh_temp3, temp_3);
}
