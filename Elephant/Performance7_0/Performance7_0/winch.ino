#define MOTORw_EN 24
#define MOTORw_INA1 25
#define MOTORw_INB1 26
#define MOTORw_PWM 46

#define WINCH_ENC1 2
#define WINCH_ENC2 3

#define WINCH_CS A6

int winch_dir = 0;
int length1 = 0;
int stepsPerRevolution = 1500;
int winch_diameter = 32;
int max_height = 400;
float iu_old, err_old;
int target = 0;
boolean done = false;
int speed_m = 0;
bool enc_use = false;
int targetH = 0;

void motor_winch(int pwm_value)
{
  if (pwm_value > 255)
  {
    pwm_value = 255;
    winch_dir = 1;
  }

  if (pwm_value < -255)
  {
    pwm_value = -255;
    winch_dir = -1;
  }

  if (pwm_value > 0)
  {
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, HIGH);
    digitalWrite(MOTORw_INB1, LOW);
    analogWrite(MOTORw_PWM, pwm_value);
  }
  else if (pwm_value == 0)
  {
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, HIGH);
    digitalWrite(MOTORw_INB1, HIGH);
    analogWrite(MOTORw_PWM, pwm_value);
  }
  else
  {
    pwm_value = pwm_value * (-1);
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, LOW);
    digitalWrite(MOTORw_INB1, HIGH);
    analogWrite(MOTORw_PWM, pwm_value);
  }
}

void winchEncoderEvent1() {
  // look for a low-to-high on channel A
  if (digitalRead(WINCH_ENC1) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC2) == LOW) {
      winch_enc++;         // CW
    }
    else {
      winch_enc--;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC2) == HIGH) {
      winch_enc++;          // CW
    }
    else {
      winch_enc--;          // CCW
    }
  }

}

void winchEncoderEvent2() {
  // look for a low-to-high on channel B
  if (digitalRead(WINCH_ENC2) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(WINCH_ENC1) == HIGH) {
      winch_enc++;         // CW
    }
    else {
      winch_enc--;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC1) == LOW) {
      winch_enc++;          // CW
    }
    else {
      winch_enc--;          // CCW
    }
  }
}
float winchGetLength()
{
  length1 = ((3.1415926 * winch_diameter) / stepsPerRevolution) * winch_enc;
  return length1;
}

void winch_homing()  //calibration to winch "zero"
{
  if (WINCH)
  {
    int max_c = 0;
    if (COSTUME)
    {
      max_c = 350;
    }
    else
    {
      max_c = 210;
    }

    int start = millis();
    LOG_PORT.println("winch_current:");
    do
    {
      LOG_PORT.print("winch_current: ");
      LOG_PORT.println(winch_current);
      LOG_PORT.print("winch_enc: ");
      LOG_PORT.println(winch_enc);
      winch_current = analogRead(WINCH_CS);
      if (COSTUME)
      {
        motor_winch(180);
      }
      else
      {
        motor_winch(125);

      }
      delay(100);
    } while (analogRead(WINCH_CS) < max_c);
    motor_winch(0);  //stop the motor: robot stops in current position
    winch_enc = 0; //make winch enc "zero"
  }
}

int move_winch(float height, float max_speed)
{
  if (WINCH)
  {
    float p = 0.45, i = 0.4, d = 1, pu, du, iu, u = 0.0, err = 10, cur_height;
    height = max_height - height;
    float u1 = 0;
    float constVal = 0.0; //max speed coefficient
    float constVal2 = 0.0; //min speed coefficient
    if (COSTUME)
    {
      constVal = 5.5;
      constVal2 = 0.3;
    }
    else
    {
      constVal = 3.5;
      constVal2 = 0.2;
    }
    int max_speed1 = round(abs(height - height_now) * constVal);  //max speed
    int min_speed1 = round(abs(height - height_now) * constVal2); //min speed
    if (COSTUME)
    {
      if (max_speed1 > 170)
      {
        max_speed1 = 170;
      }
      if (min_speed1 < 100)
      {
        min_speed1 = 100;

      }
    }
    else
    {
      if (max_speed1 > 200)
      {
        max_speed1 = 200;
      }
      if (min_speed1 < 60)
      {
        min_speed1 = 60;
      }
    }
    while (abs(err) > 5)
    {
      if (abs(height) > max_height)height = max_height;
      else height = abs(height);
      cur_height = winchGetLength();
      err = cur_height - height;
      pu = p * err;
      iu = iu_old + i * err;
      iu_old = iu;
      du = d * (err - err_old);
      u = pu + du + iu;
      if (abs(u) > abs(max_speed1))
      {
        if (u > 0)
        {
          u1 = max_speed1;
        }
        else
        {
          u1 = -max_speed1;
        }


      }
      if (abs(u) < abs(min_speed1))
      {
        if (u > 0)
        {
          u1 = min_speed1;
        }
        else
        {
          u1 = -min_speed1;
        }
      }
      motor_winch(round(u1));
      delay(1);
    }
    motor_winch(0);
    iu_old = 0;
    height_now = max_height - height;
    LOG_PORT.println("height_now = " + String(height_now));  //current height of robot's body
  }
}

void initialize_winch()
{
  pinMode(MOTORw_EN, OUTPUT);
  pinMode(MOTORw_INA1, OUTPUT);
  pinMode(MOTORw_INB1, OUTPUT);
  pinMode(MOTORw_PWM, OUTPUT);

  pinMode(WINCH_ENC1, INPUT);
  pinMode(WINCH_ENC2, INPUT);

  pinMode(WINCH_CS, INPUT);

  attachInterrupt(digitalPinToInterrupt(WINCH_ENC1), winchEncoderEvent1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(WINCH_ENC2), winchEncoderEvent2 , CHANGE);
}
void test_winch()  //test winch with potentiometr
{
  while (digitalRead(39) == 0)
  {
    targetH = map(analogRead(A12), 0, 1023, 0, 400);
    LOG_PORT.println("targetH = " + String(targetH));
    delay(1);
  }
  move_winch(targetH, 70);
}
void test_winch2() //test winch moving
{
  move_winch(140, 100);
  delay(1200);
  move_winch(200, 100);
  delay(1200);
  move_winch(260, 100);
  delay(1200);
  move_winch(320, 100);
  delay(1200);
  move_winch(380, 100);
  delay(1200);
   move_winch(140, 100);
  delay(1200);
}
