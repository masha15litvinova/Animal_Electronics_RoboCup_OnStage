bool is_started = false;
int val = 0;
int val_old = 0;
bool plus = false;
bool minus = false;
int val1 = 0;
int val2 = 0;
int val_start = 0;
bool gyro_use = false;
void turn_angle(int new_angle, int u_m_max=60, int max_err=2);
void gyro_init()
{
  int val1 = 0;
  long timer = millis();
  int f = 0;
  int f1 = 0;

  int old_f = 0;
  while ((millis() - timer) < 6000)
  {
    if (GYRO.available())
    {
      f = GYRO.read();
      LOG_PORT.println("val_read = " + String(f));
      LOG_PORT.println("doing init...");
    }
  }
  while (digitalRead(39) == 0)
  {
    if (GYRO.available())
    {
      LOG_PORT.println("button");
      f = GYRO.read();
      if (abs(f) > 0)
      {
        gyro_use = true;
      }
      old_f = f;
      f1 = map(f, 0, 255, 0, 360);
      LOG_PORT.println("doing init...");

    }
  }
  val_start = f1;
  val2 = 0;
}
int convert_val(int x)
{
  x = x - val_start;
  int x1 = x + 360;
  int x2 = x;
  int x3 = x - 360;
  if (abs(x1) < 180)
  {
    x = x1;
  }
  if (abs(x2) < 180)
  {
    x = x2;
  }
  if (abs(x3) < 180)
  {
    x = x3;
  }
  /*if (abs(x) == 180)
  {
    x = 179;
  }*/
  return x ;
}
void go_angle(int new_angle, int m1, int m2, int m3, int m4)
{
  if (gyro_use)
  {
    turn_angle(new_angle);
    bool is_begin = false;
    long timer_begin = millis();
    while (!is_begin)
    {
      if (GYRO.available())
      {
        val = GYRO.read();
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        is_begin = true;
      }
      if ((millis() - timer_begin)>2000)
      {
        gyro_use = false;
       break;
        }

    }
    float up = 0;
    float ud = 0;
    float ui = 0.;
    float kp = 2.5;
    float kd = 0.0;
    float ki = 0.0045;
    int u_m = 0;
    int u = 0;
    int err = new_angle - val2;
    int errold = new_angle - val2;


    if (GYRO.available())
    {

      val = GYRO.read();
      val1 = map(val, 0, 255, 0, 360);

      val2 = convert_val(val1);

    }
    err = -new_angle + val2;
    up = err * kp;
    ud = (err - errold) * kd;
    ui = ui + ki * err;
    errold = err;
    u = up + ud + ui;
    u_m = round(u);

    motorsGo(u_m + m1, u_m + m2, u_m + m3, u_m + m4);
    delay(5);
  }
}

void go_angle_msec(int msec, int new_angle, int m1, int m2, int m3, int m4)
{
  if (gyro_use)
  {
    turn_angle(new_angle);
    bool is_begin = false;
    long timer_begin = millis();
    while (!is_begin)
    {
      if (GYRO.available())
      {
        val = GYRO.read();

        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        
        LOG_PORT.println("angle: " + String(val2));

        is_begin = true;
      }
      if ((millis() - timer_begin)>2000)
      {
        gyro_use = false;
       break;
        }

    }
    float up = 0;
    float ud = 0;
    float ui = 0.;
    float kp = 5.0;
    float kd = 5.0;
    float ki = 0.003;
    int u_m = 0;
    int u = 0;
    int err = new_angle - val2;
    int errold = new_angle - val2;

    long time_begin = millis();
    while (millis() - time_begin < msec)
    {

      if (GYRO.available())
      {

        val = GYRO.read();
        val1 = map(val, 0, 255, 0, 360);

        val2 = convert_val(val1);

      }
      err = -new_angle + val2;
      up = err * kp;
      ud = (err - errold) * kd;
      ui = ui + ki * err;
      errold = err;
      u = up + ud + ui;
      u_m = round(u);

      motorsGo(u_m + m1, u_m + m2, u_m + m3, u_m + m4);
      delay(5);
    }
    motorsGo(0, 0, 0, 0);
  }
}
void turn_angle(int new_angle, int u_m_max, int max_err)
{
  LOG_PORT.println("---------------------------------");
  LOG_PORT.println("BEGIN TURN ANGLE");
  LOG_PORT.println("---------------------------------");
  if (gyro_use)
  {
    //LOG_PORT.println("val_begin = " + String(val));
    bool is_begin = false;
    long time_begin = millis();
    while ((!is_begin) or ((millis() - time_begin) < 100))
    {
      if (GYRO.available())
      {
        val = GYRO.read();
        LOG_PORT.println("val_read = " + String(val));
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        /*LOG_PORT.println("!!!!!!!!!!!!!!!!!");
          LOG_PORT.println("val_begin = " + String(val));
          LOG_PORT.println("!!!!!!!!!!!!!!!!!");*/

        is_begin = true;
      }
      if ((millis() - time_begin)>2000)
      {
        gyro_use = false;
       break;
        }

    }





    int err = new_angle - val2;
    int errold = new_angle - val2;
    float up = 0;
    float ud = 0;
    float ui = 0.0;   //подобрать коэффициенты
    float kp = 1.2;
    float kd = 0.0;
    float ki = 0.0058;
    int u = 0;
    
    int u_m = u_m_max + 1;


    while (abs(err) > max_err)
    {

      if (GYRO.available())
      {

        val = GYRO.read();


        LOG_PORT.println("val = " + String(val));
        val1 = map(val, 0, 255, 0, 360);

        val_old = val1;

        //LOG_PORT.println("val_read_map = " + String(val1));
        val2 = convert_val(val1);
        // LOG_PORT.println("val_start = " + String(val_start));
        LOG_PORT.println("angle: " + String(val2));
      }
      err = -new_angle + val2;
      //LOG_PORT.println("err = " + String(err));
      up = err * kp;
      ud = (err - errold) * kd;
      ui = ui + ki * err;
      errold = err;
      u = up + ud + ui;
      u_m = round(u);
      if (abs(err) < 2)
      {
        u_m = 0;
        break;
      }
      //LOG_PORT.println("u_m = "+String(u_m));
      if (abs(u_m) > u_m_max)
      {
        if (u_m > 0)
        {
          u_m = u_m_max;
        }
        else
        {
          u_m = -u_m_max;
        }
      }
      //LOG_PORT.println("u_m = "+String(u_m));
      motorsGo(u_m, u_m, u_m, u_m);
      //LOG_PORT.println("val = "+String(val));
      //LOG_PORT.println("err = " + String(err));
      // LOG_PORT.println("target = "+String(new_angle));
      // LOG_PORT.println("u = " + String(u));
      delay(1);
    }
    motorsGo(0, 0, 0, 0);
    /*LOG_PORT.println("-----------------------------------------------");
      LOG_PORT.println("end turn");
      LOG_PORT.println("-----------------------------------------------");*/
  }
}
void testG()
{
  if (gyro_use)
  {
    //LOG_PORT.println("val_begin = " + String(val));
    bool is_begin = false;
    long time_begin = millis();
    while ((!is_begin) or ((millis() - time_begin) < 1000))
    {
      if (GYRO.available())
      {
        val = GYRO.read();
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        /*LOG_PORT.println("!!!!!!!!!!!!!!!!!");
          LOG_PORT.println("val_begin = " + String(val));
          LOG_PORT.println("!!!!!!!!!!!!!!!!!");*/

        is_begin = true;
      }

    }





    long timer = millis();

    while ((millis() - timer) < 4000)
    {

      if (GYRO.available())
      {

        val = GYRO.read();


        //LOG_PORT.println("val = " + String(val));
        val1 = map(val, 0, 255, 0, 360);

        val_old = val1;

        //LOG_PORT.println("val_read_map = " + String(val1));
        val2 = convert_val(val1);
        // LOG_PORT.println("val_start = " + String(val_start));
        LOG_PORT.println("angle: " + String(val2));
        motorsGo(40, 40, 40, 40);
        delay(1);
      }

      //motorsGo(0, 0, 0, 0);
      /*LOG_PORT.println("-----------------------------------------------");
        LOG_PORT.println("end turn");
        LOG_PORT.println("-----------------------------------------------");*/
    }
  }
  motorsGo(0, 0, 0, 0);
  LOG_PORT.println("END TURNING");
  delay(3000);
  turn_angle(1);
  delay(3000);
}
void test_gyro()
{

  delay(300);
  while (digitalRead(39) == 0)
  {
    turn_angle(0);
  }
}
void gyro_begin()
{
  gyro_init();
  move_winch(140, 80);
  test_gyro();
}
void test_turn()
{
  turn_angle(90, 30, 9);
  }
