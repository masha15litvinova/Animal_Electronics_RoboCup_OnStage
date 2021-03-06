/*
--gymnastics  0
--square  1
--flight  2
--dance  3
--sing  4
--spin  5
--scare  6
*/
#include <SoftwareSerial.h>
SoftwareSerial BLUETOOTH (22, 23); //rx,tx
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include <ServoDriverSmooth.h>
ServoDriverSmooth servos[15];
ServoDriverSmooth servo(270);
#define LOG_PORT Serial
#define NANO2 Serial1
#define NANO Serial2
#define GYRO Serial3
#define byte_begin_NANO 253
#define COSTUME true
#define PLATFORM true
#define WINCH true
int tric = 50;
int oldTric = 49;
volatile long winch_enc = 0;
int winch_current = 0;
int s_num = -1;
int height_now = 0;
void setup()
{
  LOG_PORT.begin(115200);
  NANO2.begin(115200);  // receive tric
  NANO.begin(115200);  //receive marker
  GYRO.begin(115200);
  BLUETOOTH.begin(9600);
  pinMode(A12, INPUT);
  pinMode(40, INPUT);
  pinMode(A13, INPUT);
  pinMode(39, INPUT);
  pinMode(A12, INPUT);

  initialize_motors();
  initialize_winch();
  
  winch_homing();
  servos_begin();

  gyro_begin();
  
  while (digitalRead(39) == 0)
  {
    delay(1);
  }
  

  LOG_PORT.println("begin");
  end_tric();
  
  
}
void loop()
{
  
  
switch (tric)
  {
    case 7:
    
      sendSignal(0);
      gymnastics();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("gymnastics");
      LOG_PORT.println("-------------------------------------------");
     
      break;
    case 1:
    
      sendSignal(1);
      square_left();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("square");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    case 2:
    
      sendSignal(2);
      flight();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("flight");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    case 3:

      sendSignal(3);
      dance();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("dance");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    case 4:
   
      sendSignal(4);
      sing();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("sing");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    case 5:
   
      sendSignal(5);
      spin();
      sendSignal(11);
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("spin");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    case 6:
    
      sendSignal(6);
      scare();
      LOG_PORT.println("-------------------------------------------");
      LOG_PORT.println("scare");
      LOG_PORT.println("-------------------------------------------");
      
      break;
    default:
      LOG_PORT.println("error");
      break;

  }
  delay(100);
  

 }
