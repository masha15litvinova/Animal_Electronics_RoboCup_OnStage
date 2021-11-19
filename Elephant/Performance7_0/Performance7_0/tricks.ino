void gymnastics()
{
  LOG_PORT.println("start doing gymnastics...");
  int v = 60;

  move_winch(155, 150);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.3);


  set_angles(95, 70, 85, 130, 70, 90, 75, 75, 70, 125, 55, 75);
  servos_go(servos_angles, 1.5);
  v = 100;
  go_angle_msec(1800, 0, -v, v, -v, v);
  set_angles(45, 70, 85, 80, 70, 90, 25, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.5);
  go_angle_msec(1800, 0, v, -v, v, -v);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 115, 75);
  servos_go(servos_angles, 1.0);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 115, 125);
  servos_go(servos_angles, 0.5);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.5);
  set_angles(95, 5, 85, 80, 70, 90, 75, 145, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  set_angles(95, 5, 30, 80, 70, 90, 75, 145, 130, 60, 55, 75);
  servos_go(servos_angles, 0.5);
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.5);
  demo_head();
  LOG_PORT.println("stop doing gymnastics...");
  end_tric();
}
void square_right() //backward-right
{
  LOG_PORT.println("start doing square...");
  turn_angle(0,40);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], 45);
  servos_go(servos_angles, 0.9);
  int v = 80;
  if (COSTUME)
  {
    move_winch(175, 150);
  }
  else
  {
    move_winch(150, 60);

  }

  set_angles(95, 70, 85, 140, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2000, 0, v, -v, v, -v);  //backward
  }
  else
  {
    motorsGo(v, -v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);
  set_angles(95, 70, 85, 80, 70, 90, 75, 145, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2500, 0, v, -v, -v, v);  //right
  }
  else
  {
    motorsGo(v, -v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 170, 150, 0);
  all_servos_go(servos_angles, 0.5);
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 125, 55, 75, 170, 150, 0);
  all_servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2500, 0, -v, v, -v, v);  //forward
  }
  else
  {
    motorsGo(-v, v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }

  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 60, 125, 0);
  all_servos_go(servos_angles, 0.8);
  set_angles(95, 5, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2000, 0, -v, v, v, -v);  //left
  }
  else
  {
    motorsGo(-v, v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);
  int v3 = -70;
  //go_angle_msec(1500, 0, -v3, v3, -v3, v3);
  //test_gyro();
   LOG_PORT.println("stop doing square...");
  end_tric();
 
}
void square_left() //backward-left
{
  LOG_PORT.println("start doing square...");
  turn_angle(0,40);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], 45);
  servos_go(servos_angles, 0.9);
  int v = 80;
  if (COSTUME)
  {
    move_winch(175, 150);
  }
  else
  {
    move_winch(150, 60);

  }

  set_angles(95, 70, 85, 140, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2000, 0, v, -v, v, -v);  //backward
  }
  else
  {
    motorsGo(v, -v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);

  
  set_angles(95, 5, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2000, 0, -v, v, v, -v);  //left
  }
  else
  {
    motorsGo(-v, v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);

  
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 170, 150, 0);
  all_servos_go(servos_angles, 0.5);
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 125, 55, 75, 170, 150, 0);
  all_servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2500, 0, -v, v, -v, v);  //forward
  }
  else
  {
    motorsGo(-v, v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }

  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 60, 125, 0);
  all_servos_go(servos_angles, 0.8);

  
  set_angles(95, 70, 85, 80, 70, 90, 75, 145, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro_use)
  {
    go_angle_msec(2500, 0, v, -v, -v, v);  //right
  }
  else
  {
    motorsGo(v, -v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.6);

  
  int v3 = -70;
  //go_angle_msec(1500, 0, -v3, v3, -v3, v3);
  //test_gyro();
   LOG_PORT.println("stop doing square...");
  end_tric();
 
}
void flight()
{
  sendSignal("e");
  LOG_PORT.println("start doing flight...");
  int v = 40;
  /*if (COSTUME)
    {
    move_winch(140, 130);
    }
    else
    {
    move_winch(140, 100);
    }*/
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], AVG_angles[14]);
  all_servos_go(servos_angles, 0.9);
  if (gyro_use)
  {
    turn_angle(90, 28, 9);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
  }
  delay(800);
  if (COSTUME)
  {
    move_winch(310, 190);
  }
  else
  {
    move_winch(310, 70);

  }
  v = 40;
  motorsGo(-v, v, -v, v);
  for (byte i = 0; i < 2; i++)
  {
    set_all_angles(AVG_angles[0], AVG_angles[1] - 60, AVG_angles[2], AVG_angles[3], AVG_angles[4] - 60, AVG_angles[5], AVG_angles[6], AVG_angles[7] + 60, AVG_angles[8], AVG_angles[9], AVG_angles[10] + 60, AVG_angles[11], 170, 60, AVG_angles[14]);
    all_servos_go(servos_angles, 1.8);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], 45, 135, AVG_angles[14]);
    all_servos_go(servos_angles, 1.8);
  }
  motorsGo(0, 0, 0, 0);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], AVG_angles[14]);
  all_servos_go(servos_angles, 0.5);
  //move_winch(140, 90);
  if (gyro_use)
  {
    
    
    turn_angle(-90, 30, 9);
    delay(1000);
  }
  else
  {
    motorsGo(-v, -v, -v, -v);
    delay(4000);
    motorsGo(0, 0, 0, 0);
  }
  if (COSTUME)
  {
    move_winch(310, 190);
  }
  else
  {
    move_winch(310, 100);

  }
  motorsGo(-v, v, -v, v);
  for (byte i = 0; i < 2; i++)
  {
    set_all_angles(AVG_angles[0], AVG_angles[1] - 60, AVG_angles[2], AVG_angles[3], AVG_angles[4] - 60, AVG_angles[5], AVG_angles[6], AVG_angles[7] + 60, AVG_angles[8], AVG_angles[9], AVG_angles[10] + 60, AVG_angles[11], 170, 60, AVG_angles[14]);
    all_servos_go(servos_angles, 1.8);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], 45, 135, AVG_angles[14]);
    all_servos_go(servos_angles, 1.8);
  }
  motorsGo(0, 0, 0, 0);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], AVG_angles[14]);
  all_servos_go(servos_angles, 0.4);
  if (COSTUME)
  {
    move_winch(145, 190);
  }
  else
  {
    move_winch(135, 75);
  }
  turn_angle(0, 40, 10);
  motorsGo(0, 0, 0, 0);
LOG_PORT.println("stop doing flight...");
  end_tric();
}
void dance()
{
  delay(700);
  LOG_PORT.println("start doing dance...");
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 55, 150, 45);
  all_servos_go(servos_angles, 0.9);
  move_winch(150, 100);
  for (byte i = 0; i < 3; i++) //1st paw
  {
    set_angles(60, 70, 125, 80, 70, 90, 75, 75, 70, 60, 55, 75);
    servos_go(servos_angles, 0.5);
    set_angles(60, 90, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
    servos_go(servos_angles, 0.5);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
  for (byte i = 0; i < 3; i++) //2nd paw
  {
    set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 95, 55, 35);
    servos_go(servos_angles, 0.5);
    set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 95, 35, 75);
    servos_go(servos_angles, 0.5);
  }
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 0.25);
  
  set_ears(55, 150);
  ears_move(servos_angles, 1.0);
  move_winch(170, 130);
  for (byte j = 0; j < 2; j++)
  {
    motor_winch(100);     //jumping right paws
    set_angles(60, 70, 125, 45, 70, 130, 110, 75, 30, 95, 55, 35);
    servos_go(servos_angles, 0.55);
    motor_winch(0);
    delay(50);
    motor_winch(-45);
    //95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75
    set_angles(95, 40, 85, 80, 40, 90, 75, 75, 70, 60, 55, 75);
    servos_go(servos_angles, 0.5);
    motor_winch(0);
    delay(50);
    move_winch(150, 95);
    set_angles(95, 70, 85, 80, 70, 90, 110, 75, 70, 60, 55, 75);
    servos_go(servos_angles, 0.3);
    motor_winch(100);    //jumping left paws
    set_angles(60, 70, 125, 45, 70, 130, 110, 75, 30, 95, 55, 35);
    servos_go(servos_angles, 0.55);
    motor_winch(0);
    delay(50);
    motor_winch(-45);
    //95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75
    set_angles(95, 70, 85, 80, 70, 90, 75, 105, 70, 60, 85, 75);
    servos_go(servos_angles, 0.5);
    motor_winch(0);
    delay(50);
    move_winch(150, 100);
    set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
    servos_go(servos_angles, 0.6);
  }
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 55, 150, 20);
  servos_go(servos_angles, 0.3);
    move_winch(150, 140);
  LOG_PORT.println("stop doing dance...");
  end_tric();
}
void sing()
{
  LOG_PORT.println("start doing sing...");
  turn_angle(0, 40);
  steps(5, 20, 60);
  int v = -70;
  turn_angle(0,40);
  delay(200);
  paw_hitting(6, 40);
  //turn_angle(0);
  delay(200);
  motorsGo(0, 0, 0, 0);
   LOG_PORT.println("stop doing sing...");
  end_tric();
}
void spin()
{
  LOG_PORT.println("start doing top toy...");
  set_all_angles(75, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140, 145, 55, 90);
  all_servos_go(servos_angles, 2.0);
  move_winch(60, 160);
  int w_speed = 40;
  for (byte i = 0; i < 4; i++)
  {
    motorsGo(w_speed, w_speed, w_speed, w_speed);
    move_winch(300, 160);
    set_all_angles(75, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140, 145, 55, 120);
    all_servos_go(servos_angles, 0.01);
    move_winch(60, 200);
    set_all_angles(75, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140, 145, 55, 120);
    all_servos_go(servos_angles, 0.01);
    w_speed = w_speed + 50;
  }
  for (byte j = w_speed;  j > 0; j--)
  {
    motorsGo(j, j, j, j);
    delay(20);
  }
  turn_angle(0);
  motorsGo(0, 0, 0, 0);
  
  LOG_PORT.println("stop doing top toy...");
  
  end_tric();

}
void scare()
{
  LOG_PORT.println("start scarying...");
  int v = 150;
  turn_angle(0,40);
  move_winch(130, 180);
  scary_ears();
  if (gyro_use)
  {
    go_angle_msec(1000, 0, -v, v, -v, v);
    go_angle_msec(2000, 0, v, -v, -v, v);
  }
  else
  {
    motorsGo(-v, v, -v, v);
    delay(1000);
    motorsGo(v, -v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }

  motorsGo(0, 0, 0, 0);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 0.5);
  set_all_angles(95, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140, 145, 55, 40);
  all_servos_go(servos_angles, 0.8);
  motorsGo(0, 0, 0, 0);
  move_winch(25, 160);
  delay(1500);
  for (byte i = 0; i < 15; i++)
  {
    int v = 70;
    motorsGo(v, v, v, v);

    delay(100);
    motorsGo(-v, -v, -v, -v);

    delay(100);
  }
  motorsGo(0, 0, 0, 0);
  move_winch(130, 150);
  move_winch(145, 140);
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 60, 125, 0);
  servos_go(servos_angles, 1.0);
  //sendSignal(10);
  if (gyro_use)
  {
    go_angle_msec(2000, 0, -v, v, v, -v);
    go_angle_msec(1000, 0, v, -v, v, -v);

  }
  else
  {
    motorsGo(-v, v, v, -v);
    delay(1000);
    motorsGo(v, -v, v, -v);
    delay(1000);
    motorsGo(0, 0, 0, 0);
  }
  LOG_PORT.println("stop scarying...");
  end_tric();
}
void end_tric()
{
  //sendSignal(7);
  int   v5 = -70;

  move_winch(150, 100);
  set_all_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75, 55, 150, 40);
  all_servos_go(servos_angles, 1.2);
  set_ears(55, 130);
  ears_move(servos_angles, 0.4);

  goMarker();
  LOG_PORT.println("end current tric");
  

}
void steps(int count, float amplitude, int v)
{
  turn_angle(0,40);

  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], 55, 150, 175);
  all_servos_go(servos_angles, 1.5);
  move_winch(135, 150);
  int const_value = 41;
  float time_s = amplitude / const_value;

  int ampl = round(amplitude);
  for (byte j = 0; j < count / 2; j++)
  {
    motorsGo(-v, v, -v, v);


    LOG_PORT.println("servos move");
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 75 );

    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 75);
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 175 );

    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 175);
    all_servos_go(servos_angles, time_s);
  }
  turn_angle(0,40);
  for (byte j = 0; j < count / 2; j++)
  {
    motorsGo(v, -v, v, -v);

    LOG_PORT.println("servos move");
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 75 );
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 75);
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 175 );
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 175);
    all_servos_go(servos_angles, time_s);
  }
  motorsGo(0, 0, 0, 0);

}
void steps_dance(int count, float amplitude)
{
  

  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], 55, 150, 175);
  all_servos_go(servos_angles, 0.5);
  move_winch(135, 100);
  int const_value = 41;
  float time_s = amplitude / const_value;

  int ampl = round(amplitude);
  for (byte j = 0; j < count / 2; j++)
  {
    


    LOG_PORT.println("servos move");
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 75 );

    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 75);
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 150, 175 );

    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11], 145, 55, 175);
    all_servos_go(servos_angles, time_s);
  }
  
  
  motorsGo(0, 0, 0, 0);

}

void sit_lie_stand()
{
  turn_angle(0);
  int v4 = 80;
  if (gyro_use)
  {
    turn_angle(-70);
  }

  move_winch(160, 90);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1.5);
  set_angles(90, 70, 85, 125, 70, 10, 30, 75, 135, 65, 55, 75);
  servos_go(servos_angles, 2.0);
  move_winch(30, 75);
  set_angles(95, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140);
  servos_go(servos_angles, 2.0);
  move_winch(30, 80);

  turn_angle(0);
  end_tric();
}



void ballet()
{

  smooth_down_speed(0, -20, 20);
  motorsGo(-20, -20, -20, -20);
  delay(1000);
  smooth_down_speed(-20, -27, 20);
  set_angles(70, 20, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);//1st paw left
  servos_go(servos_angles, 1.5);
  smooth_down_speed(-27, -38, 20);
  set_angles(90, 20, 130, 75, 70, 85, 75, 75, 75, 85, 55, 75);//1st paw back
  servos_go(servos_angles, 1.0);
  smooth_down_speed(-27, -45, 20);
  set_angles(90, 20, 130, 75, 10, 85, 75, 75, 75, 85, 55, 75);//2nd paw left
  servos_go(servos_angles, 1.5);
  smooth_down_speed(-45, -55, 20);
  set_angles(90, 20, 130, 90, 10, 130, 75, 75, 75, 85, 55, 75);//2nd paw back
  servos_go(servos_angles, 1.0);
  smooth_down_speed(-55, -65, 20);
  set_angles(90, 20, 130, 90, 10, 130, 75, 140, 75, 85, 55, 75);//3rd paw right
  servos_go(servos_angles, 1.5);
  smooth_down_speed(-65, -80, 20);
  set_angles(90, 20, 130, 90, 10, 130, 55, 140, 20, 85, 55, 75);//3rd paw right
  servos_go(servos_angles, 1.0);
  smooth_down_speed(-80, -120, 20);
  delay(1000);
  smooth_up_speed(-120, 0, 20);
  set_angles(70, 95, 85, 75, 70, 85, 75, 75, 75, 55, 55, 75);
  servos_go(servos_angles, 2.0);

}
void ears_tric()
{
  set_ears(145, 55);
  ears_move(servos_angles, 0.6);
  set_ears(55, 130);
  ears_move(servos_angles, 0.6);
  set_ears(145, 130);
  ears_move(servos_angles, 0.6);
  set_ears(55, 55);
  ears_move(servos_angles, 0.6);
  set_ears(55, 130);
  ears_move(servos_angles, 0.6);
}
void scary_ears()
{
  for (byte j = 0; j < 8; j++)
  {

    set_ears(75, 120);
    ears_move(servos_angles, 0.09);
    LOG_PORT.println("first");
    //delay(3000);
    set_ears(110, 85);
    ears_move(servos_angles, 0.09);
  }
}
void paw_hitting(int count, float amplitude)
{
  servos_begin();
  int const_value = 45;
  float time_s = amplitude / const_value;
  int ampl = round(amplitude);
  for (byte j = 0; j < count / 2; j++)
  {
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl, 55, 145, 170);
    all_servos_go(servos_angles, time_s);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], 55, 145, 75);
    all_servos_go(servos_angles, time_s);
  }
}
void start_position()
{
  if (COSTUME)
  {
    move_winch(140, 80);
  }
  else
  {
    move_winch(130, 50);
  }
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1);
  turn_angle(0);
}
void circle_moving()
{
  int count_steps = 15;
  int current_angle = 0;
  int v = 75;
  turn_angle(0);
  LOG_PORT.println("1st part");

  while (current_angle < 170 - round(360 / count_steps) )
  {
    current_angle = current_angle + round(360 / count_steps);
    turn_angle(current_angle);
    go_angle_msec(800, current_angle, -v, v, -v, v);
  }
  turn_angle(179);
  LOG_PORT.println("turning");
  motorsGo(-v, -v, -v, -v);
  delay(500);
  motorsGo(0, 0, 0, 0);
  turn_angle(-179);
  current_angle = -180;
  LOG_PORT.println("2nd part");
  while (current_angle < round(360 / count_steps))
  {
    current_angle = current_angle + round(360 / count_steps);
    turn_angle(current_angle);
    go_angle_msec(800, current_angle, -v, v, -v, v);
  }
  turn_angle(0);
  motorsGo(0, 0, 0, 0);
}
void smooth_up_speed(int b_s, int e_s, int t)
{
  for (byte i = b_s; i < e_s; i++)
  {
    motorsGo(i, i, i, i);
    LOG_PORT.println("i = " + String(i));
    delay(t);
  }
}
void smooth_down_speed(int b_s, int e_s, int t)
{
  Serial.println("b_s = " + String(b_s));
  int j = b_s;
  while (j > e_s)
  {
    motorsGo(j, j, j, j);
    Serial.println("b_s = " + String(b_s));

    LOG_PORT.println("j = " + String(j));

    delay(t);
    j--;
  }
  Serial.println("e_s = " + String(e_s));

}
void go_sleep()
{


  set_all_angles(45, 70, 85, 120, 70, 90, 40, 75, 70, 105, 55, 75, 150, 40, 90);
  all_servos_go(servos_angles, 1.7);
  move_winch(20, 45);
  delay(3000);

  end_tric();
}
void wake_up()
{
  move_winch(130, 80);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], AVG_angles[14]);
  all_servos_go(servos_angles, 2.0);

}
void lie()
{
  set_angles(95, 70, 25, 80, 70, 30, 75, 75, 135, 60, 55, 140);
  servos_go(servos_angles, 1.0);
}
void stand()
{
  set_angles(95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75);
  servos_go(servos_angles, 1.0);
}
void sit()
{
  set_angles(90, 70, 85, 125, 70, 10, 30, 75, 135, 65, 55, 75);
  servos_go(servos_angles, 1.0);
}
void sleeping()
{
  set_angles(45, 70, 85, 120, 70, 90, 40, 75, 70, 105, 55, 75);
  servos_go(servos_angles, 2.0);
}
void gymnastics1()
{
  int v = 60;
  if (gyro_use)
  {
    turn_angle(30);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(1000);
    motorsGo(0, 0, 0, 0);
  }

  move_winch(170, 75);
  //95, 70, 85, 80, 70, 90, 75, 75, 70, 60, 55, 75
  set_all_angles(65, 70, 85, 115, 70, 140, 40, 75, 20, 90, 55, 75, 60, 150, 145);
  all_servos_go(servos_angles, 2.0);
  move_winch(0, 90);
  for (byte j = 0; j < 4; j++)
  {
    set_all_angles(65, 70, 85, 115, 70, 140, 5, 75, 0, 90, 55, 75, 145, 150, 145);
    all_servos_go(servos_angles, 0.5);
    set_all_angles(65, 70, 85, 150, 70, 160, 40, 75, 20, 90, 55, 75, 60, 55, 145);
    all_servos_go(servos_angles, 0.5);
  }
  set_all_angles(65, 70, 85, 115, 70, 140, 40, 75, 20, 90, 55, 75, 60, 150, 145);
  all_servos_go(servos_angles, 2.0);
  /*
    set_angles(35, 70, 85, 115, 70, 15, 40, 75, 140, 70, 55, 75);
    servos_go(servos_angles, 1);

    set_angles(35, 70, 30, 115, 70, 15, 40, 75, 140, 70, 55, 75);
    servos_go(servos_angles, 1);
    set_angles(35, 70, 85, 115, 70, 15, 40, 75, 140, 70, 55, 75);
    servos_go(servos_angles, 1);
    set_angles(85, 70, 85, 115, 70, 15, 40, 75, 140, 70, 55, 75);
    servos_go(servos_angles, 1);
    int v3 = -70;
    go_angle_msec(1500, 0, -v3, v3, -v3, v3);
  */

  delay(2000);
  end_tric();
}
void demo_head()
{
  ears_tric();
  trunk_tric();
}
void trunk_tric()
{
  move_winch(150, 100);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], AVG_angles[14]);
  all_servos_go(servos_angles, 0.4);
  for (byte i = 0; i < 1; i++) //1 for perfance
  {
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], 0);
    all_servos_go(servos_angles, 1.5);
    set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13], 175);
    all_servos_go(servos_angles, 1.5);

  }
  
}
