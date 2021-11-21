#include "defin.h"
#include "gyro_acsel.h"
#include "motorstep.h"  //motors description
#include "irq_robot.h"  //working with interrupts
#include "Adafruit_APDS9960.h"
#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"
Adafruit_APDS9960 apds;
SoftwareSerial myPort(35, 32);

void setup() {
  //init motors
  setup_motor_system();
  //off motors
  motor_off();
  // initializing steps
  timer_setup();



  myPort.begin(9600);
  Serial.begin(115200);
    mp3_set_serial (myPort);  //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (15);
  
  apds.enableProximity(true);
  apds.enableGesture(true);
  giroscop_setup();
  delay(100);
  Calc_CompensatorZ(4000);
  t0 = micros() - 5000;
  t2 = micros();
  Speed = 0;
  flag_crash = true;
  time_stop_move = millis() + 1000;
  //calibration();
}

uint32_t micros_;
void loop()
{
  int32_t speed_L;
  int32_t speed_R;
  t_period = 4000;
  static int i = 0; 
  micros_ = micros();
  uint8_t gesture = apds.readGesture();
  if (gesture == APDS9960_LEFT)
  {
    mp3_play (1);
    Serial.println("gesture left");
  }
  if (gesture == APDS9960_RIGHT)
  {
    mp3_play (1);
    Serial.println("gesture right");
  }
  if (micros_ < t2) return;//if period <t2 if yes, change angular velocity
  //Опрос гироприбора:
  Data_mpu6050();
  dt = micros() - t0; // time of previous period
  t0 += dt; //begin of new regulator period
  double Dt = double(dt) * 0.000001;
  //angle near "zero"
  //counting angle with accelerometer
  Acsel = (atan2(AcX, AcZ)) + vertical_Y_adjustment; // * RAD_TO_DEG;
  //velocity of falling down
  Gyro = - (double(GyY) - CompensatorY)  * _1_d_131;

  //Комплементарный фильтр
  AcYsum = ONE_ALFA * (AcYsum + Gyro * Dt) + ALFA * Acsel;
  t2 = t0 + t_period;

  if ( flag_crash)
  {
    if (time_stop_move > millis()) return;
    //Если робот поднят после падения
    if (abs(AcYsum * RAD_TO_DEG) < 15)
    {
      motor_on();
      counter_stepR = 0;
      counter_stepL = 0;
      flag_crash = false;
    }
    else return;
  }

  Serial.println(dMove);
  // Если вошли в критичный режим - робот упал
  if (abs(Move) > MoveLimit || abs(dMove) > dMoveLimit || abs(AcYsum * RAD_TO_DEG) > 40)
  {
    flag_crash = true;
    XSpeed = 0;
    Speed = 0;
    speed_L = 0;
    speed_R = 0;
    counter_stepR = 0;
    counter_stepL = 0;
    speed_xxx_L = 0;
    newSpeedflag_L  = true;
    speed_xxx_R = 0;
    newSpeedflag_R  = true;
    dGyro = 0;
    Move = 0;
    dMove = 0;
    ddMove = 0;
    dMoveOld = 0;
    motor_off();
    //6 Секунд на стабилизацию после падения
    time_stop_move = millis() + 1500;
    GyroOld = 0;
    return;
  }

  XL = counter_stepL; counter_stepL = 0;
  XR = counter_stepR; counter_stepR = 0;

  dMove = double(XL + XR) * 0.5 / Dt;

  ddMove = ddMove * 0.9 + (dMove - dMoveOld) * 0.1 / Dt;
  dMoveOld = dMove;
  Move += (XL + XR) / 2.0; //the distance

  dGyro = 0.9 * dGyro + 0.1 * ((Gyro - GyroOld) / Dt);
  GyroOld = Gyro;

  Speed = (AcYsum)  * Ka + Gyro  * Kg + dGyro * Kdg + XSpeed + (dMove) * Kdm + Move * Km + ddMove * Kddm;
  Speed *= 400.0;

  speed_L = (Speed + Turn);
  speed_R = (Speed - Turn);
  speed_L = constrain(speed_L, -maxSPEED, maxSPEED);
  speed_R = constrain(speed_R, -maxSPEED, maxSPEED);

  //Speed - steps per 100 seconds
  SetSpeed(speed_L, speed_R);
  //counted velocity and formula
  XSpeed = (speed_L + speed_R) / 800.0;
}
