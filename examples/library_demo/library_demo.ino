
//This program is a demo of how to use most of the functions 
//in LCD GUI library.


#include <LCD_GUI.h> //Core graphics library
#include <LCD_KBV.h> //Hardware-specific library

LCD_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

unsigned long show_text(void)
{
    unsigned long time_start = micros();

    //Top text
    mylcd.Set_Draw_color(32, 0,255);
    mylcd.Fill_Rectangle(0, 0, mylcd.Get_Display_Width()-1, 14);
    mylcd.Set_Text_colour(0, 255, 0);   
    mylcd.Set_Text_Size(1);
    mylcd.Set_Text_Mode(1);
    mylcd.Print_String("* Universal Color LCD Display Library *", CENTER, 3);

    //Bottom text
    mylcd.Set_Draw_color(128, 128, 128);
    mylcd.Fill_Rectangle(0, mylcd.Get_Display_Height()-15, mylcd.Get_Display_Width()-1, mylcd.Get_Display_Height()-1);
    mylcd.Set_Text_colour(255, 255, 255);   
    mylcd.Set_Text_Size(1);
    mylcd.Set_Text_Mode(1);
    mylcd.Print_String("<http://www.SGBotic.com>", CENTER, mylcd.Get_Display_Height()-11);

    mylcd.Set_Draw_color(255, 0, 0); 
    mylcd.Draw_Rectangle(0, 15, mylcd.Get_Display_Width()-1, mylcd.Get_Display_Height()-16);   
    return micros() - time_start;
}

//display triangle functions
unsigned long show_triangle_function(void)
{
     uint16_t i;
     unsigned long time_start = micros();
     // Draw crosshairs
     mylcd.Set_Draw_color(0, 0, 255); 
     mylcd.Draw_Fast_VLine(mylcd.Get_Display_Width()/2-1, 16, mylcd.Get_Display_Height()- 32);
     mylcd.Draw_Fast_HLine(1, mylcd.Get_Display_Height()/2-1, mylcd.Get_Display_Width()-2);
     for(i = 1;i <= (mylcd.Get_Display_Height()- 32)/2/10;i++)
     {
         mylcd.Draw_Fast_HLine(mylcd.Get_Display_Width()/2-1-2, mylcd.Get_Display_Height()/2-1-i*10, 5);
         mylcd.Draw_Fast_HLine(mylcd.Get_Display_Width()/2-1-2, mylcd.Get_Display_Height()/2-1+i*10, 5);
     }
     for(i = 1;i <= (mylcd.Get_Display_Width()-2)/2/10;i++)
     {
         mylcd.Draw_Fast_VLine(mylcd.Get_Display_Width()/2-1-i*10, mylcd.Get_Display_Height()/2-1-2, 5);
         mylcd.Draw_Fast_VLine(mylcd.Get_Display_Width()/2-1+i*10, mylcd.Get_Display_Height()/2-1-2, 5);
     }
     
     // Draw sin lines
     mylcd.Set_Text_colour(0, 255, 255);
     mylcd.Set_Text_Back_colour(0,0,0);   
     mylcd.Set_Text_Size(1);
     mylcd.Set_Text_Mode(0);
     mylcd.Print_String("sin",5,17);
     mylcd.Set_Draw_color(0, 255, 255); 
     for (i=1; i<mylcd.Get_Display_Width()-2; i++)
     {
        mylcd.Draw_Pixel(i,mylcd.Get_Display_Height()/2-1+(sin(((i*1.13)*3.14)/180)*95));
     }

     // Draw cos lines
     mylcd.Set_Text_colour(0, 255, 0);
     mylcd.Set_Text_Back_colour(0,0,0);   
     mylcd.Set_Text_Size(1);
     mylcd.Set_Text_Mode(0);
     mylcd.Print_String("cos",5,25);
     mylcd.Set_Draw_color(0, 255, 0);
     for (i=1; i<mylcd.Get_Display_Width()-2; i++)
     {
        mylcd.Draw_Pixel(i,mylcd.Get_Display_Height()/2-1+(cos(((i*1.13)*3.14)/180)*95));
     }

     // Draw tan lines
     mylcd.Set_Text_colour(255, 255, 0); 
     mylcd.Set_Text_Back_colour(0,0,0);  
     mylcd.Set_Text_Size(1);
     mylcd.Set_Text_Mode(0);
     mylcd.Print_String("tan",5,33);
     mylcd.Set_Draw_color(255, 255, 0);
     for (i=1; i<mylcd.Get_Display_Width()-2; i++)
     {
        mylcd.Draw_Pixel(i,mylcd.Get_Display_Height()/2-1+(tan(((i*1.13)*3.14)/180)*10));
     }

     // Draw cot lines
     mylcd.Set_Text_colour(255, 0, 0); 
     mylcd.Set_Text_Back_colour(0,0,0);  
     mylcd.Set_Text_Size(1);
     mylcd.Set_Text_Mode(0);
     mylcd.Print_String("cot",5,41);
     mylcd.Set_Draw_color(255, 0, 0);
     for (i=1; i<mylcd.Get_Display_Width()-2; i++)
     {
        mylcd.Draw_Pixel(i,mylcd.Get_Display_Height()/2-1+1/(tan(((i*1.13)*3.14)/180)*0.1));
     }
     return micros()-time_start;
}

// Draw a moving sinewave
unsigned long show_sinewave(void)
{
   uint16_t buf[mylcd.Get_Display_Width()-2],x = 1,i,y;
   unsigned long time_start = micros();
   int16_t wid = mylcd.Get_Display_Width();
   int16_t t;
   float k;
   if(wid == 320)
   {
      t = 20;
      k = 1.1; 
   }
   else
   {
     t = 15;
     k = 0.7;  
   }
   mylcd.Set_Draw_color(0, 0, 255); 
   mylcd.Draw_Fast_VLine(mylcd.Get_Display_Width()/2-1, 16, mylcd.Get_Display_Height()- 32);
   mylcd.Draw_Fast_HLine(1, mylcd.Get_Display_Height()/2-1, mylcd.Get_Display_Width()-2);
   for (i=1; i<((mylcd.Get_Display_Width()-2)*t); i++) 
   {
      x++;
      if (x==mylcd.Get_Display_Width()-1)
      {
          x=1;
      }
      if (i>mylcd.Get_Display_Width()-1)
      {
          if ((x==mylcd.Get_Display_Width()/2-1)||(buf[x-1]==mylcd.Get_Display_Height()/2-1))
          {
              mylcd.Set_Draw_color(0, 0, 255); 
          }
          else
          {
             mylcd.Set_Draw_color(0, 0, 0); 
          }
          mylcd.Draw_Pixel(x,buf[x-1]);
    }
    mylcd.Set_Draw_color(255, 64, 255);
    y=mylcd.Get_Display_Height()/2-1+(sin(((i*k)*3.14)/180)*(90-(i/100)));
    mylcd.Draw_Pixel(x,y);
    buf[x-1]=y;
  }
  return micros()- time_start;   
}

// Draw some filled rectangles
unsigned long show_fill_rectangle(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    uint16_t side_len = (mylcd.Get_Display_Height()-40)/5;
    uint16_t x_spec = (mylcd.Get_Display_Width()-5*side_len)/2;
    uint16_t y_spec = (mylcd.Get_Display_Height()-5*side_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              mylcd.Set_Draw_color(255,0,255);
              break;
            case 1:
              mylcd.Set_Draw_color(255,0,0);
              break;
            case 2:
              mylcd.Set_Draw_color(0,255,0);
              break;
            case 3:
              mylcd.Set_Draw_color(0,0,255);
              break;
            case 4:
              mylcd.Set_Draw_color(255,255,0);
              break;
            default:
              break;
          }   
          mylcd.Fill_Rectangle(x_spec+i*side_len-1, y_spec+i*side_len-1, x_spec+(i+1)*side_len-1, y_spec+(i+1)*side_len-1);
          mylcd.Fill_Rectangle(x_spec+i*side_len-1, y_spec+(5-i)*side_len-1, x_spec+(i+1)*side_len-1, y_spec+(4-i)*side_len-1); 
     }
     return micros()- time_start;   
}

// Draw some filled round rectangles
unsigned long show_fill_round_rectangle(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    uint16_t side_len = (mylcd.Get_Display_Height()-40)/5;
    uint16_t x_spec = (mylcd.Get_Display_Width()-5*side_len)/2;
    uint16_t y_spec = (mylcd.Get_Display_Height()-5*side_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              mylcd.Set_Draw_color(255,0,255);
              break;
            case 1:
              mylcd.Set_Draw_color(255,0,0);
              break;
            case 2:
              mylcd.Set_Draw_color(0,255,0);
              break;
            case 3:
              mylcd.Set_Draw_color(0,0,255);
              break;
            case 4:
              mylcd.Set_Draw_color(255,255,0);
              break;
            default:
              break;
          }   
          mylcd.Fill_Round_Rectangle(x_spec+i*side_len-1, y_spec+i*side_len-1, x_spec+(i+1)*side_len-1, y_spec+(i+1)*side_len-1,10);
          mylcd.Fill_Round_Rectangle(x_spec+i*side_len-1, y_spec+(5-i)*side_len-1, x_spec+(i+1)*side_len-1, y_spec+(4-i)*side_len-1,10); 
     }
     return micros()- time_start;   
}

// Draw some filled circles
unsigned long show_fill_circle(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    uint16_t r_len = (mylcd.Get_Display_Height()-40)/5/2;
    uint16_t x_spec = (mylcd.Get_Display_Width()-5*r_len*2)/2;
    uint16_t y_spec = (mylcd.Get_Display_Height()-5*r_len*2)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              mylcd.Set_Draw_color(255,0,255);
              break;
            case 1:
              mylcd.Set_Draw_color(255,0,0);
              break;
            case 2:
              mylcd.Set_Draw_color(0,255,0);
              break;
            case 3:
              mylcd.Set_Draw_color(0,0,255);
              break;
            case 4:
              mylcd.Set_Draw_color(255,255,0);
              break;
            default:
              break;
          }   
          mylcd.Fill_Circle(x_spec+r_len+i*r_len*2-1, y_spec+r_len+i*r_len*2-1,r_len);
          mylcd.Fill_Circle(x_spec+r_len+i*r_len*2-1, y_spec+(5-i)*r_len*2-r_len-1,r_len); 
     }
     return micros()- time_start;   
 }

// Draw some filled triangles
unsigned long show_fill_triangle(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    uint16_t h_len = (mylcd.Get_Display_Height()-40)/5;
    uint16_t side_len = (h_len*115)/100;
    uint16_t x_spec = (mylcd.Get_Display_Width()-5*side_len)/2;
    uint16_t y_spec = (mylcd.Get_Display_Height()-5*h_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              mylcd.Set_Draw_color(255,0,255);
              break;
            case 1:
              mylcd.Set_Draw_color(255,0,0);
              break;
            case 2:
              mylcd.Set_Draw_color(0,255,0);
              break;
            case 3:
              mylcd.Set_Draw_color(0,0,255);
              break;
            case 4:
              mylcd.Set_Draw_color(255,255,0);
              break;
            default:
              break;
          } 
          mylcd.Fill_Triangle(x_spec+i*side_len-1,y_spec+(i+1)*h_len-1,x_spec+side_len/2+i*side_len-1,y_spec+i*h_len-1,x_spec+(i+1)*side_len-1,y_spec+(i+1)*h_len-1); 
          mylcd.Fill_Triangle(x_spec+i*side_len-1,y_spec+(5-i)*h_len-1,x_spec+side_len/2+i*side_len-1,y_spec+(4-i)*h_len-1,x_spec+(i+1)*side_len-1,y_spec+(5-i)*h_len-1);  
     }
     return micros()- time_start;   
}

// Draw some lines in a pattern
unsigned long show_grid_lines(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    int16_t wid = mylcd.Get_Display_Width();
   float k;
   if(wid == 320)
   {
      k = 1.44; 
    }
    else
    {
     k = 1.6;  
    }
    mylcd.Set_Draw_color(255,0,0);
    for (i=16; i<mylcd.Get_Display_Height()-17; i+=5)
    {
       mylcd.Draw_Line(1, i, (i*k)-10, mylcd.Get_Display_Height()-17);
     }
     mylcd.Set_Draw_color(255,0,0);
     for (i=mylcd.Get_Display_Height()-17; i>16; i-=5)
    {
      mylcd.Draw_Line(mylcd.Get_Display_Width()-2, i, (i*k)-11, 16);
    }
    mylcd.Set_Draw_color(0,255,255);
    for (i=mylcd.Get_Display_Height()-16; i>16; i-=5)
    {
        mylcd.Draw_Line(1, i, (mylcd.Get_Display_Height()-17)*k+10-(i*k), 16);
    }
    mylcd.Set_Draw_color(0,255,255);
    for (int i=15; i<mylcd.Get_Display_Height()-17; i+=5)
    {
        mylcd.Draw_Line(mylcd.Get_Display_Width()-2, i, (mylcd.Get_Display_Height()-17)*k+10-(i*k), mylcd.Get_Display_Height()-17);
    }
    return micros()- time_start;   
}

// Draw some random pixels
unsigned long show_random_pixels(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 10000;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Pixel(2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34));
    }
    return micros()- time_start; 
}

// Draw some random lines
unsigned long show_random_lines(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 300;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Line(2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34));
    }
    return micros()- time_start; 
}

// Draw some random rectangles
unsigned long show_random_rectangles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Rectangle(2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34));
    }
    return micros()- time_start; 
}

// Draw some random round rectangles
unsigned long show_random_round_rectangles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Round_Rectangle(2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),5);
    }
    return micros()- time_start; 
}

// Draw some random circles
unsigned long show_random_circles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Circle(41+random(mylcd.Get_Display_Width()-82), 56+random(mylcd.Get_Display_Height()-112), random(40));
    }
    return micros()- time_start; 
}

// Draw some random triangles
unsigned long show_random_triangles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       mylcd.Set_Draw_color(random(255),random(255),random(255));
       mylcd.Draw_Triangle(2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34),2+random(mylcd.Get_Display_Width()-4),17+random(mylcd.Get_Display_Height()-34));
    }
    return micros()- time_start; 
}

// Draw some random bit maps
unsigned long show_random_bit_map(void)
{
    uint16_t buf[48],i;
    unsigned long time_start = micros();
    int16_t len = (mylcd.Get_Display_Height()*3/4)/6;
    for(i = 0;i< 48; i++)
    {
       mylcd.Set_Draw_color(random(255), random(255), random(255));
       buf[i] = mylcd.Get_Draw_color();
    }
    for(i = 1;i<=6;i++)
    {
        mylcd.Draw_Bit_Map(mylcd.Get_Display_Width()/2-1-((len/2)*4/3)*i, mylcd.Get_Display_Height()/2-1-(len/2)*i, 8, 6, buf, i*(len/6));
        delay(100);
    }
    return micros()- time_start; 
}

//Clear the screen
void clear_screen(void)
{
   delay(2000);  
   mylcd.Set_Draw_color(0, 0, 0);
   mylcd.Fill_Rectangle(1, 16, mylcd.Get_Display_Width()-2, mylcd.Get_Display_Height()-17);
}

unsigned long (*show_function[])(void) = 
 {
                                          show_text,
                                          show_triangle_function,
                                          show_sinewave,
                                          show_fill_rectangle,
                                          show_fill_round_rectangle,
                                          show_fill_circle,
                                          show_fill_triangle,
                                          show_grid_lines,
                                          show_random_pixels,
                                          show_random_lines,
                                          show_random_rectangles,
                                          show_random_round_rectangles,
                                          show_random_circles,
                                          show_random_triangles,
                                          show_random_bit_map,
                                          };
uint8_t *show_str[]=
 {
                       "show text                    :", 
                       "show triangle function       :",
                       "show sinewave                :",
                       "show fill rectangle          :",
                       "show fill round rectangle    :",
                       "show fill circle             :",
                       "show fill triangle           :",
                       "show grid lines              :",
                       "show random pixels           :",
                       "show random lines            :",
                       "show random rectangles       :",
                       "show random round rectangles :",
                       "show random circles          :",
                       "show random triangles        :",
                       "show random bit_map          :"
                     };

//display the running time of programs 
unsigned long show_total_time(void)
{
     uint16_t i;
     unsigned long buf[15];
     unsigned long time_start = micros();
     for(i = 0;i< 15;i++)
     {
        buf[i] = show_function[i](); 
        clear_screen();  
     }
     for(i = 0;i<15; i++)
     {
         mylcd.Set_Text_colour(255, 165, 0);   
         mylcd.Set_Text_Size(1);
         mylcd.Set_Text_Mode(1);
         mylcd.Print_String(show_str[i], (mylcd.Get_Display_Width()-260)/2-1, (mylcd.Get_Display_Height()-150)/2+i*10-1);
         mylcd.Set_Text_colour(0, 255, 0); 
         mylcd.Print_Number_Int(buf[i], (mylcd.Get_Display_Width()-260)/2-1+200, (mylcd.Get_Display_Height()-150)/2+i*10-1, 0, ' ', 10);
     }
     delay(5000);
     return micros()- time_start; 
}

//display ending and total running time
void show_end(unsigned long run_time)
{
    mylcd.Fill_Screen(0, 255, 255);
    mylcd.Set_Draw_color(255, 0, 0);
    mylcd.Fill_Round_Rectangle(mylcd.Get_Display_Width()/2-1-120+1, mylcd.Get_Display_Height()/2-1-60+1, mylcd.Get_Display_Width()/2-1+120-1, mylcd.Get_Display_Height()/2-1+60-1,5);
    mylcd.Set_Text_colour(0, 255, 255);   
    mylcd.Set_Text_Size(1);
    mylcd.Set_Text_Mode(1);
    mylcd.Print_String("Running over!", CENTER, mylcd.Get_Display_Height()/2-1-40);
    mylcd.Print_String("That's ok!", CENTER, mylcd.Get_Display_Height()/2-1-30);
    mylcd.Print_String("After a few seconds,", CENTER, mylcd.Get_Display_Height()/2-1-20);
    mylcd.Print_String("it will restart.", CENTER, mylcd.Get_Display_Height()/2-1-10);
    mylcd.Print_String("Please wait ...", CENTER, mylcd.Get_Display_Height()/2-1);
    mylcd.Set_Text_colour(255, 255, 0); 
    mylcd.Print_String("Total runtime(us):  ", mylcd.Get_Display_Width()/2-1-90, mylcd.Get_Display_Height()/2-1+40);
    mylcd.Set_Text_colour(0, 255, 0);
    mylcd.Print_Number_Int(run_time, mylcd.Get_Display_Width()/2-1+30, mylcd.Get_Display_Height()/2-1+40, 0, ' ', 10);  
    delay(10000);   
}

void setup() 
{
  mylcd.Init_LCD();
  mylcd.Fill_Screen(0x0);  
  mylcd.Set_Rotation(1);  
}

void loop() 
{
    unsigned long total_time;
    mylcd.Fill_Screen(0x0); 
    total_time = show_total_time();
    show_end(total_time);    
}
