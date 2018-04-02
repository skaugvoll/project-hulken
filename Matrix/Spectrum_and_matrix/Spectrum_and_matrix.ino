/****************************************************************************** 
Author: S. Skaugvoll
Date: Easter 2018

Description:
This script eanbles Sparkfun spectrum shield and Adafruit 32x16 Led Matrix
to work toghter. And displays the audio spectrum on the ledmatrix as a equalizer would.

*********************************************************************************/

/****************************************************************************** 
                                    MATRIX 
*********************************************************************************/
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int topRow = 0;
int bottomRow = 15;



/****************************************************************************** 
                                    SPECTRUM
*********************************************************************************/
//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 6
#define DC_One A8
#define DC_Two A9 

//Define spectrum variables
int freq_amp;
int Frequencies_Left[7];
int Frequencies_Right[7]; 



/********************Setup Loop*************************/
void setup() {
  /**************************
          MATRIX 
  ***************************/
  matrix.begin();
  
  // startup screen just to check pixels
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  delay(333);
  matrix.fillScreen(matrix.Color333(0, 7, 0));
  delay(333);
  matrix.fillScreen(matrix.Color333(0, 0, 7));
  delay(333);
  matrix.fillScreen(matrix.Color333(0, 0, 0)); // turn the matrix black.
  delay(500);
  matrix.fillScreen(matrix.Color333(7, 7, 7));
  delay(333);
  

  /**************************
          SPECTRUM 
  ***************************/
  Serial.begin(115200);
  //Set spectrum Shield pin configurations
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

  Serial.println("Start loop done");
}


/**************************  Main Function Loop  *****************************/
long loop_counter = 0;
void loop() {
  // Clear background
  matrix.fillScreen(0);
  
  Read_Frequencies();
//  drawMatrixCombined();
//  drawMatrixVS();
  testMatrix();


  
  
  // Update display
  matrix.swapBuffers(false);
  Serial.print("Loop counter:\t");
  Serial.println(loop_counter);
  loop_counter++;
  delay(300);
 
 
}


/*******************  Pull frquencies from Spectrum Shield  ********************/
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_Left[freq_amp] = analogRead(DC_One);
    Frequencies_Right[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

/******************* DRAW MATRIX *****************************/

long R_randNumber;
long G_randNumber;
long B_randNumber;
void testMatrix() {
  R_randNumber = random(0,8);
  G_randNumber = random(0,8);
  B_randNumber = random(0,8);
  matrix.drawPixel(0,15, matrix.Color333(2,7,2));
  delay(10);
}



void drawMatrixVS() {
  /* 
   *  Don't use the 2 columns to the far left and right.
   *  because 7 bands pr channel = 14 columns. give each band 2 columns == 28 columns. 4 unused.
   *  
   *  if we think about it now, we know that the left channels is getting columns (x coord) [2,15] and right channel [16,29]
   *  thus leaving columns 0,1 and 30,31
   */

  int left_band = 0;
  int right_band = 7;
  bool count = false;
  for(int x = 2; x <=15; x++){
    // find out how heigh the band or how many rows / pixels to draw.
    int height_left = map(Frequencies_Left[left_band], 0, 1024, 0, 15);
    int height_right = map(Frequencies_Right[right_band], 0, 1024, 0, 15);

    // Left Channel
    int startPixelTopToBottom_left = bottomRow - height_left;
    matrix.drawLine(x, startPixelTopToBottom_left, x, bottomRow, getColor(x));

    // Right Channel
    int startPixelTopToBottom_right = bottomRow - height_left;
    matrix.drawLine(31 - x, startPixelTopToBottom_right, x, bottomRow, getColor(x));
    
    // making sure that we only change channel-band every second iteration.
    if(count){
      left_band++;
      right_band--;
      count = false; 
    }
    else {
      count = true;    
    }
    
    // reset for new round of drawing
    if(left_band > 7 || right_band < 0){
      left_band = 0;
      right_band = 7;
    }
  } 
}


void drawMatrixCombined() {
  /* 
   *  Don't use the 2 columns to the far left and right.
   *  because 7 bands pr channel = 14 columns. give each band 2 columns == 28 columns. 4 unused.
   *  
   *  if we think about it now, we know that the left channels is getting columns (x coord) [2,15] and right channel [16,29]
   *  thus leaving columns 0,1 and 30,31
   */

  int left_band = 0;
  int right_band = 7;
  
  for(int x = 2; x <= 29; x += 2){ // we are goint to draw left and right at the same time.
    // find out how heigh the band or how many rows / pixels to draw.
    int height_left = map(Frequencies_Left[left_band], 0, 1024, 0, 15);
    int height_right = map(Frequencies_Right[right_band], 0, 1024, 0, 15);

    drawLineWithSplitColors(height_left, x);
    drawLineWithSplitColors(height_right, x+1);

    left_band++;
    right_band--;
    if(left_band > 7 || right_band < 0){
      left_band = 0;
      right_band = 7;
    }
  }
}

void drawLineWithSplitColors(int lineHeight, int column) {
  /*
   * NB: line draws from top to bottom! thus top is red pixels, middele is yellow and bottom is green.
   * 
   * Max height = 15
   * Red =    3 pixels  | rows
   * Yellow = 6 pixels  | rows
   * Green =  6 pixels  | rows
   */
   const int red = 3;
   const int yellow = 6;
   const int green = 6;
   
   int startPixelTopToBottom = bottomRow - lineHeight;
    
   if(lineHeight <= green){
    matrix.drawLine(column, startPixelTopToBottom, column, bottomRow, matrix.Color333(2,7,2)); // draws from [9,15] rows.
   }
   else if(lineHeight <= green + yellow){

    // draw yellow line   lets say we have a hight of 8, this gives 6 green and 2 yello thus; we should start 15 - 8 = 7 down from the top.
    // startPixelTopToBottom = 15 - 8 = 7
    // yellow should then only have 1 pixel, but start at the 7th row, and exapnd over 1 row
    // start at 7, and end at 8 (15 - 7) = 8.  
    matrix.drawLine(column, startPixelTopToBottom, column, bottomRow - yellow, matrix.Color333(7,7,2)); // draws from YELLOW start to end of yellow
    // now we need to color the rest of the line rows 9 to 15 green
    matrix.drawLine(column, bottomRow - green, column, bottomRow, matrix.Color333(2,7,2)); // draws from green end to GREEN start. (thing end is towards top, start is towards bottom)
   }
   else {
    // Now we know that the line is both red, yellow and green
    // start by drawing red
    matrix.drawLine(column, startPixelTopToBottom, column, bottomRow - (yellow + green), matrix.Color333(7,2,2)); // draws from yellow start to end of yellow :: lets say hight is 14: spttb = 15 - 14 = 1, (yellow + green) = 12, red start = 15 - 12 = 3. thus red has row 1,2,3 colored.
    // then yellow
    matrix.drawLine(column, bottomRow - (yellow + green) , column, bottomRow - green, matrix.Color333(7,7,2));
    // then green
    matrix.drawLine(column, bottomRow - green, column, bottomRow - green, matrix.Color333(2,7,2));
   } 
}


// found in the src of matrix library, that matrix.Color333() return uint16_t
uint16_t getColor(int x) {
  return matrix.Color333(2,7,2);
}


