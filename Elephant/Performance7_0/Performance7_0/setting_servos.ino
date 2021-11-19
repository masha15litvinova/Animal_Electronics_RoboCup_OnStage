void waiting_num()
{
  LOG_PORT.println("waiting num");
  while (!LOG_PORT.available())
  {
    delay(1);
  }
  if (LOG_PORT.available())
  {
    s_num = LOG_PORT.parseInt();
    LOG_PORT.println("s_num = " + String(s_num));
    delay(500);
  }
}
void setting_servo(int num)
{
  int s_angle = 0;
  LOG_PORT.println("waiting angle");
  while (!LOG_PORT.available())
  {
    delay(1);
  }
  if (LOG_PORT.available())
  {
     s_angle = LOG_PORT.parseInt();
  }
      LOG_PORT.println("s_angle = " + String(s_angle));

  switch (num)
  {
    case 12:
      set_angles(s_angle, AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 1:
      set_angles(AVG_angles[0], s_angle, AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 2:
      set_angles(AVG_angles[0], AVG_angles[1], s_angle, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 3:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], s_angle, AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 4:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], s_angle, AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 5:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], s_angle, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 6:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], s_angle, AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 7:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], s_angle, AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 8:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], s_angle, AVG_angles[9], AVG_angles[10], AVG_angles[11] );
    case 9:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], s_angle, AVG_angles[10], AVG_angles[11] );
    case 10:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], s_angle, AVG_angles[11] );
    case 11:
      set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], s_angle );
    default:
      delay(1);
      servos_go(servos_angles, 0.5);
  }
}
