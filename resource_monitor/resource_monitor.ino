#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
Adafruit_SSD1306 display(4);
SoftwareSerial debug(11, 12);
int hour, minute, cpu_p, mem_p;

char INFO[4][21];
byte packet[10] = {0,};

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("resource monitor v1.0");
  display.setCursor(0, 8);
  display.println("");
  display.setCursor(0, 16);
  display.println("mechasolution");
  display.setCursor(0, 24);
  display.println("thanks for using");
  display.display();
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  debug.begin(9600);
  delay(1000);
  Serial.print('a');
}

void loop() {
  if (Serial.available() > 9) {//입력데이터가 10개가 되면 읽어들입니다.
    for (int i = 0; i < 10; i++) {
      packet[i] = Serial.read();//10byte의 데이터를 읽어들입니다.
    }
    if (   packet[0] != 'h'
           && packet[2] != 'm'
           && packet[4] != 'C'
           && packet[6] != 'M'
           && packet[8] != 'D') {//포멧이 올바르게 왔는지 확인
      //data format error
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      //포멧이 올바르지 않으면, 에러 출력
      while (Serial.available() > 0 && Serial.read());
      //시리얼 버퍼 초기화
      return;//루프문 종료
    }
    //데이터가 올바르게 오면 한번 깜빡임
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    //화면 출력 데이터 수정
    sprintf(INFO[0], "                %02d:%02d", (int)packet[1], (int)packet[3]);
    sprintf(INFO[1], "CPU  : %3d%%", (int)packet[5]);
    sprintf(INFO[2], "RAM  : %3d%%", (int)packet[7]);
    sprintf(INFO[3], "DISK : %3d%%", (int)packet[9]);
    display.clearDisplay();//디스플레이 초기화
    display.setCursor(0, 0);
    display.println(INFO[0]);
    display.setCursor(0, 8);
    display.println(INFO[1]);
    display.setCursor(0, 16);
    display.println(INFO[2]);
    display.setCursor(0, 24);
    display.println(INFO[3]);
    //화면 출력 데이터들을 실제로 출력합니다.
    display.display();
  }
}

