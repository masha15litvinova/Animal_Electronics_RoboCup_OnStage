void sendSignal(int num)
{
  
  BLUETOOTH.write(num);
  delay(100);

  }

  void test_monkey()
  {
    /*BLUETOOTH.print(0);
    delay(4000);
    BLUETOOTH.print(1);
    delay(4000);
    BLUETOOTH.print(2);
    delay(4000);
    BLUETOOTH.print(3);
    delay(4000);
    BLUETOOTH.print(4);
    delay(4000);
    BLUETOOTH.print(5);
    delay(4000);*/
    sendSignal(11);
    delay(3000);
    sendSignal(0);
    delay(3000);
    }
