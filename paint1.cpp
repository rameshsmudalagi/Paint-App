#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <SOIL.h>
#include <GL/glut.h>
#include "Menu.cpp"
#define MAX_ITEMS 10000
using namespace std; 

enum Type {LINES,CURVES,SQUARE,CIRCLE,POLYGON,TEXT,ERASER,COLOR,CLEAR,UNDO,CIRCLE_POLY,SHAPES,SAVE,BRUSH};

int itemCount=-1;
int text_itemCount=-1;
int width,height;
Type menu_flag=LINES;
float r=0,theta=0,x,y;
int menu;
int j;
int N=1;
int circle_flag=0;
float color_pre[3]={0.0,0.0,0.0};
float p_size=0.0;
int screen_flag=0;
char image_name[50];
GLint WindowID1, WindowID2;
char *image;

char fname[50];
int saving;
FILE *fptr;
char str[100];


struct Point
{
	double x,y;
	void setpoint(int x1,int y1) //function to store the x and y values of mouse
	{
		x = x1;
		y = y1;
	}
	void display_point() //function used to display the line
	{
		glVertex2f(x,y);
	}
};

 
struct ItemData{
  
   GLfloat colors[3];
   GLfloat point_size;
   Type type;
   int num_points;
   Point *points;
   int sides;
};
ItemData items[MAX_ITEMS];


struct  TextData{

   GLfloat text_colors[3];
   int char_count;
   int text_points[2];
   char text[40];
};
TextData texts[MAX_ITEMS];



// function used to select the item from the menu bar
// used Selection Method for picking
int check(int x,int y)
{
	void drawItems(GLenum);
	unsigned int sb[100];
	int hits,vp[4];
	glGetIntegerv(GL_VIEWPORT,vp);
	glSelectBuffer(100,sb);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((double)x,(double)(y),1,1,vp);
	gluOrtho2D(0 , width , 0, height);
	drawMenu(GL_SELECT);
	drawItems(GL_SELECT);
	drawshaes_menu(GL_SELECT);
	draw_brushes(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	cout<<"hit ="<<hits<<endl;
	if(hits>0)
		return *(sb+3);
	return -1;
}

// my initialisation function
void myinit(){

}

// window reshape function
void reshape(GLsizei new_width, GLsizei new_height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	width=new_width;
	height=new_height;
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 //  myinit();
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   gluOrtho2D(0 , width , 0, height);
    glMatrixMode(GL_MODELVIEW);

}

// function used to store the character in the texts[] structure
void text_key(unsigned char key,int x,int y)
{
	if(menu_flag==TEXT)
    {
    	texts[text_itemCount].text[texts[text_itemCount].char_count++]=key;
    	texts[text_itemCount].text[texts[text_itemCount].char_count]='\0';
    }
    
    if(screen_flag==0 && key)
    {
    	screen_flag=1;
    	glutPostRedisplay();
    }
    
				
    if(key==27)
    	exit(0);
    glutPostRedisplay();
}


// function used to draw the text/string using Raster Method
void draw_text()
{
		for(i=0;i<=text_itemCount;i++)
		{
			glColor3fv(texts[i].text_colors);
			glRasterPos2i(texts[i].text_points[0],texts[i].text_points[1]);
			for(j=0;j<texts[i].char_count;j++)
			{
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15,texts[i].text[j]);
			}
		}
}


//function used to draw the items from the frame buffer to screen
void drawItems(GLenum Mode) 
{	

	float n1=0;
	theta=n1;
	for (int i = 0; i < itemCount; i++)
   {
   	   glColor3fv(items[i].colors);
   	   glLineWidth(items[i].point_size);
	   if (Mode == GL_SELECT)
		   glLoadName(i);
	
	switch(items[i].type)
   	{
   		case LINES :  	glBegin(GL_LINES); break;
   		case CURVES :	glBegin(GL_LINE_STRIP);break; 
   		case SQUARE:  glBegin(GL_LINE_LOOP);break;
   		case CIRCLE :  glBegin(GL_LINE_LOOP);break;
   		case CIRCLE_POLY :  glBegin(GL_POLYGON);break;

   		case ERASER :	glColor3f(1,1,1);glBegin(GL_LINE_STRIP);break;

   		case POLYGON : glBegin(GL_POLYGON);break;
   		case SHAPES : glBegin(GL_LINE_LOOP);break;
   	}
    
    //shapes
   	if(items[i].type==SHAPES )
   	{
   		n1=360.0/items[i].sides;
   		r=sqrt(pow((items[i].points[1].x-items[i].points[0].x),2)+pow((items[i].points[1].y-items[i].points[0].y),2));
	    r=r/2;
	     int midx=(items[i].points[1].x+items[i].points[0].x)/2;
	    int midy=(items[i].points[1].y+items[i].points[0].y)/2;
	    
	    for(j=1;j<=items[i].sides;j++)
	    {
	    	x=r*cos((theta*3.142)/180)+midx;
         	y=r*sin((theta*3.142)/180)+midy;
         	glVertex2f(x,y);
            theta=theta+n1;
        }

   	}
   	//square
   	else if(items[i].type==SQUARE)
   	{
   		theta=135;
   		n1=360.0/4;
   		r=sqrt(pow((items[i].points[1].x-items[i].points[0].x),2)+pow((items[i].points[1].y-items[i].points[0].y),2));
	    r=r/2;
	    int midx=(items[i].points[1].x+items[i].points[0].x)/2;
	    int midy=(items[i].points[1].y+items[i].points[0].y)/2;
	    for(j=1;j<=4;j++)
	    {
	    	x=r*cos((theta*3.142)/180)+midx;
         	y=r*sin((theta*3.142)/180)+midy;
         	glVertex2f(x,y);
            theta=theta+n1;  
        }


   	}
    
    //polygon
   	else if(items[i].type==POLYGON )
   	{
   		n1=360.0/items[i].sides;
   		r=sqrt(pow((items[i].points[1].x-items[i].points[0].x),2)+pow((items[i].points[1].y-items[i].points[0].y),2));
	    r=r/2;
	    int midx=(items[i].points[1].x+items[i].points[0].x)/2;
	    int midy=(items[i].points[1].y+items[i].points[0].y)/2;
	    
	    for(j=1;j<=items[i].sides;j++)
	    {
	    	x=r*cos((theta*3.142)/180)+midx;
         	y=r*sin((theta*3.142)/180)+midy;
         	glVertex2f(x,y);
            theta=theta+n1;  
        }

   	}

   	//circle polygon
   	else if(items[i].type==CIRCLE_POLY)
    {
    	r=sqrt(pow((items[i].points[1].x-items[i].points[0].x),2)+pow((items[i].points[1].y-items[i].points[0].y),2));
	    r=r/2;
	    int midx=(items[i].points[1].x+items[i].points[0].x)/2;
	    int midy=(items[i].points[1].y+items[i].points[0].y)/2;
        
        for(theta=0;theta<=360;theta=theta+5)
        {
         	x=r*cos((theta*3.142)/180)+midx;
         	y=r*sin((theta*3.142)/180)+midy;
         	glVertex2f(x,y);
        }
    }
   
 	//circle
  	else if(items[i].type==CIRCLE)
    {
    	r=sqrt(pow((items[i].points[1].x-items[i].points[0].x),2)+pow((items[i].points[1].y-items[i].points[0].y),2));
	    r=r/2;
	    int midx=(items[i].points[1].x+items[i].points[0].x)/2;
	    int midy=(items[i].points[1].y+items[i].points[0].y)/2;
        
        for(theta=0;theta<=360;theta=theta+5)
        {
         	x=r*cos((theta*3.142)/180)+midx;
         	y=r*sin((theta*3.142)/180)+midy;
         	glVertex2f(x,y);
        }
    }
    else
    {   // for curve or for line
    	for(int j=0;j<items[i].num_points;j++)
   	    {
   			items[i].points[j].display_point();
   		}
    }
   	glEnd();
  }
}

void color_pan(float col[])
{
	glColor3fv(col);
	glBegin(GL_POLYGON);
	glVertex2f((width/2+260)-2,10-3);
          glVertex2f((width/2+300)-2,10-3);
          glVertex2f((width/2+300)-2,70-3);
          glVertex2f((width/2+260)-2,70-3);
          glVertex2f((width/2+260)-2,70-3);
          glEnd();
	// cout<<"hello "<<color_flag<<endl;
 //    switch(color_flag)
 //     {
 //          case 1007:glColor3f(0,0,0);
 //                    glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
          // glVertex2f((width/2+260)-2,70-3);
          // glEnd();
 //                    break;
 //          case 1008:glColor3f(1,0.8,1);
 //          			  glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //          			break;
 //          case 1009:glColor3f(0,0,1);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //          break;
 //          case 1010:glColor3f(0,1,0);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                 break;
 //          case 1011:glColor3f(1,0,0);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //          break;
 //          case 1012:glColor3f(1,1,0);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                break;
 //          case 1013:glColor3f(1,0,1);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f(250,250);
 //          glVertex2f(270,250);
 //          glVertex2f(270,270);
 //          glVertex2f(250,270);
 //          glEnd();
 //                 break;
 //          case 1014:glColor3f(0,1,1);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                 break;
 //          case 1015:glColor3f(0.25,0,0.25);
 //                 glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                 break;
 //          case 1016:glColor3f(0,0.25,0);
 //                  glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                  break;
 //          case 1017:glColor3f(0,0,0.25);
 //                  glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                   break;
 //          case 1018:glColor3f(0.25,0,0);
 //                  glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
 //                 break;

 //          default:
 //                    glColor3f(0,0,0);
 //                    glBegin(GL_POLYGON);
 //          glVertex2f((width/2+260)-2,10-3);
 //          glVertex2f((width/2+300)-2,10-3);
 //          glVertex2f((width/2+300)-2,70-3);
 //          glVertex2f((width/2+260)-2,70-3);
 //          glEnd();
                 
 //     }
 //     glFlush();
}


/* mymouse function is called 
to select the item from the menu and also to select the x and y values of the mouse */
void mymouse(int b,int s,int x,int y)
{
	if(screen_flag==0)
	{
		screen_flag=1;
		glutPostRedisplay();
	}
	y=height-y;
	int menu=0;
	cout<<"x="<<x<<" y="<<y<<endl;
	if((menu = check(x,y))>0)
		{
			cout<<"menu = "<<menu<<endl;
			switch (menu)
			{
				//normal tools
				case 1001:menu_flag = LINES;break;
				case 1002:menu_flag = CURVES;break;
				case 1003:menu_flag = CIRCLE;break;
				case 1004:menu_flag = ERASER;break;
				case 1005:menu_flag = CLEAR;itemCount=0;text_itemCount=-1;glutPostRedisplay();break;
				case 1006:menu_flag = UNDO;break;
				case 1019:menu_flag = TEXT;break;
				case 1020:menu_flag = SAVE;break;
				case 1021:menu_flag = SQUARE;break;

		 		//color selected
		 		case 1007:color_pre[0]=0;color_pre[1]=0;color_pre[2]=0;break;
          		case 1008:color_pre[0]=1;color_pre[1]=0.8;color_pre[2]=1;break;
          		case 1009:color_pre[0]=0;color_pre[1]=0;color_pre[2]=1;break;
          		case 1010:color_pre[0]=0;color_pre[1]=1;color_pre[2]=0;break;
          		case 1011:color_pre[0]=1;color_pre[1]=0;color_pre[2]=0;break;
         		case 1012:color_pre[0]=1;color_pre[1]=1;color_pre[2]=0;break;
          		case 1013:color_pre[0]=1;color_pre[1]=0;color_pre[2]=1;break;
          		case 1014:color_pre[0]=0;color_pre[1]=1;color_pre[2]=1;break;
          		case 1015:color_pre[0]=0.25;color_pre[1]=0;color_pre[2]=0.25;break;
          		case 1016:color_pre[0]=0;color_pre[1]=0.25;color_pre[2]=0;break;
          		case 1017:color_pre[0]=0;color_pre[1]=0;color_pre[2]=0.25;break;
          		case 1018:color_pre[0]=0.25;color_pre[1]=0;color_pre[2]=0;break;


				//polygon selected
				case 2001:menu_flag = POLYGON; N = 4; break;
				case 2002:menu_flag = POLYGON; N = 3; break;
				case 2003:menu_flag = POLYGON; N = 6; break;
				case 2004:menu_flag = POLYGON; N = 5; break;
				case 2005:menu_flag = CIRCLE_POLY;break;

				//shapes selected
				case 3001:menu_flag = SHAPES; N = 4; break;
				case 3002:menu_flag = SHAPES; N = 3; break;
				case 3003:menu_flag = SHAPES; N = 6; break;
				case 3004:menu_flag = CIRCLE;break;
				case 3005:menu_flag = SHAPES; N = 5; break;


				//brush selected
				case 5001:p_size=10;break;
				case 5002:p_size=7;break;
				case 5003:p_size=5;break;
				case 5004:p_size=3;break;
				case 5005:p_size=2;break;

			}
		}
		
	if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN )
	{
		cout<<"x"<<x<<" y="<<y<<endl;
		items[itemCount].colors[0]=color_pre[0];
		items[itemCount].colors[1]=color_pre[1];
		items[itemCount].colors[2]=color_pre[2];

          

		items[itemCount].point_size=p_size;
		
		
		switch(menu_flag)
		{
			case LINES : items[itemCount].type=LINES;
			             items[itemCount].points=new Point[2];
						 items[itemCount].num_points=2;
						 items[itemCount].points[0].setpoint(x,y);
						 items[itemCount].points[1].setpoint(x,y);
						 itemCount++;
						 break;
			
			case CURVES: items[itemCount].type=CURVES;
						 items[itemCount].points=new Point[MAX_ITEMS];
						 items[itemCount].num_points=1;
						 items[itemCount].points[0].x=x;
						 items[itemCount].points[0].y=y;
						 items[itemCount].points[1].x=x;
						 items[itemCount].points[1].y=y;
						 itemCount++;
						 break;

			case SQUARE:items[itemCount].type=SQUARE;
						items[itemCount].points=new Point[MAX_ITEMS];
						items[itemCount].num_points=2;
						items[itemCount].points[0].x=x;
						 items[itemCount].points[0].y=y;
						 items[itemCount].points[1].x=x;
						 items[itemCount].points[1].y=y;
						 itemCount++;
						 break;

			case CIRCLE: items[itemCount].type=CIRCLE;
						items[itemCount].points=new Point[MAX_ITEMS];
						 items[itemCount].num_points=2;
						  items[itemCount].points[0].x=x;
						 items[itemCount].points[0].y=y;
						 items[itemCount].points[1].x=x;
						 items[itemCount].points[1].y=y;
						 itemCount++;
						 break;
			case CIRCLE_POLY: items[itemCount].type=CIRCLE_POLY;
						items[itemCount].points=new Point[MAX_ITEMS];
						 items[itemCount].num_points=2;
						  items[itemCount].points[0].x=x;
						 items[itemCount].points[0].y=y;
						 items[itemCount].points[1].x=x;
						 items[itemCount].points[1].y=y;
						 itemCount++;
						 break;

				case ERASER: 
						 items[itemCount].type=ERASER;
						 items[itemCount].points=new Point[MAX_ITEMS];
						 items[itemCount].num_points=1;
						  items[itemCount].points[0].x=x;
						 items[itemCount].points[0].y=y;
						 items[itemCount].points[1].x=x;
						 items[itemCount].points[1].y=y;
						 itemCount++; 
						 break;

			case UNDO : if(itemCount>0)--itemCount;
						if(texts[text_itemCount].char_count>0)--texts[text_itemCount].char_count;
						else if(text_itemCount>0 && texts[text_itemCount].char_count==0)--text_itemCount;
						break;
			

			case POLYGON :
						items[itemCount].sides = N;
			 			items[itemCount].type=POLYGON;
			            items[itemCount].points=new Point[2];
						items[itemCount].num_points=2;
						items[itemCount].points[0].x=x;
						items[itemCount].points[0].y=y;
						items[itemCount].points[1].x=x;
						items[itemCount].points[1].y=y;
						itemCount++;
						break;


			case SHAPES :
						items[itemCount].sides = N;
			 			items[itemCount].type=SHAPES;
			            items[itemCount].points=new Point[2];
						items[itemCount].num_points=2;
						items[itemCount].points[0].x=x;
						items[itemCount].points[0].y=y;
						items[itemCount].points[1].x=x;
						items[itemCount].points[1].y=y;
						itemCount++;
						break;



			case TEXT:	
						text_itemCount++;  
						texts[text_itemCount].text_points[0]=x;
						texts[text_itemCount].text_points[1]=y;
						texts[text_itemCount].char_count=0;

						texts[text_itemCount].text_colors[0]=color_pre[0];
						texts[text_itemCount].text_colors[1]=color_pre[1];
						texts[text_itemCount].text_colors[2]=color_pre[2];
		
						
						break;

			case SAVE://here SOIL is used to save the contents of the frame buffer as a bmp image
					
					
					int  save_result = SOIL_save_screenshot
   					 (
    					"awesomenessity.bmp",
    					SOIL_SAVE_TYPE_BMP,
    					100+1.7, 100+1.7, width-100, height-100
    				 );

    			  	break;

    
		}
	  
	}


}

//mymotion is called to store the points(x and y) of mouse when dragged
void mymotionfunc(int x,int y)
{
	y=height-y;
	
   		int current = itemCount - 1;
   		if(x > 100 && y > 100 )
   		{
   		switch(menu_flag)
		{
		case LINES :
					items[current].points[1].setpoint(x,y);
					break;

	    case CURVES:items[current].num_points++;
	    			items[current].points[items[current].num_points].setpoint(x,y);break;

	    case SQUARE:items[current].points[1].setpoint(x,y);break;

	    case CIRCLE:items[current].points[1].setpoint(x,y);break;

	    case CIRCLE_POLY:items[current].points[1].setpoint(x,y);break;

	    case ERASER:items[current].num_points++;
	    			items[current].points[items[current].num_points].setpoint(x,y);break;

	    case POLYGON:
	    			items[current].points[1].setpoint(x,y);break;

	    case SHAPES:
	    			items[current].points[1].setpoint(x,y);break;
		}
	}
	glutPostRedisplay();

}

//function used to draw string using stroke method
void drawString(const char *str, int color_flag,double x = 0, double y = 0, double size = 1.0) {
	glPushMatrix();
	
	switch(color_flag)
	{
		case 1:glColor3f(0.8,0.8,0.5);break;
		case 2:glColor3f(0.25,.55,0.25);break;
		case 3:glColor3f(0.55,0.25,0.55);break;
		case 4:glColor3f(0.15,0.25,0.55);break;
	}
	
	glTranslatef(x, y, 0);
	glScalef(size/120 , size/120, 1.0);
	int itemCt = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		

		if (str[i] == '\n')
		{
			itemCt++;
			 glPopMatrix();
			     glPushMatrix();
			glTranslatef(x, y - size, 0);
			glScalef(size / 153.0, size / 153.0, 1.0);
		}
		else {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
		}
	}
	glPopMatrix();
}


//display function 
void disp()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	color_pan(color_pre);
    if(screen_flag!=0)
    {
    	if(itemCount>0)
	    {
	      drawItems(GL_RENDER);
	    }
	    if(text_itemCount >=0)
	    {

		draw_text();
	    }
	    drawMenu(GL_RENDER);
	   drawshaes_menu(GL_RENDER); 
	   draw_brushes(GL_RENDER);
    }
    //starting screen
    if(screen_flag==0)
    {

    	char coll[60]="VISVESVARAYA TECHNOLOGICAL UNIVERSITY";
    	char bgm[20]="BELGAUM - 590014";
    	char cg[30]="Computer Graphics Project";
    	char pg[30]="PAINT APPLICATION";
    	char name[50]="RAMESH SIDARAY MUDALAGI { IRN12CS074 } ";
    	char by[3]="BY";
    	char guide[50]="Under the Guidance of: ";
    	char lecname[80]="Kiran, Sanjay P.K (Lecturers, Dept of CSE, RNSIT)";
    	char app[50]="Press MOUSE to start the ";
    	char app1[20]="APPLICATION";
    	  
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT);
     	
  		drawString(coll, 1,70, 550+30, 35);
  		drawString(bgm, 1,300, 500+30, 35);
  		drawString(cg, 2,250, 470-10, 35);
  		drawString(pg, 2,350, 410-10, 30);
  		drawString(by, 3,460, 350-20, 30);
  		drawString(name, 3,150, 300-20, 30);
  		drawString(guide, 4,300, 250-50, 30);
  		drawString(lecname, 4,100, 200-50, 30);
		
		glColor3f(0,0,1);
  		glBegin(GL_LINES);
  		glVertex2f(0,510);
  		glVertex2f(width,510);
  		glEnd();

  		glRasterPos2i(100,50);
     	for(i=0;i<strlen(app);i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,app[i]);
		
		glColor3f(1,1,1);
  		glRasterPos2i(330,50);
     	for(i=0;i<strlen(app1);i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15,app1[i]);
  	}

	
    glutSwapBuffers();  // Makes the drawing appear on the screen!
}

//function used to change the mouse cursor
void mouse_Cursor(int x,int y)
{
	if(x<100)
	{
		
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	}
	else if(menu_flag==TEXT)
	{
		glutSetCursor(GLUT_CURSOR_TEXT);
	}
	else
		
	glutSetCursor(GLUT_CURSOR_SPRAY);
}

//function used to get the modifiers for the special keys like CTRL,ALT etc
//here CTRL is used to save the image
void special_keys(int key,int x,int y)
{

	int mod_key = glutGetModifiers();
	if (mod_key == GLUT_ACTIVE_CTRL)
    {
        int  save_result = SOIL_save_screenshot
   					 (
    					"awesomenessity.bmp",
    					SOIL_SAVE_TYPE_BMP,
    					100+1.7, 100+1.7, width-100, height-100
    				 );
    }
}

//main function
int main(int argc,char* argv[])
{
	
    image =(char*)malloc(3*1600*900*sizeof(char));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		myinit();

	glutInitWindowSize(1000,650);
	glutInitWindowPosition(20,10);
   glutCreateWindow("paint");
	glutDisplayFunc(disp);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymotionfunc);
	glutPassiveMotionFunc(mouse_Cursor);
	glutKeyboardFunc(text_key);
	glutSpecialFunc(special_keys);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}