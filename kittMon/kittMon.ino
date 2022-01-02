//+--------------------------------------------------------------------------
//
// 2022 TBoy58.  
//
// File:        kittMon               
//
// Description: A program for the two monitors in the Fanhome Kitt model
//              from one display
//              
//              
//
// History:     2-Jan-2022     TBoy58      Created
//
//---------------------------------------------------------------------------


#include "kitt.h" // data for rotating kitt display

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();

//String array for typed out Kitt ID display
String id[51]= {"K","KN","KNI","KNIG","KNIGH","KNIGHT",
                "I","IN","IND","INDU","INDUS","INDUST","INDUSTR",
                "INDUSTRI","INDUSTRIE","INDUSTRIES",
                "2","20","200","2000",
                "S","SE","SER","SERI","SERIA","SERIAL","SERIAL ",
                "SERIAL N","SERIAL NU","SERIAL NUM","SERIAL NUMB",
                "SERIAL NUMBE","SERIAL NUMBER","SERIAL NUMBER:",
                "A","AL","ALP","ALPH","ALPHA","ALPHA ","ALPHA D",
                "ALPHA DE","ALPHA DEL","ALPHA DELT","ALPHA DELTA",
                "2","22","227","2275","22752","227529"};
int idIndex = 0;
int x = 180;
int y = 16;

int  hold  = 14;
int   f     = 0;
int   j     = 0;

bool isID = false;

//Select lines for Kitt ID 
void select(int s)
{
  switch (s)
    {
        case 6: 
                x = 166;
                y = 28;
                break;

        case 16: 
        
                x = 186;
                y = 40;                
                break;
                
        case 20: 
                
                x = 156;
                y = 52;               
                break;
                
        case 34: 
        
                x = 162;
                y = 64;                
                break;
                
        case 45: 
        
                x = 180;
                y = 76;                
                break;             
        default:
                break;
      }
  
}

void setup() {
  tft.init();
  tft.setRotation(1);

  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  
}

void loop() {

  do
  {
    if (hold != 0)
    {
      //Left monitor rotating Kitt pause before next rotation
      tft.pushImage(15, 30,animation_width  , animation_height, rotate[f]);      
      --hold;  

      //Type out Kitt ID right monitor
      if ((idIndex < 51) && isID)
      {
        tft.drawString(id[idIndex],x,y);
        select(++idIndex);        
      }
      delay(100);
    }
    else
    {
      ++f;
      for(int i = 0; i < 8; ++i)
      {
        tft.pushImage(15, 30,animation_width  , animation_height, rotate[f]);

        //Type out Kitt ID
        if ((idIndex < 51) && isID)
        {
          tft.drawString(id[idIndex],x,y);
          select(++idIndex);        
        }
        ++f;
        delay(100);
      }
      hold = 14;      
    }
  }while(f < frames - 1);

  if ((idIndex < 51) && isID)
  {
    tft.pushImage(15, 30,animation_width  , animation_height, rotate[f]);
    for(int i = 0; i < 14; ++i)
    {      
        tft.drawString(id[idIndex],x,y);
        select(++idIndex);
        delay(100);       
    }
  }
  else
  {
    tft.pushImage(15, 30,animation_width  , animation_height, rotate[f]);
    if(++j == 3)
    {
      //Clear right monitor and reset
      tft.fillRect(150,15,90,90,TFT_BLACK);
      j = 0;
      idIndex = 0;
      x = 180;
      y = 16;
    }
    delay(1400);
  }
    
  f = 0;
  isID = !isID;

}
