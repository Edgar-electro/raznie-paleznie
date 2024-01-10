#include <SoftwareSerial.h>                     // Библиотека програмной реализации обмена по UART-протоколу
SoftwareSerial SIM800(2, 3);                    // RX, TX

String response = "";                          // Переменная для хранения ответа модуля

const int BUTTON_PIN = 5; 
bool buttonPressed = false;

void setup() {
  Serial.begin(9600);                           // Скорость обмена данными с компьютером
  SIM800.begin(9600);                           // Скорость обмена данными с модемом
  Serial.println("Start!");
pinMode(BUTTON_PIN, INPUT_PULLUP);
  sendATCommand("AT", true);                    // Отправили AT для настройки скорости обмена данными

  // Команды настройки модема при каждом запуске
  response = sendATCommand("AT+CLIP=1", true);  // Включаем АОН

  //response = sendATCommand("AT+DDET=1", true);  // Включаем DTMF
}

String sendATCommand(String cmd, bool waiting) {
  String _resp = "";                            // Переменная для хранения результата
  Serial.println(cmd);                          // Дублируем команду в монитор порта
  SIM800.println(cmd);                          // Отправляем команду модулю
  if (waiting) {                                // Если необходимо дождаться ответа...
    _resp = waitResponse();                     // ... ждем, когда будет передан ответ
    // Если Echo Mode выключен (ATE0), то эти 3 строки можно закомментировать
    if (_resp.startsWith(cmd)) {                // Убираем из ответа дублирующуюся команду
      _resp = _resp.substring(_resp.indexOf("\r", cmd.length()) + 2);
    }
    Serial.println(_resp);                      // Дублируем ответ в монитор порта
  }
  return _resp;                                 // Возвращаем результат. Пусто, если проблема
}

String waitResponse() {                         // Функция ожидания ответа и возврата полученного результата
  String _resp = "";                            // Переменная для хранения результата
  long _timeout = millis() + 10000;             // Переменная для отслеживания таймаута (10 секунд)
  while (!SIM800.available() && millis() < _timeout)  {}; // Ждем ответа 10 секунд, если пришел ответ или наступил таймаут, то...
  if (SIM800.available()) {                     // Если есть, что считывать...
    _resp = SIM800.readString();                // ... считываем и запоминаем
  }
  else {                                        // Если пришел таймаут, то...
    Serial.println("Timeout...");               // ... оповещаем об этом и...
  }
  return _resp;                                 // ... возвращаем результат. Пусто, если проблема
}

void loop() {
  if (SIM800.available())   {                   // Если модем, что-то отправил...
    response = waitResponse();                 // Получаем ответ от модема для анализа
    response.trim();                           // Убираем лишние пробелы в начале и конце
    Serial.println(response);                  // Если нужно выводим в монитор порта
    String whiteListPhones = "0769888360";  // Белый список телефонов   +33769888360

    if (response.startsWith("RING")) {         // Есть входящий вызов

      int phoneindex = response.indexOf("+CLIP: \"");// Есть ли информация об определении номера, если да, то phoneindex>-1

      String innerPhone = "";                   // Переменная для хранения определенного номера

      if (phoneindex >= 0) {                    // Если информация была найдена

        phoneindex += 8;                     // Парсим строку и ...

        innerPhone = response.substring(phoneindex, response.indexOf("\"", phoneindex)); // ...получаем номер

        Serial.println("Number: " + innerPhone); // Выводим номер в монитор порта

      }

      // Проверяем, чтобы длина номера была больше 6 цифр, и номер должен быть в списке   +7928xxxxxxx

      if (innerPhone.length() >= 7 && whiteListPhones.indexOf(innerPhone) >= 0) {

        sendATCommand("ATA", true);        // Если да, то отвечаем на вызов

      }

      else {

        sendATCommand("ATH", true);        // Если нет, то отклоняем вызов

      }

    }

  }

  

 if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    // Если кнопка нажата и предыдущего вызова не было
    makeCall();
    buttonPressed = true;  // Устанавливаем флаг, чтобы предотвратить повторный вызов
  }

  if (digitalRead(BUTTON_PIN) == HIGH && buttonPressed) {
    // Если кнопка отпущена и был вызов, сбрасываем флаг
    buttonPressed = false;
  }

  if (Serial.available())  {                    // Ожидаем команды по Serial...
    SIM800.write(Serial.read());                // ...и отправляем полученную команду модему
  }
  
  
  }




void makeCall() {
  SIM800.println("ATD+33769888360;");  // Замените "+1234567890" на номер, на который нужно сделать вызов
 
}
