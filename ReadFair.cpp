/************************************************************************************************************
 * 
 * FFFFFFF   AAAAA   III  RRRRRRR  UU   UU  NN     NN  PPPPPPP   AAAAA   CCCCCC  KK    KK  EEEEEEE  RRRRRRR
 * FF       AA   AA  III  RR   RR  UU   UU  NNNN   NN  PP   PP  AA   AA  CC      KK   KK   EE       RR   RR
 * FF       AA   AA  III  RRRRRRR  UU   UU  NN NN  NN  PP   PP  AA   AA  CC      KK KK     EE       RRRRRRR
 * FFFFFFF  AAAAAAA  III  RRRR     UU   UU  NN  NN NN  PPPPPP   AAAAAAA  CC      KKKK      EEEEEEE  RRRR   
 * FF       AA   AA  III  RR RR    UU   UU  NN   NNNN  PP       AA   AA  CC      KK  KK    EE       RR RR  
 * FF       AA   AA  III  RR  RR   UU   UU  NN    NNN  PP       AA   AA  CC      KK   KK   EE       RR  RR 
 * FF       AA   AA  III  RR   RR  UUUUUUU  NN     NN  PP       AA   AA  CCCCCC  KK    KK  EEEEEEE  RR   RR
 *
 * v. 1.0
 * 17/01/2016
 * 
 * CREATOR: DANIELE DELL'AQUILA
 *          dellaquila@na.infn.it
 * 
 * Convert FAIR data into a ROOT file.
 * 
 * USAGE: ./ReadFair path_run_1 path_run_2 ...
 * each run folder should be indicated without the final "/"
 * 
 ************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <TTree.h>
#include <TFile.h>
#include <string.h>

#include "mask.h"
#include "configurator.h"
#include "RootEvent.h"
#include "EventBuffer.h"
#include "Monitor.h"
#include "FairLogo.h"

#include "FAIRGlob.h"

int main (int argc, char** argv)
{
  FairLogo();
  
  /*variabili utili***********************************************************************************/
  char file_config_name[]="configuration.conf";
  char file_output_name[]="output.root";
  char file_data_name[100];
  char run_name[100];
  int  numero_runs=argc-1;
  int  file_code[1000]; /*array che contiene i codici dei files aperti per la lettura binaria*/
  /***************************************************************************************************/
  
  /*get configuration*/
  pLayout = new configurator(file_config_name);
  
  /*costruzione della struttura del tree*/
  RootEvent * RootTools = new RootEvent();
  RootTools->DefineTree(pLayout, file_output_name);
  
  /*Costruzione del monitor eventi*/
  Monitor EvtMonitor;
  
  /*ciclo esterno su tutte le cartelle di run*********************************************************/
  for(int curr_run=0; curr_run<numero_runs; curr_run++)
  {
    strncpy(run_name,strrchr(argv[curr_run+1],'/')+1,13);
    /*ciclo principale di lettura su tutti i files del run*/
    printf("Starting run %s\n",run_name);
    /*Inizializzazione del monitor*/
    EvtMonitor.Init();
    for(int curr_file=0; ; curr_file++)
    {
      /*apertura file*/
      sprintf(file_data_name,"%s/%s_%06d.dat",argv[curr_run+1],run_name,curr_file+1);
            
      if ((file_code[curr_file]=open(file_data_name,O_RDONLY))==-1) break;
      printf("Unpacking file %s\n",file_data_name);      
      
      /*Inizializzazione del buffer di eventi*/
      pEventManager->InitBuffer(file_code[curr_file]);
      /*Riempimento del buffer*/
      pEventManager->FillBuffer();
      
      /*loop su tutti gli eventi*/
      for(unsigned int EvtCounter = 0; EvtCounter<NumEvents; EvtCounter++)
      {
        if(EvtMonitor.EndOfEvent(RootTools->ReadEvent(EvtCounter, pLayout))==4)
          break;
      }
    }
    printf("Run %s completed.\n", run_name);
    EvtMonitor.EndOfRun();
  }
  /*fine del ciclo principale*************************************************************************/
  
  /*scrittura del tree su file*/
  RootTools->WriteTree();
  
  return 0; 
}


