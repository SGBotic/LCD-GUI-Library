
//Demo of graphic test and rotate funcitons for text.



#include <LCD_GUI.h> //Core graphics library
#include <LCD_KBV.h> //Hardware-specific library

LCD_KBV mylcd(ILI9341, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//clear screen
void fill_screen_test()
{
  mylcd.Fill_Screen(BLACK);
  mylcd.Fill_Screen(RED);
  mylcd.Fill_Screen(GREEN);
  mylcd.Fill_Screen(BLUE);
  mylcd.Fill_Screen(BLACK);
}

//display some strings
void text_test()
{
  mylcd.Set_Text_Mode(0);

  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Hello World!", 0, 0);

  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Size(2);
  mylcd.Print_Number_Float(1234.56, 2, 0, 8, '.', 0, ' ');

  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(3);
  //mylcd.Print_String("DEADBEEF", 0, 24);
  mylcd.Print_Number_Int(0xDEADBEF, 0, 24, 0, ' ', 16);

  mylcd.Set_Text_colour(GREEN);
  mylcd.Set_Text_Size(5);
  mylcd.Print_String("Hello World!", 0, 56);

  mylcd.Set_Text_Size(2);
  mylcd.Print_String("Hello World!", 0, 96);

  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Hello World!", 0, 112);
  mylcd.Print_String("Hello World!", 0, 120);
  mylcd.Print_String("Hello World!", 0, 128);
  mylcd.Print_String("Hello World!", 0, 136);
  mylcd.Print_String("Hello World!", 0, 144);
  mylcd.Print_String("Hello World!", 0, 152);
  mylcd.Print_String("Hello World!", 0, 160);
}

//draw some oblique lines
void lines_test(void)
{
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(GREEN);
  int i = 0;
  for (i = 0; i < mylcd.Get_Display_Width(); i += 5)
  {
    mylcd.Draw_Line(0, 0, i, mylcd.Get_Display_Height() - 1);
  }
  for (i = mylcd.Get_Display_Height() - 1; i >= 0; i -= 5)
  {
    mylcd.Draw_Line(0, 0, mylcd.Get_Display_Width() - 1, i);
  }

  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(RED);
  for (i = mylcd.Get_Display_Width() - 1; i >= 0; i -= 5)
  {
    mylcd.Draw_Line(mylcd.Get_Display_Width() - 1, 0, i, mylcd.Get_Display_Height() - 1);
  }
  for (i = mylcd.Get_Display_Height() - 1; i >= 0; i -= 5)
  {
    mylcd.Draw_Line(mylcd.Get_Display_Width() - 1, 0, 0, i);
  }

  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(BLUE);
  for (i = 0; i < mylcd.Get_Display_Width(); i += 5)
  {
    mylcd.Draw_Line(0, mylcd.Get_Display_Height() - 1, i, 0);
  }
  for (i = 0; i < mylcd.Get_Display_Height(); i += 5)
  {
    mylcd.Draw_Line(0, mylcd.Get_Display_Height() - 1, mylcd.Get_Display_Width() - 1, i);
  }

  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(YELLOW);
  for (i = mylcd.Get_Display_Width() - 1; i >= 0; i -= 5)
  {
    mylcd.Draw_Line(mylcd.Get_Display_Width() - 1, mylcd.Get_Display_Height() - 1, i, 0);
  }
  for (i = 0; i < mylcd.Get_Display_Height(); i += 5)
  {
    mylcd.Draw_Line(mylcd.Get_Display_Width() - 1, mylcd.Get_Display_Height() - 1, 0, i);
  }
}

//draw some vertical lines and horizontal lines
void h_l_lines_test(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(GREEN);
  for (i = 0; i < mylcd.Get_Display_Height(); i += 5)
  {
    mylcd.Draw_Fast_HLine(0, i, mylcd.Get_Display_Width());
    delay(5);
  }
  mylcd.Set_Draw_color(BLUE);
  for (i = 0; i < mylcd.Get_Display_Width(); i += 5)
  {
    mylcd.Draw_Fast_VLine(i, 0, mylcd.Get_Display_Height());
    delay(5);
  }
}

//draw some rectangles
void rectangle_test(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(GREEN);
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Draw_Rectangle(i, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 + i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 - i);
    delay(5);
  }
}

//draw some filled rectangles
void fill_rectangle_test(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(YELLOW);
  mylcd.Fill_Rectangle(0, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2, mylcd.Get_Display_Width() - 1, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2);
  mylcd.Set_Draw_color(MAGENTA);
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Draw_Rectangle(i, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 + i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 - i);
    delay(5);
  }
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Set_Draw_color(random(255), random(255), random(255));
    mylcd.Fill_Rectangle(i, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 + i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 - i);
    delay(5);
  }
}

//draw some filled circles
void fill_circles_test(void)
{
  int r = 10, i = 0, j = 0;
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Draw_color(MAGENTA);
  for (i = r; i < mylcd.Get_Display_Width(); i += 2 * r)
  {
    for (j = r; j < mylcd.Get_Display_Height(); j += 2 * r)
    {
      mylcd.Fill_Circle(i, j, r);
    }
  }
}

//draw some circles
void circles_test(void)
{
  int r = 10, i = 0, j = 0;
  mylcd.Set_Draw_color(GREEN);
  for (i = 0; i < mylcd.Get_Display_Width() + r; i += 2 * r)
  {
    for (j = 0; j < mylcd.Get_Display_Height() + r; j += 2 * r)
    {
      mylcd.Draw_Circle(i, j, r);
    }
  }
}

//draw some triangles
void triangles_test(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 5)
  {
    mylcd.Set_Draw_color(0, i + 64, i + 64);
    mylcd.Draw_Triangle(mylcd.Get_Display_Width() / 2 - 1, mylcd.Get_Display_Height() / 2 - 1 - i,
                        mylcd.Get_Display_Width() / 2 - 1 - i, mylcd.Get_Display_Height() / 2 - 1 + i,
                        mylcd.Get_Display_Width() / 2 - 1 + i, mylcd.Get_Display_Height() / 2 - 1 + i);
  }
}

//draw some filled triangles
void fill_triangles_test(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  for (i = mylcd.Get_Display_Width() / 2 - 1; i > 0; i -= 5)
  {

    mylcd.Set_Draw_color(0, i + 64, i + 64);
    mylcd.Fill_Triangle(mylcd.Get_Display_Width() / 2 - 1, mylcd.Get_Display_Height() / 2 - 1 - i,
                        mylcd.Get_Display_Width() / 2 - 1 - i, mylcd.Get_Display_Height() / 2 - 1 + i,
                        mylcd.Get_Display_Width() / 2 - 1 + i, mylcd.Get_Display_Height() / 2 - 1 + i);
    mylcd.Set_Draw_color(i, 0, i);
    mylcd.Draw_Triangle(mylcd.Get_Display_Width() / 2 - 1, mylcd.Get_Display_Height() / 2 - 1 - i,
                        mylcd.Get_Display_Width() / 2 - 1 - i, mylcd.Get_Display_Height() / 2 - 1 + i,
                        mylcd.Get_Display_Width() / 2 - 1 + i, mylcd.Get_Display_Height() / 2 - 1 + i);
  }
}

//draw some round rectangles
void round_rectangle(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Set_Draw_color(255 - i, 0, 160 - i);
    mylcd.Draw_Round_Rectangle(i, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 + i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 - i, 8);
    delay(5);
  }
}

//draw some filled round rectangles
void fill_round_rectangle(void)
{
  int i = 0;
  mylcd.Fill_Screen(BLACK);
  for (i = 0; i < mylcd.Get_Display_Width() / 2; i += 4)
  {
    mylcd.Set_Draw_color(255 - i, 160 - i, 0);
    mylcd.Fill_Round_Rectangle(i, (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 + i, mylcd.Get_Display_Width() - 1 - i, mylcd.Get_Display_Height() - (mylcd.Get_Display_Height() - mylcd.Get_Display_Width()) / 2 - i, 8);
    delay(5);
  }
}

void setup()
{
  mylcd.Init_LCD();
  fill_screen_test();
  delay(500);
  text_test();
  delay(500);
  lines_test();
  delay(500);
  h_l_lines_test();
  delay(500);
  rectangle_test();
  delay(500);
  fill_rectangle_test();
  delay(500);
  fill_circles_test();
  delay(500);
  circles_test();
  delay(500);
  triangles_test();
  delay(500);
  fill_triangles_test();
  delay(500);
  round_rectangle();
  delay(500);
  fill_round_rectangle();
  delay(3000);
}

void loop()
{
  //rotate for four directions
  for (uint8_t rotation = 0; rotation < 4; rotation++)
  {
    mylcd.Set_Rotation(rotation);
    text_test();
    delay(2000);
  }
}
