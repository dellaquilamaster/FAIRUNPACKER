#include <vector>

#include "EventBuffer.h"
#include "configurator.h"
#include "RootEvent.h"

#include "FAIRDef.h"

extern std::vector<unsigned int>   *pBufferVector;
extern EventBuffer                 *pEventManager;
extern unsigned int                 NumEvents;
extern std::vector<unsigned int>   *pStartEvent;
extern unsigned int                 BufferLength;
extern configurator                *pLayout;

RootEvent::RootEvent()
{}

RootEvent::~RootEvent()
{}

void RootEvent::DefineTree(configurator * pConfig, const char * file_name)
{
  char BranchName[100];
  char LeafList[100];
  ModsNumber = pConfig->get_number_modules();
  pChannelsNumber = new unsigned int [ModsNumber];
  ppData=new unsigned int *[ModsNumber];
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    ppData[i]=new unsigned int[pChannelsNumber[i]=pConfig->get_number_channels(i)]();
  }
  /*opening output file*/
  pfout = new TFile(file_name,"RECREATE");
  pfout->SetCompressionLevel(1);
  /*creation of branches*/
  pTreeOut=new TTree("h1","FAIRUNPACKER Tree");
  pTreeOut->SetAutoSave(50000000);
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    for(unsigned int j=0; j<pChannelsNumber[i]; j++)
    {
      sprintf(BranchName,"m%02d_%02d",i+1,j);
      sprintf(LeafList,"%s/i",BranchName);
      pTreeOut->Branch(BranchName, &ppData[i][j], LeafList);
    }
  }
}

void RootEvent::ClearTTreeBuffer()
{
  for(unsigned int i=0; i<ModsNumber; i++)
  {
    for(unsigned int j=0; j<pChannelsNumber[i]; j++)
    {
      ppData[i][j]=0;
    }
  }
  return;
}

int RootEvent::ReadEvent(unsigned int EventNumber, configurator * pConfig)
{
  int ExitCode;
  unsigned int NumMod;
  unsigned int NumWords;
  unsigned int StartingEvent=(*pStartEvent)[EventNumber];
  unsigned int EndingEvent=(*pStartEvent)[EventNumber+1]-1;
  
  /* controllo evento */
  ExitCode=pEventManager->TestEventConsistency(EventNumber);
  switch (ExitCode)
  {
    case 1:
    case 2:
    case 3:
      return ExitCode;
      break;
    case 4:
      return ExitCode; /*File corrotto --> devo rigettare il resto del file con codice 4*/
      break;
  }
  
  /* riempimento del tree */
  for(unsigned int j, iglob=StartingEvent; iglob<EndingEvent ; iglob++) /*questo ciclo è su tutte le footer word dell'evento*/
  {
    /*j è un indice che uso soltanto per ciclare fino alla footer word*/
    j=iglob;
    for(NumWords=0; ((*pBufferVector)[j]&FTNMask)==0 ;NumWords++, j++)
    {}
    NumMod=((*pBufferVector)[j]&VSNMask) - 1; /*estraggo il numero di modulo dalla footerword (-1 per partire da 0)*/
    /*ciclo su tutto il modulo per NumWords volte a partire da iglob*/
    for(unsigned int i_module=0; i_module<NumWords; i_module++)
    {
      ppData[NumMod][pMask(NumMod)->DWN((*pBufferVector)[iglob])]=pMask(NumMod)->Data((*pBufferVector)[iglob]);
      iglob++;
    }
    /*qui iglob identifica una footerword*/
  }
  
  /*scrittura dati su tree*/
  pTreeOut->Fill();
  /*azzeramento della matrice di dati*/
  ClearTTreeBuffer();

  return ExitCode;
}

int RootEvent::WriteTree()
{
  pfout->WriteTObject(pTreeOut,"h1");
  
  pfout->Close();
  return 0;
}