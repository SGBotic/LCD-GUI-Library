// Format the microSD card to FAT16 or FAT32 and copy all the photos in the photo folder to this microSD card.
//This example supports only Arduino Uno. Mega is not supported as the SPI pin assignment is different from Uno.


#include <SD.h>
#include <SPI.h>
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

#define PIXEL_NUMBER  (mylcd.Get_Display_Width()/4)
#define FILE_NUMBER 4
#define FILE_NAME_SIZE_MAX 20

uint32_t bmp_offset = 0;
uint16_t s_width = mylcd.Get_Display_Width();  
uint16_t s_heigh = mylcd.Get_Display_Height();
//int16_t PIXEL_NUMBER;

char file_name[FILE_NUMBER][FILE_NAME_SIZE_MAX];

uint16_t read_16(File fp)
{
    uint8_t low;
    uint16_t high;
    low = fp.read();
    high = fp.read();
    return (high<<8)|low;
}

uint32_t read_32(File fp)
{
    uint16_t low;
    uint32_t high;
    low = read_16(fp);
    high = read_16(fp);
    return (high<<8)|low;   
 }
 
bool analysis_bpm_header(File fp)
{
    if(read_16(fp) != 0x4D42)
    {
      return false;  
    }
    //get bpm size
    read_32(fp);
    //get creator information
    read_32(fp);
    //get offset information
    bmp_offset = read_32(fp);
    //get DIB infomation
    read_32(fp);
    //get width and heigh information
    uint32_t bpm_width = read_32(fp);
    uint32_t bpm_heigh = read_32(fp);
    if((bpm_width != s_width) || (bpm_heigh != s_heigh))
    {
      return false; 
    }
    if(read_16(fp) != 1)
    {
        return false;
    }
    read_16(fp);
    if(read_32(fp) != 0)
    {
      return false; 
     }
     return true;
}

void draw_bmp_picture(File fp)
{
  uint16_t i,j,k,l,m=0;
  uint8_t bpm_data[PIXEL_NUMBER*3] = {0};
  uint16_t bpm_color[PIXEL_NUMBER];
  fp.seek(bmp_offset);
  for(i = 0;i < s_heigh;i++)
  {
    for(j = 0;j<s_width/PIXEL_NUMBER;j++)
    {
      m = 0;
      fp.read(bpm_data,PIXEL_NUMBER*3);
      for(k = 0;k<PIXEL_NUMBER;k++)
      {
        bpm_color[k]= mylcd.Color_To_565(bpm_data[m+2], bpm_data[m+1], bpm_data[m+0]);
        m +=3;
      }
      for(l = 0;l<PIXEL_NUMBER;l++)
      {
        mylcd.Set_Draw_color(bpm_color[l]);
        mylcd.Draw_Pixel(j*PIXEL_NUMBER+l,i);
      }    
     }
   }    
}

void setup() 
{
    Serial.begin(9600);
   mylcd.Init_LCD();
   mylcd.Fill_Screen(BLUE);
   //s_width = mylcd.Get_Display_Width();  
   //s_heigh = mylcd.Get_Display_Height();
   //PIXEL_NUMBER = mylcd.Get_Display_Width()/4;
   if(PIXEL_NUMBER == 60)
   {
       strcpy(file_name[0],"flower.bmp");
       strcpy(file_name[1],"tiger.bmp");
       strcpy(file_name[2],"tree.bmp");
       strcpy(file_name[3],"RedRose.bmp");
   }
   else
   {
       strcpy(file_name[0],"01.bmp");
       strcpy(file_name[1],"02.bmp");
       strcpy(file_name[2],"03.bmp");
       strcpy(file_name[3],"04.bmp");
   }
  //Init SD_Card
   pinMode(10, OUTPUT);
   
    if (!SD.begin(10)) 
    {
      mylcd.Set_Text_Back_colour(BLUE);
      mylcd.Set_Text_colour(WHITE);    
      mylcd.Set_Text_Size(1);
      mylcd.Print_String("SD Card Init fail!",0,0);
    }
}

void loop() 
{
    int i = 0;
    File bmp_file;
    for(i = 0;i<FILE_NUMBER;i++)
    {
       bmp_file = SD.open(file_name[i]);
       if(!bmp_file)
       {
            mylcd.Set_Text_Back_colour(BLUE);
            mylcd.Set_Text_colour(WHITE);    
            mylcd.Set_Text_Size(1);
            mylcd.Print_String("didnt find BMPimage!",0,10);
            while(1);
        }
        if(!analysis_bpm_header(bmp_file))
        {  
            mylcd.Set_Text_Back_colour(BLUE);
            mylcd.Set_Text_colour(WHITE);    
            mylcd.Set_Text_Size(1);
            mylcd.Print_String("bad bmp picture!",0,0);
            return;
        }
          draw_bmp_picture(bmp_file);
         bmp_file.close(); 
         delay(2000);
     }
}
