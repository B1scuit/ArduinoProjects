#include <Wire.h>
#include <Servo.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Servo s9g;
Servo s9g2;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int sumx, sumy;
int hx, hy;

void servo_setup(){
  lis.begin(0x18);
  lis.setRange(LIS3DH_RANGE_4_G);

  s9g.attach(12);
  s9g2.attach(11);

  s9g.write(90);
  s9g2.write(90);
  delay(1000);
}

void loop(){
  sumx = map(lis.x, -10768, 10768, 0, 180);
  sumy = map(lis.y, -10768, 10768, 0, 180);

  Serial.println(String(sumx) + ":" + String(sumy));

  if (sumx < hx -3 || sumx > hx + 3 ){
    s9g.write(180 - sumx); 
  }
  if (sumy < hy - 3 ||  sumy > hy + 3){
    s9g2.write(180 - sumy);
  }

  hx = sumx;
  hy = sumy;
  sumx = sumy = 0;
}
