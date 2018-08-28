//Demo of clearing screen to display black,white,red,green,blue.

#include <LCD_GUI.h> //Core graphics library
#include <LCD_KBV.h> //Hardware-specific library

LCD_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset



void setup() 
{
    mylcd.Init_LCD(); //initialize lcd
    mylcd.Fill_Screen(0xFFFF); //display white
}

void loop() 
{ 
    //display black,white,red,green,blue screen in sequent
    mylcd.Fill_Screen(0,0,0);  
    mylcd.Fill_Screen(255,255,255); 
    mylcd.Fill_Screen(255,0,0); 
    mylcd.Fill_Screen(0,255,0);
    mylcd.Fill_Screen(0,0,255);
    delay(3000);
    mylcd.Fill_Screen(0x0000);
    delay(1000);
    mylcd.Fill_Screen(0xFFFF);
    delay(1000);
    mylcd.Fill_Screen(0xF800);
    delay(1000);
    mylcd.Fill_Screen(0x07E0);
   delay(1000);
   mylcd.Fill_Screen(0x001F);
   delay(1000);
}
