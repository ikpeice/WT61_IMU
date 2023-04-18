#include <Arduino.h>
#include <math.h>

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

  Serial.println("Ready");

}
char data[100];
String c;
int x=0;
bool flag = false;

void HexTodec(uint8_t Lbyte, uint8_t Hbyte){
  uint8_t w,x,y,z;
  w = (Lbyte & 0xf0)>>4; // r = 1
  x = Lbyte & 0x0f; // r = 0
  y = (Hbyte & 0xf0)>>4; // r = 3
  z = Hbyte & 0x0f; // r = 2

  double ans =  y*pow(16,3)+z*pow(16,2)+w*pow(16,1)+x*pow(16,0);
  ans = (ans/32768)*16;

  Serial.print("Ax = ");
  Serial.print(String(ans)+"   ");
}

bool read(){
  if(Serial1.available()){
    while(Serial1.available()){
      data[x] = Serial1.read();
      x++;
    }
    return true;
  }
  return false;
}

void loop() {
  if(read()){
      for(int i=0;i<x;i++){
        if(data[i]==0x55)continue;
        if(data[i]==0x51){
          for(int j=0;j<4;j++){
            HexTodec(data[(i+j)*2], data[((i+j)*2)+1]);
          }
          Serial.println("");
          x=0;
          delay(500);
          return;
          
        }
        
      }
      x=0;
  }
}