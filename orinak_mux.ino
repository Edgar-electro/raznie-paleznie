#include <MUX74HC4067.h> // Подключение библиотеки для работы с мультиплексором (замените на фактическую библиотеку, которую вы используете)

 int analogPin0 = 0;  
 int analogPin1 = 0;  // Объявление переменной для хранения выбранного аналогового пина
 int analogPin2 = 0;  
 int analogPin3 = 0;  
MUX74HC4067 mux(D3, D4, D5, D6, D7);


void setup() {
  Serial.begin(115200); // Инициализация последовательной связи
 mux.signalPin(A0, INPUT, ANALOG);  // Другие настройки и инициализации, если необходимо
}

void loop() {
 valuepins() ;
}

void valuepins() {
  // Выбираем канал мультиплексора
 analogPin0 = mux.read(0); // Предполагается, что mux.read(0) выбирает канал 0 мультиплексора
 analogPin1 = mux.read(1);
 analogPin2 = mux.read(2);
 analogPin3 = mux.read(3);
  

  // Выводим результат в Serial Monitor
  Serial.print("pinvalue 0 ");
  Serial.println(analogPin0);
    delay(500);
    Serial.print("pinvalue 1 ");
  Serial.println(analogPin1);
    delay(500);
    Serial.print("pinvalue 2 ");
  Serial.println(analogPin2);
   delay(500);
    Serial.print("pinvalue 3 ");
  Serial.println(analogPin3);
  delay(500);
  
}
