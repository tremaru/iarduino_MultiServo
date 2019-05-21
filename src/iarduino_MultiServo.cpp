#include "iarduino_MultiServo.h"

/**	основные пользовательские функции **/
//		инициализация чипа
void	iarduino_MultiServo::begin(uint8_t i, uint16_t j){
		PCA_uint_ID=i; PCA_uint_PWM=j; PCA_func_SET_MODE(); digitalWrite(SERVO_ALL,LOW);					//	сохраняем адрес чипа и частоту ШИМ, устанавливаем регистры режимов работы, устанавливаем все выходы в логические «0»
}
//		установка ШИМ на выходе
void	iarduino_MultiServo::analogWrite(uint8_t i, uint16_t j, uint16_t k){
		if(i>=16&&i!=SERVO_ALL){return;}																	//	Игнорируем команду
		if(j==0)  {digitalWrite(i,LOW ); return;}															//	Устанавливаем логический 0
		if(j>4095){digitalWrite(i,HIGH); return;}															//	Устанавливаем логическую 1 
		if(k>4095){k=4095;}	j+=k; if(j>4095){j-=4096;}														//	Отодвигаем спад импульса в зависимости от фазового сдвига
		uint8_t data[4]={k,k>>8,j,j>>8};																	//	Определяем массив data из 4 байт данных для записи
		objI2C->writeBytes(PCA_uint_ID, (i==SERVO_ALL?0xFA:(i*4+6)), data, 4);								//	Записываем 4 байта массива data в модуль PCA_uint_ID начиная с регистра (i==SERVO_ALL?0xFA:(i*4+6))
}
//		установка логического уровня на выходе
void	iarduino_MultiServo::digitalWrite(uint8_t i, bool j){
		if(i>=16&&i!=SERVO_ALL){return;}																	//	игнорируем команду
		uint8_t data[4]={0,j?16:0,0,j?0:16};																//	Определяем массив data из 4 байт данных для записи
		objI2C->writeBytes(PCA_uint_ID, (i==SERVO_ALL?0xFA:(i*4+6)), data, 4);								//	Записываем 4 байта массива data в модуль PCA_uint_ID начиная с регистра (i==SERVO_ALL?0xFA:(i*4+6))
}
//		чтение установленного коэффициента заполнения на выходе
uint16_t iarduino_MultiServo::analogRead(uint8_t i){
		if(i>=16){return 0;} uint16_t j=0, k=0;																//	игнорируем команду
		uint8_t data[4];																					//	Объявляем массив data из 4 элементов
		objI2C->readBytes(PCA_uint_ID, (i*4+6), data, 4);													//	Заполняем массив data читая 4 байта из модуля PCA_uint_ID начиная с регистра (i*4+6)
		if(data[3]&0x10){return 0;}																			//	на читаемом выходе установлен 0
		if(data[1]&0x10){return 4096;}																		//	на читаемом выходе установлена 1
		k=(data[1]<<8)+data[0];																				//	количество тактов до фронта импульса
		j=(data[3]<<8)+data[2];																				//	количество тактов до спада импульса
		if(j<k){j+=4096;} j-=k; return j;																	//	выводим коэффициент заполнения с учётом фазового сдвига
}
//		установка угла поворота сервопривода
void	iarduino_MultiServo::servoWrite(uint8_t i, uint16_t j){
		uint8_t k=i; if(i==SERVO_ALL){i=15; k=0;} if(i>=16||j>360){return;} 								//	игнорируем команду
		for(int n=k; n<=i; n++){analogWrite(n,map((j<=PCA_uint_ANGLE[n]?j:PCA_uint_ANGLE[n]),0,PCA_uint_ANGLE[n],PCA_uint_ANGLE_MIN[n],PCA_uint_ANGLE_MAX[n]));}
}
//		установка параметров для сервопривода
void	iarduino_MultiServo::servoSet(uint8_t i, uint16_t j, uint16_t a, uint16_t b){
		uint8_t k=i; if(i==SERVO_ALL){i=15; k=0;} if(i>=16||j==0||j>360||a>4095||b>4095||b==0){return;} 	//	игнорируем команду
		for(int n=k; n<=i; n++){PCA_uint_ANGLE[n]=j; PCA_uint_ANGLE_MIN[n]=a; PCA_uint_ANGLE_MAX[n]=b;}		//	применяем значения максимального угла поворота и коэффициентов заполнения для крайних положений сервопривода
}
void	iarduino_MultiServo::servoSet(uint8_t i, uint8_t j){
		switch(j){
		case SERVO_SG90:		servoSet(i, 180, 127, 540); break;
		case SERVO_MG90:		servoSet(i, 180, 150, 555); break;
		case SERVO_MG996R:		servoSet(i, 180, 130, 515); break;
		case SERVO_FutabaS3003:	servoSet(i, 180, 140, 490); break;
		}
}


/**	дополнительные пользовательские функции **/
//		инверсия сигналов на всех выходах
void	iarduino_MultiServo::invert(bool i){PCA_flag_INVRT=i; PCA_func_SET_MODE();}										//	установка или сброс флага INVRT
//		выбор интегрированной схемы подключения выходов в чипе
void	iarduino_MultiServo::outdrv(bool i){PCA_flag_OUTDRV=i; PCA_func_SET_MODE();}									//	установка или сброс флага OUTDRV
//		состояние на выходах при подаче на вход OE уровня логической «1»
void	iarduino_MultiServo::outState(uint8_t i){if(i>2){return;} PCA_uint_OUTNE=i; PCA_func_SET_MODE();}				//	установка двух битов OUTNE
//		установка частоты внешнего источника тактирования
void	iarduino_MultiServo::extClock(uint16_t i){if(i){PCA_flag_EXTCLK=true; PCA_uint_OSC=i; PCA_uint_OSC*=1000; PCA_func_SET_MODE();}else{PCA_flag_EXTCLK=false; restart(); PCA_uint_OSC=25000000; PCA_func_SET_MODE(); digitalWrite(SERVO_ALL,LOW);}}
//		перезагрузка всех чипов на шине
void	iarduino_MultiServo::restart(void){objI2C->writeByte(0x0, 0x6);}													//	отправка команды «SWRST Call»
//		установка скорости шины
void	iarduino_MultiServo::bus(uint16_t i){objI2C->begin(i); PCA_flag_I2C=true;}										//	инициализация шины I2C с установкой частоты (в кГц)
//		чтение/запись одного байта данных из/в регистр
uint8_t	iarduino_MultiServo::reg(uint8_t i           ){return objI2C->readByte (PCA_uint_ID, i   );}
uint8_t	iarduino_MultiServo::reg(uint8_t i, uint8_t j){return objI2C->writeByte(PCA_uint_ID, i, j);}

/**	внутренние функции **/
//		установка регистров режимов работы MODE1, MODE2 и PRE_SCALE
void	iarduino_MultiServo::PCA_func_SET_MODE(){
		if(!PCA_flag_I2C){PCA_flag_I2C=true; objI2C->begin(100);}											//	инициализация шины I2C с установкой частоты в 100 кГц (если она не инициирована ранее)
		uint16_t j=(PCA_uint_OSC/(4096*uint32_t(PCA_uint_PWM)))-1; if(j<3){j=3;} if(j>255){j=255;}			//	определяем значение предделителя
		reg(0,0x30);																						//	отправляем байт данных в регистр MODE1     (устанавливаем флаги AL и SLEEP, остальные флаги сброшены)
		reg(0xFE,j);																						//	отправляем байт данных в регистр PRE_SCALE (устанавливаем предделитель для частоты ШИМ)
		reg(1,PCA_flag_INVRT<<4|PCA_flag_OUTDRV<<2|PCA_uint_OUTNE);											//	отправляем байт данных в регистр MODE2     (записываем флаги INVRT, OUTDRV, OUTNE, флаг OCH сброшен)
		reg(0,PCA_flag_EXTCLK<<6|0x30);																		//	отправляем байт данных в регистр MODE1     (записываем флаг EXTCLK, флаги AL и SLEEP установлены, остальные флаги сброшены)
		reg(0,0x20);																						//	отправляем байт данных в регистр MODE1     (сбрасываем флаг SLEEP, остальные флаги без изменений) / флаг EXTCLK не сбрасывается записью нуля
		delayMicroseconds(500);																				//	ждём выполнение действий по сбросу флага SLEEP
		reg(0,0xA0);																						//	отправляем байт данных в регистр MODE1     (сбрасываем флаг RESTART, остальные флаги без изменений) / флаг RESTART сбрасывается записью единицы
}