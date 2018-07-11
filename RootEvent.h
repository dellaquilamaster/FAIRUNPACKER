#ifndef ROOTEVENT_H
#define ROOTEVENT_H

#include <TTree.h>
#include <TFile.h>

#include <stdlib.h>
#include <string.h>

#include "EventBuffer.h"
#include "configurator.h"
#include "mask.h"


class RootEvent
{
public:
  RootEvent();
  ~RootEvent();
  
  void DefineTree(configurator *, const char * file_name);
  void ClearTTreeBuffer();
  int  ReadEvent(unsigned int, configurator*);
  int  WriteTree();
  
private:
  TTree         *pTreeOut;
  TFile         *pfout;
  unsigned int **ppData;
  unsigned int   ModsNumber;
  unsigned int  *pChannelsNumber;
  
} ;


#endif