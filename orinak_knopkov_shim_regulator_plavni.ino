#include <GyverPWM.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //(0x23, 16, 2);


//const int  voltage_pin  = A1 ;
const int pwmPin = 3; // Пин для управления ШИМ
const int buttonPlusPin = 2; // Пин для кнопки "больше"
const int buttonMinusPin = 4; // Пин для кнопки "меньше"
int pwmValue = 0; // Начальное значение ШИМ (0-6000)
const int pwmStep = 10; // Шаг изменения ШИМ (приблизительно 5%)

 
// int  voltRead = 0;
// float VOLTtotal = 0.0;
 //long voltage = 0.0;
  
  
  
 // float realVoltage = 31.92;     // Реальное напряжение, которое вы измерили (в вольтах)  stex poxem maxsimal volty testerov chapvac jisht volti masina xosqy
 // float measuredVoltage = 32.09; // Измеренное напряжение, которое Arduino показало (в вольтах)
 // float Maxviltage = 32.00;
 // float correctionFactor;        // Коэффициент коррекции
 // float correctedVoltage;        // Скорректированное напряжение (в вольтах)
        



void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, OUTPUT);
  PWM_prescaler(pwmPin, 1);
  
  analogReference(DEFAULT); 
 // pinMode(voltage_pin, INPUT);
  pinMode(buttonPlusPin, INPUT_PULLUP); // Подключаем внутренний pull-up резистор
  pinMode(buttonMinusPin, INPUT_PULLUP); // Подключаем внутренний pull-up резистор

  analogWrite(pwmPin, pwmValue); // Устанавливаем начальное значение ШИМ

  lcd.init(); 
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
  
}

void loop() {
  // Проверяем состояние кнопки "больше"
  if (digitalRead(buttonPlusPin) == LOW) {
    delay(10); // Дебаунс кнопки
    if (digitalRead(buttonPlusPin) == LOW) {
      increasePWM();
    }
  }

  // Проверяем состояние кнопки "меньше"
  if (digitalRead(buttonMinusPin) == LOW) {
    delay(10); // Дебаунс кнопки
    if (digitalRead(buttonMinusPin) == LOW) {
      decreasePWM();
    }
  }

 
  updateVoltage();
  
  updateCurrent();
  volt_update();
  updatepower();
}

void increasePWM() {
  pwmValue += pwmStep;
  if (pwmValue > 255) {
    pwmValue = 255; // Максимальное значение ШИМ
  }
  analogWrite(pwmPin, pwmValue);
}

void decreasePWM() {
  pwmValue -= pwmStep;
  if (pwmValue < 0) {
    pwmValue = 0; // Минимальное значение ШИМ
  }
  analogWrite(pwmPin, pwmValue);
}

//void volt_update() {
  //for(int i=0;i<200;i++) {
//  voltRead = analogRead(voltage_pin);
//  voltage += voltRead ;
  //delay(1);
//  } 
  
 // voltage = voltage / 200 ;
   //VOLTtotal = (voltage / 1023.0) * Maxviltage;  //stex poxem maxsimal volty testerov chapvac jisht volti masina xosqy
  // correctionFactor = realVoltage / measuredVoltage;
  // correctedVoltage = VOLTtotal * correctionFactor;
   
//}
void updateVoltage() {
  lcd.setCursor(0, 0);
  lcd.print("P");
  lcd.setCursor(1, 0);
  lcd.print(":");
  lcd.print(pwmValue);
  lcd.print(" ");
}

//void updateCurrent() {
//  lcd.setCursor(9, 0);
 // lcd.print("V");
 // lcd.setCursor(10, 0);
 // lcd.print(":");
 // lcd.print(correctedVoltage);
 // lcd.print(" ");
//}
