#include"Menu.hpp"
#include<iostream>
#include <cstring>
using namespace std;
char lines[]="Line";
char circles[10]="Circle";
char curves[10]="Pencil";
char erase[10]="Eraser";
char poly[10]="Polygons";
char shapes[10]="Shapes";
char etri[10]="eTriangle";
char rtri[10]="rTriangle";
char square[10]="Square";
char clear[10]="Clear";
char undo[5]="Undo";
char text[6]="Text";
char select[10]="Select";
char brush[10]="Brushes";
int highlightmode=0;
unsigned int i;
int color_flag=0;
extern int menu;
extern float color_pre[3];

void drawPoly(GLenum Mode,int y1,int y2,int num,bool outline=false)
{
     if(Mode==GL_SELECT)
     {    
          glLoadName(num);
          highlightmode=1;
     }
     if(outline)
     {
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
     }
     else{
          glColor3f(0.55,.55,.55);
     glBegin(GL_POLYGON);
}

     
     glVertex2f(0,y1);
     glVertex2f(100,y1);//lines
     glVertex2f(100,y2);
     glVertex2f(0,y2);
     glEnd();
     
     
}

void draw_brushes(GLenum Mode)
{
     if(Mode==GL_SELECT){glLoadName(5001);}
     //glPointSize(20);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-115+5,50);
     glVertex2f((width/2)-135+5,50);
     glVertex2f((width/2)-135+5,70);
     glVertex2f((width/2)-115+5,70);
     glEnd();


     if(Mode==GL_SELECT){glLoadName(5002);}
     //glPointSize(10);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-82+10+5,50);
     glVertex2f((width/2)-100+10+5,50);
     glVertex2f((width/2)-100+10+5,68);
     glVertex2f((width/2)-82+10+5,68);
     glEnd();


     if(Mode==GL_SELECT){glLoadName(5003);}
     //glPointSize(8);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-61+10+20+5,50);
     glVertex2f((width/2)-77+10+20+5,50);
     glVertex2f((width/2)-77+10+20+5,65);
     glVertex2f((width/2)-61+10+20+5,65);
     glEnd();



     if(Mode==GL_SELECT){glLoadName(5004);}
     //glPointSize(5);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-120+3,15);
     glVertex2f((width/2)-130,15);
     glVertex2f((width/2)-130,30);
     glVertex2f((width/2)-120+3,30);
     glEnd();



     /*if(Mode==GL_SELECT){glLoadName(5005);}
     //glPointSize(14);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-120+50+3,15);
     glVertex2f((width/2)-130+50-5,15);
     glVertex2f((width/2)-130+50-5,28);
     glVertex2f((width/2)-120+50+3,28);
     glEnd();
*/


     if(Mode==GL_SELECT){glLoadName(5005);}
     //glPointSize(3);
     glColor3f(0,0,0);
     glBegin(GL_POLYGON);
     glVertex2f((width/2)-120+50+40,15);
     glVertex2f((width/2)-130+50+40,15);
     glVertex2f((width/2)-130+50+40,25);
     glVertex2f((width/2)-120+50+40,25);
     glEnd();


/*
     if(Mode==GL_SELECT){"enters1";glLoadName(5002);}
     glPointSize(18);
     glColor3f(0,0,0);
     glBegin(GL_POINTS);
     glVertex2f((width/2)-75,60);
     glEnd();*/


  /*   if(Mode==GL_SELECT){glLoadName(5003);}
     glPointSize(16);
     glColor3f(0,0,0);
     glBegin(GL_POINTS);
     glVertex2f((width/2)-35,60);
     glEnd();
*/
/*
     if(Mode==GL_SELECT){glLoadName(5004);}
     glPointSize(14);
     glColor3f(0,0,0);
     glBegin(GL_POINTS);
     glVertex2f((width/2)-115,20);
     glEnd();*/


/*
     if(Mode==GL_SELECT){glLoadName(5005);}
     glPointSize(12);
     glColor3f(0,0,0);
     glBegin(GL_POINTS);
     glVertex2f((width/2)-75,20);
     glEnd();*/



     /*if(Mode==GL_SELECT){glLoadName(5006);}
     glPointSize(10);
     glColor3f(0,0,0);
     glBegin(GL_POINTS);
     glVertex2f((width/2)-35,20);
     glEnd();
*/
     glRasterPos2i((width/2)-110,85);
     for(i=0;i<strlen(brush);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,brush[i]);

}

void drawshaes_menu(GLenum Mode)
{
     int r=10;
     float theta=0;
     float x=0,y=0;
     if(Mode==GL_SELECT){ glLoadName(2001);}//N=4
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(110,60-10);
               glVertex2f(130,60-10);
               glVertex2f(130,80-10);
               glVertex2f(110,80-10);
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(110,60-10);
               glVertex2f(130,60-10);
               glVertex2f(130,80-10);
               glVertex2f(110,80-10);
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(2002);}//n=3
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(150,60-10);
               glVertex2f(170,60-10);
               glVertex2f(160,80-10);

          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(150,60-10);
               glVertex2f(170,60-10);
               glVertex2f(160,80-10);
          glEnd();

      if(Mode==GL_SELECT){ glLoadName(2003);}//n=6
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(190-5,70-10);
               glVertex2f(200-5,60-10);
               glVertex2f(220-5,60-10);
               glVertex2f(230-5,70-10);
               glVertex2f(220-5,80-10);
               glVertex2f(200-5,80-10);

          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(190-5,70-10);
               glVertex2f(200-5,60-10);
               glVertex2f(220-5,60-10);
               glVertex2f(230-5,70-10);
               glVertex2f(220-5,80-10);
               glVertex2f(200-5,80-10);
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(2004);}//n=5
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(140+8,20-10);
               glVertex2f(160+8,20-10);
               glVertex2f(160+8,30-10);
               glVertex2f(150+8,40-10);
               glVertex2f(140+8,30-10);
          
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(140+8,20-10);
               glVertex2f(160+8,20-10);
               glVertex2f(160+8,30-10);
               glVertex2f(150+8,40-10);
               glVertex2f(140+8,30-10);
          glEnd();

     //2nd row
      if(Mode==GL_SELECT){ glLoadName(074);}//n= border cirlce
          glColor3f(1,1,1);
          r=5;
          glBegin(GL_POLYGON);
          
          for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+100;
          y=r*sin((theta*3.142)/180)+100;
          glVertex2f(x,y);
         }
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
         for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+100;
          y=r*sin((theta*3.142)/180)+100;
          glVertex2f(x,y);
         }
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(2005);}//n= cirlce_poly
          glColor3f(1,1,1);
          r=10;
          glBegin(GL_POLYGON);
          
          for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+120;
          y=r*sin((theta*3.142)/180)+20;
          glVertex2f(x,y);
         }
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_STRIP);
          
         for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+120;
          y=r*sin((theta*3.142)/180)+20;
          glVertex2f(x,y);
         }
          glEnd();
     
     glRasterPos2i(250,85);
     for(i=0;i<strlen(shapes);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,shapes[i]);
   
     glRasterPos2i(145,85);
     for(i=0;i<strlen(poly);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,poly[i]);

     //shapes series:3001

     if(Mode==GL_SELECT){ glLoadName(3001);}//N=4
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(240,60-10);
               glVertex2f(260,60-10);
               glVertex2f(260,80-10);
               glVertex2f(240,80-10);
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(240,60-10);
               glVertex2f(260,60-10);
               glVertex2f(260,80-10);
               glVertex2f(240,80-10);
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(3002);}//n=3
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(270+10,60-10);
               glVertex2f(290+10,60-10);
               glVertex2f(280+10,80-10);

          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(270+10,60-10);
               glVertex2f(290+10,60-10);
               glVertex2f(280+10,80-10);
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(3003);}//n=6
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(310,70-10);
               glVertex2f(320,60-10);
               glVertex2f(340,60-10);
               glVertex2f(350,70-10);
               glVertex2f(340,80-10);
               glVertex2f(320,80-10);

          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(310,70-10);
               glVertex2f(320,60-10);
               glVertex2f(340,60-10);
               glVertex2f(350,70-10);
               glVertex2f(340,80-10);
               glVertex2f(320,80-10);
          glEnd();


     if(Mode==GL_SELECT){ glLoadName(3004);}//n= cirlce_shapes
          glColor3f(1,1,1);
          r=10;
          glBegin(GL_POLYGON);
          
          for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+120;
          y=r*sin((theta*3.142)/180)+20;
          glVertex2f(x,y);
         }
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
         for(theta=0;theta<=360;theta=theta+5)
         {
          x=r*cos((theta*3.142)/180)+250;
          y=r*sin((theta*3.142)/180)+20;
          glVertex2f(x,y);
         }
          glEnd();

     if(Mode==GL_SELECT){ glLoadName(3005);}//n=5
          glColor3f(1,1,1);
          glBegin(GL_POLYGON);
          
               glVertex2f(250+10+2+8+8,20-10);
               glVertex2f(270+10+2+8+8,20-10);
               glVertex2f(270+10+2+8+8,30-10);
               glVertex2f(260+10+2+8+8,40-10);
               glVertex2f(250+10+2+8+8,30-10);
          
          glEnd();
          glColor3f(0,0,0);
          glBegin(GL_LINE_LOOP);
          
               glVertex2f(250+10+2+8+8,20-10);
               glVertex2f(270+10+2+8+8,20-10);
               glVertex2f(270+10+2+8+8,30-10);
               glVertex2f(260+10+2+8+8,40-10);
               glVertex2f(250+10+2+8+8,30-10);
          glEnd();
}

void color_selected()
{
     switch(menu)
     {
          case 1007:glColor3f(0,0,0);break;
          case 1008:glColor3f(1,0.8,1);break;
          case 1009:glColor3f(0,0,1);break;
          case 1010:glColor3f(0,1,0);break;
          case 1011:glColor3f(1,0,0);break;
          case 1012:glColor3f(1,1,0);break;
          case 1013:glColor3f(1,0,1);break;
          case 1014:glColor3f(0,1,1);break;
          case 1015:glColor3f(0.25,0,0.25);break;
          case 1016:glColor3f(0,0.25,0);break;
          case 1017:glColor3f(0,0,0.25);break;
          case 1018:glColor3f(0.25,0,0);break;
     }
          glBegin(GL_POLYGON);
          glVertex2f((width/2+260)-2,10-3);
          glVertex2f((width/2+300)-2,10-3);
          glVertex2f((width/2+300)-2,70-3);
          glVertex2f((width/2+260)-2,70-3);
          glEnd();
}


void drawPoly_Hor(GLenum Mode,int y1,int y2,int x1,int x2,int color_flag,int num,bool outline=false)
{

     if(Mode==GL_SELECT)
     {    
          glLoadName(num);
          highlightmode=1;
     }
     if(outline)
     {
         glColor3f(0,0,0);
         glBegin(GL_LINE_LOOP);
     }
     else{
     switch(color_flag)
     {
          case 1:glColor3f(0,0,0);break;
          case 2:glColor3f(1,0.8,1);break;
          case 3:glColor3f(0,0,1);break;
          case 4:glColor3f(0,1,0);break;
          case 5:glColor3f(1,0,0);break;
          case 6:glColor3f(1,1,0);break;
          case 7:glColor3f(1,0,1);break;
          case 8:glColor3f(0,1,1);break;
          case 9:glColor3f(0.25,0,0.25);break;
          case 10:glColor3f(0,0.25,0);break;
          case 11:glColor3f(0,0,0.25);break;
          case 12:glColor3f(0.25,0,0);break;
     }
     glBegin(GL_POLYGON);
}
     glVertex2f(x1,y1);
     glVertex2f(x2,y1);//lines
     glVertex2f(x2,y2);
     glVertex2f(x1,y2);
     glEnd();

    

         //selected color display
     color_selected();
}

void drawMenu(GLenum Mode)
{
	
	glColor3f(0,0,0);
     glLineWidth(2);
     glBegin(GL_LINES);
     glVertex2f(1,0);
     glVertex2f(100,0);

     glVertex2f(100,0);
     glVertex2f(100,height-1);

     glVertex2f(100,height-1);
     glVertex2f(1,height-1);

     glVertex2f(1,height-1);
     glVertex2f(1,0);

     glVertex2f(100,100);
     glVertex2f(width,100);

     glVertex2f(width-(width/2),0);
     glVertex2f(width-(width/2),100);

     glVertex2f((width/2+320),0);
     glVertex2f((width/2+320),100);

     glVertex2f(100,75);
     glVertex2f((width/2),75);

     
     glVertex2f(230,0);//shapes and polygons
     glVertex2f(230,100);


     glVertex2f((width/2)-140,0);//brushes
     glVertex2f((width/2)-140,100);
    


     
     glEnd();

  
     //selecting
     //tool menu
     //vertical tool box
     drawPoly(Mode,height,height-50,1001);
     drawPoly(Mode,height-50,height-100,1002);
     drawPoly(Mode,height-100,height-150,1003);
     drawPoly(Mode,height-150,height-200,1004);
     drawPoly(Mode,height-200,height-250,1005);
     drawPoly(Mode,height-250,height-300,1006);
     drawPoly(Mode,height-300,height-350,1019);//text

     //horizontal tool box

     //color boxes:1st row
    
     drawPoly_Hor(Mode,10,30,(width/2+20),(width/2+40),1,1007);
     drawPoly_Hor(Mode,10,30,(width/2+60),(width/2+80),2,1008);
     drawPoly_Hor(Mode,10,30,(width/2+100),(width/2+120),3,1009);
     drawPoly_Hor(Mode,10,30,(width/2+140),(width/2+160),4,1010);
     drawPoly_Hor(Mode,10,30,(width/2+180),(width/2+200),5,1011);
     drawPoly_Hor(Mode,10,30,(width/2+220),(width/2+240),6,1012);

     //color boxes:2nd row
     
     drawPoly_Hor(Mode,50,70,(width/2+20),(width/2+40),7,1013);
     drawPoly_Hor(Mode,50,70,(width/2+60),(width/2+80),8,1014);
     drawPoly_Hor(Mode,50,70,(width/2+100),(width/2+120),9,1015);
     drawPoly_Hor(Mode,50,70,(width/2+140),(width/2+160),10,1016);
     drawPoly_Hor(Mode,50,70,(width/2+180),(width/2+200),11,1017);
     drawPoly_Hor(Mode,50,70,(width/2+220),(width/2+240),12,1018);


     



     //rendering
     //tool menu
     drawPoly(GL_RENDER,height,height-50,1001,true);
     drawPoly(GL_RENDER,height-50,height-100,1002,true);
     drawPoly(GL_RENDER,height-100,height-150,1003,true);
     drawPoly(GL_RENDER,height-150,height-200,1004,true);
     drawPoly(GL_RENDER,height-200,height-250,1005,true);
     drawPoly(GL_RENDER,height-250,height-300,1006,true);
     drawPoly(GL_RENDER,height-300,height-350,1019,true);
     
  
     //horizontal tool box

     //color boxes:1st row
 
     drawPoly_Hor(GL_RENDER,10,30,(width/2+20),(width/2+40),1,1007,true);
     drawPoly_Hor(GL_RENDER,10,30,(width/2+60),(width/2+80),2,1008,true);
     drawPoly_Hor(GL_RENDER,10,30,(width/2+100),(width/2+120),3,1009,true);
     drawPoly_Hor(GL_RENDER,10,30,(width/2+140),(width/2+160),4,1010,true);
     drawPoly_Hor(GL_RENDER,10,30,(width/2+180),(width/2+200),5,1011,true);
     drawPoly_Hor(GL_RENDER,10,30,(width/2+220),(width/2+240),6,1012,true);



      //color boxes:2nd row

     drawPoly_Hor(GL_RENDER,50,70,(width/2+20),(width/2+40),7,1013,true);
     drawPoly_Hor(GL_RENDER,50,70,(width/2+60),(width/2+80),8,1014,true);
     drawPoly_Hor(GL_RENDER,50,70,(width/2+100),(width/2+120),9,1015,true);
     drawPoly_Hor(GL_RENDER,50,70,(width/2+140),(width/2+160),10,1016,true);
     drawPoly_Hor(GL_RENDER,50,70,(width/2+180),(width/2+200),11,1017,true);
     drawPoly_Hor(GL_RENDER,50,70,(width/2+220),(width/2+240),12,1018,true);

      

     glColor3f(0,0,0);
     glRasterPos2i(20,height-30);
     for(i=0;i<strlen(lines);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,lines[i]);

	glRasterPos2i(20,height-80);
     for(i=0;i<strlen(curves);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,curves[i]);

	glRasterPos2i(20,height-130);
     for(i=0;i<strlen(circles);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,circles[i]);

	glRasterPos2i(20,height-180);
     for(i=0;i<strlen(erase);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,erase[i]);
     
     glRasterPos2i(20,height-230);
     for(i=0;i<strlen(clear);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,clear[i]);

	 glRasterPos2i(20,height-280);
     for(i=0;i<strlen(undo);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,undo[i]);

     glRasterPos2i(20,height-330);
     for(i=0;i<strlen(text);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,text[i]);

	/*glRasterPos2i(145,85);
     for(i=0;i<strlen(poly);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,poly[i]);*/

     /*glRasterPos2i(250,85);
     for(i=0;i<strlen(shapes);i++)
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15,shapes[i]);*/


	
     /*
     glRasterPos2i(20,height-420);
     for(i=0;i<strlen(text);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,text[i]);

	glRasterPos2i(20,height-480);
     for(i=0;i<strlen(select);i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,select[i]);*/
}