/*************************************************************************************
 * 
 * FAIRDef.h
 * 
 ************************************************************************************* 
 * 
 * 
 * Definizioni di alcune maschere utili
 * 
 * 
 * 
 * 
 * ***********************************************************************************/

#define ECMask  0x3C000000
#define VDWMask 0x03FF0000
#define VSNMask 0x0000FFFF
#define FTNMask 0x80000000
#define ECOff   26
#define VDWOff  16
#define FTNOff  31

#define pMask(a) (pLayout->get_mask(a))