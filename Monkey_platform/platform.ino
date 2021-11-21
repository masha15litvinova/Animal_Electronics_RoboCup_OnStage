//подключение библиотек для датчиков и динамика
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
SparkFun_APDS9960 apds = SparkFun_APDS9960();
bool anibeshenstvo = 0;
//пины
SoftwareSerial mySerial(16, 17); //динамик
#define MOTOR1_EN 6
#define MOTOR1_INA1 32
#define MOTOR1_INB1 4
#define MOTOR1_PWM 9

#define MOTOR2_EN 12
#define MOTOR2_INA2 7
#define MOTOR2_INB2 8
#define MOTOR2_PWM 3

#define MOTOR3_EN  6
#define MOTOR3_INA3 51
#define MOTOR3_INB3 50
#define MOTOR3_PWM 5

#define MOTOR4_EN 12
#define MOTOR4_INA4 52
#define MOTOR4_INB4 53
#define MOTOR4_PWM 44

#define trigPin_1 41 //дальномер слева
#define echoPin_1 42
#define trigPin_2 46 //дальномер справа
#define echoPin_2 47
#define light A6 //датчик света

//глобальные переменные
int duration = 1100, duration_new_1, duration_new_2, dir_1, dir_2, LIGHT; //расстояния
float kp1 = 0.04, us = 0, kp2 = 0.15, kd1 = 0, kd2 = 0.025, ut = 0, errold2, errold1, es, et; //коэффициенты и управляющие воздействия
// kp1 = 0.03 kp2 = 0.15 kd2 = 0.025
bool f = true; //для перехода из состояния в состояние



void setup() {

  //инициализация моторов и датчиков
  Serial.begin(9600);
pinMode(15, INPUT);
  
  //1st
  pinMode(32, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  //2nd
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  //3rd
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(5, OUTPUT);
  //4th
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  pinMode(44, OUTPUT);
  //sensors
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);

  //жесты
  //  Инициируем работу датчика:
  if (apds.init()) {
    Serial.println("Initialization OK!");
  } else {
    Serial.println("Initialization ERROR!");
  }

  //  Устанавливаем коэффициент усиления приёмника:
  if (apds.setGestureGain(GGAIN_2X)) {
    Serial.println("Set gain OK!");
  } else {
    Serial.println("Set gain ERROR!");
  }

  //  Устанавливаем силу тока драйвера ИК-светодиода:
  if (apds.setGestureLEDDrive(LED_DRIVE_100MA)) {
    Serial.println("Set LED drive OK!");
  } else {
    Serial.println("Set LED drive ERROR!");
  }

  //  Разрешаем режим обнаружение жестов:
  if (apds.enableGestureSensor(false)) {
    Serial.println("Start gesture sensor OK!");
  } else {
    Serial.println("Start gesture sensor ERROR!");
  }

    if(digitalRead(15)){
    anibeshenstvo = 1;
  }

  //динамик
  mySerial.begin (9600);
  // открываем софт-порт
  mp3_set_serial (mySerial);
  // задаем порт для плеера
  mp3_set_volume (20);//30
  delay(500);
}




void loop() {

  if (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:    { sound (2); lead_for_el(); } Serial.println("up" ); break;
      case DIR_DOWN:  to_corner(); Serial.println("down" ); break;
      case DIR_LEFT:  scared(5); Serial.println("left" ); break;
      case DIR_RIGHT: dance(); Serial.println("NONE" ); break;
      default:        Serial.println("NONE" ); break;
    }
  }
  else
  {
    if (f == true)
      motors(0, 0, 0, 0);
    else
      lead_for_el();
  }
  delay(10);

}
