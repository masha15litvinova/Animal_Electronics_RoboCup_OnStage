int data_array[] = {0, 0, 0, 0, 0};
int motors[] = {0, 0, 0, 0, 0};
int data = 0;
int count = 0;

bool get_data(int x)
{
  if (x == byte_begin_NANO)
  {
    count = 0;
    return true;
  }
  {
    if (count < 4)
    {
      data_array[count] = x;
      count ++;
    }
    return false;
  }
  return false;
}
void print_data()
{
  for (byte i = 0; i < 4; i++)
  {
    motors[i] = map(data_array[i], 0, 252, -252, 252);
  }

  LOG_PORT.println("Tric: " + String(tric) + " Motors: " + String(motors[0]) + ", " + String(motors[1]) + ", " + String(motors[2]) + ", " + String(motors[3]));
  motorsGo(motors[0], motors[1], motors[2], motors[3]);
delay(35);

}

void goMarker()
{
  oldTric = tric;
  LOG_PORT.println("end tric");
  while ((oldTric == tric) or (tric == 50))
  {
    if (NANO.available())
    {
      data = NANO.read();
      if (get_data(data))
      {
        if (NANO2.available())
        {
          tric = NANO2.read();
        }
        print_data();
      }
      //LOG_PORT.println("nano available");
    }
    //LOG_PORT.println("oldTric = "+String(oldTric));
    //LOG_PORT.println("tric = "+String(tric));
  }
}
