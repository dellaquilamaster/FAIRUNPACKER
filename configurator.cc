#include "configurator.h"

configurator::configurator (char * file_config_name)
{
  FILE * file_config;
  file_config=fopen(file_config_name,"r");
  char temp_string[100];
  
  /* leggo prima stringa da buttare */
  fscanf(file_config,"%s",temp_string);
  /* leggo il numero di moduli */
  fscanf(file_config,"%s",temp_string);
  modules_number=atoi(temp_string);
  
  p_channel_number= new unsigned int[modules_number];
  pp_mask_vector  = new mask*[modules_number];
  /* ciclo su tutti i moduli per riempire maschere e numeri canali */
  for(unsigned int i=0; i<modules_number; i++)
  {
    /* leggo prima stringa da buttare */
    fscanf(file_config,"%s",temp_string); 
    /* leggo il tipo di modulo e inizializzo la mascera corrispondente */
    fscanf(file_config,"%s",temp_string);
    pp_mask_vector[i]=new mask(temp_string);
    /* leggo il numero di canali e li scrivo nel vettore p_channel_number */
    fscanf(file_config,"%s",temp_string);
    p_channel_number[i]=atoi(temp_string);    
  }
  
  fclose(file_config);
}

configurator::~configurator()
{
  for(unsigned int i=0; i<modules_number; i++)
  {
    delete [] pp_mask_vector[i];
  } 
  delete [] pp_mask_vector;
}

unsigned int configurator::get_number_modules ()
{
  return modules_number; 
}

unsigned int configurator::get_number_channels(int mod_number)
{
  return p_channel_number[mod_number]; 
}

mask* configurator::get_mask(int mod_number)
{
  return pp_mask_vector[mod_number]; 
}