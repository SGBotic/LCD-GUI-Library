//Demo of reading color value from GRAM


#include <LCD_GUI.h> //Core graphics library
#include <LCD_KBV.h> //Hardware-specific library

LCD_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void color_dump(uint16_t x,uint16_t y)
{
    uint8_t buf[30] = {0},pbuf[10] = {0};
    uint8_t wd = (mylcd.Get_Display_Width() - 9 * 6)/ (5 * 6);
    uint8_t hi = (mylcd.Get_Display_Height() / 8) - 1;
    uint16_t pixel = 0;
    //set white
    mylcd.Set_Text_colour(WHITE);
    //set text size 1
    mylcd.Set_Text_Size(1);
    for(int j = 0;j< hi;j++)
    {
      sprintf(buf,"%3d,%3d:",x,y+j);
      mylcd.Print_String(buf, 0, 8*(j+1)*mylcd.Get_Text_Size());
      for(int i=0;i<wd;i++)
      {          
//          mylcd.Print_String(buf, 0, line+8);
        //read pixel
          pixel = mylcd.Read_Pixel(x+i,y+j);

        // if white set green
          if(WHITE == pixel)
          {
             mylcd.Set_Text_colour(GREEN); 
           }
           sprintf(pbuf,"%04X ",pixel); 
           mylcd.Print_String(pbuf,(strlen(buf)+strlen(pbuf)*i)*6*mylcd.Get_Text_Size(),8*(j+1)*mylcd.Get_Text_Size());
        //set white
           mylcd.Set_Text_colour(WHITE);
        } 
     }
}   

uint8_t aspect;
char *aspectname[] = {"PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"};
uint16_t colors[] = {BLACK, BLUE};

void setup()
{
  mylcd.Init_LCD();
//mylcd.Set_Text_Back_colour(BLACK);
}

void loop() 
{
  uint16_t iter, color;
    char buf[80];
    aspect = (aspect + 1) & 3;
    mylcd.Set_Rotation(aspect);
 //color_dump(36,0);
 
    for (iter = 0; iter < sizeof(colors) / sizeof(uint16_t); iter++) 
    {
        color = colors[iter];
        mylcd.Fill_Screen(color);
        mylcd.Set_Text_Back_colour(color);
        mylcd.Set_Text_colour(WHITE);
        mylcd.Set_Text_Size(1);
     sprintf(buf, " ID=0x%04X Background=%04X %s", mylcd.Read_ID(), color, aspectname[aspect]);
      mylcd.Print_String(buf,0,0);
        color_dump(36,0);
        delay(3000);
       
    } 

}
