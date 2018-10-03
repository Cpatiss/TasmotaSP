# TasmotaSP
Special version of tasmota (Copyright (C) 2017  Theo Arends) with some adds

based on  sonoff.ino - Sonoff-Tasmota firmware for iTead Sonoff, Wemos and NodeMCU hardware

  Copyright (C) 2017  Theo Arends version 5.9.2 (thanks to him)
  
  It's add (all adds are tagged 'cpat') :
  new embedded functionalities:
  - timer or clock for each relay (access vi web server configuration a submenu 'config.relay' was added)
  - libraries and code to drive LCD oled display type ssd1306 with sonoff or electrodragon esp (define USE_SSD1306)
  - re-use of old settings to add new one.
  - add ftp server (one client only see library comment),  and access to embedded web pages in SPIFFS through web server (define USE_ElectroDragon, cause need 4 Mbts memory, works also with sonoff pow)
  - add some USE definition for reduce size (i.e. USE_ExtraSonOff comment it to only use sonoff device)
  - set acces to interlockrelay via WEB server configuration and define USE_InterlockDelay
  - set a sequence of relays via defin USE_PowerEvenOdd
  - set a max value on analog port to shut down relays (set via web server and new use of some commands) (define USE_ADC_MAX)	
  - french language 
  - add sonoff dual R2 board
  - a jason web message can be send to a web site (using old web ota url witch is not avaible in this case) when relay off (define        USE_SENDOFF)
  
  the pupose of this,  is to use electrodragon to drive shutter roller with timer up and down , stop on double press , stop on max current.
  You can also use dual sonoff but it's not easy to provide analog input pin.
  max current is detected by use a simple C.T. HWCT 5A/5ma with resitor and dual diode to limit voltage at 1V (see picture included).
  Up and down can be set by command (domitics, ...) or web interface as well as 2 push buttons gpi01, gpi03 (using tasmota extra pin function)
 
 An optional LCD screen provide connection information on start, up/down activity or time otherwise (only on electrodragon cause free memory)
  
  this change must be transposed on lastest version of tasmota as soon as possible.
  
sonoff directory is c project
libraries directory is functionnal version of extra libraries used

Ceci est une version spéciale de tasmota Copyright (C) 2017  Theo Arends (de base en version 5.2.9)

celle-ci a été modifiée (toutes les modifications sont taggées 'CPAT') pour :
  -associer un timer et une horloge à chaque relay (paramètrage accessible via l'interface Web et les commandes) (menu 'configuration relais' ajouté)
  - association des librairies et code pour piloter un LCD (utiliser  #define USE_SSD1306)
  - réutilisation d'anciens paramètres (settings) obsolets pour les nouvelles fonctionnalités.
  - ajout d'un serveur ftp (un access seulement voir aide de la librairie)  et accès aux pages embraquées (via ftp) dans la mémoire SPIFFS depuis l'interface web (define USE_ElectroDragon car besoin des 4 Mbts de mémoire, fonctionne aussi avec sonoff pow)
  - utilisation de la définition USE_ExtraSonOff pour limiter la taille utilisée (commenter pour exclure les autres devices que sonoff)
  - accès à l'interlock des relais via le serveur WEB configuration (utiliser #define USE_InterlockDelay).
  - Création possible d'une sequence de relais  via #define USE_PowerEvenOdd
  - possibilité de fournir une valeur maxi du port analogique pour couper les relais sur un seuil (fixé via l'interface web server et de nouveau usage des commandes power/current) (#define USE_ADC_MAX pour activer)	
  - ajout du language français qui n'existait pas dans cette version 
  - ajout du modèle sonoff dual R2 ''                          ''
  - un message jason peut être envoyé à un site web  (celui défini par l'URL de mise à jour OTA via le web , fonctionnalité qui n'est alors plus disponible) quant un relais passe à off (utilisez : #define  USE_SENDOFF pour activer).
  
  Ces modifications ont été apportées pour permettre d'utiliser un sonoff dual et un electrodragon en tant que commande de volet roulant avec limiteur d'effort par détection du courant consommé.
  Attention la mise à disposition de la pin analogique sur le sonoff dual requiert beaucoup de précision.
  La détection se fait par un simple TI HWCT 5A/5ma branché sur une résistance et deux diodes de limitation de tension à 1V.
  La montée descente du volet étant alors temporisé et commandé soit par l'interface Web , des commands (domotics,...) , des BPs branchés sur les ports libre (via les fonctionnalité add hoc de tasmota) GPIO01 et GPIO03.
  
  Un LCD optionnel peut être ajouté, il affiche alors les paramètres de connection au démarrage, le statut montée , descente pendant le fonctionnement (et la consommation de courant) , l'heure autrement (disponible seulement sur l'electrodargon à cause de la mémoire disponible).
  
  Dès que j'aurai un peu de temps, je transposerai ces changements dans la dernière version de tasmota (et de l'esp).
