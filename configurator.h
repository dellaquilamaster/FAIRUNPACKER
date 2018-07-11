#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mask.h"

class configurator
{
public:
  configurator(char *);
  ~configurator();
  
  unsigned int get_number_modules  ();
  unsigned int get_number_channels (int);
  mask*        get_mask            (int);
  
private:
  mask        **pp_mask_vector;
  unsigned int  modules_number;
  unsigned int *p_channel_number;
  
} ;

#endif