// receptorRc.h

#ifndef _RECEPTORRC_h
#define _RECEPTORRC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
void inicioReceptorYMotores();
void recibirDatos();
#endif
