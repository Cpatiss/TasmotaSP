# TasmotaSP
Special version of tasmota (Copyright (C) 2017  Theo Arends) with some adds

based on  sonoff.ino - Sonoff-Tasmota firmware for iTead Sonoff, Wemos and NodeMCU hardware

  Copyright (C) 2017  Theo Arends version 5.9.2
  
  It's add (all adds tagged 'cpat') :
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
  
  the objective is to use electrodragon to drive shutter roller with timer up and down , stop on double press , stop on max current.
  You can also use dual sonoff but it's not easy to provide analog input pin.
  max current is detected by use a simple 
  
  
