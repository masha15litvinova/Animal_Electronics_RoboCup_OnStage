//движение моторов
void motors(int m1, int m2, int m3, int m4)
{
  if (m1 > 255)
    m1 = 255;
  if (m1 < -255)
    m1 = -255;
  if (m2 > 255)
    m2 = 255;
  if (m2 < -255)
    m2 = -255;
  if (m3 > 255)
    m3 = 255;
  if (m3 < -255)
    m3 = -255;
  if (m4 > 255)
    m4 = 255;
  if (m4 < -255)
    m4 = -255;

  if (m1 > 0)
  {
    digitalWrite(MOTOR1_EN , HIGH);
    digitalWrite(MOTOR1_INA1, HIGH);
    digitalWrite(MOTOR1_INB1, LOW);
    analogWrite(MOTOR1_PWM, m1);
  }
  else
  {
    m1 = m1 * (-1);
    digitalWrite(MOTOR1_EN, HIGH);
    digitalWrite(MOTOR1_INA1, LOW);
    digitalWrite(MOTOR1_INB1, HIGH);
    analogWrite(MOTOR1_PWM, m1);
  }


  if (m2 > 0)
  {
    digitalWrite(MOTOR2_EN , HIGH);
    digitalWrite(MOTOR2_INA2, LOW);
    digitalWrite(MOTOR2_INB2, HIGH);
    analogWrite( MOTOR2_PWM, m2);
  }
  else
  {
    m2 = m2 * (-1);
    digitalWrite(MOTOR2_EN, HIGH);
    digitalWrite(MOTOR2_INA2, HIGH);
    digitalWrite(MOTOR2_INB2, LOW);
    analogWrite(MOTOR2_PWM, m2);
  }


  if (m3 > 0)
  {
    digitalWrite(MOTOR3_EN , HIGH);
    digitalWrite(MOTOR3_INA3, HIGH);
    digitalWrite(MOTOR3_INB3, LOW);
    analogWrite( MOTOR3_PWM, m3);
  }
  else
  {
    m3 = m3 * (-1);
    digitalWrite(MOTOR3_EN, HIGH);
    digitalWrite(MOTOR3_INA3, LOW);
    digitalWrite(MOTOR3_INB3, HIGH);
    analogWrite(MOTOR3_PWM, m3);
  }


  if (m4 > 0)
  {
    digitalWrite(MOTOR4_EN , HIGH);
    digitalWrite(MOTOR4_INA4, HIGH);
    digitalWrite(MOTOR4_INB4, LOW);
    analogWrite( MOTOR4_PWM, m4);
  }
  else
  {
    m4 = m4 * (-1);
    digitalWrite(MOTOR4_EN, HIGH);
    digitalWrite(MOTOR4_INA4, LOW);
    digitalWrite(MOTOR4_INB4, HIGH);
    analogWrite(MOTOR4_PWM, m4);
  }
}

//фильтр значений датчиков
float FilVal(float newVal1, float newVal2, int num) {
  static float filVal1 = 0;
  static float filVal2 = 0;
  float k;
  // резкость фильтра зависит от модуля разности значений
  if (num == 1)
  {
    if (abs(newVal1 - filVal1) > 1.5) k = 0.9;
    else k = 0.03;

    filVal1 += (newVal1 - filVal1) * k;
    return filVal1;
  }
  else
  {
    if (abs(newVal2 - filVal2) > 1.5) k = 0.9;
    else k = 0.03;

    filVal2 += (newVal2 - filVal2) * k;
    return filVal2;
  }
}

//считывание значений датчиков
int dir (int num) {
  if (num == 1)
  {
    digitalWrite(trigPin_1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_1, LOW);
    duration_new_1 = FilVal(pulseIn(echoPin_1, HIGH), 0, 1);
    return duration_new_1;
  }
  else
  {
    digitalWrite(trigPin_2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_2, LOW);
    duration_new_2 = FilVal(0, pulseIn(echoPin_2, HIGH), 2);
    return duration_new_2;
  }
}

//воспроизведение звука
void sound (int num) {
  if(anibeshenstvo){
    mp3_play (num + 3);
  }else{
  mp3_play (num); // Произрываем "mp3/0001.mp3"
  }
  delay (700);
  //mp3_stop ();
}
