#include <Magenta_lib.h>
#include <esp_now.h>
#include <WiFi.h>

#define COLOR   1
#define BGCOLOR 2

#define PURPLE  1
#define BLUE    2
#define RED     3
#define GREEN   4
#define WHITE   5

#define NORA  1
#define REMO  2

#define ACC 1

#define SERVO1  1
#define SERVO2  2

#define HIGH  1
#define LOW   2

#define PEEPHIGH  0
#define PEEPLOW   1

int Counter = 0;

int potentiometer_last0 = 0;
int potentiometer_last1 = 0;
int potentiometer_last2 = 0;

int button_last1      = 0;
int button_last2      = 0;
int button_last3      = 0;
int button_lastUp     = 0;
int button_lastRight  = 0;
int button_lastDown   = 0;
int button_lastLeft   = 0;
int button_lastCenter = 0;

int r     = 0;
int g     = 0;
int b     = 0;
int BGC_r = 0;
int BGC_g = 0;
int BGC_b = 0;

int change = 1;
int color = 1;
int segment = 1;
int acc = 0;
int servo = 1;
int buzzer = 1;

int move = 0;
int grad1 = 0;
int grad2 = 0;

char SA1;
char SA2;
char SA3;
char SA4;

int SAM;

typedef struct data_struct {
  int r, g, b;
  int BGC_r, BGC_g, BGC_b;
  int grad1, grad2;
  int button1, button2, button3, buttonC, buttonU, buttonR, buttonD, buttonL;
  char sa1, sa2, sa3, sa4;
  int sam;
} data_struct;

data_struct sendData;

// Empfänger-MAC-Adresse (anpassen!)
uint8_t peerAddress1[] = {0x28, 0x37, 0x2F, 0x05, 0x93, 0x24};
uint8_t peerAddress2[] = {0xCC, 0x8D, 0xA2, 0x33, 0x3D, 0x04};
esp_now_peer_info_t peerInfo;

// ======================
// Callback für Sendestatus
// ======================
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Sendestatus: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Erfolg" : "Fehler");
}

void setup() 
{
  Serial.begin(115200);
  magentaobj.init();
  magentaobj.setSegmentAnzeige('!', '!', '!', '!');
  WiFi.mode(WIFI_STA);

  // --- ESP-NOW Init ---
  if (esp_now_init() != ESP_OK) {
    Serial.println("Fehler bei ESP-NOW Init");
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, peerAddress2, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Fehler beim Hinzufügen des Peers");
    return;
  }

  Serial.println("Sender bereit");
}

// void Buzzer()
// {
//   switch (buzzer)
//   {
//     case HIGH:
//       magentaobj.Buzzer(PEEPHIGH);
//       break;
//
//     case LOW:
//       magentaobj.Buzzer(PEEPLOW);
//       break;
//   }
// }

void ChangeColor()
{
  switch (change)
  {
  case COLOR:
    // printf("->color\n");
    if(magentaobj.potentiometer_0 != potentiometer_last0 && magentaobj.potentiometer_0 >= potentiometer_last0)
    {
      r = r + 10;
      if (r >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        r = 250;
      }
      potentiometer_last0 = magentaobj.potentiometer_0;
    }
    if(magentaobj.potentiometer_0 != potentiometer_last0 && magentaobj.potentiometer_0 <= potentiometer_last0)
    {
      r = r - 10;
      if (r <= 0)
      {
        buzzer = LOW;
        // Buzzer();
        r = 0;
      }
      potentiometer_last0 = magentaobj.potentiometer_0;
    }

    if(magentaobj.potentiometer_1 != potentiometer_last1 && magentaobj.potentiometer_1 >= potentiometer_last1)
    {
      g = g + 10;
      if (g >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        g = 250;
      }
      potentiometer_last1 = magentaobj.potentiometer_1;
    }
    if(magentaobj.potentiometer_1 != potentiometer_last1 && magentaobj.potentiometer_1 <= potentiometer_last1)
    {
      g = g - 10;
      if (g <= 0)
      {
        buzzer = LOW;
        // Buzzer();
        g = 0;
      }
      potentiometer_last1 = magentaobj.potentiometer_1;
    }

    if(magentaobj.potentiometer_2 != potentiometer_last2 && magentaobj.potentiometer_2 >= potentiometer_last2)
    {
      b = b + 10;
      if (b >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        b = 250;
      }
      potentiometer_last2 = magentaobj.potentiometer_2;
    }
    if(magentaobj.potentiometer_2 != potentiometer_last2 && magentaobj.potentiometer_2 <= potentiometer_last2)
    {
        buzzer = LOW;
        // Buzzer();
      b = b - 10;
      if (b <= 0)
      {
        b = 0;
      }
      potentiometer_last2 = magentaobj.potentiometer_2;
    }

  break;
  
  case BGCOLOR:
  // printf("->bgcolor\n");
    if(magentaobj.potentiometer_0 != potentiometer_last0 && magentaobj.potentiometer_0 >= potentiometer_last0)
    {
      BGC_r = BGC_r + 10;
      if (BGC_r >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        BGC_r = 250;
      }
      potentiometer_last0 = magentaobj.potentiometer_0;
    }
    if(magentaobj.potentiometer_0 != potentiometer_last0 && magentaobj.potentiometer_0 <= potentiometer_last0)
    {
      BGC_r = BGC_r - 10;
      if (BGC_r <= 0)
      {
        buzzer = LOW;
        // Buzzer();
        BGC_r = 0;
      }
      potentiometer_last0 = magentaobj.potentiometer_0;
    }

    if(magentaobj.potentiometer_1 != potentiometer_last1 && magentaobj.potentiometer_1 >= potentiometer_last1)
    {
      BGC_g = BGC_g + 10;
      if (BGC_g >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        BGC_g = 250;
      }
      potentiometer_last1 = magentaobj.potentiometer_1;
    }
    if(magentaobj.potentiometer_1 != potentiometer_last1 && magentaobj.potentiometer_1 <= potentiometer_last1)
    {
      BGC_g = BGC_g - 10;
      if (BGC_g <= 0)
      {
        buzzer = LOW;
        // Buzzer();
        BGC_g = 0;
      }
      potentiometer_last1 = magentaobj.potentiometer_1;
    }

    if(magentaobj.potentiometer_2 != potentiometer_last2 && magentaobj.potentiometer_2 >= potentiometer_last2)
    {
      BGC_b = BGC_b + 10;
      if (BGC_b >= 250)
      {
        buzzer = HIGH;
        // Buzzer();
        BGC_b = 250;
      }
      potentiometer_last2 = magentaobj.potentiometer_2;
    }

    if(magentaobj.potentiometer_2 != potentiometer_last2 && magentaobj.potentiometer_2 <= potentiometer_last2)
    {
      BGC_b = BGC_b - 10;
      if (BGC_b <= 0)
      {
        buzzer = LOW;
        // Buzzer();
        BGC_b = 0;
      }
      potentiometer_last2 = magentaobj.potentiometer_2;
    }

  break;
  }
	
}

void Accelerometer()
{
  move = ((magentaobj.accelerometer_x + 1) * 4);
	
	if((magentaobj.accelerometer_y >= 0.8) && (magentaobj.accelerometer_y <= 0.95))
	{
		magentaobj.write((0x80 >> move), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	}
	if((magentaobj.accelerometer_y >= 0.5) && (magentaobj.accelerometer_y <= 0.7))
	{
		magentaobj.write(0x00, (0x80 >> move), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	}
	if((magentaobj.accelerometer_y >= 0.2) && (magentaobj.accelerometer_y <= 0.4))
	{
		magentaobj.write(0x00, 0x00, (0x80 >> move), 0x00, 0x00, 0x00, 0x00, 0x00);
	}
	if((magentaobj.accelerometer_y >= 0) && (magentaobj.accelerometer_y <= 0.2))
	{
		magentaobj.write(0x00, 0x00, 0x00, (0x80 >> move), 0x00, 0x00, 0x00, 0x00);
	}
       
	if((magentaobj.accelerometer_y >= -0.2) && (magentaobj.accelerometer_y <= -0))
	{
		magentaobj.write(0x00, 0x00, 0x00, 0x00, (0x80 >> move), 0x00, 0x00, 0x00);
	}
	if((magentaobj.accelerometer_y >=  -0.4) && (magentaobj.accelerometer_y <= -0.2))
	{
		magentaobj.write(0x00, 0x0, 0x00, 0x00, 0x00, (0x80 >> move), 0x00, 0x00);
	}
	if((magentaobj.accelerometer_y >= -0.7) && (magentaobj.accelerometer_y <= -0.5))
	{
		magentaobj.write(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (0x80 >> move), 0x00);
	}
	if((magentaobj.accelerometer_y >= -0.95) && (magentaobj.accelerometer_y <= -0.8))
	{
		magentaobj.write(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (0x80 >> move));
	} 
}

void Servo()
{
  switch (servo)
  {
    case SERVO1:
      magentaobj.setServo1(grad1);
      break;
    
    case SERVO2:
      magentaobj.setServo2(grad2);
      break;
  }
}

void ReadButton()
{
  if(magentaobj.button_1 != button_last1 && magentaobj.button_1 == 1)
  {
    // acc = ACC;
    segment = NORA;
    servo = SERVO1;

    grad1 = random(1, 180);

    Servo();
  }

  if(magentaobj.button_2 != button_last2 && magentaobj.button_2 == 1)
  {
    change = COLOR;
    servo = SERVO1;

    grad1 = random(1, 180);

    Servo();
  }

  if(magentaobj.button_3 != button_last3 && magentaobj.button_3 == 1)
  {
    change = BGCOLOR;
    servo = SERVO1;

    grad1 = random(1, 180);

    Servo();
  }

  if(magentaobj.button_Center != button_lastCenter && magentaobj.button_Center == 1)
  {
    acc = 0;
    servo = SERVO2;

    grad2 = random(1, 180);

    Servo();

    r     = 100;
    g     = 100;
    b     = 100;
    BGC_r = 30;
    BGC_g = 30;
    BGC_b = 30;
    segment = REMO;
  }

  if(magentaobj.button_Up != button_lastUp && magentaobj.button_Up == 1)
  {
    acc = 0;
    servo = SERVO2;

    grad2 = random(1, 180);

    Servo();

    r     = 140;
    g     = 0;
    b     = 0;
    BGC_r = 50;
    BGC_g = 20;
    BGC_b = 0;
  }

  if(magentaobj.button_Right != button_lastRight && magentaobj.button_Right == 1)
  {
    acc = 0;
    servo = SERVO2;

    grad2 = random(1, 180);

    Servo();

    r     = 0;
    g     = 0;
    b     = 150;
    BGC_r = 0;
    BGC_g = 20;
    BGC_b = 30;
  }

  if(magentaobj.button_Down != button_lastDown && magentaobj.button_Down == 1)
  {
    acc = 0;
    servo = SERVO2;

    grad2 = random(1, 180);

    Servo();

    r     = 0;
    g     = 100;
    b     = 0;
    BGC_r = 0;
    BGC_g = 50;
    BGC_b = 20;
  }

  if(magentaobj.button_Left != button_lastLeft && magentaobj.button_Left == 1)
  {
    acc = 0;
    servo = SERVO2;

    grad2 = random(1, 180);

    Servo();

    r     = 70;
    g     = 0;
    b     = 140;
    BGC_r = 20;
    BGC_g = 0;
    BGC_b = 50;
  }  
  
  button_last1 = magentaobj.button_1;
  button_last2 = magentaobj.button_2;
  button_last3 = magentaobj.button_3;
  button_lastCenter = magentaobj.button_Center;
  button_lastUp = magentaobj.button_Up;
  button_lastRight = magentaobj.button_Right;
  button_lastDown = magentaobj.button_Down;
  button_lastLeft = magentaobj.button_Left;
}

void printStats()
{
  // printf("change: %i\n", change);
  // printf("Colors: %i-%i-%i-%i-%i-%i\n", r,g,b,BGC_r, BGC_g, BGC_b);
  // printf("color: %i\n", color);
  // printf("segment: %i\n", segment);
  // printf("Button1: %i\n", magentaobj.button_1);
  // printf("button1_last: %i\n", button_last1);
  // printf("Button2: %i\n", magentaobj.button_2);
  // printf("button2_last: %i\n", button_last2);
  // printf("Button3: %i\n", magentaobj.button_3);
  // printf("button3_last: %i\n", button_last3);
  // printf("Button_UP: %i\n", magentaobj.button_Up);
  // printf("button_UP_last: %i\n", button_lastUp);
  // printf("Button_RIGHT: %i\n", magentaobj.button_Right);
  // printf("button_RIGHT_last: %i\n", button_lastRight);
  // printf("Button_DOWN: %i\n", magentaobj.button_Down);
  // printf("button_DOWN_last: %i\n", button_lastDown);
  // printf("Button_LEFT: %i\n", magentaobj.button_Left);
  // printf("button_LEFT_last: %i\n", button_lastLeft);
  // printf("Button_CENTER: %i\n", magentaobj.button_Center);
  // printf("button_CENTER_last: %i\n", button_lastCenter);
  // printf("Acc: %i\n", acc);
  // printf ("Grad 1: %i\n", grad1);
  // printf ("Grad 2: %i\n", grad2);
  // printf("Buzzer: %i", buzzer);
  // printf("=== Neue Daten gesendet ===\n");
  // printf("Farbe: R=%d G=%d B=%d\n", sendData.r, sendData.g, sendData.b);
  // printf("BG:    R=%d G=%d B=%d\n", sendData.BGC_r, sendData.BGC_g, sendData.BGC_b);
  // printf("Servo: grad1=%d grad2=%d\n", sendData.grad1, sendData.grad2);
  // printf("Buttons: B1=%d B2=%d B3=%d\n", sendData.button1, sendData.button2, sendData.button3);
  // printf("Joystick: U=%d R=%d D=%d L=%d C=%d\n", sendData.buttonU, sendData.buttonR, sendData.buttonD, sendData.buttonL, sendData.buttonC);
  // printf("Sample: %d\n",sendData.sam);
  // printf("============================\n");
}

void loop() 
{
  delay(100);
  magentaobj.read_io();

  printStats();

  ReadButton();

  switch (segment)
  {
    case NORA:
      magentaobj.setSegmentAnzeige('N', 'O', 'R', 'A');
       SA1 = 'N';
       SA2 = 'O';
       SA3 = 'R';
       SA4 = 'A';
      break;
  
    case REMO:
      magentaobj.setSegmentAnzeige('R', 'E', 'M', 'O');   
       SA1 = 'R';
       SA2 = 'E';
       SA3 = 'M';
       SA4 = 'O';
      break;
  }

  switch (acc)
  {
    case ACC:
      Accelerometer();
      break;
    
    default:
        Counter ++;
      if(Counter <= 1)
      {
        magentaobj.sample(1);
        SAM = 1;
      }
      
      if(Counter > 1)
      {
        magentaobj.sample(0);
        SAM = 0;
        if(Counter >= 2)
        {
          Counter = 0;
        }
      }
      break;
  }

  ChangeColor();
 
  magentaobj.setColor(r, g, b, BGC_r, BGC_g, BGC_b);

  sendData.r = r;
  sendData.g = g;
  sendData.b = b;
  sendData.BGC_r = BGC_r;
  sendData.BGC_g = BGC_g;
  sendData.BGC_b = BGC_b;
  sendData.grad1 = grad1;
  sendData.grad2 = grad2;
  sendData.button1 = magentaobj.button_1;
  sendData.button2 = magentaobj.button_2;
  sendData.button3 = magentaobj.button_3;
  sendData.buttonU = magentaobj.button_Up;
  sendData.buttonC = magentaobj.button_Center;
  sendData.buttonR = magentaobj.button_Right;
  sendData.buttonL = magentaobj.button_Left;
  sendData.buttonD = magentaobj.button_Down;
  sendData.sa1 = SA1;
  sendData.sa2 = SA2;
  sendData.sa3 = SA3;
  sendData.sa4 = SA4;
  sendData.sam = SAM;

  esp_err_t result = esp_now_send(peerAddress2, (uint8_t *) &sendData, sizeof(sendData));
  if (result == ESP_OK) {
    printf("Daten gesendet\n");
  } else {
    printf("Fehler beim Senden\n");
  }
}
