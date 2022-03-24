#include <Wire.h>

int direccion = 0x68;


int BCDToBinary(uint8_t numero){
  uint8_t firstH = ((numero & 0b11110000) >> 4) * 10;
  uint8_t lastH = (numero & 0b00001111);
  return firstH + lastH;
}
int extractHours(uint8_t numero){
  if((numero & 0b0100000) == 0){//comprobar modo 12 horas
    //Serial.println("Estamos en 12 horas");
    return BCDToBinary(numero & 0b00011111);
  }
  else{//estamos en modo 24 horas 
    //Serial.println("Estamos en 24 horas");
    return BCDToBinary(numero & 0b00111111);
  }
}



void setup() {
 Serial.begin(9600);

 
 //Serial.print(Wire.endTransmission());//si devuelve 0 es éxito

}

void loop() {
  Wire.begin();
  Wire.beginTransmission(direccion);
  Wire.write(0x0);
  Wire.requestFrom(direccion,3);
  uint8_t segundos =  BCDToBinary(Wire.read());
  uint8_t minutos = BCDToBinary(Wire.read());
  uint8_t horas = extractHours(Wire.read());
  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
  Wire.endTransmission();
  delay(1000);

}
