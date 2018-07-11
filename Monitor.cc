#include <stdio.h>

#include "Monitor.h"

Monitor::Monitor() :
NRead(0),
NParityFail(0),
NDecorrelation(0)
{}

Monitor::~Monitor()
{}

void Monitor::Init()
{
  NRead=0;
  NParityFail=0;
  NDecorrelation=0;
  
  return;
}

unsigned int Monitor::EndOfEvent(int ExitCode)
{
  NRead++;
  switch(ExitCode)
  {
    case 1:
      NParityFail++;
      printf("  Found damaged data\n");
      break;
    case 2:
    case 3:
      NDecorrelation++;
      printf("  Found decorrelation\n");
      break;
    case 4:
      printf("  Found syncronization error --> rest of file rejected\n");
      break;
  }
  return ExitCode;
}

void Monitor::EndOfRun()
{
  printf("  Events Read        : %u\n", NRead);
  printf("  Damaged Data       : %u\n", NParityFail);
  printf("  Decorrelation Found: %u\n\n", NDecorrelation);
  
  return;
}