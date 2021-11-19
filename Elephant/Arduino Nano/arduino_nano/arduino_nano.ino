
/*smooth turns, Running Average for data from rpi*/

#include <SoftwareSerial.h>
SoftwareSerial MegaSerial(7, 8); // RX, TX
SoftwareSerial MegaTric(5, 6); //RX, TX
#define RPI Serial
#define MEGA MegaSerial
#define TRIC MegaTric
#define RPI_baudrate 115200
#define MEGA_baudrate 115200
#define byte_begin_RPI 254
#define byte_begin_MEGA 253

int data_array[] = {0, 0, 0, 0, 0};
int data = 0;
int count = 0;
float FILTER_COEF_TURN = 0.2;
float FILTER_COEF_STRAIGHT = 0.25;
// Screen dimentsions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define SCLK_PIN 12
#define MOSI_PIN 11
#define DC_PIN   9
#define CS_PIN   10
#define RST_PIN  6


#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>


Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

uint16_t markerColors[] = {WHITE, WHITE, RED, GREEN, BLUE};
String markerNames[] = {"Off", "No", "Stop", "Move", "Listen"};
String trics[] = {"", "Square", "Flight", "Dance", "Sing", "Top toy", "Scary", "Gymnastics"};
int textSize = 2;

int oldCX = 50;
int oldCY = 50;
int oldSide = 50;

long oldTime = 0;

int oldState = 1;

int oldCommand = 50;
int newCommand = 50;
int e_straight = 0;
int e_turn = 0;
int e_straight_old = 0;
int e_turn_old = 0;
int side = 0;
int side_f = 0;
int cx = 0;
int cy = 0;
int cy_f = 0;
int cx_f = 0;
int cx_old = 0;
int cy_old = 0;
int side_old = side;
int mode = 0;
int last_mode = 0;
int u_straight_i = 0;
int u_straight_d = 0;
int u_turn_i = 0;
int motors[] = {0, 0, 0, 0};
bool get_data(int x)
{
  if (x == byte_begin_RPI)
  {
    count = 0;
    return true;
  }
  else
  {
    if (count < 5)
    {
      data_array[count] = x;
      count ++;
    }
    return false;
  }
  return false;
}
void send_data()
{
  int u_straight = 0;
  int u_turn = 0;
  
  int u_straight_send = 0;
  int u_turn_send = 0;
  int u_send = 0;
  int u = 0;
  float k_straight_p = 0.0;
  float k_straight_i = 0.0;
  float k_straight_d = 4.0;
  float k_turn_p = 0.0;
  float k_turn_i = 0.0;
  //cx_f = map(cx_f, 0, 240, 0, 500);
  //side_f = map(side_f, 0, 240, 0, 500);

  if (mode == 3)
  {
    if (last_mode != 3)
    {
      u_straight = 0;
      u_turn = 0;
      k_straight_i = 0.00;
      k_straight_d = 0.0;
      k_turn_i = 0.00; //-0.008
      u_straight_i = 0;
      u_turn_i = 0;
    }
    else
    {
      //k_straight_i = 0.001;
      k_straight_i = 0.000;
      k_straight_d = 4.0;
      k_turn_i = 0.0099; //-0.008
      
    }
    // k_straight_p = 2.1;
    k_straight_p = 1.9; //1.8
    k_turn_p = 0.4;

    

  }

  else
  {
    k_straight_p = 0.0;
    k_straight_i = 0.0;
    k_straight_d = 0.0;
    u_straight_i = 0;
    k_turn_p = 0.0;
    k_turn_i = 0.0;
    u_turn_i = 0;

  }
  e_straight_old = e_straight;
  e_straight = 60 - side_f;
  e_turn = convert_x(cx_f);
  e_turn_old = e_turn;
  

  if (abs(e_turn) < 5)
  {
    e_turn = 0;
    e_turn_old = 0;
    u_turn_i = 0;
  }
  if (abs(e_straight) < 3)
  {
    e_straight = 0;
    e_straight_old = 0;
    u_straight_i = 0;
  }
  u_straight_i = u_straight_i + e_straight * k_straight_i;
    u_straight_d = (e_straight - e_straight_old) * k_straight_d;
  u_straight = (e_straight * k_straight_p + u_straight_i+u_straight_d);

  u_turn_i = u_turn_i + e_turn * k_turn_i;
  u_turn = -(e_turn * k_turn_p +  u_turn_i);
  motors[0] = -u_straight + u_turn;
  motors[1] = u_straight + u_turn;
  motors[2] = -u_straight + u_turn;
  motors[3] = u_straight + u_turn;
  for (byte i = 0; i < 4; i++)
  {
    if (motors[i] > 252)
    {
      motors[i] = 252;
    }
    if (motors[i] < -252)
    {
      motors[i] = -252;
    }
  }

  for (byte i = 0; i < 4; i++)
  {
    motors[i] = map(motors[i], -252, 252, 0, 252);
  }
  MEGA.write(byte_begin_MEGA);
  for (byte i = 0; i < 4; i++)
  {
    MEGA.write(motors[i]);
  }
  TRIC.write(newCommand);



}


void printText(int xText, int yText, uint16_t color, String str)
{
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  tft.setCursor(xText, yText);
  tft.setTextColor(color);
  tft.print(char_array);
}

void eraseSymbol(int x, int y)
{
  tft.fillRect(x, y, x + textSize * 5, y + textSize * 8, BLACK);
}

void changeText(int oldN, int newN)
{
  if (oldN != newN)
  {
    printText(0, 0, BLACK, markerNames[oldN]);
    printText(0, 0, markerColors[newN], markerNames[newN]);
  }
  if (oldCommand != newCommand)
  {
    if (oldCommand == 50)
    {
      printText(0, 25, BLACK, "No");
    }
    else
    {
      printText(0, 25, BLACK, trics[oldCommand]);
    }
    if (newCommand == 50)
    {
      printText(0, 25, BLUE, "No");
    }
    else
    {
      printText(0, 25, BLUE, trics[newCommand]);
    }
  }
}
void changeTextNew(int oldN, int newN, int oldM0, int newM0, int oldM1, int newM1, int oldM2, int newM2, int oldM3, int newM3)
{
  if (oldN != newN)
  {
    printText(0, 0, BLACK, markerNames[oldN]);
    printText(0, 0, markerColors[newN], markerNames[newN]);
  }
  //printText(20, 20, BLACK, String(oldM0)/*+String(" ")+String(oldM1)+String(" ")+String(oldM2)+String(" ")+String(oldM3)*/);
  delay(25);

  //printText(20, 20, YELLOW, String(newM0)/*+String(" ")+String(oldM1)+String(" ")+String(oldM2)+String(" ")+String(oldM3)*/);

}

void marker(int state, int command, int c_x, int c_y, int side) {
  c_x = 128 - map(c_x, 0, 240, 0, 128);
  c_y = map(c_y, 0, 240, 0, 128);
  changeText(oldState, state);
  last_mode = oldState;
  switch (state) {
    case 1:
      if (oldState > 1)
      {
        tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      }
      break;
    case 2:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
    case 3:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
    case 4:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
  }
  oldCX = c_x;
  oldCY = c_y;
  oldSide = side;
  oldState = state;
}
int convert_x(int x)
{
  return map(x, 0, 240, -128, 128);
}
void setup(void) {
  RPI.begin(RPI_baudrate);
  MEGA.begin(MEGA_baudrate);
  TRIC.begin(MEGA_baudrate);
  //tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
  tft.begin();        // initialize a SSD1351 chip, 128x128 pixels
  tft.fillScreen(BLACK);

  tft.setTextSize(textSize);
  marker(0, 50, 0, 0, 50);
  delay(1000);

}

void loop() {
  if (RPI.available())
  {
    data = RPI.read();
    if (get_data(data))
    {
      mode = data_array[0];
      newCommand = data_array[1];
      cx = data_array[2];
      cx_f = cx * FILTER_COEF_TURN + cx_f * (1 - FILTER_COEF_TURN);
      side = data_array[4];
      side_f = side * FILTER_COEF_STRAIGHT + side_f * (1 - FILTER_COEF_STRAIGHT);
      cy = data_array[3];
      cy_f = cy * FILTER_COEF_TURN + cy_f * (1 - FILTER_COEF_TURN);
      
      
        FILTER_COEF_TURN = 0.38;
      
      
        FILTER_COEF_STRAIGHT = 0.25;
      

      marker(mode, newCommand, cx_f, cy_f, side_f);
      send_data();
      oldCommand = newCommand;
      cx_old = cx;
      cy_old = cy;
      side_old = side;
delay(15);
    }

  }

}
