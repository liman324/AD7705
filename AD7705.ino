// liman324@yandex.ru
// Alexander Liman
// rcl-radio.ru

#include <SPI.h>
#include <AD7705.h>
AD7705 ad(8,7);// DRDY,RESET
// SS    10 // CS
// MOSI  11 // DIN
// MISO  12 // DOUT
// SCK   13 // SCLK

long data;

void setup() {
  Serial.begin(9600);
  ad.conf();
  delay(500);
}

void loop() {
  // CH1 = 1/CH2 = 2
  // GAIN = 1,2,4,8,16,32,64,128
  // RATE = 20,25,100,200 Hz
  // UNIPOLAR = 0/BIPOLAR = 1 

  ad.setSetup(1,1,25,0);
  data = ad.read_unipolar();
  Serial.print("CH1 ");Serial.print(data);

  ad.setSetup(2,1,25,0);
  data = ad.read_unipolar();
  Serial.print("  CH2 ");Serial.println(data);

  delay(1000);
}

/****CH1,GAIN1,25Hz,bipolar*****
 ad.setSetup(1,1,25,1);
 data = ad.read_bipolar();
 // long data = -32768...32767 = -2.5...+2.5 V
 */

/****CH1,GAIN1,25Hz,unipolar*****
 ad.setSetup(1,1,25,0);
 data = ad.read_unipolar();
 // long data = 0...65535  = 0...+5 V
 */
