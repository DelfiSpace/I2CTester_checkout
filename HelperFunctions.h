#ifndef _HELPERFUNCTIONS_H__
#define _HELPERFUNCTIONS_H__

#include "Energia.h"
#include <DWire.h>
#include <DSerial.h>

extern DWire wire;
extern DSerial serial;

unsigned char scanBus();

#endif
