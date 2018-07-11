/*************************************************************************************
 * 
 * FAIRGLob.h
 * 
 ************************************************************************************* 
 * 
 * 
 * Variabili globali 
 * 
 * 
 * 
 * 
 * ***********************************************************************************/

#ifndef FAIRGLOB_H
#define FAIRGLOB_H

#include "EventBuffer.h"
#include "configurator.h"
#include <vector>
#include <stdlib.h>

std::vector<unsigned int>  *pBufferVector = new std::vector<unsigned int>;
EventBuffer                *pEventManager = new EventBuffer();
unsigned int                BufferLength;
unsigned int                NumEvents; /*numero totale di eventi*/
std::vector<unsigned int>  *pStartEvent = new std::vector<unsigned int>;; /*vettore contenente la word di inizio evento per ogni evento*/
configurator               *pLayout;


#endif