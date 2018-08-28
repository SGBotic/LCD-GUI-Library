// Demo of graphic control switches and list box

#include <LCD_Touch.h> //touch library
#include <LCD_GUI.h> //Core graphics library
#include <LCD_KBV.h> //Hardware-specific library
#include "switch_font.c"

LCD_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset


#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 100
#define TS_MAXX 920

#define TS_MINY 70
#define TS_MAXY 900
// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65


boolean switch_flag_1 = true,switch_flag_2 = true,switch_flag_3 = true,switch_flag_4 = true,switch_flag_5 = true,switch_flag_6 = true;  
int16_t menu_flag = 1,old_menu_flag;     

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//display string
void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    mylcd.Set_Text_Mode(mode);
    mylcd.Set_Text_Size(csize);
    mylcd.Set_Text_colour(fc);
    mylcd.Set_Text_Back_colour(bc);
    mylcd.Print_String(str,x,y);
}

//diaplay a picture
void show_picture(const uint8_t *color_buf,int16_t buf_size,int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
    mylcd.Set_Addr_Window(x1, y1, x2, y2); 
    mylcd.Push_Any_Color(color_buf, buf_size, 1, 1);
}

//Check whether to press or not
boolean is_pressed(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int16_t px,int16_t py)
{
    if((px > x1 && px < x2) && (py > y1 && py < y2))
    {
        return true;  
    } 
    else
    {
        return false;  
    }
 }

//show the system menu
void show_system_menu(void)
{    
    show_string("time setting",10,150,2,BLACK, BLACK,1);
    show_string("date setting",10,170,2,BLACK, BLACK,1);
    show_string("alarm setting",10,190,2,BLACK, BLACK,1);
    show_string("talk setting",10,210,2,BLACK, BLACK,1);
    show_string("sound setting",10,230,2,BLACK, BLACK,1);
    switch(menu_flag)
    {
      case 1:
      {
          mylcd.Set_Draw_color(BLUE);
          mylcd.Fill_Rectangle(0, 147, mylcd.Get_Display_Width()-1, 166);
          show_string("time setting",10,150,2,WHITE, BLACK,1);
          break;
      }
      case 2:
      {
          mylcd.Set_Draw_color(BLUE);
          mylcd.Fill_Rectangle(0, 167, mylcd.Get_Display_Width()-1, 186);
          show_string("date setting",10,170,2,WHITE, BLACK,1);
          break;
      }
      case 3:
      {
          mylcd.Set_Draw_color(BLUE);
          mylcd.Fill_Rectangle(0, 187, mylcd.Get_Display_Width()-1, 206);
          show_string("alarm setting",10,190,2,WHITE, BLACK,1);
          break;
      }
      case 4:
      {
          mylcd.Set_Draw_color(BLUE);
          mylcd.Fill_Rectangle(0, 207, mylcd.Get_Display_Width()-1, 226);
          show_string("talk setting",10,210,2,WHITE, BLACK,1);
          break;
      }
      case 5:
      {
          mylcd.Set_Draw_color(BLUE);
          mylcd.Fill_Rectangle(0, 227, mylcd.Get_Display_Width()-1, 246);
          show_string("sound setting",10,230,2,WHITE, BLACK,1);
          break;
      }
      default:
        break;
    }
}
                    
void setup(void) 
{    
 mylcd.Init_LCD();
 mylcd.Fill_Screen(WHITE); 

 //show the switch picture
 mylcd.Set_Draw_color(192, 192, 192);
 mylcd.Draw_Fast_HLine(0, 3, mylcd.Get_Display_Width());
 show_picture(switch_on_2,sizeof(switch_on_2)/2,5,5,34,34);
 show_string("switch is on ",60,11,2,GREEN, BLACK,1);

 mylcd.Draw_Fast_HLine(0, 37, mylcd.Get_Display_Width());
 
 show_string("wifi setting",5,40,2,BLACK, BLACK,1);
 show_picture(switch_on_3,sizeof(switch_on_3)/2,195,40,234,54);

  mylcd.Draw_Fast_HLine(0, 57, mylcd.Get_Display_Width());
 
 show_string("bt setting",5,60,2,BLACK, BLACK,1);
 show_picture(switch_on_3,sizeof(switch_on_3)/2,195,60,234,74);

 mylcd.Draw_Fast_HLine(0, 77, mylcd.Get_Display_Width());
 
 show_string("auto time",5,80,2,BLACK, BLACK,1);
 show_picture(switch_on_1,sizeof(switch_on_1)/2,204,80,218,94);

 mylcd.Draw_Fast_HLine(0, 97, mylcd.Get_Display_Width());
 
 show_string("enable lock",5,100,2,BLACK, BLACK,1);
 show_picture(switch_on_1,sizeof(switch_on_1)/2,204,100,218,114);

 mylcd.Draw_Fast_HLine(0, 116, mylcd.Get_Display_Width());
 
 show_string("system setting   >",5,119,2,BLUE, BLACK,1);
 mylcd.Draw_Fast_HLine(0, 138, mylcd.Get_Display_Width());
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop(void)
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, mylcd.Get_Display_Width(), 0);
    p.y = (mylcd.Get_Display_Height()-map(p.y, TS_MINY, TS_MAXY, mylcd.Get_Display_Height(), 0));
  } 
  if(is_pressed(5,5,34,34,p.x,p.y))
  {
      if(switch_flag_1)
      {   //display off 
          show_picture(switch_off_2,sizeof(switch_off_2)/2,5,5,34,34);
          mylcd.Set_Draw_color(WHITE);
          mylcd.Fill_Rectangle(60, 11,  216, 27);
          show_string("switch is off ",60,11,2,RED, BLACK,1); 
          switch_flag_1 = false;
       }
       else
       {  //display on
         show_picture(switch_on_2,sizeof(switch_on_2)/2,5,5,34,34);
         mylcd.Set_Draw_color(WHITE);
         mylcd.Fill_Rectangle(60, 11,  216, 27);
         show_string("switch is on ",60,11,2,GREEN, BLACK,1);
         switch_flag_1 = true;
       }
       delay(100);
   }
   if(is_pressed(195,40,234,54,p.x,p.y))
   {
      if(switch_flag_2)
      {
          show_picture(switch_off_3,sizeof(switch_off_3)/2,195,40,234,54);
          switch_flag_2 = false;
      }
      else
      {
         show_picture(switch_on_3,sizeof(switch_on_3)/2,195,40,234,54);
         switch_flag_2 = true;
      }
      delay(100);
    }
    if(is_pressed(195,60,234,74,p.x,p.y))
    {
       if(switch_flag_3)
      {
          show_picture(switch_off_3,sizeof(switch_off_3)/2,195,60,234,74);
          switch_flag_3 = false;
      }
      else
      {
         show_picture(switch_on_3,sizeof(switch_on_3)/2,195,60,234,74);
         switch_flag_3 = true;
      }
      delay(100);
     }
     if(is_pressed(205,81,217,93,p.x,p.y))
     {
       if(switch_flag_4)
       {
         show_picture(switch_off_1,sizeof(switch_off_1)/2,204,80,218,94);
          switch_flag_4 = false;
       }
       else
       {
         show_picture(switch_on_1,sizeof(switch_on_1)/2,204,80,218,94);
          switch_flag_4 = true;
       }
      delay(100);
     }
     if(is_pressed(205,101,217,113,p.x,p.y))
     {
       if(switch_flag_5)
       {
        show_picture(switch_off_1,sizeof(switch_off_1)/2,204,100,218,114);
        switch_flag_5 = false;
       }
       else
       {
         show_picture(switch_on_1,sizeof(switch_on_1)/2,204,100,218,114);
         switch_flag_5 = true;
        }
       delay(100);
     }
     if(is_pressed(5,119,mylcd.Get_Display_Width()-1,137,p.x,p.y))
     {     
          mylcd.Set_Draw_color(MAGENTA);
          mylcd.Fill_Rectangle(0, 117, mylcd.Get_Display_Width()-1, 137);
          delay(100);
          mylcd.Set_Draw_color(WHITE);
          mylcd.Fill_Rectangle(0, 117, mylcd.Get_Display_Width()-1, 137);
          if(switch_flag_6)
          {
              show_string("system setting   <",5,119,2,BLUE, BLACK,1);
              show_system_menu();
              switch_flag_6 = false;
          }
          else
          {
               show_string("system setting   >",5,119,2,BLUE, BLACK,1);
               mylcd.Set_Draw_color(WHITE);
               mylcd.Fill_Rectangle(0, 147, mylcd.Get_Display_Width()-1, 250);
               switch_flag_6 = true;
          }
     }
     if(is_pressed(0,147,mylcd.Get_Display_Width()-1,247,p.x,p.y)&&(!switch_flag_6))
     {
        old_menu_flag = menu_flag;     
        if(is_pressed(0,147,mylcd.Get_Display_Width()-1,166,p.x,p.y))
        {
            mylcd.Set_Draw_color(BLUE);
            mylcd.Fill_Rectangle(0, 147, mylcd.Get_Display_Width()-1, 166);
            show_string("time setting",10,150,2,WHITE, BLACK,1);
            menu_flag = 1;
         }
         if(is_pressed(0,167,mylcd.Get_Display_Width()-1,186,p.x,p.y))
         {
            mylcd.Set_Draw_color(BLUE);
            mylcd.Fill_Rectangle(0, 167, mylcd.Get_Display_Width()-1, 186);
            show_string("date setting",10,170,2,WHITE, BLACK,1);
            menu_flag = 2;
         }
         if(is_pressed(0,187,mylcd.Get_Display_Width()-1,206,p.x,p.y))
         {
            mylcd.Set_Draw_color(BLUE);
            mylcd.Fill_Rectangle(0, 187, mylcd.Get_Display_Width()-1, 206);
            show_string("alarm setting",10,190,2,WHITE, BLACK,1);
            menu_flag = 3;
         }
         if(is_pressed(0,207,mylcd.Get_Display_Width()-1,226,p.x,p.y))
         {
             mylcd.Set_Draw_color(BLUE);
             mylcd.Fill_Rectangle(0, 207, mylcd.Get_Display_Width()-1, 226);
            show_string("talk setting",10,210,2,WHITE, BLACK,1);
            menu_flag = 4;
         }
         if(is_pressed(0,227,mylcd.Get_Display_Width()-1,246,p.x,p.y))
         {
            mylcd.Set_Draw_color(BLUE);
            mylcd.Fill_Rectangle(0, 227, mylcd.Get_Display_Width()-1, 246);
            show_string("sound setting",10,230,2,WHITE, BLACK,1);
            menu_flag = 5;
         }  
         if(old_menu_flag != menu_flag)
         {
            switch(old_menu_flag)
            {
              case 1:
              {
                  mylcd.Set_Draw_color(WHITE);
                  mylcd.Fill_Rectangle(0, 147, mylcd.Get_Display_Width()-1, 166);
                  show_string("time setting",10,150,2,BLACK, BLACK,1);
                  break;
              }
              case 2:
              {
                  mylcd.Set_Draw_color(WHITE);
                  mylcd.Fill_Rectangle(0, 167, mylcd.Get_Display_Width()-1, 186);
                  show_string("date setting",10,170,2,BLACK, BLACK,1);
                  break;
              }
              case 3:
              {
                  mylcd.Set_Draw_color(WHITE);
                  mylcd.Fill_Rectangle(0, 187, mylcd.Get_Display_Width()-1, 206);
                  show_string("alarm setting",10,190,2,BLACK, BLACK,1);
                  break;
              }
              case 4:
              {
                  mylcd.Set_Draw_color(WHITE);
                  mylcd.Fill_Rectangle(0, 207, mylcd.Get_Display_Width()-1, 226);
                  show_string("talk setting",10,210,2,BLACK, BLACK,1);
                  break;
              }
              case 5:
              {
                  mylcd.Set_Draw_color(WHITE);
                  mylcd.Fill_Rectangle(0, 227, mylcd.Get_Display_Width()-1, 246);
                  show_string("sound setting",10,230,2,BLACK, BLACK,1);
                  break;
              }
              default:
                break;                  
           }       
       }
       delay(100);
   }
}

