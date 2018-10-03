// cpat.h

#ifndef _CPAT_h
#define _CPAT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define Use_Relay								// Comment to not use config relay web page (+1.5K) add cpat
												// use 
#define USE_SENDOFF								// comment to not use http get send message on event off relay NB use Ota_Url so can't be use with OTA

#ifndef OTA_URL
	#ifdef USE_SENDOFF
		#define OTA_URL  "http://domus1:80/api/arduino/" PROJECT ".ino.bin"  // [OtaUrl] re-use yo send off message instaead of ota message
	#endif
#endif

#endif

