[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino_MultiServo

**This is a library for Arduino IDE. It allows to control [Multi Servo](http://iarduino.ru/shop/Expansion-payments/multi-servo-shield-na-16-servoprivodov.html) shields that can handle up to 16 servos. Shields are made by iArduino.ru**

**Данная библиотека для Arduino IDE позвляет управлять шилдами [Multi Servo](http://iarduino.ru/shop/Expansion-payments/multi-servo-shield-na-16-servoprivodov.html) к которым можно подключить до 16 сервоприводов.**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/multi-servo-shield-na-16-servoprivodov/)


| Модель | Ссылка на магазин |
|--|--|
| ![](https://wiki.iarduino.ru/img/resources/710/710.svg) |  https://iarduino.ru/shop/Expansion-payments/multi-servo-shield-na-16-servoprivodov.html |

## Примеры:

**Управление сервоприводами SG90, MG90, MG996R, Futaba S3003:**

```C++
#include <iarduino_MultiServo.h>        //  Подключаем библиотеку iarduino_MultiServo
iarduino_MultiServo MSS;                //  Объявляем объект MSS, для работы с библиотекой
void setup() {
// Указываем какой тип сервопривода подключен к выводам MultiServoShield
   MSS.servoSet(0, SERVO_SG90);         //  Сервопривод SG90 подключён к выводу № 0 MultiServoShield.
   MSS.servoSet(1, SERVO_SG90);         //  Сервопривод SG90 подключён к выводу № 1 MultiServoShield.
   MSS.servoSet(2, SERVO_SG90);         //  Сервопривод SG90 подключён к выводу № 2 MultiServoShield.
   MSS.servoSet(3, SERVO_MG90);         //  Сервопривод MG90 подключён к выводу № 3 MultiServoShield.
   MSS.servoSet(4, SERVO_MG996R);       //  Сервопривод MG996R подключён к выводу № 4 MultiServoShield.
   MSS.servoSet(5, SERVO_FutabaS3003);  //  Сервопривод Futaba S3003 подключён к выводу № 5 MultiServoShield.
// MSS.servoSet(SERVO_ALL, SERVO_SG90); //  На любом выводе используются только сервоприводы SG90
   MSS.begin();                         //  Инициируем работу с MultiServoShield
}
void loop(){
// Управляем сервоприводами
   MSS.servoWrite(3, 50);               //  Повернуть сервопривод, подключённый к 3 выводу, на 50°
   delay(1000);                         //  Ждём 1 сек.
   MSS.servoWrite(5, 120);              //  Повернуть сервопривод, подключённый к 5 выводу, на 120°
   delay(1000);                         //  Ждём 1 сек.
   MSS.servoWrite(SERVO_ALL, 180);      //  Повернуть все сервоприводы на 180°
   delay(1000);                         //  Ждём 1 сек.
   MSS.servoWrite(SERVO_ALL, 0);        //  Повернуть все сервоприводы на 0°
   delay(1000);                         //  Ждём 1 сек.
}
```

**Управление любыми сервоприводами:**

```C++
#include <iarduino_MultiServo.h>        //  Подключаем библиотеку iarduino_MultiServo
iarduino_MultiServo MSS;                //  Объявляем объект MSS, для работы с библиотекой
void setup() {
// Указываем какой тип сервопривода подключен к выводам MultiServoShield
   MSS.servoSet(0, 180, 130, 470);      //  К выводу 0, подключен сервопривод с максимальным углом поворота 180°, ШИМ для 0° = 130. ШИМ для 180° = 470
   MSS.servoSet(1, 120, 100, 500);      //  К выводу 1, подключен сервопривод с максимальным углом поворота 120°, ШИМ для 0° = 100. ШИМ для 120° = 500
// MSS.servoSet(SERVO_ALL, 90, 50, 300);//  На любом выводе используются сервоприводы с максимальным углом поворота 90°, ШИМ для 0° = 50. ШИМ для 90° = 300
   MSS.begin();                         //  Инициируем работу с MultiServoShield
}
void loop(){
// Управляем сервоприводами как и в предыдущем примере
}
```

## Основные функции библиотеки:

**Подключаем библиотеку:**
```C++
#include <iarduino_MultiServo.h> // Подключаем библиотеку
iarduino_MultiServo ОБЪЕКТ; // Создаём объект
```

**Инициализация работы с Multi Servo Shield.**

```C++
ОБЪЕКТ.begin( [ АДРЕС [ , ЧАСТОТА ]] ); // Инициализация работы с Multi Servo Shield.

```

**Установка параметров для каждого сервопривода.**

```C++
ОБЪЕКТ.servoSet( №_ВЫХОДА , ПАРАМЕТРЫ ); // Установка параметров для каждого сервопривода.

```

**Поворот указанного сервопривода на заданный угол.**

```C++
ОБЪЕКТ.servoWrite( №_ВЫХОДА , УГОЛ ); // Поворот указанного сервопривода на заданный угол.

```

**Установка сигнала ШИМ на выходе.**

```C++
ОБЪЕКТ.analogWrite( №_ВЫХОДА , ШИМ [ , ФАЗОВЫЙ_СДВИГ ] ); // Установка сигнала ШИМ на выходе.

```

**Установка логического состояния на выходе.**

```C++
ОБЪЕКТ.digitalWrite( №_ВЫВОДА , СОСТОЯНИЕ ); // Установка логического состояния на выходе.

```

**Чтение ранее установленного коэффициента заполнения ШИМ.**

```C++
ОБЪЕКТ.analogRead( №_ВЫВОДА ); // Чтение ранее установленного коэффициента заполнения ШИМ.

```

## Дополнительные функций библиотеки:

**Установка скорости работы Multi Servo Shield на шине I2C.**

```C++
ОБЪЕКТ.bus( ЧАСТОТА ); // Установка скорости работы Multi Servo Shield на шине I2C.

```

**Перезагрузка Multi Servo Shield, с установкой значений по умолчанию.**

```C++
ОБЪЕКТ.restart(); // Перезагрузка Multi Servo Shield, с установкой значений по умолчанию.

```

**Инверсия сигналов на всех выходах Multi Servo Shield.**

```C++
ОБЪЕКТ.invert( ФЛАГ ); // Инверсия сигналов на всех выходах Multi Servo Shield.

```

**Установка схемы с каскадным выходом выводов внутри чипа.**

```C++
ОБЪЕКТ.outdrv( ФЛАГ ); // Установка схемы с каскадным выходом выводов внутри чипа.

```

**Установка состояний на всех выходах LOW, HIGH или IMPEDANCE.**

```C++
ОБЪЕКТ.outState( СОСТОЯНИЕ ); // Установка состояний на всех выходах LOW, HIGH или IMPEDANCE.

```

**Установка работы чипа от внешнего источника тактирования.**

```C++
ОБЪЕКТ.extClock( ЧАСТОТА ); Установка работы чипа от внешнего источника тактирования.

```

**Чтение или запись одного байта данных в (из) регистр чипа.**

```C++
ОБЪЕКТ.reg( АДРЕС [ , ДАННЫЕ ] ); // Чтение или запись одного байта данных в (из) регистр чипа.
```
