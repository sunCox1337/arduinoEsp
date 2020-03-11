#define ON 0 // константа 0 
#define OFF 1 // константа 1
bool button_state = false; // переменная для хранения состояния кнопки
int flag = 0; // значение для переменной 0
int btn = 43;
 
void setup() {
  Serial.begin(115200);
  Serial.println("Welcome");
// подтягивающий резистор на PIN'ы для реле
  digitalWrite(46, OFF); // Реле Свечи накала
  digitalWrite(45, OFF); // Реле АСС
  digitalWrite(44, OFF); // Реле Стартер  
//------------------------------------------//  
  digitalWrite(43, OFF); // Реле Основной ввод (статус)
  digitalWrite(42, OFF); // Реле Питание от генератора(статус)
  digitalWrite(41, OFF); // Реле Подогрев
//-----------------------------------------//  
  digitalWrite(40, OFF); // Реле РЕЗЕРВ
  // digitalWrite(36, OFF); // Лед запуска генератора
  digitalWrite(37, OFF); // Реле РЕЗЕРВ
  digitalWrite(38, OFF); // Реле РЕЗЕРВ
  digitalWrite(39, OFF); // Реле РЕЗЕРВ
// подтягивающий резистор на PIN'ы для LED
  digitalWrite(53, ON); // Синий LED Выполнение
  digitalWrite(52, ON); // Большой Синий LED Статус Автомтический режим АВР
  digitalWrite(51, ON); // Белый LED Статус Ручной режим АВР
// Реле
  pinMode(46, OUTPUT); // Реле Свечи накала
  pinMode(45, OUTPUT); // Реле АСС
  pinMode(44, OUTPUT); // Реле Стартер
  pinMode(36, INPUT_PULLUP); // Лед запуска генератора
   pinMode(37, OUTPUT); // реле катушек ГЕНЕРАТОРА
   pinMode(38, OUTPUT); // реле катушек ОСНОВНОГО ВООДА
  pinMode(btn, INPUT); // Реле Основной ввод СТАТУС
  pinMode(42, OUTPUT); // Реле Питание от генератора СТАТУС
  pinMode(41, OUTPUT); // Реле Подогрев  
// Кнопки ВЛК/ВЫКЛ
  pinMode(50, INPUT_PULLUP); // Кнопка Запуска генератора
  pinMode(49, INPUT_PULLUP); // Кнопка Глушение генератора
  pinMode(48, INPUT_PULLUP); // Кнопка Ручной режим АВР
  pinMode(47, INPUT_PULLUP); // Кнопка Автоматический режим АВР
// Светодиоды LED Статусы
  pinMode(53, OUTPUT); // Синий LED Выполнение
  pinMode(52, OUTPUT); // Большой Синий LED Статус Автомтический режим АВР
  pinMode(51, OUTPUT); // Белый LED Статус Ручной режим АВР
  
}

void loop() {
// Кнопка Ручной режим АВР то делай ...
if (digitalRead(48) == LOW){
    digitalWrite(51, LOW);/*отключаем белый диод*/
    digitalWrite(52, HIGH); /*включаем синий диод*/
    // Запуск генератора с кнопки Старт
    if (digitalRead(50) == LOW && !button_state){
      button_state = true;
      Serial.println("[-Mode manual start-]");
      digitalWrite(53, OFF); // Вкл Синий LED
      delay(2000); // ждем 1 секунд
      Serial.println(" -Start Svechi nakala");
      digitalWrite(46, ON); // зажигаем свечи накала
      delay(15000); // ждем 15 секунд
     Serial.println(" ------>power generator ON");
     digitalWrite(37, ON); // Отключаем ввод генератора
     delay(100);
     digitalWrite(38, ON); // Отключаем основной ввод
      delay(2000);
      Serial.println(" -Stop Svechi nakala");
      digitalWrite(46, OFF); // отключаем свечи накала
      delay(1000); // ждем 1 секунд
      Serial.println(" -Start ACC");
      digitalWrite(45, ON); // включаем АСС
      delay(1500); // ждем 1 секунд
      Serial.println(" -Start Starter");
      digitalWrite(44, ON); // Включаем стартер
      delay(1500); // ждем 1.5 секунды
      Serial.println(" -Stop Starter");
      digitalWrite(44, OFF); // Отключаем стартер
     delay(120000);
     Serial.println(" ------>power generator OFF");
     digitalWrite(37, OFF); // Включаем ввод генератора
     delay(100);
     digitalWrite(38, OFF); // Отключаем основной ввод
       delay(1000);
      Serial.println(" -Stop BLUE Led");
      digitalWrite(53, ON); // отключаем светодиод синий
      delay(2000); // ждем 2 секунд
      Serial.println("[-Mode manual on-]");
    }else {
      // Статус кнопки FALSE
      button_state = false;
    }
  // Глушение генератора с кнопки
  if (digitalRead(49) == LOW && !button_state) {
      button_state = true;
      digitalWrite(53, OFF); // Включаем светодиод синий
     delay(1000);
     digitalWrite(37, ON); // Отключаем ввод генератора
     delay(100);
     digitalWrite(38, ON); // Отключаем основной ввод
     delay(1000);
      Serial.println("[-Stop ACC-]");
      digitalWrite(45, OFF); // Отключаем АСС
     delay(10000);
     digitalWrite(37, OFF); //Включаем ввод генератора
     delay(100);
     digitalWrite(38, OFF); //Включаем основной ввод
     delay(1000);
      Serial.println(" -Stop BLUE Led");
      digitalWrite(53, ON); // отключаем светодиод синий
    }
}
// Если кнопка на автоматическом режиме то делай ...
if (digitalRead(47) == LOW){
  digitalWrite(52, LOW);/*отключаем синий диод*/
  digitalWrite(51, HIGH); /*включаем белый диод*/
//*******LOGI*********//
//Serial.println(digitalRead(36));  
delay(1000);
// Проверить есть ли свет ?? 
 if (digitalRead(btn)==HIGH && digitalRead(36)==HIGH){ 
          Serial.println("[-Mode automatic start-]");
      digitalWrite(53, OFF); // Вкл Синий LED
      delay(2000); // ждем 1 секунд
      Serial.println(" -Start Svechi nakala");
      digitalWrite(46, ON); // зажигаем свечи накала
      delay(15000); // ждем 15 секунд
     Serial.println(" ------>power generator ON");
     digitalWrite(37, ON); // Отключаем ввод генератора
     delay(100);
     digitalWrite(38, ON); // Отключаем основной ввод
      delay(2000);
      Serial.println(" -Stop Svechi nakala");
      digitalWrite(46, OFF); // отключаем свечи накала
      delay(1000); // ждем 1 секунд
      Serial.println(" -Start ACC");
      digitalWrite(45, ON); // включаем АСС
      delay(1500); // ждем 1 секунд
      Serial.println(" -Start Starter");
      digitalWrite(44, ON); // Включаем стартер
      delay(1500); // ждем 1.5 секунды
      Serial.println(" -Stop Starter");
      digitalWrite(44, OFF); // Отключаем стартер
     delay(120000);
     Serial.println(" ------>power generator OFF");
     digitalWrite(37, OFF); // Включаем ввод генератора
     delay(100);
     digitalWrite(38, OFF); // Отключаем основной ввод
       delay(1000);
      Serial.println(" -Stop BLUE Led");
      digitalWrite(53, ON); // отключаем светодиод синий
      delay(2000); // ждем 2 секунд
      
      }
      if (digitalRead(btn)==LOW && digitalRead(36)==LOW){
            digitalWrite(53, OFF); // Включаем светодиод синий
           delay(1000);
           digitalWrite(37, ON); // Отключаем ввод генератора
           delay(100);
           digitalWrite(38, ON); // Отключаем основной ввод
           delay(1000);
            Serial.println("[-Stop ACC-]");
            digitalWrite(45, OFF); // Отключаем АСС
           delay(10000);
           digitalWrite(37, OFF); //Включаем ввод генератора
           delay(100);
           digitalWrite(38, OFF); //Включаем основной ввод
           delay(1000);
            Serial.println(" -Stop BLUE Led");
            digitalWrite(53, ON); // отключаем светодиод синий
       }
        
       
}

}
