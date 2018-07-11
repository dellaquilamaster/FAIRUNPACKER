#ifndef MONITOR_H
#define MONITOR_H

class Monitor
{
public:
  Monitor();
  ~Monitor();
  
  void         Init();
  unsigned int EndOfEvent(int ExitCode);
  void         EndOfRun();
  
private:
  unsigned int NRead;
  unsigned int NParityFail;
  unsigned int NDecorrelation;  
} ;

#endif