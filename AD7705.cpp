#include <Arduino.h>
#include <SPI.h>
#include "AD7705.h"

AD7705::AD7705(uint8_t drdy, uint8_t reset){
             DRDY = drdy;
             RESET = reset;
}

void AD7705::conf(){
              pinMode(DRDY, INPUT);
              pinMode(RESET, OUTPUT);
              digitalWrite(RESET,LOW);
              SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE3));
              SPI.begin();
              digitalWrite(RESET,HIGH);
              delay(300);
}

void AD7705::setSetup(int ch, int gain,int rate, int polarity){
          switch(ch){
            case 1: ch = 0x00;break;
            case 2: ch = 0x01;break;
}
          switch(gain){
            case 1:   gain = 0b00000000;break;
            case 2:   gain = 0b00001000;break; 
            case 4:   gain = 0b00010000;break; 
            case 8:   gain = 0b00011000;break;
            case 16:  gain = 0b00100000;break;
            case 32:  gain = 0b00101000;break;
            case 64:  gain = 0b00110000;break;
            case 128: gain = 0b00111000;break;
}
          switch(rate){
           case 20:  rate = 0b00000000;break;
           case 25:  rate = 0b00000001;break;
           case 100: rate = 0b00000010;break;
           case 200: rate = 0b00000011;break;
}

          switch(polarity){
           case 0: polarity = 0b00000100;break;
           case 1: polarity = 0b00000000;break;
}

          digitalWrite(RESET,HIGH);

          digitalWrite(SS, LOW);
          delayMicroseconds(1);
          SPI.transfer(0x10 + ch);
          SPI.transfer(0b01000000 + gain + polarity);
          digitalWrite(SS, HIGH);
          delay(10);

          digitalWrite(SS, LOW);
          delayMicroseconds(1);
          SPI.transfer(0x20 + ch);
          SPI.transfer(0b00001000 + rate);
          digitalWrite(SS, HIGH);
          delay(10);
}

int32_t AD7705::read_unipolar(){
         while(digitalRead(DRDY)!=LOW); 
         digitalWrite(SS, LOW);
         delayMicroseconds(1);
         SPI.transfer(0x38);    
         long code = SPI.transfer16(0); 
         digitalWrite(SS, HIGH);
         while(digitalRead(DRDY)!=HIGH);
         delay(10);
         digitalWrite(RESET,LOW);
         return (int32_t)code;
}
   
int32_t AD7705::read_bipolar(){
         while(digitalRead(DRDY)!=LOW); 
         digitalWrite(SS, LOW);
         delayMicroseconds(1);
         SPI.transfer(0x38);    
         long code = SPI.transfer16(0) - 32768; 
         digitalWrite(SS, HIGH);
         while(digitalRead(DRDY)!=HIGH);
         delay(10);
         digitalWrite(RESET,LOW);
         return (int32_t)code;
}
     
