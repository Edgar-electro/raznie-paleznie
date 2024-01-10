const int analogInputPin = A1;  // Пин, к которому подключен аналоговый сенсор
int baselineValue = 0;  // Начальное значение для калибровки

void setup() {
  Serial.begin(9600);  // Инициализация последовательной связи
  calibrateAnalogInput();  // Запуск процедуры калибровки
}

void loop() {
  // Считывание значения с аналогового входа
  int sensorValue = analogRead(analogInputPin);

  // Вычитание базовой точки для обнуления значения
  int zeroedValue = sensorValue - baselineValue;

  // Отображение значения от 0 до 1023 после калибровки
  int mappedValue = map(zeroedValue, 0, 1023 - baselineValue, 0, 1023);

  // Вывод отображенного значения в монитор порта
  Serial.print("Mapped Value: ");
  Serial.println(mappedValue);

  delay(1000);  // Пауза 1 секунда
}

void calibrateAnalogInput() {
  Serial.println("Начните калибровку...");

  // Ждем, чтобы удостовериться, что датчик установлен в желаемое значение
  delay(2000);

  // Считываем и сохраняем текущее значение аналогового входа как базовую точку
  baselineValue = analogRead(analogInputPin);
  Serial.print("Базовая точка установлена: ");
  Serial.println(baselineValue);
  Serial.println("Калибровка завершена. Значение теперь обнулено.");
}
