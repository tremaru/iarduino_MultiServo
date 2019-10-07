//	Библиотека для работы с Multi Servo Shield: http://iarduino.ru/shop/Expansion-payments/multi-servo-shield-na-16-servoprivodov.html
//  Версия: 1.1.3
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/255.html
//  Подробное описание функции бибилиотеки доступно по ссылке: http://wiki.iarduino.ru/page/multi-servo-shield-na-16-servoprivodov/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_MultiServo_h																				//
#define iarduino_MultiServo_h																				//
																											//
#if defined(ARDUINO) && (ARDUINO >= 100)																	//
#include <Arduino.h>																						//
#else																										//
#include <WProgram.h>																						//
#endif																										//
																											//
#include <iarduino_MultiServo_I2C.h>																		//	Подключаем файл iarduino_MultiServo_I2C.h - для работы с шиной I2C        (используя функции производного класса iarduino_I2C)
																											//
#define	IMPEDANCE			2																				//	третье состояние выхода (состояние высокого импеданса - состояние высокого сопротивления - состояние отключённого выхода)
#define	SERVO_ALL			255																				//	№ выхода используемый как указание значений всем выходам
#define SERVO_SG90			1																				//	http://iarduino.ru/shop/Mehanika/mikroservoprivod---1-6-kg-sm.html
#define SERVO_MG90			2																				//	http://iarduino.ru/shop/Mehanika/mg995r-pro-servo.html
#define SERVO_MG996R		3																				//	http://iarduino.ru/shop/Mehanika/mg995r-pro-servo.html
#define SERVO_FutabaS3003	4																				//	http://iarduino.ru/shop/Mehanika/futaba-s3003.html
																											//
class iarduino_MultiServo{																					//
	public:																									//
	/**	Конструктор класса **/																				//
		iarduino_MultiServo				(){	objI2C = new iarduino_I2C; }									//	Конструктор основного класса
	/**	основные пользовательские функции **/																//
		void	begin					(uint8_t=0x40, uint16_t=50);										//	инициализ-я	чипа										(ID адрес, частота ШИМ в Гц)
		void	analogWrite				(uint8_t, uint16_t, uint16_t=0);									//	установка	ШИМ на выходе								(№ выхода от 0 до 15, коэффициент заполнения от 0 до 4095, фазовый сдвиг от 0 до 4095)
		void	digitalWrite			(uint8_t, bool);													//	установка	логического уровня на выходе				(№ выхода от 0 до 15, LOW / HIGH)
	   uint16_t	analogRead				(uint8_t);															//	чтение		коэффициента заполнения на выходе			(№ выхода от 0 до 15)
		void	servoWrite				(uint8_t, uint16_t);												//	установка	угла поворота сервопривода					(№ выхода от 0 до 15, угол поворота от 0° до 360°)
		void	servoSet				(uint8_t, uint16_t, uint16_t, uint16_t);							//	установка	параметров для сервопривода					(№ выхода от 0 до 15, максимальный угол поворота от 1° до 360°, коэффициент заполнения от 0 до 4095 для угла 0°, коэффициент заполнения от 0 до 4095 для максимального угла поворота)
		void	servoSet				(uint8_t, uint8_t);													//	установка	параметров для сервопривода					(№ выхода от 0 до 15, название сервопривода)
																											//
	/**	дополнительные пользовательские функции **/															//
		void	invert					(bool=true);														//	инверсия	сигналов на всех выходах					(true / false)
		void	outdrv					(bool=true);														//	выбор схемы	подключения всех выходов внутри чипа		(true - схема с каскадным выходом / false - схема с открытым стоком)
		void	outState				(uint8_t=0);														//	состояние	на всех выходах при подаче «1» на вход OE	(LOW / HIGH / IMPEDANCE) примечание: при указании HIGH и выборе схемы с открытым стоком, на выходах будет состояние высокого импеданса
		void	extClock				(uint16_t=0);														//	установка	частоты внешнего источника тактирования		(частота в кГц, от 1 до 50000)
		void	restart					();																	//	перезагр-ка	всех чипов на шине							(без параметров)
		void	bus						(uint16_t=100);														//	установка	скорости работы шины I2C					(частота в кГц)
		uint8_t	reg						(uint8_t);															//	чтение      регистра									(адрес регистра)
		uint8_t	reg						(uint8_t, uint8_t);													//	запись      в регистр									(адрес регистра, запысываемый байт)
																											//
	private:																								//
	/**	внутренние переменные **/																			//
		iarduino_I2C_BASE*				objI2C;																//	Объявляем указатель на объект полиморфного класса iarduino_I2C_BASE, но в конструкторе данного класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C
		uint8_t	PCA_uint_ID =			0x40;																//	адрес		чипа на шине I2C
	   uint16_t	PCA_uint_PWM =			50;																	//	частота		ШИМ на выходах чипа в Гц
	   uint32_t	PCA_uint_OSC =			25000000;															//	частота		генератора тактовых импульсов в Гц, для формирования ШИМ
	   uint16_t	PCA_uint_ANGLE[16] =	{180,180,180,180,180,180,180,180,180,180,180,180,180,180,180,180};	//	максимальный угол поворота
	   uint16_t	PCA_uint_ANGLE_MIN[16] ={170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170};	//	коэффициент заполнения для угла 0°
	   uint16_t	PCA_uint_ANGLE_MAX[16] ={470,470,470,470,470,470,470,470,470,470,470,470,470,470,470,470};	//	коэффициент заполнения для максимального угла
		bool	PCA_flag_I2C =			false;																//	флаг		инициализации шины I2C
		bool	PCA_flag_EXTCLK =		false;																//	флаг		состояния бита EXTCLK
		bool	PCA_flag_INVRT =		false;																//	флаг		состояния бита INVRT
		bool	PCA_flag_OUTDRV =		true;																//	флаг		состояния бита OUTDRV
		uint8_t	PCA_uint_OUTNE =		0;																	//	значение	двух битов OUTNE
																											//
	/**	внутренние функции **/																				//
		void	PCA_func_SET_MODE();																		//	установка	регистров режимов MODE1, MODE2 и PRE_SCALE	(без параметров)
};																											//
																											//
#endif																										//