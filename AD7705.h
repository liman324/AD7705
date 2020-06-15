#ifndef AD7705_H
#define AD7705_H

#include <Arduino.h>

class AD7705
{
  public:
    AD7705(uint8_t, uint8_t);
        void conf();
        void setSetup(int ch, int gain,int rate, int polarity); 
        int32_t read_unipolar();
        int32_t read_bipolar();
	
  private: 
        uint8_t DRDY;
        uint8_t RESET;
};
	
#endif //AD7705_H
