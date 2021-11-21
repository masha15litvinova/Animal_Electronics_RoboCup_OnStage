//танец
void dance() {
  f = true;
  sound(4);
  for (int i = 0; i < 50; i++)
  {
    motors(-i, i, -i, i);
    delay(100);
  }
  motors(-50, 50, -50, 50);
  delay(800);
  for (int i = 50; i > 0; i--)
  {
    motors(-i, i, -i, i);
    delay(100);
  }
  motors(0, 0, 0, 0);
  delay(400);
  for (int i = 0; i < 50; i++)
  {
    motors(i, -i, i, -i);
    delay(100);
  }
  motors(50, -50, 50, -50);
  delay(800);
  for (int i = 50; i > 0; i--)
  {
    motors(i, -i, i, -i);
    delay(100);
  }
  motors(0, 0, 0, 0);
  delay(400);
  //sound(1);
}



void lead_for_el() {
  f = false;
  dir_1 = dir(1);
  dir_2 = dir(2);
  Serial.println();
  Serial.println("crash");
  Serial.print(dir_1);
  Serial.print("     ");
  Serial.println(dir_2);
  Serial.println("crash");
  float es = ((dir_1 + dir_2) / 2) - duration;
  us = (es * kp1) + ((es - errold1) * kd1);
  if (us > 60)
    us = 60;
  if (us < -60)
    us = -60;
//  if ( ((dir_1 == 0) or (dir_1 > duration * 3)) or ((dir_2 == 0) or (dir_2 > duration * 3)))
//    us = 0;
  et = dir_1 - dir_2;
  float ut = ((et * kp2) + (et - errold2) * kd2) * 0.3;
  if (ut > 30)
    ut = 30;
  if (ut < -30)
    ut = -30;
  errold1 = es;
  errold2 = et;
  motors(us - ut, us + ut, us - ut , us + ut);
}

void to_corner() {
  sound(2);
  f = true;
  LIGHT = analogRead(light);
  long int TIME = millis();
  //motors(-60, -60, 60, 60);
  //delay(4000);
  while ((LIGHT < 160 || LIGHT > 1000) && ((millis() - TIME) < 3000))
  {
    motors(-120, -120, 120, 120);
    LIGHT = analogRead(light);
    delay(10);
    // TIME += 10;
  }
  motors(0, 0, 0, 0);
  delay(300);
  motors(45, 45, -45, -45);
  delay(2000);
  motors(0, 0, 0, 0);
  delay(300);
  //sound(1);
}

void scared(int times) {
  f = true;
  sound(3);
  for (int i = 0; i < times; i++)
  {
    motors(-30, 30, -30, 30);
    delay(300);
    motors(30, -30, 30, -30);
    delay(300);
  }
  //mp3_stop ();
  motors(0, 0, 0, 0);
  //sound(1);
}
