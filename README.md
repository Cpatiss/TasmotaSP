# TasmotaSP
Special version of tasmota (Copyright (C) 2017  Theo Arends) with some adds

based on  sonoff.ino - Sonoff-Tasmota firmware for iTead Sonoff, Wemos and NodeMCU hardware

  Copyright (C) 2017  Theo Arends version 5.9.2 (thanks to him)
  
  It's add (all adds are tagged 'cpat') :
  new embedded functionalities:
  - timer or clock for each relay (acces vi web server configuration)
  - libraries and code to drive LCD oled display type ssd1306 with sonoff or electrodragon esp (define USE_SSD1306)
  - re-use of old settings to add new one.
  - add ftp server,  and acces to embedded web pages through web server (define USE_ElectroDragon)
  - add some USE definition for reduce size (i.e. USE_ExtraSonOff )
  - set acces to interlockrelay via WEB server configuration and define USE_InterlockDelay
  - set a sequence of relays via defin USE_PowerEvenOdd
  - set a max value on analog port to shut down relays (set via web server and new use of some commands) (define USE_ADC_MAX)	
  - french language 
  - add sonoff dual R2 board
  - a jason web message can be send to a web site (using old web ota url witch is not avaible in this case) when relay off (define        USE_SENDOFF)
  
  the objective is to use electrodragon to drive shutter roller with timer up and down , stop on double press , stop on max current.
  You can also use dual sonoff but it's not easy to provide analog input pin.
  max current is detected by use a simple HWCT 5A/5ma with resitor and dual diode to limit voltage at 1V (see picture included).
  Up and down can be set by command (domitics, ... or web interface as well as 2 push button gpi01, gpi03 using tasmota extra pin function)
 
 An optional LCD screen provide connection information on start, up/down activity or time otherwise (only on electrodragon cause free memory)
  
  this change must be transposed on lastest version of tasmota as soon as possible.
  
sonoff is avaible on sonoff branch
