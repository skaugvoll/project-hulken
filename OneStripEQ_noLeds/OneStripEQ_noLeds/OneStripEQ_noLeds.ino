
/****************************************************************************** 
Author: Sigve Skaugvoll
Version: 1.0
Created: 03.02.16
Email: skaugvoll@gmail.com

Board: Arduino Genuino Uno
*********************************************************************************/

//NeoPixel Strip:
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 30
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 

int i;
int color;

/********************Setup Loop*************************/
void setup() {
  Serial.begin(9600);
  pixels.begin(); //prepare the data pin for NeoPixel output.
  pixels.show(); // Initialize all pixels to 'off'
  
  
  //Set Spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);

}


/**************************Main Function Loop*****************************/
void loop() {
  Read_Frequencies();
  eq();
//  Puls_LEDS(); // ikke ferdig implementert. fungerer halveis.. men noe mystisk shit
  
  delay(50);
 
}


/*******************Pull frequencies from Spectrum Shield********************/
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
   
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}


void eq(){
   int intens = Frequencies_Two[4];
   Serial.print("intens:\t");
   Serial.print(intens);
   Serial.print("\t antLeds:\t");
   int antLeds = map(intens, 0, 1024, 0, 30);
   Serial.println(antLeds);
   for(i = 0; i < NUMPIXELS; i++){
    if(i < antLeds && i <15){
      pixels.setPixelColor(i, getColor(3));
      pixels.show();
    }
    else if(i < antLeds && i >=15 && i<=26){
      pixels.setPixelColor(i, getColor(2));
      pixels.show();
    }
    else if(i < antLeds && i >=27 && i < 30){
      pixels.setPixelColor(i, getColor(1));
      pixels.show();
    }
    else{
      pixels.setPixelColor(i,0);
      pixels.show();
    }
   }
   setIntensitivity(intens);
   pixels.show();
}



void Puls_LEDS(){
  int intensBASS = Frequencies_One[0];
  int intensMID = Frequencies_One[4];
  int intensTREBLE = Frequencies_Two[7];
  intensBASS = map(intensBASS, 0, 1023, 0, 255);
  intensMID = map(intensMID, 0, 1023, 0, 255);
  intensTREBLE = map(intensTREBLE, 0, 1023, 0, 255);
  
  for(i = 0; i<=9; i++) {    //Sets the color for the 10 first leds, to bass color (red)  //lengst unna kontakt mot arduino.
    pixels.setPixelColor(i, getColor(10));
    setIntensitivity(intensBASS);

  } 

  for(i = 10; i<=19; i++) {    //Sets the color for the 10 middle leds, to mid color (blue)
    pixels.setPixelColor(i, getColor(20));
    setIntensitivity(intensMID);

  } 

  for(i = 20; i<30; i++) {    //Sets the color for the 10 last leds, to treable color (green)
    pixels.setPixelColor(i, getColor(30));
    setIntensitivity(intensTREBLE);
  }
   setIntensitivity(intensBASS);
   pixels.show();

}

uint32_t magenta = pixels.Color(255, 0, 255);

uint32_t red = pixels.Color(255,0,0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t bossanova = pixels.Color(68, 50, 102);
  

void setIntensitivity(int intens){
  if(intens < 20){
    pixels.setBrightness(0);
  }
  else{
    pixels.setBrightness(intens);
  }
  //pixels.show();
}

uint32_t getColor(int indexColor){

  if(indexColor == 1){
    return red;
  }
  else if(indexColor == 2){
    return yellow;
  }
  else if(indexColor == 3){
    return green;
  }
  else {
    return magenta;
  }
}

