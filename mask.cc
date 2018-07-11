#include "mask.h"

/* constructor */
mask::mask(char * module_type) :
footer_(0x80000000),
footer_offset(31)
{
  /* ADC case*/
  if(strcmp(module_type,"ADC")==0)
  {
    DWN_= 0x01F00000;
    VDW_= 0x003F0000;
    Data_=0x00000FFF;
    DWN_offset = 5*4;
    VDW_offset = 4*4;
    Data_offset= 0;
  }
  /* TDC case*/
  if(strcmp(module_type,"TDC")==0)
  {
    DWN_= 0x01F00000;
    VDW_= 0x003F0000;
    Data_=0x00000FFF;
    DWN_offset = 5*4;
    VDW_offset = 4*4;
    Data_offset= 0;
  }
  /* SEGC case*/
  if(strcmp(module_type,"SEGC")==0)
  {
    DWN_= 0x00100000;
    VDW_= 0x00010000;
    Data_=0x0000003F;
    DWN_offset = 5*4;
    VDW_offset = 4*4;
    Data_offset= 0;
  }
  /* SCL case*/
  if(strcmp(module_type,"SCL")==0)
  {
    DWN_= 0x01E00000;
    VDW_= 0x001F0000;
    Data_=0x001FFFFF;
    DWN_offset = 5*4+1;
    VDW_offset = 4*4;
    Data_offset= 0;    
  }
}

/* destructor */
mask::~mask()
{}

/* data word number */
unsigned int mask::DWN(unsigned long LONG_WORD)
{
  return (LONG_WORD & DWN_)>>DWN_offset;
}

/* valid data words */
unsigned int mask::VDW(unsigned long LONG_WORD)
{
  return (LONG_WORD & VDW_)>>VDW_offset;
}

/* data */
unsigned int mask::Data(unsigned long LONG_WORD)
{
  return (LONG_WORD & Data_)>>Data_offset;
}

/* footer */
bool mask::footer(unsigned long LONG_WORD)
{
  return (LONG_WORD & footer_)>>footer_offset;
}
