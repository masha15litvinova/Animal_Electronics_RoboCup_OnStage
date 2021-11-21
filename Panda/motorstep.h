#define STEP_L 26 //Пин левого шага 
#define STEP_R 14 //Пин правого шага
#define STEPER_EN 2 //Пин включения моторов
// Функция инициализации управления моторами.//
#define DIR_L 27 //Пин направления левого шага 
#define DIR_R 12 //Пин направления правого шага

#define DIR_L_FORWARD true
#define DIR_L_BACKWARD false

#define DIR_R_FORWARD false
#define DIR_R_BACKWARD true

#define RXD2 22 //player pins
#define TXD2 23
  

int32_t maxSPEED = 1500000; //Скорость шагов за 100 сек
int32_t minSPEED = 40000; //Скорость шагов за 100 сек
//20000; теперь это значение поделено на 1000 для вхождения в рамки 32 разрядных целых чисел
int32_t  acceleration = 30; //10
int32_t  accelerationL = 0;
int32_t  accelerationR = 0;

volatile int32_t speed_last_L = 0;
volatile int32_t speed_last_R = 0;
volatile int32_t speed_left = 0;
volatile int32_t speed_right = 0;

volatile int32_t speed_xxx_L = 0;
volatile int32_t speed_xxx_R = 0;

//=========================================
//=========================================
bool STEPER_EN_level = true;
//===============================
void setup_motor_system()
{
  STEPER_EN_level = true;
  pinMode(STEP_L, OUTPUT);
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(STEPER_EN, OUTPUT);
  digitalWrite(DIR_L, DIR_L_FORWARD);
  digitalWrite(DIR_R, DIR_R_FORWARD);
  digitalWrite(STEPER_EN, STEPER_EN_level);
}
//===============================
// == Включение /отключние моторов
void motor_off()
{ 
  // Отключаем все колеса.
  if (!STEPER_EN_level)
  {
    STEPER_EN_level = true;
    digitalWrite(STEPER_EN, STEPER_EN_level);
  }
}
//===============================
void motor_on()
{
  // Включаем все колеса.
  if (STEPER_EN_level)
  {
    STEPER_EN_level = false;
    digitalWrite(STEPER_EN, STEPER_EN_level);
    // Задержка на включение драйверов.
 //   delay(500);
  }
}
//======================
