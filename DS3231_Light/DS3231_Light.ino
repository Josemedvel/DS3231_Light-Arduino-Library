#include <Wire.h>

int address = 0x68;


int BCDToBinary(uint8_t number){
  uint8_t firstH = ((number & 0b11110000) >> 4) * 10;
  uint8_t lastH = (number & 0b00001111);
  return firstH + lastH;
}
int extractHours(uint8_t number){
  if((number & 0b0100000) == 0){//check 12 hours mode
    //Serial.println("We are in 12 hours mode");
    return BCDToBinary(number & 0b00011111);
  }
  else{//We are in 24 hours mode 
    //Serial.println("We are in 24 hours mode");
    return BCDToBinary(number & 0b00111111);
  }
}



void setup() {
 Serial.begin(9600);

 
 //Serial.print(Wire.endTransmission());//si devuelve 0 es éxito

}

void loop() {
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0x0);
  Wire.requestFrom(address,3);
  uint8_t seconds =  BCDToBinary(Wire.read());
  uint8_t minutes = BCDToBinary(Wire.read());
  uint8_t hours = extractHours(Wire.read());
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  Wire.endTransmission();
  delay(1000);

}
