# Project-Hulken
<img src="pictures/stereo_build.jpg" style="border-radius: 50px" />
Repository for my Arduino based carstereo project. Hulken. The Arduino will analyze and divide headunit sound signal, divide the signal in 7 specters. Then the frequenzies will be used to create a visual Equalizer on a 16x32 matrix, and puls EQ-ledstrips with the beat.

## Bilens system
Bilen har ~13 v —> vi kaller dette 12v i bilens system

### Trenger:
- 12v --> 5v
- 12v --> 9v
- Splitte lydsignal fra headunit slik at det kan gå til forsterkere og arduinoer parallelt og ikke sekvensielt?
- sette sammen splittet lyd til en aux for arduinoer


## Produkter
| Product | Quantity bought | Quantity needed |
| -------- | -------- | -------- |
| Arduino Uno     |  1    |  1    |
| Arduino Mega     |  1    |   1   |
| Adafruit NeoPixel LedStrip 30     |  1    |  3    |
| Adafruit 16x32 Led Matrix Panel     |  1    |  1    |
| Sparkfun Spectrum shield     |  2    |  2    |
| Powersupply for Ledstrip(s) and matrix, during  prototyping and development. (5v,2A)     |  2    |  2    |
| Resistors 300 ~ 500r     |   30   |  3    |
| Capasitors 1000uF     |   20   |  5?    |
| AUX cable(s)     |   1   |  2    |
| AUX splitters     |   0   |  2    |
| AUX combiners     |   0   |  2    |
| Power adapter - 12v -> 9v     |  0    |  1    |
| Power adapter - 12v -> 5v    |   0   |  1    |


## Dokumentasjon under utvikling
### Bilder
### LedStrips
<img src="pictures/ledStrip_dev_overview.jpg" style="border-radius: 50px" />

<img src="pictures/ledStrip_dev_1.jpg" style="border-radius: 50px" />

<img src="pictures/ledStrip_dev_2.jpg" style="border-radius: 50px" />

### Matrix
### I bilen

Mer Kommer snart...
### Video
### LedStrips
<video src="videos/ledStrips_dev_snut.mp4" controls poster="poster.jpg" width="320" height="240" style="border-radius: 50px" />

### Matrix
### I bilen

Kommer snart...



## Links
Her lister jeg relevante kilder brukt for mitt prosjekt.

### Resistor color calculator:
- https://www.allaboutcircuits.com/tools/resistor-color-code-calculator/

### Neopixel ledstrip
- **_Docs_**: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
- **_strøm_**: https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels
- **_Wireing_**: https://learn.adafruit.com/assets/30892 

### Neopixel matrix
- **_Produkt_**: https://www.adafruit.com/product/420

### MSGQ7 spectrum analyzer
- **_Hookup_**: https://learn.sparkfun.com/tutorials/spectrum-shield-hookup-guide 
- **_Examples_**: https://github.com/sparkfun/Spectrum\_Shield

### Arduino
#### Uno
#### Mega
