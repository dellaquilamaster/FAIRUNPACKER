#ifndef MASK_H
#define MASK_H

#include <string.h>

/*
 * Possible module_type:
 * 
 * ADC  --> ADC 9418V
 * TDC  --> TDC 9418T
 * SEGC --> Segment Controller
 * SCL  --> Scaler
 * 
 */

class mask
{
public:
  mask(char *);
  ~mask();
  
  unsigned int DWN   (unsigned long);
  unsigned int VDW   (unsigned long);
  unsigned int Data  (unsigned long);
  bool         footer(unsigned long);
  
private:
  unsigned int DWN_;
  unsigned int VDW_;
  unsigned int Data_;
  unsigned int footer_;
  unsigned int DWN_offset;
  unsigned int VDW_offset;
  unsigned int Data_offset;
  unsigned int footer_offset;
} ;

#endif 