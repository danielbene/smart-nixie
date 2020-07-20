# smart-nixie
BEWARE TRAVELLER! This thing is so unnecessarily overengeneered that it can make a crocodile cry (theoretically). You tought a simple four digit clock wouldn't need wifi connection, or a count up timer, or maybe a humidity sensor?! YOU WERE WRONG! I added many things to this badboy, because... well... I COULD!

So, let me just put that marketing aside. This is my wifi-enabled nixie clock that I proudly present to you. I'm a beginner with electronics, but a bit better around code, so don't you dare judge me on my technical decisions. I wanted to make the most out of my design, only because of the sake of my own fulfillment.

Main aspects of the project:  
- working four digit nixie clock display (as you probably guessed)  
- wifi connection  
- manual or automatic mode for time setting  
  - automatic time updates from the web - configurable NTP time server  
  - timezone offset can be set dinamically from the config page  
- OOP code (YASSS!!! 'Duinos needs more sweet-sweet object-oriented love)  
- webpage based control panel  
  - by using mdns the clock has it's own domain address in the local network  
  - Androids do not support mDNS so there is option for static ip in the config page  
- timed AP mode (broadcasting his own network) for the essential setups  
- count up/down timers  
- humidity and temperature values  
  - there is an air pressure sensor inside too, so maybe...  
- automatic slot-machine effect to protect against cathode poisoning  
- automatic tube turn off based on the presence of specific device MAC on the network (optional)  
- leading zeros turn off  
- display flashing feature  
- modular design for easier repairs/modifications  
- code design focuses on the longevity of the electronic parts (tries to avoid unnecessary actions)  
