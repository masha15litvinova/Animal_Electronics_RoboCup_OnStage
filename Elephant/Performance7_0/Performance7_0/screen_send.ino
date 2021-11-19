/*
  0 - begin performance
  1 - begin tech demo
  2 - gyro calibration
  3 - marker following and waiting command
  4 - winch calibration
*/
void set_nano_mode(char mode)
{
  NANO2.write(mode);
}
void send_values(char text[])
{
  if (text == "gyro")
  {
    NANO2.write(val2);
  }
  if (text == "winch")
  {
    NANO2.write(winch_current);

  }

}
