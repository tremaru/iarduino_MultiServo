// ПРИМЕР ПОВОРОТА СЕРВОПРИВОДОВ:                            //
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Multi Servo Shield на 16 сервоприводов:                   // https://iarduino.ru/shop/Expansion-payments/multi-servo-shield-na-16-servoprivodov.html
// Информация о подключении модулей к шине I2C:              // https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                // https://wiki.iarduino.ru/page/multi-servo-shield-na-16-servoprivodov/
// Сервопривод SERVO_SG90                                    // https://iarduino.ru/shop/Mehanika/mikroservoprivod---1-6-kg-sm.html
// Сервопривод SERVO_MG90                                    // https://iarduino.ru/shop/Mehanika/mg995r-pro-servo.html
// Сервопривод SERVO_MG996R                                  // https://iarduino.ru/shop/Mehanika/mg995r-pro-servo.html
// Сервопривод SERVO_FutabaS3003                             // https://iarduino.ru/shop/Mehanika/futaba-s3003.html
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_MultiServo.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_MultiServo.h>                             // Подключаем библиотеку iarduino_MultiServo.
iarduino_MultiServo MSS;                                     // Объявляем объект MSS, для работы с Multi Servo Shield на 16 сервоприводов используя библиотеку iarduino_MultiServo.
                                                             //
void setup(){                                                //
//   Указываем параметры сервоприводов:                      // Параметры указываются до инициализации модуля.
//   MSS.servoSet(10       ,180,130,470);                    // Ручное позиционирование сервопривода: Подключён к выводу 10 , Максимальный угол поворота 180°, ШИМ для 0° = 130, ШИМ для 180° = 470.
//   MSS.servoSet(11       ,180,140,480);                    // Ручное позиционирование сервопривода: Подключён к выводу 11 , Максимальный угол поворота 180°, ШИМ для 0° = 140, ШИМ для 180° = 480.
//   MSS.servoSet(SERVO_ALL,180,140,480);                    // Ручное позиционирование сервопривода: Для всех сервоприводов, Максимальный угол поворота 180°, ШИМ для 0° = 140, ШИМ для 180° = 480.
     MSS.servoSet(15       , SERVO_SG90);                    // Авто   позиционирование сервопривода: Подключён к выводу 15 , Название сервопривода.
//   MSS.servoSet(SERVO_ALL, SERVO_SG90);                    // Авто   позиционирование сервопривода: Ко всем выводам подключены сервоприводы SG90.
                                                             //
//   Инициируем работу Multi Servo Shield:                   //
     MSS.begin(&sWire, 0x40, 1000);                           // Инициируем работу с модулем, указав: ссылку на объект для работы с шиной I2C на которой находится модуль, адрес модуля на шине I2C, частота сигнала ШИМ от 1 до 1526 Гц.
//   MSS.begin();                                            // Все указанные параметры являются не обязательными, по умолчанию: шина &Wire, адрес 0x40, частота 1000 Гц.
}                                                            //
                                                             //
void loop(){                                                 //
     MSS.servoWrite(15,  0); delay(3000);                    // Повернуть сервопривод, подключённый к 15 выводу, на   0° и ждать 3 сек.
     MSS.servoWrite(15,180); delay(3000);                    // Повернуть сервопривод, подключённый к 15 выводу, на 180° и ждать 3 сек.
}                                                            //